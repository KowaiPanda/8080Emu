#include <iostream>
#include <windows.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "emulator_shell.h"
#include "io.h"
#include "gui.h"

SYSTEMTIME st;
FILETIME currentTimeSystem;
unsigned long long currentTime, lastGuiUpdate = 0, clockCycle = 0, invadersUpdate = 0, interruptTimer1 = 0, interruptTimer2 = 0;
bool notHalted = true;
float fps = 60.0;
float period = 1.0 / fps;
float scanlines = 256.0;
float freq = 2000000;
float cycleperscanline = (period / scanlines) * freq;

void ISR(State8080* state, int intaddress) {
    PUSH(state, ((state->pc & 0xff00) >> 8), (state->pc & 0xff));
    state->pc = intaddress;
    state->int_enable = false;
}

int HexToByte(char* hex) {
    int result = 0;
    for (int i = 0; i < 4; i++) {
        if ((hex[i] >= 48) && (hex[i] <= 57)) {
            result += (hex[i] - 48) * pow(16, (3 - i));
        }
        else if ((hex[i] >= 65) && (hex[i] <= 70)) {
            result += (hex[i] - 65 + 10) * pow(16, (3 - i));
        }
        else if ((hex[i] >= 97) && (hex[i] <= 102)) {
            result += (hex[i] - 97 + 10) * pow(16, (3 - i));
        }
    }
    return result;
}

int main() {

	State8080* state = Init8080();
	
	ReadFileIntoMemoryAt(state, "rom/invaders.h", 0);
	ReadFileIntoMemoryAt(state, "rom/invaders.g", 0x800);
	ReadFileIntoMemoryAt(state, "rom/invaders.f", 0x1000);
	ReadFileIntoMemoryAt(state, "rom/invaders.e", 0x1800);

    bool runOnce = false;
    bool runFrame = true;
    int totalCycles = 0;

    long long int oneInstructionCycle = 166666;
    unsigned long long timePerFrame = 166666;

    bool haltatInterrupt = true;
    bool midInterruptTriggered = false;
    bool cleared = false;
    uint8_t previous = 0;
    bool runNext = false;

    uint16_t previousCoin = 0;
    uint16_t previousSwitch = 0;

    char PauseOnLine[5];
    int PauseOnLineInt;
    bool breakpointActive = false;

    const int MAXINSTRUCTIONS = 1000;
    int currentInstruction = 0;
    int previousInstructions[MAXINSTRUCTIONS * 4];

    for (int i = 0; i < MAXINSTRUCTIONS * 4; i++) {
        previousInstructions[i] = 0;
    }

    GLFWwindow* window;
    window = InitGUI();

    unsigned int VAO;
    VAO = InitializeVAO();
    unsigned int shaderProgram;
    shaderProgram = InitializeShader();
    unsigned int texture;
    glGenTextures(1, &texture);
	while (!glfwWindowShouldClose(window)) {

        GetSystemTime(&st);
        SystemTimeToFileTime(&st, &currentTimeSystem);
        unsigned long long upper = currentTimeSystem.dwHighDateTime;
        unsigned long long lower = currentTimeSystem.dwLowDateTime;
        currentTime = (upper << 32) | lower;

        if (oneInstructionCycle <= 10000) {
            oneInstructionCycle = 0;
        }

        if (runFrame) {
            if (((currentTime - invadersUpdate) >= timePerFrame) && notHalted) {
                runNext = true;
                invadersUpdate = currentTime;
                totalCycles = cycleperscanline * scanlines;
            }
        }
        else {
            if (((currentTime - invadersUpdate) >= oneInstructionCycle) && notHalted) {
                runNext = true;
                invadersUpdate = currentTime;
                totalCycles = state->cycles + 1;
            }
        }

        if (runNext) {
            while ((int(state->cycles) < totalCycles) && notHalted) {
                runNext = false;

                PauseOnLineInt = HexToByte(PauseOnLine);
                if ((state->pc == PauseOnLineInt) && breakpointActive) {
                    std::cout << "breakpoint" << std::endl;
                    notHalted = false;
                }

                if (breakpointActive) {
                    std::cout << "breakpoint" << std::endl;
                    breakpointActive = false;
                    notHalted = false;
                }

                if ((state->cyclesInterrupt >= cycleperscanline * (scanlines / 2)) && !midInterruptTriggered && state->int_enable) {
                    ISR(state, 0x08);
                    midInterruptTriggered = true;
                    state->cyclesInterrupt = 0;
                }
                if ((state->cyclesInterrupt >= cycleperscanline * (scanlines / 2)) && state->int_enable) {
                    ISR(state, 0x10);
                    midInterruptTriggered = false;
                    state->cyclesInterrupt = 0;
                }
                
                Emulate8080Op(state);
                clockCycle = currentTime;

                previousInstructions[(currentInstruction * 4)] = state->pc;
                previousInstructions[(currentInstruction * 4) + 1] = state->memory[state->pc];
                previousInstructions[(currentInstruction * 4) + 2] = state->memory[state->pc + 1];
                previousInstructions[(currentInstruction * 4) + 3] = state->memory[state->pc + 2];

                currentInstruction += 1;

                if (currentInstruction >= MAXINSTRUCTIONS) {
                    currentInstruction = 0;
                }

                if (runOnce) {
                    notHalted = false;
                    runOnce = false;
                }
            }
            state->cycles = 0;
        }

        if ((currentTime - lastGuiUpdate) >= (unsigned long long) ((10000000 / 20))) {

            processInput(window, state);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            draw(state, shaderProgram, VAO, texture);

            ImGUIFrame(oneInstructionCycle, notHalted, runOnce, runFrame, state, PauseOnLine, breakpointActive, MAXINSTRUCTIONS, currentInstruction, previousInstructions);

            glfwSwapBuffers(window);
            glfwPollEvents();
            
            lastGuiUpdate = currentTime;
        }
	}

    GraphicsCleanup(VAO, shaderProgram);
	return 0;
}
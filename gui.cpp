#include "GUI.h"
#include <iostream>
#include "shader.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_memory_editor.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

unsigned char* display = new unsigned char[224 * 256 * 3];

GLFWwindow* InitGUI() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1200, 700, "Space Invaders", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return NULL;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();

    return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


unsigned int InitializeShader() {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
    }
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
    }
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

void RenderDebugData(long long& oneInstructionCycle, bool& notHalted, bool& runOnce, bool& runFrame, State8080* state, char* PauseOnLine, bool& breakpointActive, int MAXINSTRUCTIONS, int currentInstruction, int* previousInstructions) {
    int programCount = state->pc;
    int opcode = state->memory[state->pc];
    int firstByte = state->memory[state->pc + 1];
    int secondByte = state->memory[state->pc + 2];
    ImGui::Begin("Register Info");

    ImGui::Text("Current Instruction: %02X", opcode);
    ImGui::Text("Next Byte: %02X %02X", firstByte, secondByte);

    ImGui::Text("Instruction: %s", DISSAMBLER_STATES[opcode]);

    ImGui::Text("Reg A: %02X", state->a);
    ImGui::Text("Reg B: %02X", state->b);
    ImGui::Text("Reg C: %02X", state->c);
    ImGui::Text("Reg D, E: %02X %02X", state->d, state->e);
    ImGui::Text("Reg H, L: %02X %02X", state->h, state->l);
    ImGui::Text("Reg SP: %04X", state->sp);
    ImGui::Text("Reg pc: %04X", state->pc);
    ImGui::Text("Reg Status: %XS %XZ %XAC %XP %XCS", state->cc.s, state->cc.z, state->cc.ac, state->cc.p, state->cc.cy);

    ImGui::Text("CycleTime: %d mS", (oneInstructionCycle / 10000));

    ImGui::Text("Pause on Line: ");
    ImGui::SameLine();
    ImGui::InputText("0x0000", PauseOnLine, 5);

    if (ImGui::Button("Breakpoint"))
    {
        std::cout << "Breakpoint" << std::endl;
        breakpointActive ^= 1;
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset")) {
        state->pc = 0;
        for (int address = 0x2000; address <= 0xFFFF; address++) {
            state->memory[address] = 0;
        }

        for (int address = 0; address <= MAXINSTRUCTIONS; address++) {
            previousInstructions[address] = 0;
        }
    }

    if (ImGui::Button("Start/Pause")) {
        notHalted ^= 1;
    }

    if (ImGui::Button("ISR Enable")) {
        state->int_enable ^= 1;
    }

    if (ImGui::Button("Next Code")) {
        notHalted = true;
        runOnce = true;
    }

    if (ImGui::Button("Cycle Time Up")) {
        oneInstructionCycle *= (unsigned long long)2;
        if (oneInstructionCycle == 0) {
            oneInstructionCycle = 10000000;
        }
    }

    if (ImGui::Button("Cycle Time Down")) {
        oneInstructionCycle /= (unsigned long long)2;
    }

    if (ImGui::Button("Frame/Instruction")) {
        runFrame ^= 1;
    }

    mem_edit.DrawWindow("Memory Edit", state->memory, 0xFFFF);

    ImGui::End();
}

unsigned int InitializeVAO() {

    float vertices[] = {
        //vertex x,y,z      //texture u, v
        0.2f,  0.9f,  0.0f,   1.0f, 0.0f, //top left t1
        0.9f,  0.9f,  0.0f,   1.0f, 1.0f, //top right t1
        0.2f, -0.52f, 0.0f,   0.0f, 0.0f, //bottom left t1
        0.2f, -0.52f, 0.0f,   0.0f, 0.0f, //bottom left t2
        0.9f,  0.9f,  0.0f,   1.0f, 1.0f, //top right t2
        0.9f, -0.52f, 0.0f,   0.0f, 1.0f  //bottom right t2
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return VAO;
}

void draw(State8080* state, unsigned int shaderProgram, unsigned int VAO, unsigned int texture) {
    int startVRAM = 0x2400;
    int endVRAM = 0x4000;
    int width = 224;
    int height = 256;

    int VRAMLength = (endVRAM - startVRAM);

    for (int i = 0; i <= VRAMLength; i++) {
        unsigned int currentByte = state->memory[startVRAM + i];
        for (int k = 0; k < 8; k++) {
            int indexOffset = ((i * 8) + (k)) * 3;
            if (((currentByte >> k) & 0x01) == 0) {
                display[indexOffset + 0] = 0x00;
                display[indexOffset + 1] = 0x00;
                display[indexOffset + 2] = 0x00;
            }
            else {
                display[indexOffset + 0] = 0x00;
                display[indexOffset + 1] = 0xC0;
                display[indexOffset + 2] = 0xC0;
            }
        }
    }

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, height, width, 0, GL_RGB, GL_UNSIGNED_BYTE, display);
    glGenerateMipmap(GL_TEXTURE_2D);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void ImGUIFrame(long long& oneInstructionCycle, bool& notHalted, bool& runOnce, bool& runFrame, State8080* state, char* PauseOnLine, bool& breakpointActive, int MAXINSTRUCTIONS, int currentInstruction, int* previousInstructions) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    RenderDebugData(oneInstructionCycle, notHalted, runOnce, runFrame, state, PauseOnLine, breakpointActive, MAXINSTRUCTIONS, currentInstruction, previousInstructions);

    ImGui::Begin("Last Instructions");

    for (int k = 0; k < MAXINSTRUCTIONS; k++)
    {
        int index = currentInstruction - k - 1;
        if (index < 0)
        {
            index = MAXINSTRUCTIONS + index;
        }
        ImGui::Text("%04X %02X %02X %02X     %s", previousInstructions[(index * 4)], previousInstructions[(index * 4) + 1], previousInstructions[(index * 4) + 2], previousInstructions[(index * 4) + 3], DISSAMBLER_STATES[previousInstructions[(index * 4) + 1]]);
    }

    ImGui::End();

    ImGui::Begin("Important Stuff");
    ImGui::Text("Credits: %02X", state->memory[0x20EB]);
    ImGui::Text("CoinSwitch: %02X", state->memory[0x20EA]);
    ImGui::Text("GameMode: %02X", state->memory[0x20EF]);
    ImGui::Text("Suspend: %02X", state->memory[0x20E9]);
    ImGui::Text("Port1: %02X", state->IOPorts[1]);
    ImGui::Text("Port2: %02X", state->IOPorts[2]);

    ImGui::End();

    ImGui::Begin("Controls");

    ImGui::Text("Insert Coin    - C");
    ImGui::Text("Player 1 Start - Enter");
    ImGui::Text("Player 1 Left  - A");
    ImGui::Text("Player 1 Right - D");
    ImGui::Text("Player 1 Shoot - Space");

    ImGui::End();



    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void GraphicsCleanup(unsigned int VAO, unsigned int shaderProgram) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
}
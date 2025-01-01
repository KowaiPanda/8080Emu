#include "io.h"
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

void processInput(GLFWwindow* window, State8080* state) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        state->IOPorts[1] |= 1 << p1Left;
    }
    else {
        state->IOPorts[1] &= ~(1 << p1Left);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        state->IOPorts[1] |= 1 << p1Right;
    }
    else {
        state->IOPorts[1] &= ~(1 << p1Right);
    }

    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        state->IOPorts[1] |= 1 << insertCoin;
    }
    else {
        state->IOPorts[1] &= ~(1 << insertCoin);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        state->IOPorts[1] |= 1 << p1Shoot;
    }
    else {
        state->IOPorts[1] &= ~(1 << p1Shoot);
    }

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        state->IOPorts[1] |= 1 << player1Start;
    }
    else {
        state->IOPorts[1] &= ~(1 << player1Start);
    }

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        state->IOPorts[2] |= 1 << tiltControls;
    }
    else {
        state->IOPorts[2] &= ~(1 << tiltControls);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        state->IOPorts[2] |= 1 << player2Left;
    }
    else {
        state->IOPorts[2] &= ~(1 << player2Left);
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        state->IOPorts[2] |= 1 << player2Right;
    }
    else {
        state->IOPorts[2] &= ~(1 << player2Right);
    }

    if (glfwGetKey(window, GLFW_KEY_KP_DECIMAL) == GLFW_PRESS) {
        state->IOPorts[2] |= 1 << player2Start;
    }
    else {
        state->IOPorts[2] &= ~(1 << player2Start);
    }

    if (glfwGetKey(window, GLFW_KEY_KP_0) == GLFW_PRESS) {
        state->IOPorts[2] |= 1 << player2Shoot;
    }
    else {
        state->IOPorts[2] &= ~(1 << player2Shoot);
    }
}
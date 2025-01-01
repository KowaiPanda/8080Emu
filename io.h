#ifndef INPUT_OUTPUT
#define INPUT_OUTPUT

#include "emulator_shell.h"
#include <GLFW/glfw3.h>

#define insertCoin      0
#define player2Start    1
#define player1Start    2

#define p1Shoot         4 
#define p1Left          5
#define p1Right         6

#define livesBit1       0
#define livesBit2       1
#define tiltControls    2
#define bonusLifeAmount 3
#define player2Shoot    4
#define player2Left     5
#define player2Right    6
#define displayCoin     7

void processInput(GLFWwindow* window, State8080* state);

#endif
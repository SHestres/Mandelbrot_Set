#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <math.h>

//Handles keypress events
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
//Sets which variables to update when keys are pressed
void setInputHooks(float* _scaleX, float* _scaleY, float* _xOff, float* _yOff);
//Checks which keys are currently pressed and updates values accordingly
void pollKeys(GLFWwindow* window);
#endif	INPUT_H
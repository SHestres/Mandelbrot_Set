#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void setInputHooks(float* _scaleX, float* _scaleY, float* _xOff, float* _yOff);

#endif	INPUT_H
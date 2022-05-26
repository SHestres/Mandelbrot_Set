#include "input.h"

float *scaleX, *scaleY, *xOff, *yOff;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UP) {		//Zoom in
		*scaleX *= 0.95f;
		*scaleY *= 0.95f;}
	else if (key == GLFW_KEY_DOWN) {	//Zoom out
		*scaleX *= 1.1f;
		*scaleY *= 1.1f;}
	else if (key == GLFW_KEY_W)		//Pan up
		*yOff += 0.01f * (*scaleY);
	else if (key == GLFW_KEY_S)		//Pan Down
		*yOff -= 0.01f * (*scaleY);
	else if (key == GLFW_KEY_D)		//Pan Right
		*xOff += 0.01f * (*scaleY);
	else if (key == GLFW_KEY_A)		//Pan Left
		*xOff -= 0.01f * (*scaleY);
}


void setInputHooks(float* _scaleX, float* _scaleY, float* _xOff, float* _yOff)
{
	scaleX = _scaleX;
	scaleY = _scaleY;
	xOff = _xOff;
	yOff = _yOff;
}

void pollKeys(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {		//Zoom in
		*scaleX *= 0.95f;
		*scaleY *= 0.95f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {	//Zoom out
		*scaleX *= 1.1f;
		*scaleY *= 1.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 		//Pan up
		*yOff += 0.01f * (*scaleY);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 		//Pan Down
		*yOff -= 0.01f * (*scaleY);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 		//Pan Right
		*xOff += 0.01f * (*scaleY);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 		//Pan Left
		*xOff -= 0.01f * (*scaleY);
}
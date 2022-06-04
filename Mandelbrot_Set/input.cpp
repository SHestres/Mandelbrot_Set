#include "input.h"

float *scaleX, *scaleY, *xOff, *yOff;

float curr_time;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
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
	float time = glfwGetTime();
	float deltaTime = time - curr_time;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {		//Zoom in
		*scaleX *= 1 - (.9f * deltaTime);
		*scaleY *= 1 - (.9f * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {	//Zoom out
		*scaleX *= 1 + (.9f * deltaTime);
		*scaleY *= 1 + (.9f * deltaTime);
	}
	if (*scaleX > 0.0001f)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 		//Pan up
			*yOff += 0.5f * (*scaleY) * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 		//Pan Down
			*yOff -= 0.5f * (*scaleY) * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 		//Pan Right
			*xOff += 0.5f * (*scaleY) * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 		//Pan Left
			*xOff -= 0.5f * (*scaleY) * deltaTime;
	}
	else
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 		//Pan up
			*yOff = nextafterf(*yOff, 100);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 		//Pan Down
			*yOff = nextafterf(*yOff, -100);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 		//Pan Right
			*xOff = nextafterf(*xOff, 100);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 		//Pan Left
			*xOff = nextafterf(*xOff, -100);
	}
	curr_time = time;
}
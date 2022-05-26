#include "windowConfig.h"



GLFWwindow* configureWindow(int* windowWidth, int* windowHeight, float resolutionScale)
{
	//Get the screen size from glfw
	GLFWvidmode screen = *glfwGetVideoMode(glfwGetPrimaryMonitor());

	*windowWidth = screen.width * resolutionScale;
	*windowHeight = screen.height * resolutionScale;

	//Window setup and creation
	//
	//Create window: Width, height, name, fullscreen, idk
	GLFWwindow* window = glfwCreateWindow(*windowWidth, *windowHeight, "Mandelbrot Set", glfwGetPrimaryMonitor(), NULL);


	//Actually open and show the window by making it the context
	glfwMakeContextCurrent(window);
	//Load Glad to configure openGL
	gladLoadGL();
	//Tell openGL the area of the window we want to render in
	glViewport(0, 0, *windowWidth, *windowHeight);

	return window;
}
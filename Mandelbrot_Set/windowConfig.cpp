#include "windowConfig.h"



GLFWwindow* configureWindow(int* windowWidth, int* windowHeight)
{
	//Get the screen size from glfw
	GLFWvidmode screen = *glfwGetVideoMode(glfwGetPrimaryMonitor());

	*windowWidth = screen.width;
	*windowHeight = screen.height;

	//Window setup and creation
	//
	//Create window: Width, height, name, fullscreen, idk
	GLFWwindow* window = glfwCreateWindow(*windowWidth, *windowHeight, "openGL", NULL, NULL);


	//Actually open and show the window by making it the context
	glfwMakeContextCurrent(window);
	//Load Glad to configure openGL  (idk why, but this can't be with the configuration section)
	gladLoadGL();
	//Tell openGL the area of the window we want to render in
	glViewport(0, 0, *windowWidth, *windowHeight);

	return window;
}
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "windowConfig.h"
#include "input.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"




int main()
{

	/////////Configuration
	glfwInit();
	//Tell glfw I'm using openGL v3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tell glfw I'm using the core profile (doesn't have compatibility functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Set window parameters
	int windowWidth;
	int windowHeight;
	float scale = 2.0f;
	float xOffset = 0.0f;
	float yOffset = 0.0f;
	float xScale;
	float yScale;


	//Configure window (gets the width and height out)
	GLFWwindow* window = configureWindow(&windowWidth, &windowHeight, 1.0f);
	//Make sure it actually exists
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Set individual x and y scale for non-square windows
	if (windowWidth > windowHeight)
	{
		xScale = scale * windowHeight / windowWidth;
		yScale = scale;
	}
	else
	{
		xScale = scale;
		yScale = scale * windowWidth / windowHeight;
	}

	
	//Configure inputs
	glfwSetKeyCallback(window, keyCallback);
	setInputHooks(&xScale, &yScale, &xOffset, &yOffset);
	


	//Create the Vertex array. Four corners to cover the whole window
	//
	//x, y, z of each vertex. Defined using GLfloat to ensure the right size of float
	GLfloat vertices[] =
	{	
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f
	};
	//Create the index array
	GLuint indices[]
	{
		//1   2
		//
		//0   3
		0, 1, 2,
		0, 2, 3
	};

	//Initialize Shaders
	Shader shaderProgram = Shader("default.vert", "Mandelbrot_HP.frag");
	
	//Create Vertex Array
	VAO VAO1;
	//Bind to make it active
	VAO1.Bind();

	//Create Vertex Buffer and index buffer (also assigns data)
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	//Link Vertex buffer to the vertex array (configures attributes in the VAO)
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0); //Vertex positions

	//Unbind all when finished (VAO first so unbinding VBO doesn't mess with it)
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//Get the IDs from the uniforms in the frag shader
	GLuint uniID_width = glGetUniformLocation(shaderProgram.ID, "width");
	GLuint uniID_height = glGetUniformLocation(shaderProgram.ID, "height");
	GLuint uniID_yScale = glGetUniformLocation(shaderProgram.ID, "xScale");
	GLuint uniID_xScale = glGetUniformLocation(shaderProgram.ID, "yScale");
	GLuint uniID_xOff = glGetUniformLocation(shaderProgram.ID, "xOffset");
	GLuint uniID_yOff = glGetUniformLocation(shaderProgram.ID, "yOffset");

	//Main Code loop, runs until something tells the window to close
	while (!glfwWindowShouldClose(window))
	{
		pollKeys(window);

		//std::cout << xScale << std::endl;

		//Actually use shaderProgram
		shaderProgram.Activate();
		//Set the values of the uniforms
		glUniform1i(uniID_width, windowWidth);
		glUniform1i(uniID_height, windowHeight);
		glUniform1f(uniID_xScale, xScale);
		glUniform1f(uniID_yScale, yScale);
		glUniform1f(uniID_xOff, xOffset);
		glUniform1f(uniID_yOff, yOffset);

		//Bind the VAO. Unnecesary if only one, but a good habit
		VAO1.Bind();

		//Draw the primatives: Type, starting ind, number of verticies to draw
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//Draw the pirmatives: Type, Num of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		//Swap buffers to actually draw the frame
		glfwSwapBuffers(window);


		//Allows window to respond
		glfwPollEvents();
	}


	//Garbage collection before ending program
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
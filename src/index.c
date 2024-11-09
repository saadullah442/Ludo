

// LIKING opengl32.lib IS EXTREMENLY IMPORTANT FOR WINDOWS 32
#include <stdio.h>

//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


// window dimesions
// GLint is different from int; GLint is always 32 bits
const GLint WIDTH = 800;
const GLint HEIGHT = 600;


 int main() {
	
	const int EXIT_FAILURE = -1;
	//Initializing GLFW
	glfwInit();

	// Window means the application window that will appear upon running the code
	// Set all the required options for GLFW
	
	// Setting up windows properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// windows cannot be resized
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	// Creating a GLFW window on which we can apply GLFW functions
	// Create a window with a title "Ludo"
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ludo", NULL, NULL);

	// Screen means monitor screen 
	// defining screen size
	int screen_width, screen_height;

	//// Getting the actual width of screen relative to desity of screen(numbers of pixels)
	glfwGetFramebufferSize(window, &screen_width, &screen_height);


	// Checking if our window was actually created or not
	if (NULL == window) {
		printf("Window couldn't be initialized\n");
		// Killing GLFW
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// If window was created we will create a window context
	glfwMakeContextCurrent(window);

	// Enabling GLEW
	
	// Set this to true so GLEW knows to use a modern approach to
	//retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	
	//// Initializing GLEW and making sure it's successful
	if (GLEW_OK != glewInit()) {
		printf("Failed to initialized GLEW\n");
		return EXIT_FAILURE;
	}

	// Setting up OPENGL viewport
	
	// Setting viewport with screen dimensions
	// Initialized coordinates from 0, 0 to screenWidth and screenHeight.
	glViewport(0, 0, screen_width, screen_height);


	
	//glfwWindowShouldClose() checks if windows is open or closed
	// loop until user closes window
	while (!glfwWindowShouldClose(window)) {

		// Checking if any events occured (example: mouse moved, key pressed)
		glfwPollEvents();

		// render
		// Clearing colour buffer and adding new value to it
		// Colour is defined by rgba() values ranging from 0-1
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		// cleared window and inserted the next frame
		glClear(GL_COLOR_BUFFER_BIT); 


		// Draw OpenGL
		glfwSwapBuffers(window);

	}

	// Closing the window and clearing all resources added by GLFW
	glfwTerminate();

	return 0;
}
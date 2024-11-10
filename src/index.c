

// LIKING opengl32.lib IS EXTREMENLY IMPORTANT FOR WINDOWS 32
#include <stdio.h>

//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


// window dimesions
// GLint is different from int; GLint is always 32 bits
const GLint WIDTH = 800;
const GLint HEIGHT = 600;

// To make shapes we need to define shaders

// Defining shader

// Handling position of triangle
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

// Handling colour of triangle
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";



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



	// Build and compile shader program
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compiling shader
	glCompileShader(vertexShader);
	// Checking for compilation error
	GLint success;
	GLchar infoLog[512];


	// This func wil return shader value to its parameter
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	// Checking if compilation failed
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("Shader compilation failed\n");
		printf("%s\n", infoLog);
	
	}
	
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// compiling fragment
	glCompileShader(fragmentShader);

	// This func wil return fragment value to its parameter
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	// Checking for comilation error 
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("Fragment compilation error");
		printf("%s\n", infoLog);
	}

	// Linking both shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader( shaderProgram, vertexShader );
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram( shaderProgram );


	// This function will return value to its parameters
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	// Checking for linking errors
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("Shader compliation error\n");
		printf("%s\n", infoLog);
	}
	// As our shader are part of shaderProgram we don't need them
	// Deleting individual shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// The value of screen ranges from -1(left) to 1(right)
	// vertex data
	GLfloat vertices[] = 
	{
		-0.5, -0.5, -0.5, // for left
		0.5f, -0.5f, 0.0f, // for right
		0.0f, 0.5f, 0.0f // for top
	};

	// VBO = Vertex Buffer Object
	// VAO = Vertex Array Object
	GLuint VBO, VAO;
	// Creating vertex array
	glGenVertexArrays(1, &VAO);
	// Creating vertex buffer
	glGenBuffers(1, &VBO);

	// Binding vertex array and buffer array
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Buffer data used to draw
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Creating vertex pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 
		(GLvoid * ) 0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


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

		// Drawing a trinagle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		
		// Creating buffer
		glUseProgram( shaderProgram );
		glBindVertexArray(VAO);

		// Drawing triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);


		// Swap the screen buffer
		glfwSwapBuffers(window);

	}

	//De-allocating all triangle resources
	glDeleteVertexArrays(1, &VAO); // Deleteing tringle
	glDeleteBuffers(1, &VBO); // Deleting buffer

	// Closing the window and clearing all resources added by GLFW
	glfwTerminate();


	return 0;
}



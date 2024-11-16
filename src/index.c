// LIKING opengl32.lib IS EXTREMENLY IMPORTANT FOR WINDOWS 32
#include <stdio.h>
//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


// window dimesions
// GLint is different from int; GLint is always 32 bits
const GLint WIDTH = 1000;
const GLint HEIGHT = 650;



static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	// Close window when escape key is pressed 
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		// Closing the window
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

GLint xpos, ypos;
void mouse_click_handler(GLFWwindow* window, int button, int action, int mods) {
	
	// Getting posistion of where mouse cursor is
	glfwGetCursorPos(window, &xpos, &ypos);

	// Checking if left button got clicked
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		//glfwSetWindowShouldClose(window, GLFW_TRUE);
		printf("Left mouse button pressed\n");
		printf("Current cursor position is: %d %d \n", xpos, ypos);
	}
}


// Red Colour Rectangle
static GLuint rectangle1(GLFWwindow* window) {
	// To make shapes we need to define shaders
	// Defining shader
	// Handling position of triangle
	// This is source code for vertex shader writtent in GLSL
	const GLchar* vertexShaderSource = 
		"#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		"}\0";

	// Handling colour of triangle
	// This is source code for fragment shader written in GLSL
	const GLchar* fragmentShaderSource = "#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 0.0f, 0.0f, 0.5f);\n"
		"}\0";

	// Build and compile shader program
	// Creating a Vertex shader object
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attaching source code to shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compiling shader
	glCompileShader(vertexShader);
	// Checking for compilation error
	GLint success;
	GLchar infoLog[512];


	// This func wil return compilation shader value to its parameter
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	// Checking if compilation failed
	if (!success) {
		// Getting information about the error. Error message
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("Shader compilation failed\n");
		printf("%s\n", infoLog);

	}

	// Creating Fragment shader Object
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
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


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


	return shaderProgram;


}

// Green Colour Rectange
static GLuint rectangle2(GLFWwindow* window) {
	const char* VertexShaderSource =
		"#version 330 core\n"
		"layout (location=1) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		"}\0";
	const char* FragmentShaderSource = 
		"#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
		"}\n\0";
	GLuint shaderProgram, fragmentShader, vertexShader;
	GLint success;
	GLchar infoLog[512];
	// Vertex Shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS , &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, &infoLog);
		printf("Compilation error in vertex shader for rectangle 2\n");
		printf("%s", infoLog);
		glDeleteShader(vertexShader);
	}


	// Fragment Shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FragmentShaderSource, NULL);
	glCompileShader(fragmentShader);


	// This func wil return fragment value to its parameter
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, &infoLog);
		printf("Compilation error in vertex shader for rectangle 2\n");
		printf("%s", infoLog);
		glDeleteShader(fragmentShader);
	}

	// Shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("Linking failder\n");
		printf("%s", infoLog);
		glDeleteProgram(shaderProgram);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	return shaderProgram;

}

// Yellow Colour Rectangle
static GLuint rectangle3(GLFWwindow* window) {
	const char* VertexShaderSource =
		"#version 330 core\n"
		"layout (location=2) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		"}\0";
	const char* FragmentShaderSource =
		"#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
		"}\n\0";
	GLuint shaderProgram, fragmentShader, vertexShader;
	GLint success;
	GLchar infoLog[512];
	// Vertex Shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, &infoLog);
		printf("Compilation error in vertex shader for rectangle 2\n");
		printf("%s", infoLog);
		glDeleteShader(vertexShader);
	}


	// Fragment Shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FragmentShaderSource, NULL);
	glCompileShader(fragmentShader);


	// This func wil return fragment value to its parameter
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, &infoLog);
		printf("Compilation error in vertex shader for rectangle 2\n");
		printf("%s", infoLog);
		glDeleteShader(fragmentShader);
	}

	// Shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("Linking failder\n");
		printf("%s", infoLog);
		glDeleteProgram(shaderProgram);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	return shaderProgram;

}

// Blue Colour Rectangle
static GLuint rectangle4(GLFWwindow* window) {
	const char* VertexShaderSource =
		"#version 330 core\n"
		"layout (location=3) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		"}\0";
	const char* FragmentShaderSource =
		"#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
		"}\n\0";
	GLuint shaderProgram, fragmentShader, vertexShader;
	GLint success;
	GLchar infoLog[512];
	// Vertex Shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, &infoLog);
		printf("Compilation error in vertex shader for rectangle 2\n");
		printf("%s", infoLog);
		glDeleteShader(vertexShader);
	}


	// Fragment Shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FragmentShaderSource, NULL);
	glCompileShader(fragmentShader);


	// This func wil return fragment value to its parameter
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, &infoLog);
		printf("Compilation error in vertex shader for rectangle 2\n");
		printf("%s", infoLog);
		glDeleteShader(fragmentShader);
	}

	// Shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("Linking failder\n");
		printf("%s", infoLog);
		glDeleteProgram(shaderProgram);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	return shaderProgram;

}

static GLuint center_rectangle(GLFWwindow* window) {
	const char* VertexShaderSource =
		"#version 330 core\n"
		"layout (location=4) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		"}\0";
	const char* FragmentShaderSource =
		"#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
		"}\n\0";
	GLuint shaderProgram, fragmentShader, vertexShader;
	GLint success;
	GLchar infoLog[512];
	// Vertex Shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, &infoLog);
		printf("Compilation error in vertex shader for rectangle 2\n");
		printf("%s", infoLog);
		glDeleteShader(vertexShader);
	}


	// Fragment Shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FragmentShaderSource, NULL);
	glCompileShader(fragmentShader);


	// This func wil return fragment value to its parameter
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, &infoLog);
		printf("Compilation error in vertex shader for rectangle 2\n");
		printf("%s", infoLog);
		glDeleteShader(fragmentShader);
	}

	// Shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("Linking failder\n");
		printf("%s", infoLog);
		glDeleteProgram(shaderProgram);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	return shaderProgram;
}

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
	// Create a window with a title "Ludo". Window is resizable if GLFW_REIZABLE != GL_FALSE
	 GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ludo", NULL, NULL);
	// This function will run whenver a mouse click or scroll event occurs
	glfwSetMouseButtonCallback(window, mouse_click_handler);
	// This function will be called when key will be pressed
	glfwSetKeyCallback(window, keyCallback);
	// Screen means monitor screen 
	// defining screen size
	int screen_width, screen_height;
	// Getting the actual width of screen relative to desity of screen(numbers of pixels)
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
	// Initializing GLEW and making sure it's successful
	if (GLEW_OK != glewInit()) {
		printf("Failed to initialized GLEW\n");
		return EXIT_FAILURE;
	}
	// Setting up OPENGL viewport
	// Setting viewport with screen dimensions
	// Initialized coordinates from 0, 0 to screenWidth and screenHeight.
	glViewport(0, 0, screen_width, screen_height);
	/*--------------------------- Calling All Rectangles ------------------------------*/
	
	GLuint shaderProgram = rectangle1(window);
	GLuint shaderProgram2 = rectangle2(window);
	GLuint shaderProgram3 = rectangle3(window);
	GLuint shaderProgram4 = rectangle4(window);
	GLuint ShaderProgramCenterRect = center_rectangle(window);
	/*---------------------------------------------------------------------------------*/
	
	

	
	/* -------------------------------- For First Rectangle ------------------------------------------ */
	// VAO = Vertex Array Object
	GLuint VAO;
	// Creating vertex array
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// OpenGL works on 3D space. We are rendering in 2D space so we can speicfy z coordinate as 0.0f
	// The value of screen ranges from -1(left) to 1(right) Horinatally And -1(down) to 1(Up) Vertically
	// vertex data
	
	// For First rectangle
	GLfloat rect1_vertices[] =
	{		
			//x		y		z
			-1.0f, 1.0f, 0.0f, // Top left
			-0.5f, 1.0f, 0.0f, // Top Middle
			-0.5f, 0.25f, 0.0f, // On x-axis (In Middle)
			-1.0f, 0.25f, 0.0f, // On x-axis (Left Most)
	};
	// Creating indeces for specific vertex of rectangle1
	GLuint rect1_indices[] = {
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	
	// IBO(Index Buffer Object) OR EBO(Element Buffer Object)
	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rect1_indices), rect1_indices, GL_STATIC_DRAW);

	// VBO = Vertex Buffer Object
	GLuint VBO;
	// Creating vertex buffer
	glGenBuffers(1, &VBO);
	// Binding vertex array and buffer array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Buffer data used to draw
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect1_vertices), rect1_vertices, GL_STATIC_DRAW);
	// Enabling vertex attribute and sending its location
	glEnableVertexAttribArray(0);
	// Telling OpenGL how to interpret vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid * ) 0);
	// Unbinding
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Unbinding VAO
	glBindVertexArray(0);
	/* --------------------------- For Second Rectangle ---------------------------------*/
	// VAO = Vertex Array Object
	GLuint VAO2;
	// Creating vertex array
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);
	
	
	GLfloat rect2_vertices[] = {
		//x		y		z
		0.5f, 1.0f, 0.0f, // Top Middle
		1.0f, 1.0f, 0.0f, // Top Right
		0.5f, 0.25f, 0.0f, // On x-axis
		1.0f, 0.25f, 0.0f, // On x-axis (To Most Right)
		
	};
	// Creating indeces for specific vertex of rectangle2
	GLuint rect2_indices[] = {
		0, 1, 2, // First Triangle
		1, 2, 3  // Second Triangle
	};
	
	
	GLuint VBO2, IBO2;

	
	// For IBO2
	glGenBuffers(1, &IBO2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rect2_indices), rect2_indices, GL_STATIC_DRAW);
	
	
	// FOR VBO2
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect2_vertices), rect2_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid * ) 0);
	
	// Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/* --------------------------- For Third Rectangle ---------------------------------*/
	// VAO = Vertex Array Object
	GLuint VAO3;
	// Creating vertex array
	glGenVertexArrays(1, &VAO3);
	glBindVertexArray(VAO3);


	GLfloat rect3_vertices[] = {
		//x		y		z
		0.5f, -0.25f, 0.0f, // x-axis (In Middle)
		1.0f, -0.25f, 0.0f, // x-axis (To Most Right) 
		0.5f, -1.0f, 0.0f, // Bottom
		1.0f, -1.0f, 0.0f, // Bottom Right

	};
	// Creating indeces for specific vertex of rectangle2
	GLuint rect3_indices[] = {
		0, 1, 2, // First Triangle
		1, 2, 3  // Second Triangle
	};


	GLuint VBO3, IBO3;


	// For IBO3
	glGenBuffers(1, &IBO3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rect3_indices), rect3_indices, GL_STATIC_DRAW);


	// FOR VBO3
	glGenBuffers(1, &VBO3);
	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect3_vertices), rect3_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	// Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	/* --------------------------- For Fourth Rectangle ---------------------------------*/
	// VAO = Vertex Array Object
	GLuint VAO4;
	// Creating vertex array
	glGenVertexArrays(1, &VAO4);
	glBindVertexArray(VAO4);


	GLfloat rect4_vertices[] = {

		//x		y		z
		-1.0f, -1.0f, 0.0f, // Bottom Left
		-0.5f, -1.0f, 0.0f, // Bottom Middle 
		-0.5f, -0.25f, 0.0f, // On x-axis (In Middle)
		-1.0f, -0.25f, 0.0f, // On x-axis (Left Most)

	};
	// Creating indeces for specific vertex of rectangle2
	GLuint rect4_indices[] = {
		0, 1, 2, // First Triangle
		0, 2, 3  // Second Triangle
	};


	GLuint VBO4, IBO4;


	// For IBO4
	glGenBuffers(1, &IBO4);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rect4_indices), rect4_indices, GL_STATIC_DRAW);


	// FOR VBO4
	glGenBuffers(1, &VBO4);
	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect4_vertices), rect4_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	// Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	/* ------------------------------ Center Winning Box -------------------------------------------*/
	
	GLfloat center_rect_vertices[] = {
		//x		  y		z
		-0.25f,	0.25f,	0.0f, // Top Left
		0.25f,	0.25f,	0.0f, // Top Right
		0.25f,	-0.25f,	0.0f, // Bottom Right
		-0.25,  -0.25f, 0.0f  // Bottom Left
	};

	GLuint center_rect_indices[] = {
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	GLuint cen_IBO, cen_VBO, cen_VAO;

	glGenVertexArrays(1, &cen_VAO);
	glBindVertexArray(cen_VAO);

	glGenBuffers(1, &cen_IBO);
	glGenBuffers(1, &cen_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, cen_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cen_IBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(center_rect_vertices), center_rect_vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(center_rect_indices), center_rect_indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);

	//Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	

	//glfwWindowShouldClose() checks if windows is open or closed
	// loop until user closes window
	while (!glfwWindowShouldClose(window)) {

		// Checking if any events occured (example: mouse moved, key pressed)
		glfwPollEvents();

		// render
		// Clearing colour buffer and adding new value to it
		// Colour is defined by rgba() values ranging from 0-1
		// Colour of background
		glClearColor(0.2f, 0.8f, 0.7f, 0.75f);

		// cleared window and inserted the next frame
		glClear(GL_COLOR_BUFFER_BIT); 

		// Draw OpenGL

		/* --------------------------- Rectangle1 -----------------------------------*/
		
		// Activating shader object for rectangle1
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		// Drawing elements or indices for rectangle 1
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		
		/* --------------------------- Rectangle2 ----------------------------------- */
		
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO2);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO2);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
		/* --------------------------- Rectangle3 ----------------------------------- */
		glUseProgram(shaderProgram3);
		glBindVertexArray(VAO3);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/* --------------------------- Rectangle4 ----------------------------------- */
		glUseProgram(shaderProgram4);
		glBindVertexArray(VAO4);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO4);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/*--------------------------- Center Rectangle -----------------------------------*/
		glUseProgram(ShaderProgramCenterRect);
		glBindVertexArray(cen_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cen_IBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		// Unbinding
		glBindVertexArray(0); 
		// Swap the screen buffer
		glfwSwapBuffers(window);
		
	}



	// Destroying window and context
	glfwDestroyWindow(window);

	// Closing the window and clearing all resources added by GLFW
	glfwTerminate();


	return 0;
}



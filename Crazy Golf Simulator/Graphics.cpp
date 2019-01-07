#include "Graphics.h"



int Graphics::Start()
{



	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		return EXIT_FAILURE;

	}



	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
	return 0;

}
int Graphics::Set_Window()
{
	// Create window with graphics context
	window = glfwCreateWindow(1280, 720, "Crazy Golf Simulator", NULL, NULL);

	if (window == NULL)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

						 // Initialize OpenGL loader
	bool err = glewInit() != GLEW_OK;

	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return EXIT_FAILURE;
	}

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");





	Texture = loadDDS("gameSprites2.dds");




	for (Square square : Square::game_map)
	{
		Add_Square(square);
	}

	//std::cout << g_vertex_buffer_data[1] << std::endl;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* g_vertex_buffer_data.size(), &g_vertex_buffer_data[0], GL_DYNAMIC_DRAW);


	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * g_uv_buffer_data.size(), &g_uv_buffer_data[0], GL_DYNAMIC_DRAW);

#pragma region glfwTest

	/*glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
	glCompileShader(vertex_shader);
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
	glCompileShader(fragment_shader);
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	mvp_location = glGetUniformLocation(program, "MVP");
	vpos_location = glGetAttribLocation(program, "vPos");
	vcol_location = glGetAttribLocation(program, "vCol");
	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
		sizeof(float) * 5, (void*)0);
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 5, (void*)(sizeof(float) * 2));*/
#pragma endregion
	

	return 0;
}
void Graphics::Add_Square(Square square)
{
	g_vertex_buffer_data.insert(g_vertex_buffer_data.end(), square.vertex_data, square.vertex_data + 12);
	g_uv_buffer_data.insert(g_uv_buffer_data.end(), square.uv_coord_data, square.uv_coord_data + 8);
}
void Graphics::Screen_Refresh(glm::mat4x4 &m)
{
	g_vertex_buffer_data.clear();
	g_uv_buffer_data.clear();
	for (Square square : Square::game_map)
	{
		Add_Square(square);
	}
	//std::cout << g_vertex_buffer_data[1] << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* g_vertex_buffer_data.size(), &g_vertex_buffer_data[0], GL_DYNAMIC_DRAW);
	int display_w, display_h;
	glfwMakeContextCurrent(Graphics::window);
	glfwGetFramebufferSize(Graphics::window, &display_w, &display_h);

	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	float ratio;


	ratio = display_w / (float)display_h;
	glViewport(0, 0, display_w, display_h);

	
	//camera perspective
	glm::mat4 Projection = glm::perspective(glm::radians(60.0f), ratio, 0.1f, 1000.0f);
	// Camera matrix
	glm::mat4 View = glm::lookAt(
		Square::game_map_centre + glm::vec3(0, 0, 30), // Camera is at (4,3,3), in World Space
		Square::game_map_centre, // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = m;
	// Our ModelViewProjection : multiplication of our 3 matrices
	MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around


	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shader
	glUseProgram(programID);

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_QUADS, 0, g_vertex_buffer_data.size()); // 12*3 indices starting at 0 -> 12 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
}
void Graphics::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Graphics::error_callback(int error, const char* description)
{
	std::cout << (stderr, "Error: %s\n", description) << std::endl;
}




Graphics::Graphics()
{
}


Graphics::~Graphics()
{
}


GLFWwindow *Graphics::window;

GLuint Graphics::VertexArrayID,
Graphics::programID,
Graphics::MatrixID,
Graphics::Texture,
Graphics::TextureID,
Graphics::vertexbuffer,
Graphics::uvbuffer;
glm::mat4 Graphics::MVP;

GLuint Graphics::vertex_buffer, Graphics::vertex_shader, Graphics::fragment_shader, Graphics::program;
GLint Graphics::mvp_location, Graphics::vpos_location, Graphics::vcol_location;

ImVec4 Graphics::clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
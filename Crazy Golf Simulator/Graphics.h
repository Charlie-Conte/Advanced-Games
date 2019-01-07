#pragma once
#include "GlobalHeaders.h"
#include "Square.h"

// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static std::vector <GLfloat> g_vertex_buffer_data;


// Two UV coordinatesfor each vertex. They were created with Blender.
static std::vector <GLfloat> g_uv_buffer_data;





// GL 3.0 + GLSL 130
static const char* glsl_version = "#version 130";

class Graphics
{
public:


	static void error_callback(int error, const char * description);
	static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);


	static int Start();
	static int Set_Window();
	static void Add_Square(Square ground);
	static void Screen_Refresh(glm::mat4x4 &m, float camZoom);
	Graphics();
	~Graphics();


	static GLFWwindow* window;

	static GLuint vertex_buffer, vertex_shader, fragment_shader, program;
	static GLint mvp_location, vpos_location, vcol_location;

	static ImVec4 clear_color;

	static GLuint VertexArrayID, 
		programID,
		MatrixID, 
		Texture, 
		TextureID, 
		vertexbuffer,
		uvbuffer;
	static glm::mat4 MVP;
};


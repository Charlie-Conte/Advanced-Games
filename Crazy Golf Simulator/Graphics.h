#pragma once
#include "GlobalHeaders.h"
#include "Square.h"

// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static std::vector <GLfloat> g_vertex_buffer_data;//= {
//	-1.0f,-1.0f,0.0f,
//	1.0f,-1.0f,0.0f,
//	1.0f,1.0f,0.0f,
//	-1.0f,1.0f,0.0f		,
//
//	3.0f,-1.0f,0.0f,
//	5.0f,-1.0f,0.0f,
//	5.0f,1.0f,0.0f,
//	3.0f,1.0f,0.0f
//
//
//	//-1.0f,-1.0f,-1.0f,
//	//-1.0f,-1.0f, 1.0f,
//	//-1.0f, 1.0f, 1.0f,
//	// 1.0f, 1.0f,-1.0f,
//	//-1.0f,-1.0f,-1.0f,
//	/*-1.0f, 1.0f,-1.0f,
//	1.0f,-1.0f, 1.0f,
//	-1.0f,-1.0f,-1.0f,
//	1.0f,-1.0f,-1.0f,
//	1.0f, 1.0f,-1.0f,
//	1.0f,-1.0f,-1.0f,
//	-1.0f,-1.0f,-1.0f,
//	-1.0f,-1.0f,-1.0f,
//	-1.0f, 1.0f, 1.0f,
//	-1.0f, 1.0f,-1.0f,
//	1.0f,-1.0f, 1.0f,
//	-1.0f,-1.0f, 1.0f,
//	-1.0f,-1.0f,-1.0f,
//	-1.0f, 1.0f, 1.0f,
//	-1.0f,-1.0f, 1.0f,
//	1.0f,-1.0f, 1.0f,
//	1.0f, 1.0f, 1.0f,
//	1.0f,-1.0f,-1.0f,
//	1.0f, 1.0f,-1.0f,
//	1.0f,-1.0f,-1.0f,
//	1.0f, 1.0f, 1.0f,
//	1.0f,-1.0f, 1.0f,
//	1.0f, 1.0f, 1.0f,
//	1.0f, 1.0f,-1.0f,
//	-1.0f, 1.0f,-1.0f,
//	1.0f, 1.0f, 1.0f,
//	-1.0f, 1.0f,-1.0f,
//	-1.0f, 1.0f, 1.0f,
//	1.0f, 1.0f, 1.0f,
//	-1.0f, 1.0f, 1.0f,
//	1.0f,-1.0f, 1.0f*/
//};

// Two UV coordinatesfor each vertex. They were created with Blender.
static std::vector <GLfloat> g_uv_buffer_data; //= {
//	0.001f, .249f,
//	0.249f, .249f,
//	0.249f, 0.001f,
//	0.001f, 0.001f,
//
//	.5f, .5f,
//	1.f, .5f,
//	1.f, 0.f,
//	.5f, 0.f
//
//	//0.0000f, 1.0f-0.00000f, 
//	//1.0000f, 1.0f-0.00000f, 
//	//1.0000f, 1.0f-1.00000f, 
//	//0.0000f, 1.0f-1.00000f
//
//	//0.000059f, 1.0f-0.000004f, 
//	//0.000103f, 1.0f-0.336048f, 
//	//0.335973f, 1.0f-0.335903f, 
//	//1.000023f, 1.0f-0.000013f, 
//	//0.667979f, 1.0f-0.335851f, 
//	//0.999958f, 1.0f-0.336064f, 
//	//0.667979f, 1.0f-0.335851f, 
//	//0.336024f, 1.0f-0.671877f, 
//	//0.667969f, 1.0f-0.671889f, 
//	//1.000023f, 1.0f-0.000013f, 
//	//0.668104f, 1.0f-0.000013f, 
//	//0.667979f, 1.0f-0.335851f, 
//	//0.000059f, 1.0f-0.000004f, 
//	//0.335973f, 1.0f-0.335903f, 
//	//0.336098f, 1.0f-0.000071f, 
//	//0.667979f, 1.0f-0.335851f, 
//	//0.335973f, 1.0f-0.335903f, 
//	//0.336024f, 1.0f-0.671877f, 
//	//1.000004f, 1.0f-0.671847f, 
//	//0.999958f, 1.0f-0.336064f, 
//	//0.667979f, 1.0f-0.335851f, 
//	//0.668104f, 1.0f-0.000013f, 
//	//0.335973f, 1.0f-0.335903f, 
//	//0.667979f, 1.0f-0.335851f, 
//	//0.335973f, 1.0f-0.335903f, 
//	//0.668104f, 1.0f-0.000013f, 
//	//0.336098f, 1.0f-0.000071f, 
//	//0.000103f, 1.0f-0.336048f, 
//	//0.000004f, 1.0f-0.671870f, 
//	//0.336024f, 1.0f-0.671877f, 
//	//0.000103f, 1.0f-0.336048f, 
//	//0.336024f, 1.0f-0.671877f, 
//	//0.335973f, 1.0f-0.335903f, 
//	//0.667969f, 1.0f-0.671889f, 
//	//1.000004f, 1.0f-0.671847f, 
//	//0.667979f, 1.0f-0.335851f
//};




// GL 3.0 + GLSL 130
static const char* glsl_version = "#version 130";

class Graphics
{
public:


	static void error_callback(int error, const char * description);
	static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);


	static int Start();
	static int Set_Window();
	static void Add_Square(Square &ground);
	static void Screen_Refresh(glm::mat4x4 &m);
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


#pragma once
#include <iostream>
#include <string>
#include "GlobalHeaders.h"

// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// About OpenGL function loaders: modern OpenGL doesn't have a standard header file and requires individual function pointers to be loaded manually. 
// Helper libraries are often used for this purpose! Here we are supporting a few common ones: gl3w, glew, glad.
// You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h> 

#include "shader.hpp"
#include "texture.hpp"

static const char* vertex_shader_text =
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";
static const char* fragment_shader_text =
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";


static const struct
{
	float x, y;
	float r, g, b;
} vertices[3] =
{
	{ -0.6f, -0.4f, 1.f, 0.f, 0.f },
{ 0.6f, -0.4f, 0.f, 1.f, 0.f },
{ 0.f,  0.6f, 0.f, 0.f, 1.f }
};



// GL 3.0 + GLSL 130
static const char* glsl_version = "#version 130";

class Graphics
{
public:


	static void error_callback(int error, const char * description);
	static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);


	static int Start();
	static int Set_Window();
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


#pragma once
#include "Graphics.h"


class GUI 
{
public:

	static void Setup();
	static int Update_GUI();

	GUI();
	~GUI();

	static ImVec4 clear_color;
	static glm::vec3 rAngle;
private:

	static bool show_demo_window;
	static bool show_another_window;
	static bool show_main_window;

	static float aX, aY, aZ;

};


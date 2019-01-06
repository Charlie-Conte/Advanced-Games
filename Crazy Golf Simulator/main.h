#pragma once


#include "GUI.h"
#include "DataLoader.h"


#include "Box2D/Box2D.h"


#include <SOIL.h>



int const TARGET_FPS = 60;

std::string matrix = "";


int current_state = 0;
int main(int argc, char * argv[]);

void Transform_Scene(glm::mat4x4 &m);

void Render_Scene(glm::mat4x4 &m);

std::string TestIdentityMatrix4x4(glm::mat4x4 &l);

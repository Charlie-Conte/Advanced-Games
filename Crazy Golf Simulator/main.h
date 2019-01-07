#pragma once


#include "GUI.h"
#include "DataLoader.h"

#include "PhysicsSource.h"




int const TARGET_FPS = 60;

std::string matrix = "";


int current_state = 0;
int main(int argc, char * argv[]);

void Display(float timeStep, int velocityIterations, int positionIterations, double &lasttime);

void Transform_Scene(glm::mat4x4 &m);

void Render_Scene(glm::mat4x4 &m);

std::string TestIdentityMatrix4x4(glm::mat4x4 &l);



double lasttime = glfwGetTime();

float timeStep = 1.0f / 120.0f;
int velocityIterations = 8;
int positionIterations = 3;
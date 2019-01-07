#include "main.h"


int main(int argc, char *argv[])
{

	current_state = Graphics::Start();

	if (current_state != 0)
		return  current_state;

	DataLoader::Load_Data();

	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	current_state = Graphics::Set_Window();

	if (current_state != 0)
		return  current_state;


	PhysicsSource::world.SetAllowSleeping(false);




	GUI::Setup();

	double lasttime = glfwGetTime();

	float timeStep = 1.0f / 120.0f;
	int velocityIterations = 8;
	int positionIterations = 3;

	Display(timeStep, velocityIterations, positionIterations, lasttime);


	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(Graphics::window);



	// Cleanup VBO and shader
	glDeleteBuffers(1, &Graphics::vertexbuffer);
	glDeleteBuffers(1, &Graphics::uvbuffer);
	glDeleteProgram(Graphics::programID);
	glDeleteTextures(1, &Graphics::Texture);
	glDeleteVertexArrays(1, &Graphics::VertexArrayID);

	glfwTerminate();
	return EXIT_SUCCESS;
}

void Display(float timeStep, int velocityIterations, int positionIterations, double &lasttime)
{


	//Game Loop
	while (!glfwWindowShouldClose(Graphics::window))
	{


		PhysicsSource::world.Step(timeStep, velocityIterations, positionIterations);

		GUI::Update_GUI();

		glm::mat4x4 m = glm::mat4x4(1);//glm::mat4x4(glm::vec4(0),glm::vec4(0),glm::vec4(0),glm::vec4(1));//scene matrix

		Transform_Scene(m);

		Render_Scene(m);



		for (Square &sq : Square::game_map)
		{
			if (glm::distance(glm::vec3(sq.vertex_data[0], sq.vertex_data[1], sq.vertex_data[2]), Square::game_map_hole_0) >= 0.2f)
			{
				b2Vec2 groundPhysicsPosition = sq.squareBody->GetPosition();
				glm::vec3 groundGraphicsPosition = glm::vec3(0, 0, 0);

				groundGraphicsPosition.x = (groundPhysicsPosition.x);
				groundGraphicsPosition.y = (groundPhysicsPosition.y);
				groundGraphicsPosition.z = sq.vertex_data[2];

				sq.Move(groundGraphicsPosition);
			}
			
		}
		

		glfwSetKeyCallback(Graphics::window, key_callback);
		//frame limit
		while (glfwGetTime() < lasttime + 1.0 / TARGET_FPS);
		lasttime += 1.0 / TARGET_FPS;
	}
}

void Transform_Scene(glm::mat4x4 &m)
{


	float angleToRotate = glm::radians((float)glfwGetTime() * 100);

	if (GUI::rAngle != glm::vec3(0)) {
		m = glm::rotate(m, angleToRotate, GUI::rAngle);
	}


}

void Render_Scene(glm::mat4x4 &m)
{
	// Rendering
	ImGui::Render();


	glClearColor(Graphics::clear_color.x, Graphics::clear_color.y, Graphics::clear_color.z, Graphics::clear_color.w);




	Graphics::Screen_Refresh(m, DataLoader::zoom);



}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)PhysicsSource::world.SetGravity(b2Vec2(0, 0));
	if (action == GLFW_REPEAT)
	{
		float cap = 8.f;
		float accel = 0.8f;
		if (key == GLFW_KEY_UP)
		{
			PhysicsSource::world.SetGravity(PhysicsSource::world.GetGravity() + b2Vec2(0, accel));
			if (PhysicsSource::world.GetGravity().y > cap)PhysicsSource::world.SetGravity(b2Vec2(PhysicsSource::world.GetGravity().x, cap));
		}
		if (key == GLFW_KEY_DOWN)
		{
			PhysicsSource::world.SetGravity(PhysicsSource::world.GetGravity() - b2Vec2(0, accel));
			if (PhysicsSource::world.GetGravity().y < -cap)PhysicsSource::world.SetGravity(b2Vec2( PhysicsSource::world.GetGravity().x, -cap));
		}
		if (key == GLFW_KEY_RIGHT)
		{
			PhysicsSource::world.SetGravity(PhysicsSource::world.GetGravity() + b2Vec2(accel, 0));
			if (PhysicsSource::world.GetGravity().x > cap)PhysicsSource::world.SetGravity(b2Vec2(cap, PhysicsSource::world.GetGravity().y));
		}
		if (key == GLFW_KEY_LEFT)
		{
			PhysicsSource::world.SetGravity(PhysicsSource::world.GetGravity() - b2Vec2(accel, 0));
			if (PhysicsSource::world.GetGravity().x < -cap)PhysicsSource::world.SetGravity(b2Vec2(-cap, PhysicsSource::world.GetGravity().y));

		}
			
		
	}

	std::cout << PhysicsSource::world.GetGravity().x<<" , "<<PhysicsSource::world.GetGravity().y  <<"\n";
}


std::string TestIdentityMatrix4x4(glm::mat4x4 &l)
{
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(l, scale, rotation, translation, skew, perspective);
	std::string out = "Translation:\t"+ std::to_string(translation.x)+", "+ std::to_string(translation.y) + ", " + std::to_string(translation.z)+"\n"+
					  "Rotation:\t"+ std::to_string(rotation.x)+", "+std::to_string(rotation.y)+", "+std::to_string(rotation.z)+"\n"+
					  "Scale:\t\t"+std::to_string(scale.x)+", "+std::to_string(scale.y)+", "+std::to_string(scale.z)+"\n\n";

	return out;
}




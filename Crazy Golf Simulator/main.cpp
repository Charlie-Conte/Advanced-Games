#include "main.h"


int main(int argc, char *argv[])
{

	current_state = Graphics::Start();

	if (current_state != 0)
		return  current_state;

	DataLoader::Load_Data();

	B2_NOT_USED(argc);
	B2_NOT_USED(argv);




	//b2BodyDef myBodyDef;
	//myBodyDef.type = b2_dynamicBody;

	////shape definition
	//b2PolygonShape polygonShape;
	//polygonShape.SetAsBox(1, 1); //a 2x2 rectangle

	//							 //fixture definition
	//b2FixtureDef myFixtureDef;
	//myFixtureDef.shape = &polygonShape;
	//myFixtureDef.density = 1;

	////create identical bodies in different positions
	//for (int i = 0; i < 3; i++) {
	//	myBodyDef.position.Set(-10 + i * 10, 20);
	//	bodies[i] = PhysicsSource::world.CreateBody(&myBodyDef);
	//	bodies[i]->CreateFixture(&myFixtureDef);
	//}

	////a static floor to drop things on
	//myBodyDef.type = b2_staticBody;
	//myBodyDef.position.Set(0, 0);
	////polygonShape.SetAsEdge(b2Vec2(-15, 0), b2Vec2(15, 0));
	//PhysicsSource::world.CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);



	current_state = Graphics::Set_Window();

	if (current_state != 0)
		return  current_state;


	




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


	//std::cout << "Hello World\n";
	//std::string input;
	//std::getline(std::cin, input);

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

		//glTranslatef(0.0f, 0.0f, -35.0f); //Translate whole scene to -ve z-axis by -35 unit



		/* The Step() function is called every frame of our simulation and
		updates the positions and orientations of physics entities, as well
		as resolving any collisions, etc. */

		PhysicsSource::world.Step(timeStep, velocityIterations, positionIterations);

		GUI::Update_GUI();

		glm::mat4x4 m = glm::mat4x4(1);//glm::mat4x4(glm::vec4(0),glm::vec4(0),glm::vec4(0),glm::vec4(1));//scene matrix

		Transform_Scene(m);

		Render_Scene(m);



		for (Square &sq : Square::game_map)
		{
			b2Vec2 groundPhysicsPosition = sq.squareBody->GetPosition();
			glm::vec3 groundGraphicsPosition;

			groundGraphicsPosition.x = (groundPhysicsPosition.x);
			groundGraphicsPosition.y = (groundPhysicsPosition.y);
			groundGraphicsPosition.z = sq.vertex_data[2];

			sq.Move(groundGraphicsPosition);
		}


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

	//int display_w, display_h;
	//glfwMakeContextCurrent(Graphics::window);
	//glfwGetFramebufferSize(Graphics::window, &display_w, &display_h);
	//glViewport(0, 0, display_w, display_h);
	glClearColor(Graphics::clear_color.x, Graphics::clear_color.y, Graphics::clear_color.z, Graphics::clear_color.w);
	//glClear(GL_COLOR_BUFFER_BIT);
	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	//float ratio;


	//ratio = display_w / (float)display_h;
	//glViewport(0, 0, display_w, display_h);


	////camera perspective
	//glm::mat4x4 p = glm::ortho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

	//glm::mat4x4 mvp = p * m;

	//glUseProgram(Graphics::program);
	//glUniformMatrix4fv(Graphics::mvp_location, 1, GL_FALSE, (const GLfloat*)glm::value_ptr(mvp));
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//glfwMakeContextCurrent(Graphics::window);
	//glfwSwapBuffers(Graphics::window);



	Graphics::Screen_Refresh(m);



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




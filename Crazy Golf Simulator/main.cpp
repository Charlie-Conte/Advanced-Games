#include "main.h"


int main(int argc, char *argv[])
{

	current_state = Graphics::Start();

	if (current_state != 0)
		return  current_state;



	B2_NOT_USED(argc);
	B2_NOT_USED(argv);


		// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// This is our little game loop.
	for (int32 i = 0; i < 60; ++i)
	{
		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world.Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();

		//printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}

	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.


	std::cout << ("K:\Desktop\Advanced-Games\Crazy Golf Simulator\\" "gameSprites.png");
	//Graphics::TextureID = SOIL_load_OGL_texture("K:\Desktop\Advanced-Games\Crazy Golf Simulator\\" "gameSprites2.dds", SOIL_LOAD_AUTO, Graphics::TextureID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);


	current_state = Graphics::Set_Window();

	if (current_state != 0)
		return  current_state;


	GUI::Setup();

	double lasttime = glfwGetTime();

	//Game Loop
	while (!glfwWindowShouldClose(Graphics::window))
	{
		GUI::Update_GUI();

		glm::mat4x4 m = glm::mat4x4(1);//glm::mat4x4(glm::vec4(0),glm::vec4(0),glm::vec4(0),glm::vec4(1));//scene matrix

		Transform_Scene(m);

		Render_Scene(m);




		//frame limit
		while (glfwGetTime() < lasttime + 1.0 / TARGET_FPS);
		lasttime += 1.0 / TARGET_FPS;
	}


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




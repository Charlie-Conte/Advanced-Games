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

	if (enet_initialize() != 0)
	{
		std::cout << "Enet failed to initialise!" << "\n\n";
	}

	/* Much of this will be familiar from the server code. What differs
	is the inclusion of an Peer. This is basically ENet's way of tracking
	what you're connected to. Since our Client will be initialising the
	connection, they need a peer to store information about the server they're
	connecting to. */


	client = enet_host_create(NULL, 1, 2, 0, 0);

	if (client == NULL)
	{
		std::cout << "Client failed to initialise!" << "\n\n";
	}

	enet_address_set_host(&address, "localhost");
	address.port = 1234;


	peer = enet_host_connect(client, &address, 2, 0);

	if (peer == NULL) {
		std::cout << "No available peers for initializing an ENet connection.\n";
	}

	/* To make our lives a little easier, we declare this newPosition variable on
	the heap. It's where the data from our received packet is going to be stored,
	if it reaches us. */

	double lasttime = glfwGetTime();

	float timeStep = 1.0f / 120.0f;
	int velocityIterations = 8;
	int positionIterations = 3;

	glm::vec2* newPosition = new glm::vec2;
	//Game Loop
	while (!glfwWindowShouldClose(Graphics::window))
	{

		Display(timeStep, velocityIterations, positionIterations, lasttime);

		while (enet_host_service(client, &enetEvent, 0) > 0)
		{
			switch (enetEvent.type) {

			case ENET_EVENT_TYPE_CONNECT:

				std::cout << "A server connected from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << ".\n";


				//enetEvent.peer->data = "This is a client";

				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				std::cout << "The server from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << " disconnected \n";

				//enetEvent.peer->data = NULL;

				break;

				/* Again, we're reacting based on the detected event type. In this case, it's
				ENET_EVENT_TYPE_RECEIVE, which means our client has recieved a packet from a
				peer (in this case, the server). After quickly outputting some debug text to
				console to confirm packet receipt, what happens next is the key part.

				Our packet has some intrinsic variables - its data (what it's storing) and its
				dataLength (how much data it's storing). In this case, since we KNOW the packet
				is a Vector2, we can use the memcpy function fairly easily. This is a basic C++
				function which copies a given amount of data from one location to another. In
				this case, it copies TO newPosition FROM data, and it copies an amount dataLength.

				Given what we know about pointer arithmetic, it should be obvious to us that we
				can make these packets more sophisticated. We can make huge packets which hold
				many different kinds of data. We simply include an enumerator at the beginning of
				each data segment, saying what data type it is, and either copy that much data over
				into a variable of that type, or include as the next element of a packet the amount
				of data this variable type needs to copy. This is particularly useful when it comes
				to Part 2 of the coursework, where 'level data' is likely very different to the
				'physics data' you'll have been transmitting for Part 1. */

			case ENET_EVENT_TYPE_RECEIVE:
				std::cout << "Packet received!\n";
				memcpy(newPosition, enetEvent.packet->data, enetEvent.packet->dataLength);
				std::cout << newPosition->x << "," << newPosition->y << "\n";
				//enemy.setPosition(sf::Vector2f(newPosition->x, newPosition->y));
				break;
			}
		}

	}

	if (peer != NULL)
	{
		enet_peer_disconnect_now(peer, 0);
	}

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





		PhysicsSource::world.Step(timeStep, velocityIterations, positionIterations);

		GUI::Update_GUI();

		glm::mat4x4 m = glm::mat4x4(1);//glm::mat4x4(glm::vec4(0),glm::vec4(0),glm::vec4(0),glm::vec4(1));//scene matrix

		Transform_Scene(m);

		Render_Scene(m);



		for (Square &sq : Square::game_map)
		{
			if (glm::distance(glm::vec3(sq.vertex_data[0], sq.vertex_data[1], sq.vertex_data[2]), Square::game_map_hole_0) >= 0.5f)
			{
				b2Vec2 groundPhysicsPosition = sq.squareBody->GetPosition();
				glm::vec3 groundGraphicsPosition = glm::vec3(0, 0, 0);

				if (sq.this_square_type == Square::sprite_ball)
				{
					//std::cout << "The position of the entity is (" << groundPhysicsPosition.x << "," << groundPhysicsPosition.y << ")\n";
					dataPacket = enet_packet_create(&groundPhysicsPosition, sizeof(b2Vec2), ENET_PACKET_FLAG_RELIABLE);
					enet_host_broadcast(client, 0, dataPacket);
				}


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

	//std::cout << PhysicsSource::world.GetGravity().x<<" , "<<PhysicsSource::world.GetGravity().y  <<"\n";
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




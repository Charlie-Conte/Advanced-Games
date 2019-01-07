#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>

#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <GL/glew.h>    // Initialize with glewInit()

#include <GLFW/glfw3.h> 

#include <Box2D/Box2D.h>

#include <enet/enet.h>




using namespace std;


struct Vector2 {
	float x;
	float y;
};

void main()
{
	bool err = glewInit() != GLEW_OK;


	glm::vec2* newPosition = new glm::vec2;


	if (enet_initialize() != 0)
	{
		cout << "Enet failed to initialise!" << "\n\n";
	}

	ENetAddress address;
	ENetHost* server;
	ENetEvent enetEvent;

	ENetPacket* dataPacket;

	address.host = ENET_HOST_ANY;
	address.port = 1234;


	server = enet_host_create(&address, 32, 2, 0, 0);


	if (server == NULL)
	{
		cout << "Server failed to initialise!" << "\n\n";
	}
	
		newPosition->x = 600.0f;
		newPosition->y = 300.0f;

	while (true)
	{


		glfwPollEvents();

		while (enet_host_service(server, &enetEvent, 0) > 0)
		{
			switch (enetEvent.type)
			{
			case ENET_EVENT_TYPE_CONNECT:

				cout << "A client connected from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << ".\n";


				enetEvent.peer->data = "This is a client";

				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				cout << "The client from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << " disconnected \n";

				enetEvent.peer->data = NULL;

				break;
			case ENET_EVENT_TYPE_RECEIVE:
				//std::cout << "Packet received!\n";
				memcpy(newPosition, enetEvent.packet->data, enetEvent.packet->dataLength);
				cout << "The position of the entity is (" << newPosition->x << "," << newPosition->y << ")\n";
				break;
			}
		}






		//dataPacket = enet_packet_create(&newPosition, sizeof(Vector2), ENET_PACKET_FLAG_RELIABLE);
		//enet_host_broadcast(server, 0, dataPacket);
	}


	enet_host_destroy(server);
	atexit(enet_deinitialize);
}





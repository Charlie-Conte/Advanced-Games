#pragma once
#include "GlobalHeaders.h"
#include "PhysicsSource.h"


static float square_size = 1.0f;
class Square
{
public:
	enum SpritesEnum
	{
		sprite_ground = 1,
		sprite_wall = 2,
		sprite_corner_tr = 3,
		sprite_corner_tl = 4,
		sprite_corner_br = 5,
		sprite_corner_bl = 6,
		sprite_ball = 7,
		sprite_hole = 8,
		sprite_arrow_up = 9,
		sprite_arrow_down = 10,
		sprite_arrow_left = 11,
		sprite_arrow_right = 12,
	};

	Square();
	Square(glm::vec3 pos,SpritesEnum squareType);
	void Move(glm::vec3 vector);
	~Square();

	int square_type;
	GLfloat vertex_data[12];
	GLfloat uv_coord_data[8];
	static std::vector<Square> game_map;
	static glm::vec3 game_map_centre;

	// Define the physics.
	b2PolygonShape squareBox;
	b2BodyDef squareBodyDef;
	b2Body* squareBody;
};


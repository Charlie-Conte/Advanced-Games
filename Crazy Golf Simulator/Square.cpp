#include "Square.h"



Square::Square()
{
}

Square::Square(glm::vec3 pos, SpritesEnum squareType)
{
	this_square_type = squareType;

	glm::vec3 tr = pos + glm::vec3(square_size / 2, square_size / 2, 0);
	glm::vec3 tl = pos + glm::vec3(-square_size / 2, square_size / 2, 0);
	glm::vec3 br = pos + glm::vec3(square_size / 2, -square_size / 2, 0);
	glm::vec3 bl = pos + glm::vec3(-square_size / 2, -square_size / 2, 0);

	vertex_data[0] = tl[0];
	vertex_data[1] = tl[1];
	vertex_data[2] = tl[2];
	vertex_data[3] = tr[0];
	vertex_data[4] = tr[1];
	vertex_data[5] = tr[2];
	vertex_data[6] = br[0];
	vertex_data[7] = br[1];
	vertex_data[8] = br[2];
	vertex_data[9] = bl[0];
	vertex_data[10] = bl[1];
	vertex_data[11] = bl[2];





	glm::vec2 trUV;
	glm::vec2 tlUV;
	glm::vec2 brUV;
	glm::vec2 blUV;
	switch (squareType)
	{
	case sprite_ground:

		tlUV = { 0.251,0.001 }; trUV = { 0.499,0.001 };

		blUV = { 0.251,0.249 }; brUV = { 0.499,0.249 };
		break;
	case sprite_wall:

		tlUV = { 0.251,0.251 }; trUV = { 0.499,0.251 };

		blUV = { 0.251,0.499 }; brUV = { 0.499,0.499 };
		break;
	case sprite_arrow_up:

		tlUV = { 0.501,0.749 }; trUV = { 0.749,0.749 };

		blUV = { 0.501,0.999 }; brUV = { 0.749,0.999 };
		break;
	case sprite_arrow_down:

		tlUV = { 0.751,0.501 }; trUV = { 0.999,0.501 };

		blUV = { 0.751,0.749 }; brUV = { 0.999,0.749 };
		break;
	case sprite_arrow_left:

		tlUV = { 0.751,0.749 }; trUV = { 0.999,0.749 };

		blUV = { 0.751,0.999 }; brUV = { 0.999,0.999 };
		break;
	case sprite_arrow_right:

		tlUV = { 0.501,0.501 }; trUV = { 0.749,0.501 };

		blUV = { 0.501,0.749 }; brUV = { 0.749,0.749 };
		break;

	case sprite_corner_tl:

		tlUV = { 0.501,0.001 }; trUV = { 0.749,0.001 };

		blUV = { 0.501,0.249 }; brUV = { 0.749,0.249 };
		break;
	case sprite_corner_tr:

		tlUV = { 0.751,0.001 }; trUV = { 0.999,0.001 };

		blUV = { 0.751,0.249 }; brUV = { 0.999,0.249 };
		break;
	case sprite_corner_br:

		tlUV = { 0.751,0.251 }; trUV = { 0.999,0.251 };

		blUV = { 0.751,0.499 }; brUV = { 0.999,0.499 };
		break;
	case sprite_corner_bl:

		tlUV = { 0.501,0.251 }; trUV = { 0.749,0.251 };

		blUV = { 0.501,0.499 }; brUV = { 0.749,0.499 };
		break;


	case sprite_ball:

		tlUV = { 0.001,0.001 }; trUV = { 0.249,0.001 };

		blUV = { 0.001,0.249 }; brUV = { 0.249,0.249 };
		break;
	case sprite_hole:

		tlUV = { 0.001,0.251 }; trUV = { 0.249,0.251 };

		blUV = { 0.001,0.499 }; brUV = { 0.249,0.499 };
		break;
	default:

		std::cout << "incorrect square type" << std::endl;
		break;

	}

	uv_coord_data[0] = tlUV[0];
	uv_coord_data[1] = tlUV[1];
	uv_coord_data[2] = trUV[0];
	uv_coord_data[3] = trUV[1];
	uv_coord_data[4] = brUV[0];
	uv_coord_data[5] = brUV[1];
	uv_coord_data[6] = blUV[0];
	uv_coord_data[7] = blUV[1];





		// The extents are the half-widths of the box.
		squareBox.SetAsBox(1, 1);




		if (squareType == sprite_wall || squareType == sprite_hole)
		{

			squareBodyDef.type = b2_dynamicBody;
			squareBodyDef.position.Set(pos.x, pos.y);
			squareBody = PhysicsSource::world.CreateBody(&squareBodyDef);
			



			b2FixtureDef fixtureDef;
			fixtureDef.shape = &squareBox;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.0f;
			squareBody->CreateFixture(&fixtureDef);
		}
		else if (squareType == sprite_ball)
		{
			squareBodyDef.type = b2_dynamicBody;
			squareBodyDef.position.Set(pos.x, pos.y);
			squareBody = PhysicsSource::world.CreateBody(&squareBodyDef);
			
			
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &squareBox;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.0f;
			squareBody->CreateFixture(&fixtureDef);
		}
		else
		{

			squareBodyDef.type = b2_staticBody;
			squareBodyDef.position.Set(pos.x, pos.y);
			squareBody = PhysicsSource::world.CreateBody(&squareBodyDef);

		}





}

void Square::Move(glm::vec3 vector)
{


	glm::vec3 tr = vector + glm::vec3(square_size / 2, square_size / 2, 0);
	glm::vec3 tl = vector + glm::vec3(-square_size / 2, square_size / 2, 0);
	glm::vec3 br = vector + glm::vec3(square_size / 2, -square_size / 2, 0);
	glm::vec3 bl = vector + glm::vec3(-square_size / 2, -square_size / 2, 0);

	vertex_data[0] = tl[0];
	vertex_data[1] = tl[1];
	vertex_data[2] = tl[2];
	vertex_data[3] = tr[0];
	vertex_data[4] = tr[1];
	vertex_data[5] = tr[2];
	vertex_data[6] = br[0];
	vertex_data[7] = br[1];
	vertex_data[8] = br[2];
	vertex_data[9] = bl[0];
	vertex_data[10] = bl[1];
	vertex_data[11] = bl[2];

}


Square::~Square()
{
}
std::vector<Square> Square::game_map;
glm::vec3 Square::game_map_centre;
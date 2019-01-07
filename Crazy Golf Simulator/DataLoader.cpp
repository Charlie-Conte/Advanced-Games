#include "DataLoader.h"
using namespace std;


DataLoader::DataLoader()
{
}


DataLoader::~DataLoader()
{
}

void DataLoader::Load_Data()
{
	vector<vector<Square::SpritesEnum>> map;
	float mapSizeX = 0, mapSizeY = 0;
	string line;
	ifstream myfile("level.txt");


	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{

			if (line != "" && line[0] != '#')
			{
				vector<string> itemList = split(line, ',');
				vector<Square::SpritesEnum> MapLine;
				for (string item : itemList)
				{
					if (item == "0")MapLine.push_back(Square::sprite_wall);
					if (item == "1")MapLine.push_back(Square::sprite_ground);
					if (item == "q")MapLine.push_back(Square::sprite_corner_tl);
					if (item == "w")MapLine.push_back(Square::sprite_corner_tr);
					if (item == "a")MapLine.push_back(Square::sprite_corner_bl);
					if (item == "s")MapLine.push_back(Square::sprite_corner_br);	
					if (item == "^")MapLine.push_back(Square::sprite_arrow_up);
					if (item == ">")MapLine.push_back(Square::sprite_arrow_right);
					if (item == "<")MapLine.push_back(Square::sprite_arrow_left);
					if (item == "|")MapLine.push_back(Square::sprite_arrow_down);
					if (item == "p")MapLine.push_back(Square::sprite_hole);
					if (item == "@")MapLine.push_back(Square::sprite_ball);
				}
				map.push_back(MapLine);
				if (MapLine.size() > mapSizeX) mapSizeX = MapLine.size();
			}


			/*std::cout << line << '\n';*/
		}
		myfile.close();
		mapSizeY = map.size();
	}

	else cout << "\nUnable to open file\n";

	float bx, by, bz=0;
	float hx, hy, hz=0;
	float x=0, y=0 ,z=0;
	for (vector<Square::SpritesEnum> row : map)
	{

		for (Square::SpritesEnum item : row)
		{
			z = 0;
			if (item == Square::sprite_ball)
			{
				Square::game_map.push_back(Square(glm::vec3(x, y, z), Square::sprite_ground));
				bx = x;
				by = y;
				bz = 0.02f; 
				
			}
			else if (item == Square::sprite_hole)
			{
				Square::game_map.push_back(Square(glm::vec3(x, y, z), Square::sprite_ground));
				hx = x;
				hy = y;
				hz = 0.01f;
				
			}
			else 
			{
				Square::game_map.push_back(Square(glm::vec3(x, y, z), item));
			}
				
			

			
			x++;
		}
		x = 0;
		y--;
	}
	Square::game_map.push_back(Square(glm::vec3(hx, hy, hz), Square::sprite_hole));
	Square::game_map.push_back(Square(glm::vec3(bx, by, bz), Square::sprite_ball));

	Square::game_map_centre = glm::vec3(mapSizeX / 2.0f, -mapSizeY / 2.0f, 0);
	zoom = glm::sqrt(glm::pow(mapSizeX / 2, 2) + glm::pow(mapSizeY / 2, 2));
}


vector<string>DataLoader::split(string strToSplit, char delimeter)
{
	stringstream ss(strToSplit);
	string item;
	vector<string> splittedStrings;
	while (getline(ss, item, delimeter))
	{
		splittedStrings.push_back(item);
	}
	return splittedStrings;
}

float DataLoader::zoom;
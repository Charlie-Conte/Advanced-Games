#include "main.h"


int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not initialise! SDL Error: " << SDL_GetError() << std::endl;
	}



	std::cout << "Hello World\n";
	std::string input;
	std::getline(std::cin, input);


	return EXIT_SUCCESS;
}

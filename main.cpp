#include"GameBoard.h"
#include<cstdlib>


using namespace std;
using namespace sf;

int main()
{
	//Resolution
	const int window_width = 700;
	const int window_height = 700;

	//Size of grid
	int board_width;
	int board_height;

	//Tiles  variables
	float tile_size;
	int Active_tiles;

	//to seed rand()
	srand(time(0));


	//window
	RenderWindow window(VideoMode(window_width, window_height), "Memory Game");
	window.setFramerateLimit(60);


	//Texts, Main screen and levels logic

	bool MainMenu = true;
	Vector2f mousePosView;
	Gameboard* gameboard = nullptr;
	bool Selected = false;

	Font font;
	Text easy;
	Text med;
	Text hard;
	Text esc;
	Sprite mainmenu;
	Texture tmain;


	tmain.loadFromFile("mainmenu.jpg");
	mainmenu.setTexture(tmain);
	font.loadFromFile("AmaticFont.ttf");

	//Setting up font for escape statement
	esc.setFont(font);
	esc.setCharacterSize(32);
	esc.setPosition(520, 630);
	esc.setFillColor(Color::White);
	esc.setString("Press esc to exit!");
	esc.setStyle(Text::Bold);

	//setting font for easy mode
	easy.setFont(font);
	easy.setCharacterSize(40);
	easy.setPosition(300, 370);
	easy.setFillColor(Color::White);
	easy.setString("EASY");
	easy.setStyle(Text::Bold);

	//setting font for medium mode
	med.setFont(font);
	med.setCharacterSize(40);
	med.setPosition(300, 450);
	med.setFillColor(Color::White);
	med.setString("MEDIUM");
	med.setStyle(Text::Bold);

	//setting font for hard mode
	hard.setFont(font);
	hard.setCharacterSize(40);
	hard.setPosition(300, 530);
	hard.setFillColor(Color::White);
	hard.setString("HARD");
	hard.setStyle(Text::Bold);


	//Main game loop

// Main Game Loop

	while (window.isOpen()) {

		//If statement for showing the main menu

		if (MainMenu) {
			Event event;
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
				}
			}

			mousePosView = window.mapPixelToCoords(Mouse::getPosition(window)); //Gets mouse cursor pos wrt window

			window.clear();
			window.draw(mainmenu);
			window.draw(easy);
			window.draw(med);
			window.draw(hard);
			window.draw(esc);
			window.display();

			//MODES LOGIC

			//IF EASY MODE IS SELECTED
			if (easy.getGlobalBounds().contains(mousePosView) && Mouse::isButtonPressed(Mouse::Left)) {
				board_width = 5;
				board_height = 5;
				tile_size = min(window_width / (float)board_width, window_height / (float)board_height);
				Active_tiles = 4;
				MainMenu = false;
				gameboard = new Gameboard(&window, tile_size, board_width, board_height, Active_tiles);
			}
			//IF MEDIUM MODE IS SELECTED
			else if (med.getGlobalBounds().contains(mousePosView) && Mouse::isButtonPressed(Mouse::Left)) {
				board_width = 6;
				board_height = 6;
				tile_size = min(window_width / (float)board_width, window_height / (float)board_height);
				Active_tiles = 5;
				MainMenu = false;
				gameboard = new Gameboard(&window, tile_size, board_width, board_height, Active_tiles);
			}
			//IF HARD MODE IS SELECTED
			else if (hard.getGlobalBounds().contains(mousePosView) && Mouse::isButtonPressed(Mouse::Left)) {
				board_width = 7;
				board_height = 7;
				tile_size = min(window_width / (float)board_width, window_height / (float)board_height);
				Active_tiles = 6;
				MainMenu = false;
				gameboard = new Gameboard(&window, tile_size, board_width, board_height, Active_tiles);
			}
		}

		//Else statement to run the actual game

		else
		{
			Event event;
			while (window.pollEvent(event)) {

				if (event.type == Event::Closed) {
					window.close();
				}
				// Return to Main Menu if escape key is pressed
				else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {

					system("cls"); //Clears the cmd
					delete gameboard;
					gameboard = nullptr;
					MainMenu = true;
					break;
				}
			}
			//Runs the game
			if (!MainMenu) {
				gameboard->update(window);

				window.clear();
				gameboard->render(window);
				window.display();
			}
		}
	}
	if (gameboard) {
		delete gameboard;
	}
	window.close();
}




#pragma once
#define NOMINMAX
#include"Tile.h"
#include<iostream>
#include<vector>
#include<time.h>
#include<windows.h>
#include"Queue.h"
#include<algorithm>

using namespace std;
using namespace sf;

class Gameboard
{
private:
	RenderWindow* window;
	vector<Tile*> tilesVec;
	vector<int> activeTilesvec;
	vector<int> selectionVec;
	float keyTime, keyTimeMax;
	Vector2f mousePosView;
	float tileSize;
	bool exitGame;
	int tilesSelected;
	int nrOfActiveTiles;
	bool restarting;
	float displayTimer;
	int correct;
	int incorrect;
	float timer;

	//Queues
	Queue activeTiles;
	Queue SelectedTiles;
	Queue dummyQueue;

	//Fonts
	Text CorrectGuess;
	Text IncorrectGuess;
	Font font;

	//Sound

	Sound correctSound;
	Sound incorrectSound;
	SoundBuffer cbuffer;
	SoundBuffer ibuffer;


	//functions:
	void createBoard(const int board_width, const int board_height);
	void randomizeBoard();
	void displayOrder();
	const bool checkSelection();
	void updtaeKeyTime();
	void updateBoard(RenderWindow& window);

	inline const bool checkKeyTime() const { return this->keyTime >= this->keyTimeMax; }
	inline void resetkeyTime() { this->keyTime = 0.f; }


public:
	Gameboard();
	Gameboard(RenderWindow* window, float tile_size , int board_width , int board_height , int nr_active );
	~Gameboard();

	inline const bool checkExit() const { return this->exitGame; }


	void restart();
	void update(RenderWindow& window);
	void render(RenderTarget& target);


};

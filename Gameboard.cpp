#include "Gameboard.h"
#include"Queue.h"

void Gameboard::createBoard(const int board_width, const int board_height)
{
	float x = 0.f;
	float y = 0.f;
	for (size_t i = 0; i < board_height; i++)//To set y coordinates
	{
		for (size_t k = 0; k < board_width; k++)//To set x coordinates
		{
			this->tilesVec.push_back(new Tile(Vector2f(x, y), this->tileSize, false));
			x += this->tileSize;
		}
		y += this->tileSize;
		x = 0.f;
	}
}

//Function Generates pattern for it to be displayed
void Gameboard::randomizeBoard()
{
	activeTilesvec.clear();//to clear all the vector spaces.

	for (size_t i = 0; i < this->tilesVec.size(); i++)
	{
		tilesVec[i]->setActive(false);//initializing with non active tiles, removing this pointer with the replacement of queue
		tilesVec[i]->setColorInactive();//setting all tiles to blue.

	}

	// a vector to store the indexes of Gameboard
	vector<int> index_vector;
	for (size_t i = 0; i < tilesVec.size(); i++)
	{
		index_vector.push_back(i);
		//will iteratively store all the indexes of the tiles.
	}

	int tiles_added = 0;
	int index = -1;


	while (tiles_added != this->nrOfActiveTiles)
	{
		index = rand() % index_vector.size();
		tilesVec[index_vector[index]]->setActive(true);//To activate the status of the tiles tpo be active.
		activeTiles.Enqueue(index_vector[index]);//to show the randomly generated tiles for user to remember 
		dummyQueue.Enqueue(index_vector[index]);//to check if the selected tiles are right


		index_vector.erase(index_vector.begin() + index);
		//To remove the last so it would not be repeated in the random pattern

		tiles_added++;
	}
}

//This function will be used to display the initial screen and show us the pattern for a specific time 
void Gameboard::displayOrder()
{
	//show board
	static int frameRate;
	float phase1 = 50.f;
	float phase2 = 150.f;
	float phase3 = 200.f;

	//Setting the time ranges for patterns to be displayed

	if (displayTimer < phase1) {
		for (size_t i = 0; i < tilesVec.size(); i++) {
			tilesVec[i]->setColorInactive();
		}
	}
	else if (displayTimer >= phase1 && displayTimer < phase2) {
		if (!activeTiles.isEmpty()) {

			// Highlight the current active tile
			tilesVec[activeTiles.peek()]->setColorActive();

			// Increment frame counter to control display duration of the current tile
			frameRate++;
			if (frameRate >= ((phase2 - phase1) / nrOfActiveTiles)) {
				frameRate = 0;
				activeTiles.Dequeue(); // Move to the next active tile
			}
		}
	}
	else if (displayTimer >= phase2 && displayTimer < phase3) {
		for (size_t i = 0; i < tilesVec.size(); i++) {
			tilesVec[i]->setColorInactive();
		}
	}
	else {
		restarting = false;
		frameRate = 0;
	}

	displayTimer += 1.f;  //Change this to change the duration of the board and active tiles being displayed
}

const bool Gameboard::checkSelection()//to check correct incorrect selection of active tiles  
{

	while (!SelectedTiles.isEmpty())
	{
		int temp1, temp2;
		temp1 = SelectedTiles.Dequeue();
		temp2 = dummyQueue.Dequeue();

		if (temp1 != temp2)
			return false;

	}
	return true;


}


void Gameboard::updtaeKeyTime()
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 1.f;
	}
}

void Gameboard::updateBoard(RenderWindow& window)//where the user will guess his/her tiles and results will be shown
{
	if (restarting) {
		displayOrder();
	}
	else
	{
		if (this->tilesSelected < this->nrOfActiveTiles)//runs till = 4(size odf active selected tiles)
		{
			for (size_t i = 0; i < this->tilesVec.size(); i++)
			{
				this->tilesVec[i]->update(this->mousePosView, Mouse::isButtonPressed(Mouse::Left));
				//sends the mouseposition which is a refencrence& in all the functions/classes and checks if
				//the left mouse button is pressed for selection at that tile


				if (this->tilesVec[i]->isPressed() && this->checkKeyTime())//checks keytime so user doesnt spam the button
				{

					//Adding all the functionalities that will occur when the tile is selected by user

					SelectedTiles.Enqueue(i);
					tilesVec[i]->setColorActive();//even if its wrong we have to show the user what has been selected.

					tilesSelected++;
					resetkeyTime();
					//so we can start clicking again.
				}

			}
		}
		//when the tiles are selected this will show results
		else
		{
			timer = 0.f;
			if (checkSelection()) {
				correctSound.play();
				correct++;
				for (size_t i = 0; i < tilesVec.size(); i++) {
					tilesVec[i]->setclorcorect();
				}
				while (timer < 50.f) {
					render(window);
					window.draw(CorrectGuess);
					window.display();
					timer += 1.f;
				}
			}
			else {
				incorrectSound.play();
				incorrect++;
				for (size_t i = 0; i < tilesVec.size(); i++) {
					tilesVec[i]->setcolorincorrect();
				}
				while (timer < 50.f) {
					render(window);
					window.draw(IncorrectGuess);
					window.display();
					timer += 1.f;
				}
			}

			cout << "Score: " << correct << endl;
			restart();
		}
	}
}


Gameboard::Gameboard()
{
	this->window = nullptr;
	this->tileSize = 0.f;
	this->exitGame = false;
	this->keyTimeMax = 0.f;
	this->keyTime = 0.f;
	this->nrOfActiveTiles = 0;
	this->tilesSelected = 0;
	this->restarting = false;
	this->displayTimer = 0.f;
	this->correct = 0;
	this->incorrect = 0;


}

Gameboard::Gameboard(RenderWindow* window, float tile_size, int board_width, int board_height, int nr_active)
	:window(window)
{

	font.loadFromFile("ChrustyRock.ttf");

	this->tileSize = tile_size;
	this->exitGame = false;
	this->keyTimeMax = 10.f;
	this->keyTime = this->keyTimeMax;
	this->nrOfActiveTiles = nr_active;
	this->tilesSelected = 0;
	this->restarting = true;
	this->displayTimer = 0.f;
	this->correct = 0;
	this->incorrect = 0;

	this->createBoard(board_width, board_height);
	this->randomizeBoard();

	//Loading sounds
	cbuffer.loadFromFile("correct.wav");
	ibuffer.loadFromFile("negative.wav");
	incorrectSound.setBuffer(ibuffer);
	correctSound.setBuffer(cbuffer);

	//Setting up font for correct
	CorrectGuess.setFont(font);
	CorrectGuess.setCharacterSize(60);
	CorrectGuess.setPosition(200, 290);
	CorrectGuess.setFillColor(Color::White);
	CorrectGuess.setString("CORRECT");
	CorrectGuess.setStyle(Text::Bold);

	//Setting up font for incorrect
	IncorrectGuess.setFont(font);
	IncorrectGuess.setCharacterSize(60);
	IncorrectGuess.setPosition(170, 290);
	IncorrectGuess.setFillColor(Color::White);
	IncorrectGuess.setString("INCORRECT");
	IncorrectGuess.setStyle(Text::Bold);

}

//Terminating all tiles when game is finished
Gameboard::~Gameboard()
{
	for (size_t i = 0; i < this->tilesVec.size(); i++)
	{
		delete this->tilesVec[i];
	}
}

void Gameboard::restart()
{
	this->tilesSelected = 0;
	this->restarting = true;
	this->displayTimer = 0;
	this->selectionVec.clear();
	this->randomizeBoard();
}

void Gameboard::update(RenderWindow& window)
{
	this->mousePosView = window.mapPixelToCoords(Mouse::getPosition(window));
	//getPosition(window) This retrieves the current position of the mouse cursor in pixels, 
	// relative to the window passed as an argument.
	//but mapPixelToCoords determine where the mouse is located within the game world i.e used when an object is selected etc

	this->updtaeKeyTime();
	this->updateBoard(window);

}

void Gameboard::render(RenderTarget& target)
{
	for (size_t i = 0; i < tilesVec.size(); i++)
	{
		this->tilesVec[i]->render(target);
	}
}
//target is a datatype in sfml that draws us to visio board or the diaplay that we need and in the next step it is displayed in the window
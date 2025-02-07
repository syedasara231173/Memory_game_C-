#pragma once
#define NOMINMAX
#include<iostream>
#include<SFML\Graphics.hpp>
#include<SFML\System.hpp>
#include<SFML\Window.hpp>
#include<SFML/Audio.hpp>


using namespace sf;
using namespace std;
class Tile
{
private:
	RectangleShape shape;
	Color colorInactive;
	Color colorActive;
	Color correct;
	Color incorrect;
	Uint8 alphaIdle;
	Uint8 alphaHover;
	Uint8 alphaPressed;
	bool active;
	bool pressed;

	//Sound

	Sound pop;
	SoundBuffer pbuff;




public:
	Tile();
	Tile(Vector2f position, float size, bool active);
	~Tile();

	inline const bool isPressed()const { return this->pressed; }
	inline const bool isActived()const { return this->active; }

	inline void setActive(bool const active) { this->active = active; }
	inline void setColorInactive() { this->shape.setFillColor(this->colorInactive); }
	inline void setColorActive() { this->shape.setFillColor(this->colorActive); }

	void update(Vector2f& mousePosView, const bool lmb_pressed);
	void render(RenderTarget& target);

	void setclorcorect();
	void setcolorincorrect();

};

#include "Tile.h"

Tile::Tile()
{
	this->active = false;
	this->pressed = false;
	this->alphaIdle = 0;
	this->alphaHover = 0;
	this->alphaPressed = 0;
}

Tile::Tile(Vector2f position, float size, bool active)
{
	this->colorActive = Color(255, 0, 0, 200);//Red
	this->colorInactive = Color(0, 71, 171);//Blue
	this->correct = Color(76, 175, 80);//Green shade for correct
	this->incorrect = Color(229, 57, 53);//red shade for incorrect
	this->shape.setSize(Vector2f(size, size));
	this->shape.setFillColor(this->colorInactive);
	this->shape.setPosition(position);
	this->shape.setOutlineThickness(2.f);
	this->shape.setOutlineColor(Color::White);
	this->active = active;
	this->pressed = false;
	this->alphaIdle = 100;
	this->alphaHover = 255;
	this->alphaPressed = 50;


	pbuff.loadFromFile("pop.wav");
	pop.setBuffer(pbuff);

}

Tile::~Tile()
{
}

void Tile::update(Vector2f& mousePosView, const bool lmb_pressed)
{
	this->pressed = false;
	const Color sc = this->shape.getFillColor();

	if (this->shape.getGlobalBounds().contains(mousePosView))//Hover
	{
		this->shape.setFillColor(Color(sc.r, sc.g, sc.b, this->alphaHover));

		if (lmb_pressed)
		{
			pop.play();
			this->shape.setFillColor(Color(sc.r, sc.g, sc.b, this->alphaPressed));
			this->pressed = true;
		}
	}
	else//Idle
	{
		this->shape.setFillColor(Color(sc.r, sc.g, sc.b, this->alphaIdle));


	}

}

void Tile::render(RenderTarget& target)
{
	target.draw(this->shape);
}

void Tile::setclorcorect()
{
	this->shape.setFillColor(this->correct);
}

void Tile::setcolorincorrect()
{
	this->shape.setFillColor(this->incorrect);
}


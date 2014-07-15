#include <deque>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include "Food.h"

#ifndef SNAKE_H
#define SNAKE_H

class Snake{
public:
	/////Functions
	Snake();
	Snake operator= (Snake &rhs);
	
	//Returns the head of the snake
	sf::RectangleShape front();
	
	//Checks if head overlaps parameter
	bool hit(sf::RectangleShape &rectangle);
	
	//Checks if snake is on top of parameter excluding head
	bool intersects(sf::RectangleShape &rectangle);
	
	//Checks if there is food and if so grows and replaces food
	void eat(Food &food);

	bool outOfBounds(sf::RectangleShape &segment);

	void move();

	void setDirection(std::string new_direction);

	std::string getDirection();
	//sets flag for growth used in move
	void grow();

	void draw(sf::RenderWindow &window);

	int getSize();

	void setSize(int new_size);

private:
	/////Variables
	//deque of body segments from head to tail
	std::deque<sf::RectangleShape> body;
	std::string direction;
	int size; //also used as score
	bool growing;

	/////Traits
	typedef std::deque<sf::RectangleShape>::iterator body_iterator;
};

#endif
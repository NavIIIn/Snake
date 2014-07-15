#include "Food.h"

Food::Food(sf::RenderWindow &window)
:windowptr(&window){
	shape.setSize(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
	resetPosition();
}

sf::RectangleShape &Food::getShape(){
	return shape;
}

void Food::resetPosition(){
	int x = std::rand() % int(WINDOW_WIDTH/SNAKE_SIZE);
	int y = std::rand() % int(WINDOW_HEIGHT/SNAKE_SIZE);
	x *= SNAKE_SIZE;
	y *= SNAKE_SIZE;
	shape.setPosition(x, y);
	draw();
}

void Food::draw(){
	windowptr -> draw(shape);
}

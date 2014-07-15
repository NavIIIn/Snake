#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>

#ifndef FOOD_H
#define FOOD_H

const int SNAKE_SIZE = 20;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class Food {
public:
	Food(sf::RenderWindow &window);
	sf::RectangleShape &getShape();
	void resetPosition();
	void draw();
private:
	sf::RectangleShape shape;
	sf::RenderWindow *windowptr;
};

#endif
#include "Snake.h"

const std::string DEFAULT_DIRECTION = "right";

Snake::Snake()
:growing(false), direction(DEFAULT_DIRECTION), size(1){
	sf::RectangleShape segment(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
	segment.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	body.push_front(segment);
}


Snake Snake::operator=(Snake &rhs){
	if(this != &rhs){
		growing = rhs.growing;
		body = rhs.body;
		direction = rhs.direction;
		size = rhs.size;
	}
	return *this;
}

sf::RectangleShape Snake::front(){
	return body.front();
}

bool Snake::hit(sf::RectangleShape &rectangle){
	return rectangle.getGlobalBounds().intersects(front().getGlobalBounds());
}

bool Snake::intersects(sf::RectangleShape &rectangle){
	bool intersect = false;
	if(size > 3){
		for(body_iterator i = body.begin() + 1;
		i != body.end();
		++i){
			if(rectangle.getGlobalBounds().intersects((*i).getGlobalBounds())){
				intersect = true;
			}
		}
	}
	return intersect;
}

void Snake::eat(Food &food) {
	if(hit(food.getShape()))
		grow();
	
	// until food is in valid location
	while(intersects(food.getShape()) ||  hit(food.getShape())){
		food.resetPosition();
	}
}

bool Snake::outOfBounds(sf::RectangleShape &segment){
	int x = segment.getPosition().x;
	int y = segment.getPosition().y;
	return y < 0
		|| y + SNAKE_SIZE > WINDOW_HEIGHT
		|| x < 0
		|| x + SNAKE_SIZE > WINDOW_WIDTH;
}

void Snake::move(){
	//variables
	sf::RectangleShape new_segment(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
	int x = front().getPosition().x;
	int y = front().getPosition().y;

	//move
	//uncomment regions and change death circumstances -
	//in Main.cpp to have the snake loop around if edge is hit
	if(direction == "up"){
		new_segment.setPosition(x, y - SNAKE_SIZE);
		//if(outOfBounds(new_segment))
		//	new_segment.setPosition(x, WINDOW_HEIGHT - SNAKE_SIZE);
	}
	else if(direction == "down"){
		new_segment.setPosition(x, y + SNAKE_SIZE);
		//if(outOfBounds(new_segment))
		//	new_segment.setPosition(x, 0);
	}
	else if(direction == "left"){
		new_segment.setPosition(x - SNAKE_SIZE, y);
		//if(outOfBounds(new_segment))
		//	new_segment.setPosition(WINDOW_WIDTH - SNAKE_SIZE, y);
	}
	else if(direction == "right"){
		new_segment.setPosition(x + SNAKE_SIZE, y);
		//if(outOfBounds(new_segment))
		//	new_segment.setPosition(0, y);
	}
	//add new segment
	body.push_front(new_segment);
	//remove tail or grow
	if(!growing)
		body.pop_back();
	else{
		growing = false;
		++size;
	}
}

void Snake::setDirection(std::string new_direction){
	direction = new_direction;
}

std::string Snake::getDirection(){
	return direction;
}

void Snake::grow(){
	growing = true;
}

void Snake::draw(sf::RenderWindow &window){
	for(body_iterator i = body.begin();
		i != body.end();
		++i){
			window.draw(*i);
	}
}

int Snake::getSize(){
	return size;
}

void Snake::setSize(int new_size){
	size = new_size;
}

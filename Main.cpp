#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <deque>
#include <queue>
#include <random>
#include "Snake.h"
#include "Food.h"

//Global Variables
//const size_t WINDOW_WIDTH = 800;
//const size_t WINDOW_HEIGHT = 600;
//const int SNAKE_SIZE = 20; //dives evenly with window parameters
const std::string DEFAULT_DIRECTION = "right";
const size_t FONT_SIZE = 30;

int main()
{
	/////Window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake");
	window.setFramerateLimit(10);
	window.setKeyRepeatEnabled(false);

	/////Input Event
	sf::Event event;

	/////States
	bool play = true;
	bool paused = false;
	bool alive = true;

	/////Variables
	//player
	Snake snake;
	//saves score when dead
	int final_score = 0;
	//food item
	Food food(window);

	//keeps track of direction
	//queue allows for two moves to be made simultaneously
	std::string current_direction = DEFAULT_DIRECTION;
	std::queue<std::string> command_queue;

	//Text
	sf::Font font;
	if(!font.loadFromFile("arial.ttf"))
		return 1;
	sf::Text text("0", font);
	text.setCharacterSize(FONT_SIZE);
	text.setPosition(WINDOW_WIDTH/2 - FONT_SIZE/2, WINDOW_HEIGHT/4);
	text.setColor(sf::Color::White);
	std::stringstream score_stream; // converts score to string

	/////Game loop
	while(play)
	{
		/////Events
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::KeyPressed){
				 if(event.key.code == sf::Keyboard::Up
					 && current_direction != "down"){ // prevents 180 turns
					 command_queue.push("up");
					 current_direction = "up";
				 }
				 if(event.key.code == sf::Keyboard::Down
					 && current_direction != "up"){
					 command_queue.push("down");
					 current_direction = "down";
				 }
				 if(event.key.code == sf::Keyboard::Left
					 && current_direction != "right"){
					 command_queue.push("left");
					 current_direction = "left";
				 }
				 if(event.key.code == sf::Keyboard::Right
					 && current_direction != "left"){
					 command_queue.push("right");
					 current_direction = "right";
				 }
				 if(event.key.code == sf::Keyboard::P)
					 paused = !paused;
				 if(event.key.code == sf::Keyboard::Return)
					 alive = true;
			}

			if(event.type == sf::Event::Closed)
				play = false;
		}

		/////Logic
		//ensures the queue is not empty when popped in while loop
		if(command_queue.empty())
			command_queue.push(current_direction);

		//When game is in play
		if(!paused && alive){
			while(!command_queue.empty()){ //executes all commands given in this frame
				current_direction = command_queue.front();
				snake.setDirection(current_direction);
				command_queue.pop();
				snake.eat(food);
				snake.move();
				//If snake is killed
				if(snake.intersects(snake.front())
					||snake.outOfBounds(snake.front())){
					alive = false;
					final_score = snake.getSize();
					snake = Snake();
				}
			}
		}

		//updates score
		score_stream.str("");
		score_stream.clear();
		if(alive)
			score_stream << snake.getSize();
		else
			score_stream << final_score;
		text.setString(score_stream.str());

		/////Render
		window.clear();
		
		if(paused || !alive)
			window.draw(text);
		snake.draw(window);
		food.draw();

		window.display();
	}

	window.close();
	return 1;

}
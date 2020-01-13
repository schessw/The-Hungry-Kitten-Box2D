#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iomanip>
#include <sstream>

#include "Border.h"
#include "GameObject.h"
#include "GameCharacter.h"
#include "GameContactListener.h"

// Function to load font from file
sf::Font loadFont(const std::string& fontFilename = "resources/BurbankBigCondensedBlack.otf")
{
	sf::Font gameFont;
	if (!gameFont.loadFromFile(fontFilename))
	{
		std::cout << "Fail to load font from " << fontFilename << std::endl;
		exit(1);
	}
	return gameFont;
}


// Function to create character


// Main function
int main()
{
	// Timer for fixed update
	float fixedTimeStep = 1.0f / 50.0f; // 50fps
	sf::Clock fixedUpdateClock;
	sf::Clock objectClock;
	float timeElapsedSinceLastFrame = 0;
	srand (time(NULL));
	
	
	// Create game background
	sf::Sprite game_background;
	sf::Texture background_texture;
	if (!background_texture.loadFromFile("resources/background.jpg"))//, sf::IntRect(0, 0, obj_Width_, obj_Height_)))
	{	
		std::cout << "Unable to load game background!" << std::endl;
	}
	
	game_background.setTexture(background_texture);
	
	
	// Create game music
	sf::Music music;
	if (!music.openFromFile("resources/PimPoyPocket.wav"))
	{
		std::cout << "Unable to load game music!" << std::endl;
	}
	
	music.play();
	music.setLoop(true);
	
	
	// Create sound effect
	sf::SoundBuffer buffer1;
	if (!buffer1.loadFromFile("resources/grab.wav"))
        return -1;

	sf::Sound soundEffect1;
	soundEffect1.setBuffer(buffer1);
	
	sf::SoundBuffer buffer2;
	if (!buffer2.loadFromFile("resources/destroy.wav"))
        return -1;

	sf::Sound soundEffect2;
	soundEffect2.setBuffer(buffer2);
	
	
	// Window properties
	int game_width = 800; 
	int game_height = 582;
	int borderThickness = 12;
	sf::RenderWindow window(sf::VideoMode(game_width, game_height), 
							"Assignment 1 - Yoong Shen Wei");
	window.setVerticalSyncEnabled(true);
	window.setActive();
	
	// Text declaration
	sf::Font font = loadFont();
	sf::Text level_label("", font, 36);
	sf::Text score_label("", font, 36);
	sf::Text time_label("", font, 36);
	sf::Text game_over_label("", font, 48);
	
	// Set properties for Time Label
	level_label.setPosition(20, 15);
	level_label.setFillColor(sf::Color::Black);
	
	// Set properties for Score Label
	score_label.setPosition(20, 55);
	score_label.setFillColor(sf::Color::Black);
	
	// Set properties for Score Label
	time_label.setPosition(20, 95);
	time_label.setFillColor(sf::Color::Black);
	
	// Declare game properties
	int game_score = 0;
	int min_score = 50;
	int combo = 1;
	int level = 1;
	float countdown = 10.00; 
	
	// Game clock 
	sf::Clock game_clock;
	sf::Clock obj_drop_clock;
	float obj_drop_interval = 1.5;
	int next_difficulty_time = 10;
	
	// Declare Box2D world configuration
	b2Vec2 gravity(0.0f, 9.81f);
	b2World world(gravity);
	
	// Set contact listener to detect collision
	GameContactListener gameContactListenerInstance;
	world.SetContactListener(&gameContactListenerInstance);
	
	// Define border
	sf::Vector2f horizontalBorderSize(game_width, borderThickness);
	sf::Vector2f topBorderPos(game_width / 2, borderThickness / 2);
	sf::Vector2f bottomBorderPos(game_width / 2, game_height - borderThickness/2);
	Border topBorder(world, horizontalBorderSize, topBorderPos);
	Border bottomBorder(world, horizontalBorderSize, bottomBorderPos);
	
	sf::Vector2f verticalBorderSize(borderThickness, game_height - (borderThickness * 2));
	sf::Vector2f leftBorderPos(borderThickness / 2, game_height / 2);
	sf::Vector2f rightBorderPos(game_width - (borderThickness / 2), game_height / 2);
	Border leftBorder(world, verticalBorderSize, leftBorderPos);
	Border rightBorder(world, verticalBorderSize, rightBorderPos);
	
	// Define a character
	int character_height = 133;
	GameCharacter character(world, sf::Vector2f(game_width / 2, game_height - borderThickness - character_height/2));
	
	// Game object properties
	std::vector<GameObject*> objList;
	std::vector<GameObject*> body_to_remove;
	bool leftKeyPressed = false;
	bool rightKeyPressed = false;
	bool upKeyPressed = false;
	int previousKey = 0; // 0 is left, 1 is right
	float velocity = 5.0f;
	
	while (window.isOpen())
	{	
		sf::Event event;
		
		while (window.pollEvent(event));
		{
			if (event.type == sf::Event::Closed)
                window.close();
		}
		
		// Key movement to left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			if(!leftKeyPressed)
			{
				if(previousKey == 0)
				{
					// move character to left
					character.getBody().SetLinearVelocity(b2Vec2(-velocity, 0.0f));
					leftKeyPressed = true;
					previousKey = 0;
				}
				else 
				{
					velocity = 5.0f;  // change direction, so reset
					character.getBody().SetLinearVelocity(b2Vec2(-velocity, 0.0f));
					leftKeyPressed = true;
					previousKey = 0;					
				}
				velocity = velocity + 5;
			}
		}
		else 
		{
			leftKeyPressed = false;
		}
		
		// Key movement to right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{	
			if(!rightKeyPressed)
			{
				if(previousKey == 1)
				{
					// move character to right
					character.getBody().SetLinearVelocity(b2Vec2(velocity, 0.0f));
					rightKeyPressed = true;
					previousKey = 1;
				}
				else 
				{
					velocity = 5.0f;  // change direction, so reset
					character.getBody().SetLinearVelocity(b2Vec2(velocity, 0.0f));
					rightKeyPressed = true;
					previousKey = 1;					
				}
				velocity = velocity + 5;
			}
		}
		else 
			rightKeyPressed = false;


		if (true)
		{
			sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
			//character.moveCharacter(sf::Vector2f(mouse_pos.x, game_height-78-20));
		}
		
		
		// Update object time
		sf::Time elapsed_obj_drop_time = obj_drop_clock.getElapsedTime();
		float obj_time = elapsed_obj_drop_time.asSeconds();
		
		// increase the difficulty every 10 seconds!
		if (obj_time > next_difficulty_time)
		{
			if(game_score >= min_score)
			{
				// update new difficulty details
				game_clock.restart();
				level = level + 1;
				min_score = min_score * 2;
				
				obj_drop_interval = obj_drop_interval * 0.9;
				next_difficulty_time = next_difficulty_time + 10;
				std::cout << "drop time: " << next_difficulty_time << std::endl;
				std::cout << "interval: " << obj_drop_interval << std::endl;
			}
			else
			{
				//window.close();
				/*
				if(window.waitEvent(event))
				{
					// Key movement to right
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
					{	
						window.close();
					}
				}
				*/
				
	
				// Set properties for Time Label	
				game_over_label.setFillColor(sf::Color::Black);
				game_over_label.setString("Game Over!!!");
				game_over_label.setPosition(300, 260);
				//window.draw(game_over_label);
			}
		}
		
		// Update game time
		sf::Time elapsed_game_time = game_clock.getElapsedTime();
		float game_time = elapsed_game_time.asSeconds();
		
		// drop the object if the time interval is reached
		if(objectClock.getElapsedTime().asSeconds() >= obj_drop_interval)
		{
			sf::Vector2f pos = sf::Vector2f(rand() % 700 + 80, game_height * 0.15);
			objList.push_back(new GameObject(world, pos));
			objectClock.restart();
		}
		
		
		// We get the time elapsed since last frame and add it to timeElapsedSinceLastFrame
		timeElapsedSinceLastFrame += fixedUpdateClock.restart().asSeconds();

		// If sufficient time has elapsed, we update the physics
		if(timeElapsedSinceLastFrame >= fixedTimeStep)
		{
			// Step is used to update physics position/rotation
			world.Step(fixedTimeStep, //update frequency
                    8,                //velocityIterations
                    3                 //positionIterations  
                   );

			
			// update body that requires physics
			character.update();
			topBorder.update();
			bottomBorder.update();
			leftBorder.update();
			rightBorder.update();
			
			// detect collision and update the score
			for(int i = 0; i < objList.size(); i++)
			{
				std::string condition = objList[i]->update();
				
				if(condition == "score")
				{
					std::cout << "you scored!" << std::endl;
					world.DestroyBody(objList[i]->getBody());
					objList.erase(objList.begin() + i);
					game_score = game_score + 10*(level)*(combo++);
					soundEffect1.play();
				}
				else if(condition == "destroy")
				{
					std::cout << "you lose a life!" << std::endl;
					world.DestroyBody(objList[i]->getBody());
					objList.erase(objList.begin() + i);
					combo = 1;
					soundEffect2.play();
				}
			}
			
			//

			// timeElapsedSinceLastFrame can be higher than fixedTimeStep,
			// so we deduct timeElapsedSinceLastFrame with fixedTimeStep
			timeElapsedSinceLastFrame -= fixedTimeStep;
		}
		
		window.setActive();
		window.draw(game_background);
		level_label.setString("Level " + std::to_string(level) + ", Min score: " + std::to_string(min_score));
		score_label.setString("Score: " + std::to_string(game_score));
		
		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << countdown - game_time;
		std::string time_remaining = stream.str();
		time_label.setString("Time remaining: " + time_remaining);
		
		if(countdown - game_time < -1.0)
		{
			window.close();
		}
		
		window.draw(topBorder.getBorder());
		window.draw(bottomBorder.getBorder());
		window.draw(leftBorder.getBorder());
		window.draw(rightBorder.getBorder());
		
		window.draw(level_label);
		window.draw(score_label);
		window.draw(time_label);
		window.draw(character.getCharacter());
		window.draw(game_over_label);
		
		for(int i = 0; i < objList.size(); i++)
		{
			window.draw(objList[i]->getShape());
		}
		
		window.display();
	}
	
	return 0;
}
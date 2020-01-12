#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Border.h"
#include "GameObject.h"
#include "GameCharacter.h"

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
	// COPYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY //
	float fixedTimeStep = 0.02f; // 50 times per second
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
	
	
	
	
	
	
	
	
	
	
	
	// Window properties
	int game_width = 800; 
	int game_height = 582;
	int borderThickness = 20;
	sf::RenderWindow window(sf::VideoMode(game_width, game_height), 
							"Assignment 1 - Yoong Shen Wei");
	window.setVerticalSyncEnabled(true);
	window.setActive();
	
	// Text declaration
	sf::Font font = loadFont();
	sf::Text life_label("", font, 36);
	sf::Text score_label("", font, 36);
	sf::Text time_label("", font, 36);
	
	// Set properties for Time Label
	life_label.setPosition(20, 15);
	life_label.setFillColor(sf::Color::Black);
	
	// Set properties for Score Label
	score_label.setPosition(20, 55);
	score_label.setFillColor(sf::Color::Black);
	
	// Set properties for Score Label
	time_label.setPosition(20, 95);
	time_label.setFillColor(sf::Color::Black);
	
	// Declare game properties
	int game_score = 0;
	int remaining_life = 5;
	int countdown = 10;
	
	// Game clock 
	sf::Clock game_clock;
	sf::Clock obj_drop_clock;
	float obj_drop_interval = 1.5;
	int next_difficulty_time = 10;
	
	// Declare Box2D world configuration
	b2Vec2 gravity(0.0f, 9.81f);
	b2World world(gravity);
	
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
	int characterDirection = 0;  // 0 is left, 1 is right
	
	// Game object properties
	std::vector<GameObject> objList;
	bool leftMousePressed = false;
	
	while (window.isOpen())
	{	
		sf::Event event;
		while (window.pollEvent(event));
		{
			switch (event.type)
			{
				case sf::Event::Closed: 
				{
					window.close();
					break;
				}
				case sf::Event::KeyPressed:
				{
					break;
				}
				case sf::Event::Resized:
				{
					sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
					window.setView(sf::View(visibleArea));
				}
			}
		}
		
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			// move character to left
			character.getBody().SetLinearVelocity(b2Vec2(-5.0f, 0.0f));
			characterDirection = 0;
			
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			// move character to right
			character.getBody().SetLinearVelocity(b2Vec2(5.0f, 0.0f));
			characterDirection = 1;
			// https://bit.ly/35jWnKW
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			// move character to up
			character.getBody().SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			// https://bit.ly/35jWnKW
		}
		
		
		/*
		if (true)
		{
			sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
			//character.moveCharacter(sf::Vector2f(mouse_pos.x, game_height-78-20));
		}
		*/
		
		
		// Update game time
		sf::Time elapsed_game_time = game_clock.getElapsedTime();
		sf::Time elapsed_obj_drop_time = obj_drop_clock.getElapsedTime();
		
		float obj_time = elapsed_obj_drop_time.asSeconds();
		float game_time = elapsed_game_time.asSeconds();
		// std::cout << obj_time << std::endl;
		
		// increase the difficulty every 10 seconds!
		if (obj_time > next_difficulty_time)
		{
			obj_drop_interval = obj_drop_interval * 0.9;
			next_difficulty_time = next_difficulty_time + 10;
			std::cout << "drop time: " << next_difficulty_time << std::endl;
			std::cout << "interval: " << obj_drop_interval << std::endl;
		}
		
		// drop the object if the time interval is reached
		if(objectClock.getElapsedTime().asSeconds() >= obj_drop_interval)
		{
			sf::Vector2f pos = sf::Vector2f(rand() % 750 + 25, game_height * 0.1);
			GameObject r(world, pos);
			std::cout << pos.x << std::endl;
			std::cout << pos.y << std::endl;
			objList.push_back(r);
			objectClock.restart();
			std::cout << "Object dropped!!" << std::endl;
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

			
			// update that requires physics
			character.update();
			topBorder.update();
			bottomBorder.update();
			leftBorder.update();
			rightBorder.update();
			
			for(int i = 0; i < objList.size(); i++)
			{
				objList[i].update();
			}

			// timeElapsedSinceLastFrame can be higher than fixedTimeStep,
			// so we deduct timeElapsedSinceLastFrame with fixedTimeStep
			timeElapsedSinceLastFrame -= fixedTimeStep;
		}
		
		
		
		
		
		
		
	
		window.draw(game_background);
		life_label.setString("Remaining life: " + std::to_string(remaining_life));
		score_label.setString("Score: " + std::to_string(game_score));
		time_label.setString("Time remaining: " + std::to_string(game_time));
		
		window.draw(topBorder.getBorder());
		window.draw(bottomBorder.getBorder());
		window.draw(leftBorder.getBorder());
		window.draw(rightBorder.getBorder());
		
		window.draw(life_label);
		window.draw(score_label);
		window.draw(time_label);
		window.draw(character.getCharacter());
		
		for(int i = 0; i < objList.size(); i++)
		{
			window.draw(objList[i].getShape());
		}
		
		world.DrawDebugData();
		window.display();
		
	}
	
	return 0;
}
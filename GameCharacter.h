#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

class GameCharacter
{
 private:
	sf::Sprite character_;
	sf::Texture character_Texture_;
	b2Body* characterBody_;
	b2BodyDef characterBodyDef_;
	b2PolygonShape characterBodyShape_;
	b2FixtureDef characterBodyFixtureDef_;

 public:
	GameCharacter(b2World& world, sf::Vector2f pos);
	void update();
	void moveCharacter(sf::Vector2f pos);
	b2Body& getBody();
	sf::Sprite& getCharacter();
};

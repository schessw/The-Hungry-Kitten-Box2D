#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

class Border
{
 private:
	sf::RectangleShape border_;
	b2Body* body_;
	b2BodyDef bodyDef_;
	b2PolygonShape bodyShape_;
	b2FixtureDef bodyFixtureDef_;

 public:
	Border(b2World& world, sf::Vector2f size, sf::Vector2f position);
	void update();
	sf::Shape& getBorder();
};

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

class GameObject
{
 private:
	sf::Sprite obj_;
	sf::Texture obj_Texture_;
	int obj_Width_ = 80;
	int obj_Height_ = 56;
	b2Body* body_;
	b2BodyDef bodyDef_;
	b2PolygonShape bodyShape_;
	b2FixtureDef bodyFixtureDef_;

 public:
	GameObject(b2World& world, sf::Vector2f position);
	void update();
	sf::Sprite& getShape();
};

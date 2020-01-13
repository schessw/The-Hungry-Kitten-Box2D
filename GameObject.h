#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <string>

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
	struct bodyUserData {
		std::string entityType = "food";
		bool isCollided = false;
		bool isCollected = false;
		bool hasUpdated = false;
	};

 public:
	GameObject(b2World& world, sf::Vector2f position);
	std::string update();
	b2Body* getBody();
	sf::Sprite& getShape();
};

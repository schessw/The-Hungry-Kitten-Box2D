#include "GameCharacter.h"

// Box2D uses meters for simulation, so we need to set how many pixels representing one meter
// We prefer a 2^n value (e.g. 1,2,4,8,16,32,64 etc) because of reasons
// Why? Refer to Computer Graphics
static const float PIXEL_PER_METER = 32.0f;

GameCharacter::GameCharacter(b2World& world, sf::Vector2f pos)
{
	// Define character properties
	float character_width = 100.f;
	float character_height = 133.f;
	
	// Define sprite texture
	if (!character_Texture_.loadFromFile("resources/cat_character.png", sf::IntRect(0, 0, character_width, character_height)))
	{	
		std::cout << "Unable to load game character!" << std::endl;
	}
	
	character_.setOrigin(sf::Vector2f(character_width / 2, character_height / 2));
	character_.setTexture(character_Texture_, true);
	
	//define object body
	//characterBodyDef_.type = b2_kinematicBody;
	characterBodyDef_.type = b2_dynamicBody;
	characterBodyDef_.position.Set(pos.x / PIXEL_PER_METER, pos.y / PIXEL_PER_METER);
	
	
	// define object shape
	characterBodyShape_.SetAsBox((character_width / 2)/ PIXEL_PER_METER, (character_height / 2) / PIXEL_PER_METER);
	
	characterBodyFixtureDef_.shape = &characterBodyShape_;
	characterBodyFixtureDef_.density = 0.3f;
	characterBodyFixtureDef_.friction = 0.0f;
	
	characterBody_ = world.CreateBody(&characterBodyDef_);
	characterBody_->CreateFixture(&characterBodyFixtureDef_);
	std::cout << "Mass: " << characterBody_->GetMass() << std::endl;
}

void GameCharacter::update()
{
	// Box2D uses radians for rotation, SFML uses degree
    character_.setRotation( characterBody_->GetAngle() * 180/b2_pi);
    character_.setPosition( characterBody_->GetPosition().x*PIXEL_PER_METER, characterBody_->GetPosition().y*PIXEL_PER_METER);
}

void GameCharacter::moveCharacter(sf::Vector2f pos)
{
	// Box2D uses radians for rotation, SFML uses degree
    character_.setPosition( pos.x/PIXEL_PER_METER, pos.y/PIXEL_PER_METER);
}


b2Body& GameCharacter::getBody()
{
	return *characterBody_;
}

sf::Sprite& GameCharacter::getCharacter()
{
	return character_;
}
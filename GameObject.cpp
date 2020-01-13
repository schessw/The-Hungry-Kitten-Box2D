#include "GameObject.h"

// Box2D uses meters for simulation, so we need to set how many pixels representing one meter
// We prefer a 2^n value (e.g. 1,2,4,8,16,32,64 etc) because of reasons
static const float PIXEL_PER_METER = 32.0f;

GameObject::GameObject(b2World& world, sf::Vector2f position)
{
	// Define sprite texture
	if (!obj_Texture_.loadFromFile("resources/food.png", sf::IntRect(0, 0, obj_Width_, obj_Height_)))
	{	
		std::cout << "Unable to load game object!" << std::endl;
	}
	
	obj_.setOrigin(sf::Vector2f(obj_Width_ / 2, obj_Height_ / 2));

	//define object body
	bodyDef_.position.Set(position.x/PIXEL_PER_METER, position.y/PIXEL_PER_METER);
	bodyDef_.type = b2_dynamicBody;
	
	
	// define object shape
	bodyShape_.SetAsBox((obj_Width_/2)/PIXEL_PER_METER, (obj_Height_/2)/PIXEL_PER_METER);

	bodyFixtureDef_.shape = &bodyShape_;
	bodyFixtureDef_.density = 0.01f;
	bodyFixtureDef_.friction = 0.5f;
	// bodyFixtureDef_.restitution = 0.5f;

	body_ = world.CreateBody(&bodyDef_);
	body_->CreateFixture(&bodyFixtureDef_);
	body_->SetUserData(new bodyUserData);
	//std::cout << "Mass of object: " << body_->GetMass() << std::endl;
}


std::string GameObject::update()
{
	// Box2D uses radians for rotation, SFML uses degree
    //obj_.setRotation( body_->GetAngle() * 180 / b2_pi);
    obj_.setPosition( body_->GetPosition().x * PIXEL_PER_METER, body_->GetPosition().y * PIXEL_PER_METER);

	// check
	void* userData = body_->GetUserData();
	if((static_cast<bodyUserData*>(userData))->hasUpdated == false)
	{
		if((static_cast<bodyUserData*>(userData))->isCollided == true)
		{
			if((static_cast<bodyUserData*>(userData))->isCollected == false)
			{
				(static_cast<bodyUserData*>(userData))->hasUpdated = true;
				body_->SetUserData(userData);
				return "destroy";
			}
			else
			{
				(static_cast<bodyUserData*>(userData))->hasUpdated = true;
				body_->SetUserData(userData);
				return "score";
			}
		}
		else
		{
			return "";
		}
	}
	else
	{
		return "";
	}
	
}

b2Body* GameObject::getBody()
{
	return body_;
}

sf::Sprite& GameObject::getShape()
{
	obj_.setTexture(obj_Texture_);
	return obj_;
}

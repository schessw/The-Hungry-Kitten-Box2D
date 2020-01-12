#include "Border.h"

static const float PIXEL_PER_METER = 32.0f;

Border::Border(b2World& world, sf::Vector2f size, sf::Vector2f position)
{
	border_ = sf::RectangleShape(size);
	border_.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	border_.setFillColor(sf::Color(0, 0, 0, 255));
	border_.setOutlineThickness(0);
	border_.setOutlineColor(sf::Color(0, 0, 0, 255));
	
	bodyDef_.position = b2Vec2(position.x/PIXEL_PER_METER, position.y/PIXEL_PER_METER);
	bodyDef_.type = b2_staticBody;
	
	bodyShape_.SetAsBox((size.x / 2) / PIXEL_PER_METER, (size.y / 2) / PIXEL_PER_METER);

	bodyFixtureDef_.shape = &bodyShape_;
	bodyFixtureDef_.density = 1.0f;
	bodyFixtureDef_.friction = 0.5f;

	body_ = world.CreateBody(&bodyDef_);
	body_->CreateFixture(&bodyFixtureDef_);
}

void Border::update()
{
	// Box2D uses radians for rotation, SFML uses degree
    border_.setRotation( body_->GetAngle() * 180 / b2_pi);
    border_.setPosition( body_->GetPosition().x*PIXEL_PER_METER, body_->GetPosition().y*PIXEL_PER_METER);
}

sf::Shape& Border::getBorder()
{
	return border_;
}
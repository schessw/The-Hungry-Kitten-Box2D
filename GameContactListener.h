#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>

class GameContactListener : public b2ContactListener
{
	public:
		void BeginContact(b2Contact* contact);
		void EndContact(b2Contact* contact);
		void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
		/*
	private:
		std::vector<b2Body*> food_collected;
		std::vector<b2Body*> food_destroyed;
		int num_collected = 0;
		int num_destroyed = 0;
		*/
};
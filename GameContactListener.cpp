#include "GameContactListener.h"
#include <vector>

void GameContactListener::BeginContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	void* bodyAUserData = bodyA->GetUserData();
    void* bodyBUserData = bodyB->GetUserData();
	
	

	
	
	struct bodyUserData {
		std::string entityType;
		bool isCollided;
		bool isCollected;
		bool hasUpdated;
	};
	bodyUserData* data = new bodyUserData;
	
	// if cat collides with food, get score!
	if(((static_cast<bodyUserData*>(bodyAUserData))->entityType == "cat" && 
		(static_cast<bodyUserData*>(bodyBUserData))->entityType == "food") || 
		((static_cast<bodyUserData*>(bodyAUserData))->entityType == "food" && 
		(static_cast<bodyUserData*>(bodyBUserData))->entityType == "cat"))
	{
		if ((static_cast<bodyUserData*>(bodyAUserData))->entityType == "food")
		{
			//food_collected.push_back(bodyA);
			(static_cast<bodyUserData*>(bodyAUserData))->isCollided = true;
			(static_cast<bodyUserData*>(bodyAUserData))->isCollected = true;
			bodyA->SetUserData(bodyAUserData);
		}
		else
		{
			//food_collected.push_back(bodyB);
			(static_cast<bodyUserData*>(bodyBUserData))->isCollided = true;
			(static_cast<bodyUserData*>(bodyBUserData))->isCollected = true;
			bodyB->SetUserData(bodyBUserData);
		}
		//num_collected = num_collected + 1;
	}
	
	// if food collides with border, lose life!
	else if(((static_cast<bodyUserData*>(bodyAUserData))->entityType == "border" && 
		(static_cast<bodyUserData*>(bodyBUserData))->entityType == "food") || 
		((static_cast<bodyUserData*>(bodyAUserData))->entityType == "food" && 
		(static_cast<bodyUserData*>(bodyBUserData))->entityType == "border"))
	{
		if ((static_cast<bodyUserData*>(bodyAUserData))->entityType == "food")
		{
			//food_destroyed.push_back(bodyA);
			(static_cast<bodyUserData*>(bodyAUserData))->isCollided = true;
			(static_cast<bodyUserData*>(bodyAUserData))->isCollected = false;
			bodyA->SetUserData(bodyAUserData);
		}
		else
		{
			//food_destroyed.push_back(bodyB);
			(static_cast<bodyUserData*>(bodyBUserData))->isCollided = true;
			(static_cast<bodyUserData*>(bodyBUserData))->isCollected = false;
			bodyB->SetUserData(bodyBUserData);
		}
		//num_destroyed = num_destroyed + 1;
	}
	
}

void GameContactListener::EndContact(b2Contact* contact)
{
	/*
	// Sort duplicates in the array
	std::sort( food_collected.begin(), food_collected.end() );
	food_collected.erase( unique( food_collected.begin(), food_collected.end() ), food_collected.end() );
	
	std::sort( food_destroyed.begin(), food_destroyed.end() );
	food_destroyed.erase( unique( food_destroyed.begin(), food_destroyed.end() ), food_destroyed.end() );
	
	// Destroy the bodies, skipping duplicates.
	int i = 0;
	while (i < num_collected)
	{
		b2Body* b1 = food_collected[i++];
		while (i < num_collected && food_collected[i] == b1)
		{
			++i;
		}
		world->DestroyBody(b1);
		std::cout << "kill for score" << std::endl;
	}
	
	int j = 0;
	while (j < num_destroyed)
	{
		b2Body* b2 = food_destroyed[j++];
		while (j < num_destroyed && food_destroyed[j] == b2)
		{
			++j;
		}
		world->DestroyBody(b2);
		std::cout << "kill for life" << std::endl;
	}
	*/
}

void GameContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

void GameContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}

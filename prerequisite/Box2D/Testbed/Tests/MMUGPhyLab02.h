/*
MMUGPhyLab02.h
Objective: Intro to Box2D's World, Bodies and Fixtures
TGD2251 Game Physics
Copyright (C) 2009-2018 by Ya-Ping Wong <ypwong@mmu.edu.my>
Faculty of Computing & Informatics
Multimedia University
INSTRUCTIONS
============
Just experiment with the program and try to extend the code
*/
#ifndef MMUGPHYLAB02_H
#define MMUGPHYLAB02_H
#define DEG_TO_RAD 0.0174532925199432957f
#define RAD_TO_DEG 57.295779513082320876f
class MMUGPhyLab02 : public Test
{
private:
b2Body* myStaticBody;
b2Body* myDynamicBody;
b2Body* myKinematicBody;
public:
MMUGPhyLab02()
{
// ---- create static body -----------
//body definition object
b2BodyDef myBodyDef;
//specify that it would be a static body
myBodyDef.type = b2_staticBody;
//set the starting position
myBodyDef.position.Set(0, 6);
//set the starting angle
myBodyDef.angle = 0;
//m_world is inherited from class Test
//m_world is a pointer to a b2World object
//ask the world object to create a body using the body definition
myStaticBody = m_world->CreateBody(&myBodyDef);
// ---- create dynamic body ----------
//specify that it would be a dynamic body
//note: we are reusing the definition object here
myBodyDef.type = b2_dynamicBody;
//set the starting position
myBodyDef.position.Set(0, 30);
//ask the same world object to create another body using the body definition
myDynamicBody = m_world->CreateBody(&myBodyDef);
// ---- create kinematic body ----------
myBodyDef.type = b2_kinematicBody;
myBodyDef.position.Set(-18, 11);
myKinematicBody = m_world->CreateBody(&myBodyDef);
//move right 1 unit per second
myKinematicBody->SetLinearVelocity( b2Vec2( 1, 0 ) );
//1 turn per second counter-clockwise
myKinematicBody->SetAngularVelocity( 360 * DEG_TO_RAD );
// -------- create fixture -----------
//fixture definition object
b2FixtureDef myFixtureDef;
b2PolygonShape myBoxShape;
myBoxShape.SetAsBox(5,5);
//set fixture shape and density
myFixtureDef.shape = &myBoxShape;
//ask body to add fixture using fixture definition object
myStaticBody->CreateFixture(&myFixtureDef);
b2CircleShape myCircleShape;
myCircleShape.m_radius = 3.0f;
//re-using fixture definition object
myFixtureDef.shape = &myCircleShape;
myFixtureDef.density = 5;
//ask body to add fixture using fixture definition object
myDynamicBody->CreateFixture(&myFixtureDef);
b2PolygonShape myWeirdShape;
//myWeirdShape.SetAsBox(5,5);
const int numOfPoints = 5;
//last vertex will join back to first vertex
//This assumes the vertices define a convex polygon.
//It is assumed that the exterior is the right of each edge
float32 coord[][2] = { {4,0}, {2,2},{-2,2},
{-2,-2},{2,-2} };
b2Vec2 myVec2[numOfPoints];
for (int i=0; i<numOfPoints; ++i)
{
myVec2[i].Set(coord[i][0],coord[i][1]);
}
myWeirdShape.Set(myVec2, numOfPoints);
myFixtureDef.shape = &myWeirdShape;
myFixtureDef.density = 10;
myKinematicBody->CreateFixture(&myFixtureDef);
}
void Step(Settings* settings)
{
//run the default physics and rendering of superclass Test
Test::Step(settings);
//show some text in the main screen
m_debugDraw.DrawString(5, m_textLine,
"MMU Game Physics Lab is cleared for launch!");
m_textLine += 15;
}
static Test* Create()
{
return new MMUGPhyLab02;
}
};
#endif
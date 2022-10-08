#include "stdafx.h"
#include "Wall.h"


Wall::Wall(TYPE type, float height, float posY, float generatedTime) :
	m_type(type),
	m_height(height),
	m_posY(posY),
	m_generatedTime(generatedTime)
{

}

Wall::~Wall()
{

}

//void Wall::update()
//{
//
//}
//
//
//void Wall::draw()
//{
//
//}


//float Wall::GetBottomPosY(float currentTime)
//{
//	float speed = 1.0f;
//	return m_generatedPosY + (currentTime - m_generatedTime) * speed;
//}

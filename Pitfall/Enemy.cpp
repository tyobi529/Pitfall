#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy() :
	m_isValid(false),
	m_endTime(0),
	m_speed(0),
	m_heightNum(0),
	//m_count(0),
	//m_startTime(0),
	m_pos(Vec3(0, 0, 0))
	//m_isHit(false)
{

}

Enemy::~Enemy() {

}

//void Enemy::Init(int heightNum, int speed, float startTime)
//{
//	m_isValid = true;
//	m_heightNum = heightNum;
//	m_speed = speed;
//	//m_startTime = startTime;
//	//m_count = Define::START_POS_X - Define::END_POS_X;
//	//m_endTime = startTime + m_count / speed;
//
//	//m_isHit = false;
//	m_pos = Vec3(Define::START_POS_X, Define::BOTTOM_POS_Y + heightNum * Define::BLOCK_SIZE, 0.0f);
//}

void Enemy::Init(float speed)
{
	m_isValid = true;
	m_speed = speed;

	//m_pos = Vec3(Define::START_POS_X, Define::BOTTOM_POS_Y + heightNum * Define::BLOCK_SIZE, 0.0f);
}

void Enemy::UpdatePos(float difTime)
{
	if (!m_isValid)
		return;

	float x = Define::END_POS_X + difTime * m_speed;
	m_pos = Vec3(x, Define::BOTTOM_POS_Y + m_heightNum * Define::BLOCK_SIZE, 0.0f);
}

void Enemy::update()
{
	//if (!m_isValid)
	//	return;

	////float x = Define::END_POS_X - (m_endTime - Scene::Time()) / (m_endTime - m_startTime) * (Define::END_POS_X - Define::START_POS_X);
	//float x = Define::END_POS_X + (m_endTime - Scene::Time()) * m_speed;
	//m_pos = Vec3(x, Define::BOTTOM_POS_Y + m_heightNum * Define::BLOCK_SIZE, 0.0f);
}

void Enemy::draw() const
{
	if (!m_isValid)
		return;

	Box{ m_pos, 1.0f }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
}

void Enemy::CountDown()
{
	//m_count -= m_speed;

	//if (m_count < 0)
	//	assert(false);

	//if (m_count == 0)
	//{
	//	m_isHit = true; //count=0ならプレイヤーにぶつかる
	//}
}


void Enemy::Explosion()
{
	//if (!m_isHit)
	//{
	//	assert(false);
	//	return;
	//}

	//m_isHit = false;
	//m_isValid = false;
	////消える演出

}



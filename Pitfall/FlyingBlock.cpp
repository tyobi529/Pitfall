#include "stdafx.h"
#include "FlyingBlock.h"

#define SIZE Define::BLOCK_SIZE

FlyingBlock::FlyingBlock() : Block()
	, m_state(STATE_END)
	, m_startPos(Vec3(0, 0, 0))
	, m_startTime(0)
{

}


FlyingBlock::~FlyingBlock()
{
}

void FlyingBlock::FlyingInit(Vec3 startPos)
{
	m_state = STATE_MOVE_SLOW;
	m_startPos = startPos;
	m_startTime = Scene::Time();
	SetPosition(startPos.x, startPos.y, startPos.z);
	SetSize(1.0f);
}

void FlyingBlock::update()
{
	if (m_state == STATE_END) return;

	float deltaTime = Scene::Time() - m_startTime;

	float moveX = 0;
	if (deltaTime < 1)
	{
		moveX += deltaTime * 0.3f;
	}
	else
	{
		//1秒はゆっくり
		moveX += 1.0f * 0.3f;
		//残り
		float restTime = deltaTime - 1.0f;
		moveX += restTime * 5.0f;
	}

	SetPosition(m_startPos.x - moveX);

	//float deltaTime = Scene::DeltaTime();


	//if (m_state == STATE_MOVE_SLOW)
	//{
	//	//1秒はゆっくり
	//	float moveX = deltaTime * 0.3f;

	//	MovePosition(-moveX, -moveX / 5);
	//}
	//else if (m_state == STATE_MOVE)
	//{
	//	float moveX = deltaTime * 5.0f;

	//	MovePosition(-moveX, -moveX / 5);
	//}

}


void FlyingBlock::updateEverySecond()
{
	if (m_state == STATE_MOVE_SLOW)
	{
		m_state = STATE_MOVE;
	}
}

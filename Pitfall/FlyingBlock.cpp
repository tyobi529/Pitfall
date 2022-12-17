#include "stdafx.h"
#include "FlyingBlock.h"

#define SIZE Define::BLOCK_SIZE

FlyingBlock::FlyingBlock() : Block()
	, m_state(STATE_END)
	, m_startPos(Vec3(0, 0, 0))
	, m_startTime(0)
	, m_rotSpeed(Vec3(0, 0, 0))
{

}


FlyingBlock::~FlyingBlock()
{
}

void FlyingBlock::FlyingInit(Vec3 startPos)
{
	SetType(BLOCK_FLYING);
	m_state = STATE_MOVE_SLOW;
	m_startPos = startPos;
	m_startTime = Scene::Time();
	SetPosition(startPos.x, startPos.y, startPos.z);
	SetSize(1.0f);
	//回転速度
	float x = Random<float>(1.0, 2.0);
	if (RandomBool()) x = -x;
	float y = Random<float>(4.0, 6.0);
	if (RandomBool()) y = -y;
	float z = Random<float>(1.0, 2.0);
	if (RandomBool()) z = -z;
	m_rotSpeed = Vec3(x, y, z);
}

void FlyingBlock::update()
{
	if (m_state == STATE_END) return;

	float deltaTime = Scene::Time() - m_startTime;
	float flyingTime = 0; //補正してこっちの値を使う

	if (deltaTime < 1)
	{
		flyingTime = deltaTime / 15.0f; //遅めに
	}
	else
	{
		//1秒はゆっくり
		flyingTime = 1.0f / 10.0f; //遅めに
		//残り
		float restTime = deltaTime - 1.0f;
		flyingTime += restTime;
	}

	float moveX = flyingTime * 5.0f;

	SetPosition(m_startPos.x - moveX);
	SetQuaternion(flyingTime * m_rotSpeed.x, flyingTime * m_rotSpeed.y, flyingTime * m_rotSpeed.z);


}


void FlyingBlock::updateEverySecond()
{
	if (m_state == STATE_MOVE_SLOW)
	{
		m_state = STATE_MOVE;
	}
}

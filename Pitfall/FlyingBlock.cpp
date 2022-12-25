#include "stdafx.h"
#include "FlyingBlock.h"

#define SIZE Define::BLOCK_SIZE

FlyingBlock::FlyingBlock() : Block()
	, m_state(STATE_END)
	, m_startPos(Vec3(0, 0, 0))
	, m_startTime(0)
	, m_rotSpeed(Vec3(0, 0, 0))
{
	m_smpTweens.reset(new Tweens());
}


FlyingBlock::~FlyingBlock()
{
}

void FlyingBlock::FlyingInit(Vec3 startPos)
{
	SetType(BLOCK_FLYING);
	m_state = STATE_BLOW;
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

	m_smpTweens->tweenPosX.Init(m_startPos.x);
	m_smpTweens->tweenPosX
		.then(m_startPos.x - 0.5f, Define::FLYING_BLOW_SLOW_SECOND)
		.then(m_startPos.x - 5, Define::FLYING_BLOW_MOVE_SECOND);

	m_smpTweens->tweenPosY.Init(m_startPos.y);
	m_smpTweens->tweenPosZ.Init(m_startPos.z);

	m_smpTweens->tweenRotVal.Init(0);
	m_smpTweens->tweenRotVal
		.then(0.5, Define::FLYING_BLOW_SLOW_SECOND)
		.then(5, Define::FLYING_BLOW_MOVE_SECOND);

	m_smpTweens->start();
}

void FlyingBlock::OverFlowInit(Vec3 startPos)
{
	SetType(BLOCK_FLYING);
	m_state = STATE_OVERFLOW;
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
	if (m_state == STATE_END)
	{
		return;
	}

	if (m_state == STATE_BLOW)
	{
		if (!m_smpTweens->update())
		{
			m_state = STATE_END;
		}


		Vec3 pos = Vec3(m_smpTweens->tweenPosX.getValue(), m_smpTweens->tweenPosY.getValue(), m_smpTweens->tweenPosZ.getValue());
		SetPosition(pos.x);

		Vec3 rot = m_rotSpeed * m_smpTweens->tweenRotVal.getValue();
		SetQuaternion(rot);

	}
	else if (m_state == STATE_OVERFLOW)
	{
		//float flyingTime = deltaTime;

	}


}


void FlyingBlock::updateInterval()
{
	//if (m_state == STATE_BLOW_SLOW)
	//{
	//	m_state = STATE_BLOW;
	//}
}

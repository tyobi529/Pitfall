#include "stdafx.h"
#include "FlyingBlock.h"

#define SIZE Define::BLOCK_SIZE

FlyingBlock::FlyingBlock() : Block()
	, m_isFlying(false)
	, m_startPos(Vec3(0, 0, 0))
	, m_startTime(0)
	, m_rotSpeed(Vec3(0, 0, 0))
{
	m_smpTweens.reset(new Tweens());
}


FlyingBlock::~FlyingBlock()
{
}

void FlyingBlock::BlowInit(Vec3 startPos)
{
	SetType(BLOCK_BLOW);
	m_isFlying = true;
	m_startPos = startPos;
	m_startTime = Scene::Time();
	SetPosition(m_startPos);
	SetSize(1.0f);
	//回転速度
	float x = Random<float>(1.0, 2.0);
	if (RandomBool()) x = -x;
	float y = Random<float>(4.0, 6.0);
	if (RandomBool()) y = -y;
	float z = Random<float>(1.0, 2.0);
	if (RandomBool()) z = -z;
	m_rotSpeed = Vec3(x, y, z);

	//Init
	m_smpTweens->tweenPosX.Init(m_startPos.x);
	m_smpTweens->tweenPosY.Init(m_startPos.y);
	m_smpTweens->tweenPosZ.Init(m_startPos.z);
	m_smpTweens->tweenRotVal.Init(0);
	//設定
	m_smpTweens->tweenPosX
		.then(m_startPos.x - 0.5f, Define::FLYING_BLOW_SLOW_SECOND)
		.then(m_startPos.x - 5, Define::FLYING_BLOW_MOVE_SECOND);

	m_smpTweens->tweenRotVal
		.then(0.5, Define::FLYING_BLOW_SLOW_SECOND)
		.then(5, Define::FLYING_BLOW_MOVE_SECOND);

	m_smpTweens->start();
}

void FlyingBlock::OverFlowInit(float posY)
{
	SetType(BLOCK_OVERFLOW);
	m_isFlying = true;
	m_startPos = Vec3(0, posY, 0);
	m_startTime = Scene::Time();
	SetPosition(m_startPos);
	SetSize(1.0f);
	//回転速度
	float x = Random<float>(1.0, 2.0);
	if (RandomBool()) x = -x;
	float y = Random<float>(4.0, 6.0);
	if (RandomBool()) y = -y;
	float z = Random<float>(1.0, 2.0);
	if (RandomBool()) z = -z;
	m_rotSpeed = Vec3(x, y, z);

	//スタートのy座標によって落ちる時間を変える
	float difY = posY + 2.0f;
	Duration downDuration = static_cast<Duration>(difY / 25.0f);



	//Init
	m_smpTweens->tweenPosX.Init(m_startPos.x);
	m_smpTweens->tweenPosY.Init(m_startPos.y);
	m_smpTweens->tweenPosZ.Init(m_startPos.z);
	m_smpTweens->tweenRotVal.Init(0);
	//設定
	//y方向
	m_smpTweens->tweenPosY
		.then(m_startPos.y + 2.0f, Define::FLYING_OVERFLOW_UP_SECOND, EaseInOutSine)
		.then(-2.0f, downDuration, EaseInOutSine);

	//xz方向

	//const double angle = Random<double>(3.0f, 9.0f);
	const double angle = Random<double>(1.0f, 9.0f);
	const double speed = Random<double>(5.0f, 6.0f);

	m_smpTweens->tweenPosX
		.then(m_startPos.x + Math::Cos(angle * 30_deg) * speed, Define::FLYING_OVERFLOW_UP_SECOND + downDuration);

	m_smpTweens->tweenPosZ
		.then(m_startPos.z + Math::Sin(angle * 30_deg) * speed, Define::FLYING_OVERFLOW_UP_SECOND + downDuration);

	//m_smpTweens->tweenPosX
	//	.then(m_startPos.x - 0.5f, Define::FLYING_OVERFLOW_UP_SECOND)
	//	.then(m_startPos.x - 2.0f, downDuration);



	m_smpTweens->start();

}


void FlyingBlock::update()
{
	if (!m_isFlying)
	{
		return;
	}


	if (!m_smpTweens->update())
	{
		m_isFlying = false;
	}

	Vec3 pos = Vec3(m_smpTweens->tweenPosX.getValue(), m_smpTweens->tweenPosY.getValue(), m_smpTweens->tweenPosZ.getValue());
	SetPosition(pos);

	Vec3 rot = m_rotSpeed * m_smpTweens->tweenRotVal.getValue();
	SetQuaternion(rot);

}


void FlyingBlock::updateInterval()
{
	//if (m_state == STATE_BLOW_SLOW)
	//{
	//	m_state = STATE_BLOW;
	//}
}

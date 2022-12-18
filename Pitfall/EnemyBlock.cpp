#include "stdafx.h"
#include "EnemyBlock.h"

#define SIZE Define::BLOCK_SIZE

EnemyBlock::EnemyBlock() : Block()
	, m_state(STATE_IDLE)
	, m_inStartTime(0)
	, m_delayStartTime(0)
	//, m_inEndTime(0)
	, m_moveStartTime(0)
	//, m_moveEndTime(0)
{
}


EnemyBlock::~EnemyBlock()
{
}

void EnemyBlock::EnemyInit()
{
	m_state = STATE_IDLE;
}

void EnemyBlock::update()
{
	float time = Scene::Time();
	if (time < m_inStartTime)
	{
		//待機
		int a = 0;
	}
	else if (time < m_delayStartTime)
	{
		//画面に入る動き
		float deltaTime = Scene::Time() - m_inStartTime;
		float x = Define::ENEMY_GENERATE_POS_X -
			(Define::ENEMY_GENERATE_POS_X - Define::ENEMY_START_POS_X) * (deltaTime / Define::ENEMY_IN_SECOND);
		SetPosition(x);
	}
	else if (time < m_moveStartTime)
	{
		//ディレイ中
		float deltaTime = Scene::Time() - m_delayStartTime;
		float x = Define::ENEMY_START_POS_X;
		SetPosition(x);
	}
	else
	{
		//メイン移動
		float deltaTime = Scene::Time() - m_moveStartTime;
		float x = Define::ENEMY_START_POS_X -
			(Define::ENEMY_START_POS_X - Define::ENEMY_END_POS_X) * (deltaTime / m_moveSecond);
		SetPosition(x);
	}


}


//void EnemyBlock::UpdatePos(float difTime)
//{
//	float x = Define::END_POS_X + difTime * m_speedLevel * Define::SPEED_PER_LEVEL;
//	//m_pos = Vec3(x, Define::BOTTOM_POS_Y + m_heightNum * Define::BLOCK_SIZE, 0.0f);
//	SetPosition(x);
//}

void EnemyBlock::SetTime(float endTime)
{
	switch (m_type)
	{
	case Block::BLOCK_ENEMY_1:
		m_moveSecond = Define::ENEMY_MOVE_1_SECOND;
		break;
	case Block::BLOCK_ENEMY_2:
		m_moveSecond = Define::ENEMY_MOVE_2_SECOND;
		break;
	case Block::BLOCK_ENEMY_3:
		m_moveSecond = Define::ENEMY_MOVE_3_SECOND;
		break;
	default:
		assert(false);
		break;
	}

	m_moveStartTime = endTime - m_moveSecond;
	m_delayStartTime = m_moveStartTime - Define::ENEMY_DELAY_SECOND;
	m_inStartTime = m_delayStartTime - Define::ENEMY_IN_SECOND;
}

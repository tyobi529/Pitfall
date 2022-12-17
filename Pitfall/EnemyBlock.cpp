#include "stdafx.h"
#include "EnemyBlock.h"

#define SIZE Define::BLOCK_SIZE

EnemyBlock::EnemyBlock() : Block()
{
}


EnemyBlock::~EnemyBlock()
{
}

void EnemyBlock::EnemyInit()
{
}

void EnemyBlock::update()
{
}


void EnemyBlock::UpdatePos(float difTime)
{
	float x = Define::END_POS_X + difTime * m_speedLevel * Define::SPEED_PER_LEVEL;
	//m_pos = Vec3(x, Define::BOTTOM_POS_Y + m_heightNum * Define::BLOCK_SIZE, 0.0f);
	SetPosition(x);
}

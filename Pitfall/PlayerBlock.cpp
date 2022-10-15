#include "stdafx.h"
#include "PlayerBlock.h"

#define SIZE Define::BLOCK_SIZE

PlayerBlock::PlayerBlock(int rowIndex, int colIndex) :
	Block(rowIndex, colIndex),
	m_isMove(false),
	m_maxDifY(0),
	m_preColIndex(0),
	m_isExpand(false)
{

}


PlayerBlock::~PlayerBlock()
{
}

void PlayerBlock::Init()
{
	m_isExpand = true;
	m_size = 0;
}

void PlayerBlock::update()
{
	if (m_isExpand)
	{
		m_size += (float)Scene::DeltaTime() * Define::BLOCK_EXPAND_SPEED;
		if (m_size > Define::BLOCK_SIZE)
		{
			m_size = Define::BLOCK_SIZE;
			m_isExpand = false;
		}
	}
}

void PlayerBlock::SetMoveInfo(int preColIndex)
{
	if (preColIndex - m_colIndex == 0)
	{
		m_isMove = false;
	}
	else
	{
		m_isMove = true;
		m_maxDifY = (preColIndex - m_colIndex) * SIZE;
		m_preColIndex = preColIndex;
	}
}


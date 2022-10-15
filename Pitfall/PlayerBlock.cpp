#include "stdafx.h"
#include "PlayerBlock.h"

#define SIZE Define::BLOCK_SIZE

PlayerBlock::PlayerBlock(int rowIndex, int colIndex) :
	Block(rowIndex, colIndex),
	m_isMove(false),
	m_maxDifY(0),
	m_preColIndex(0)
{

}


PlayerBlock::~PlayerBlock()
{
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


//bool PlayerBlock::GetIsMove(float difY)
//{
//	if (m_isMove)
//	{
//		if (difY >= m_maxDifY)
//		{
//			m_isMove = false;
//		}
//	}
//
//	return m_isMove;
//}

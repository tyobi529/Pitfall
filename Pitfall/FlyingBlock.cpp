#include "stdafx.h"
#include "FlyingBlock.h"

#define SIZE Define::BLOCK_SIZE

FlyingBlock::FlyingBlock() : Block()
, m_state(STATE_END)
{
}


FlyingBlock::~FlyingBlock()
{
}

void FlyingBlock::FlyingInit(Vec3 startPos)
{
	m_state = STATE_SLOW;
	m_startPos = startPos;
	SetPosition(startPos.x, startPos.y, startPos.z);
	SetSize(1.0f);
}

void FlyingBlock::update()
{


}


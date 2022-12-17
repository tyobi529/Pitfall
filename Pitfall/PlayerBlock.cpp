#include "stdafx.h"
#include "PlayerBlock.h"

#define SIZE Define::BLOCK_SIZE

PlayerBlock::PlayerBlock() : Block()
	, m_isExpand(false)
	, m_sizeMag(0)
{
}


PlayerBlock::~PlayerBlock()
{
}

void PlayerBlock::PlayerInit(bool isHead)
{
	if (isHead)
	{
		m_isExpand = false;
		m_sizeMag = 1.0f;
		m_size = Define::BLOCK_SIZE;
	}
	else
	{
		m_isExpand = true;
		m_sizeMag = 0.0f;
	}

}

void PlayerBlock::update()
{
	if (m_isExpand)
	{
		//m_size += (float)Scene::DeltaTime() * Define::BLOCK_EXPAND_SPEED;
		m_sizeMag += (float)Scene::DeltaTime() * Define::BLOCK_EXPAND_SPEED;

		if (m_sizeMag >= 1.0f)
		{
			m_sizeMag = 1.0f;
			m_size = Define::BLOCK_SIZE;
			m_isExpand = false;
		}
		else
		{
			m_size = Define::BLOCK_SIZE * m_sizeMag;
		}
	}

}


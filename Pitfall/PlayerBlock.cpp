#include "stdafx.h"
#include "PlayerBlock.h"

#define SIZE Define::BLOCK_SIZE

PlayerBlock::PlayerBlock(int index) :
	Block(index),
	m_isExpand(false),
	m_sizeMag(0)
{
	Init();
}


PlayerBlock::~PlayerBlock()
{
}

void PlayerBlock::Init()
{
	Block::Init();

	m_isExpand = true;
	m_sizeMag = 0.0f;
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


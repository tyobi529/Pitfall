#include "stdafx.h"
#include "BlockUnit.h"

#include "Define.h"

BlockUnit::BlockUnit() :
	m_generatedTime(0)
{
	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		m_blocks[i].reset();
	}
}

BlockUnit::~BlockUnit()
{
	
}


void BlockUnit::Init(float generatedTime, float generatedPosX)
{
	m_generatedTime = generatedTime;
	m_generatedPosX = generatedPosX;

	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		Block::TYPE type = Block::TYPE::BLOCK_NONE;

		if (i < Define::BLOCK_HURDLE_HALL_NUM)
		{
			type = Block::TYPE::BLOCK_HALL;
		}
		else if (i < Define::BLOCK_HURDLE_HALL_NUM + Define::BLOCK_HURDLE_CENTER_NUM)
		{
			if (RandomBool())
			{
				type = Block::TYPE::BLOCK_NORMAL;
			}
		}
		else
		{
			type = Block::TYPE::BLOCK_HALL;
		}


		//m_blocks[i] = std::make_unique<Block>(type);

		m_blocks[i] = std::make_unique<Block>(type);


	}
}

void BlockUnit::update()
{
	//for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	//{
	//	//float posX = 0.0f;
	//	float posY = Define::GROUND_POS_Y + Define::BLOCK_SIZE * i;

	//	m_blocks[i]->SetPos(Vec3(m_posX, posY, 0));
	//}
}

void BlockUnit::draw()
{
	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		m_blocks[i]->draw();
	}
}

void BlockUnit::UpdatePos(float currentTime)
{
	float posX = m_generatedPosX - (currentTime - m_generatedTime) * Define::BLOCK_SPEED;

	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		float posY = Define::GROUND_POS_Y + Define::BLOCK_SIZE * i;

		m_blocks[i]->SetPos(Vec3(posX, posY, 0));
	}
}

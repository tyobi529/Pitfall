#include "stdafx.h"
#include "BlockUnit.h"

#include "Define.h"

BlockUnit::BlockUnit() :
	m_generatedTime(0),
	m_generatedPosX(0)
{
	//固定部分
	for (int i = 0; i < Define::BLOCK_GROUND_BOTTOM_NUM; i++)
	{
		m_bBlocks[i] = std::make_unique<Block>(Block::BLOCK_GROUND);
	}

	for (int i = 0; i < Define::BLOCK_GROUND_TOP_NUM; i++)
	{
		m_tBlocks[i] = std::make_unique<Block>(Block::BLOCK_GROUND);
	}
}

BlockUnit::~BlockUnit()
{
	
}


void BlockUnit::Init(Block::TYPE* types, float generatedTime, float generatedPosX)
{
	m_generatedTime = generatedTime;
	m_generatedPosX = generatedPosX;

	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		m_hBlocks[i] = std::make_unique<Block>(types[i]);
	}

	UpdatePos(generatedTime);

	//for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	//{
	//	Block::TYPE type = Block::TYPE::BLOCK_NONE;

	//	if (i < Define::BLOCK_HURDLE_HALL_NUM)
	//	{
	//		type = Block::TYPE::BLOCK_HALL;
	//	}
	//	else if (i < Define::BLOCK_HURDLE_HALL_NUM + Define::BLOCK_HURDLE_CENTER_NUM)
	//	{
	//		if (RandomBool())
	//		{
	//			type = Block::TYPE::BLOCK_NORMAL;
	//		}
	//	}
	//	else
	//	{
	//		type = Block::TYPE::BLOCK_HALL;
	//	}


	//	//m_blocks[i] = std::make_unique<Block>(type);

	//	m_blocks[i] = std::make_unique<Block>(type);


	//}
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
	for (int i = 0; i < Define::BLOCK_GROUND_BOTTOM_NUM; i++)
	{
		m_bBlocks[i]->draw();
	}

	//可変部分
	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		m_hBlocks[i]->draw();
	}

	for (int i = 0; i < Define::BLOCK_GROUND_TOP_NUM; i++)
	{
		m_tBlocks[i]->draw();
	}



}

void BlockUnit::UpdatePos(float currentTime)
{
	float posX = m_generatedPosX - (currentTime - m_generatedTime) * Define::BLOCK_SPEED;
	float posY = Define::GROUND_POS_Y;

	for (int i = 0; i < Define::BLOCK_GROUND_BOTTOM_NUM; i++)
	{
		m_bBlocks[i]->SetPos(Vec3(posX, posY, 0));

		posY += Define::BLOCK_SIZE;
	}

	//可変部分
	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		m_hBlocks[i]->SetPos(Vec3(posX, posY, 0));

		posY += Define::BLOCK_SIZE;
	}

	for (int i = 0; i < Define::BLOCK_GROUND_TOP_NUM; i++)
	{
		m_tBlocks[i]->SetPos(Vec3(posX, posY, 0));

		posY += Define::BLOCK_SIZE;
	}
}

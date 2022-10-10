#include "stdafx.h"
#include "BlockUnit.h"

#include "Define.h"

BlockUnit::BlockUnit()
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


void BlockUnit::Init(Block::TYPE* types)
{
	//m_posX = generatedPosX;
	//m_generatedPosX = generatedPosX;

	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		m_hBlocks[i] = std::make_unique<Block>(types[i]);
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

void BlockUnit::UpdatePos(float posX)
{

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

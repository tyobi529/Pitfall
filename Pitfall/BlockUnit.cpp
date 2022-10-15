#include "stdafx.h"
#include "BlockUnit.h"

#include "Define.h"

BlockUnit::BlockUnit()
{
	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		//m_smpBlocks[i] = std::make_unique<Block>(i);
	}
}

BlockUnit::~BlockUnit()
{
	
}


void BlockUnit::Init(Block::TYPE* types)
{

	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		//m_smpBlocks[i] = std::make_unique<Block>(types[i]);
		m_smpBlocks[i]->SetType(types[i]);
	}

}

void BlockUnit::update()
{

}

void BlockUnit::draw()
{
	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		m_smpBlocks[i]->draw();
	}



}

void BlockUnit::UpdatePos(float posX)
{

	float posY = Define::LIMIT_POS_Y_HURDLE_BOTTOM;

	//for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	//{
	//	m_smpBlocks[i]->SetPos(Vec3(posX, posY, 0));

	//	posY += Define::BLOCK_SIZE;
	//}

}


//void BlockUnit::SetType(int index, Block::TYPE type)
//{
//	m_types[index] = type;
//
//}



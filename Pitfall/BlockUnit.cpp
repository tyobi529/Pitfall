#include "stdafx.h"
#include "BlockUnit.h"

//#include "Define.h"

#define SIZE Define::BLOCK_SIZE


BlockUnit::BlockUnit() :
	m_unitIndex(0),
	m_preIndex{}
{
	for (int i = 0; i < SIZE; i++)
	{
		m_preIndex[i] = i;
	}
}

BlockUnit::~BlockUnit()
{
}

void BlockUnit::EnemyInit()
{
	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		m_smpBlocks[i].reset();
		m_smpBlocks[i] = std::make_shared<Block>(i);
	}
}

void BlockUnit::PlayerInit()
{
	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		m_smpBlocks[i].reset();
		m_smpBlocks[i] = std::make_unique<PlayerBlock>(i);
	}
}


//void BlockUnit::Init(Block::TYPE* types)
//{
//
//	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
//	{
//		//m_smpBlocks[i] = std::make_unique<Block>(types[i]);
//		m_smpBlocks[i]->SetType(types[i]);
//
//		m_preIndex[i] = i;
//	}
//
//}

void BlockUnit::update()
{
	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		m_smpBlocks[i]->update();
	}
}

void BlockUnit::draw()
{
	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		m_smpBlocks[i]->draw();
	}
}

void BlockUnit::SetCenterPos(float difX, float playerMoveX, float fallValue)
{
	//float posX = Define::BLOCK_SIZE * m_unitIndex + difX;
	float posX = Define::BLOCK_SIZE * m_unitIndex + difX + playerMoveX;


	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		float posY = Define::LIMIT_POS_Y_HURDLE_BOTTOM + Define::BLOCK_SIZE * i;

		if (i != m_preIndex[i])
		{
			//int preIndex = m_smpBlocks[i]->GetPreIndex();
			float difY = (m_preIndex[i] - i) * SIZE - fallValue;
			
			if (difY <= 0)
			{
				//m_smpBlocks[i]->SetIsMove(false);
				m_preIndex[i] = i;
				difY = 0;
			}

			posY += difY;
		}

		//if (m_smpBlocks[i]->GetIsMove())
		//{
		//	int preIndex = m_smpBlocks[i]->GetPreIndex();
		//	float difY = (preIndex - i) * SIZE - fallValue;

		//	if (difY <= 0)
		//	{
		//		m_smpBlocks[i]->SetIsMove(false);
		//		difY = 0;
		//	}

		//	posY += difY;
		//}

		m_smpBlocks[i]->SetCenterPos(posX, posY);


	}
}

//void BlockUnit::SetCenterPos(float difX = 0, float fallValue = 0)
//{
//	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
//	{
//		m_smpBlocks[i]->SetCenterPos(difX, difY);
//	}
//}


//void BlockUnit::UpdatePos(float posX)
//{
//
//	float posY = Define::LIMIT_POS_Y_HURDLE_BOTTOM;
//
//	//for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
//	//{
//	//	m_smpBlocks[i]->SetPos(Vec3(posX, posY, 0));
//
//	//	posY += Define::BLOCK_SIZE;
//	//}
//
//	float difX = 1;
//	float difY = 1;
//	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
//	{
//		if (m_preIndex[i] != i)
//		{
//			//移動しているブロック
//
//			float difY = Define::BLOCK_SIZE * (m_preIndex[i] - i) + fallValue;
//			if (difY <= 0)
//			{
//				m_smpPlayerBlocks[i]->SetIsMove(false);
//				m_smpPlayerBlocks[i]->SetCenterPos();
//			}
//			else
//			{
//				m_smpPlayerBlocks[i]->SetCenterPos(0, difY);
//			}
//
//		}
//	}
//
//}


//void BlockUnit::SetType(int index, Block::TYPE type)
//{
//	m_types[index] = type;
//
//}



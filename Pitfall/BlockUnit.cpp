#include "stdafx.h"
#include "BlockUnit.h"

//#include "Define.h"

#define SIZE Define::BLOCK_SIZE


BlockUnit::BlockUnit() :
	m_unitIndex(0),
	m_preIndex{},
	m_fallTime(0),
	m_fallValue(0),
	m_headIndex(0)
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
	m_headIndex = 0;

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

	m_headIndex = 0;
	m_smpBlocks[0]->SetType(Block::BLOCK_PLAYER_HEAD);

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
	m_fallTime += Scene::DeltaTime();
	float tmp = m_fallTime / 0.5f;
	//m_fallValue = (BLOCK_NUM - 1) * (m_fallTime * m_fallTime);
	m_fallValue = (Define::BLOCK_NUM - 1) * (tmp * tmp);


	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		float posY = Define::LIMIT_POS_Y_HURDLE_BOTTOM + Define::BLOCK_SIZE * i;

		if (i != m_preIndex[i])
		{
			float difY = (m_preIndex[i] - i) * SIZE - m_fallValue;

			if (difY <= 0)
			{
				m_preIndex[i] = i;
				difY = 0;
			}

			posY += difY;
		}

		m_smpBlocks[i]->SetCenterPos(0, posY);
	}

	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		m_smpBlocks[i]->update();
	}
}

void BlockUnit::draw()
{
	//ワイヤーフレームの描画
	//for (int i = 0; i < Define::BLOCK_NUM; i++)
	//{
	//	float posY = Define::LIMIT_POS_Y_HURDLE_BOTTOM + Define::BLOCK_SIZE * i;
	//	Box{ 0, posY + 0, 0 , 1 }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
	//}


	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		m_smpBlocks[i]->draw();
	}
}

void BlockUnit::updateEverySecond()
{
	m_fallTime = 0;
	m_fallValue = 0;
}

void BlockUnit::SetCenterPos(float difX, float fallValue)
{
	//float posX = Define::BLOCK_SIZE * m_unitIndex + difX;
	float posX = Define::BLOCK_SIZE * m_unitIndex + difX;


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



void BlockUnit::CreateBlock()
{
	//int headIndex = -1;

	//for (int i = 0; i < Define::BLOCK_NUM; i++)
	//{
	//	if (m_smpBlocks[i]->GetType() == Block::BLOCK_PLAYER_HEAD)
	//	{
	//		headIndex = i;
	//		break;
	//	}
	//}

	//if (headIndex == Define::BLOCK_NUM - 1)
	//{
	//	//生成限界
	//	return;
	//}


	if (m_headIndex == Define::BLOCK_NUM - 1)
	{
		//生成限界
		return;
	}


	m_smpBlocks[m_headIndex]->Init();
	m_smpBlocks[m_headIndex]->SetType(Block::BLOCK_PLAYER_BODY);

	//1つ上に頭を移動
	int newHeadIndex = m_headIndex + 1;
	m_smpBlocks[newHeadIndex]->SetType(Block::BLOCK_PLAYER_HEAD);
	m_headIndex = newHeadIndex;

}

void BlockUnit::CheckHit(const int* hitStatus)
{
	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		if (hitStatus[i] == 1)
		{
			m_smpBlocks[i]->SetType(Block::BLOCK_NONE);
		}

	}
}

void BlockUnit::DropBlock()
{
	Block::TYPE* types;

	Block::TYPE emptyTypes[Define::BLOCK_NUM] = {};
	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		if (m_smpBlocks[i]->GetType() == Block::BLOCK_PLAYER_HEAD ||
			m_smpBlocks[i]->GetType() == Block::BLOCK_PLAYER_BODY)
		{
			emptyTypes[i] = Block::BLOCK_NONE;
		}
		else
		{
			emptyTypes[i] = m_smpBlocks[i]->GetType();
		}
	}
	types = emptyTypes;



	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		Block::TYPE type = m_smpBlocks[i]->GetType();
		if (type == Block::BLOCK_PLAYER_HEAD || type == Block::BLOCK_PLAYER_BODY)
		{
			//元の位置を先に削除
			m_smpBlocks[i]->SetType(Block::BLOCK_NONE);

			if (i == 0) //一番下
			{
				m_smpBlocks[0]->SetType(type);
				//移動先にブロックを入れる
				types[0] = type;

				//移動元情報入れる
				m_preIndex[0] = i;
			}
			else
			{
				//下を確認
				for (int j = i - 1; j >= 0; j--)
				{
					if (types[j] != Block::BLOCK_NONE)
					{
						//ブロックが存在する場合はその１つ上に移動
						//真下にある場合は変化なし
						m_smpBlocks[j + 1]->SetType(type);
						//移動先にブロックを入れる
						types[j + 1] = type;

						//移動元情報入れる
						m_preIndex[j + 1] = i;

						if (type == Block::BLOCK_PLAYER_HEAD)
						{
							m_headIndex = j + 1;
						}

						break;
					}
					if (j == 0)
					{
						m_smpBlocks[0]->SetType(type);
						//移動先にブロックを入れる
						types[0] = type;

						//移動元情報入れる
						m_preIndex[0] = i;

						if (type == Block::BLOCK_PLAYER_HEAD)
						{
							m_headIndex = 0;
						}

						break;
					}
				}
			}


		}
	}
}

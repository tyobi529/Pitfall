#include "stdafx.h"
#include "Player.h"

#define SIZE Define::BLOCK_SIZE

Player::Player() :
	m_headIndex(0)
{
	m_smpBlockUnit.reset();
	m_smpBlockUnit = std::make_shared<BlockUnit>();

	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		std::shared_ptr<PlayerBlock> smpBlock = std::make_shared<PlayerBlock>();
		if (!m_smpBlockUnit->SetObject(i, smpBlock))
			assert(false);

	}

	m_headIndex = 0;
	std::shared_ptr<PlayerBlock> smpPlayerBlock = std::static_pointer_cast<PlayerBlock>(m_smpBlockUnit->GetObject(0));
	smpPlayerBlock->SetType(Block::BLOCK_PLAYER_HEAD);
	smpPlayerBlock->PlayerInit(true);

	m_smpFlyingBlockManager.reset();
	m_smpFlyingBlockManager = std::make_shared<FlyingBlockManager>();

}

Player::~Player()
{

}

void Player::update()
{

	m_fallTime += Scene::DeltaTime();
	float tmp = m_fallTime * 3.0f;
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
		std::shared_ptr<PlayerBlock> smpBlock = std::static_pointer_cast<PlayerBlock>(m_smpBlockUnit->GetObject(i));
		smpBlock->SetPosition(0, posY);
	}


	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		std::shared_ptr<PlayerBlock> smpBlock = std::static_pointer_cast<PlayerBlock>(m_smpBlockUnit->GetObject(i));
		smpBlock->update();
	}

	m_smpFlyingBlockManager->update();
		
}


void Player::draw() const
{
	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		std::shared_ptr<PlayerBlock> smpBlock = std::static_pointer_cast<PlayerBlock>(m_smpBlockUnit->GetObject(i));
		smpBlock->draw();
	}

	//drawGuid();

	//飛んでいるブロック
	m_smpFlyingBlockManager->draw();
}

void Player::drawGuid() const
{
	//ガイド
	ColorF color = ColorF(1.0f, 1.0f, 1.0f, 0.5f);
	float bottomY = Define::LIMIT_POS_Y_HURDLE_BOTTOM - Define::BLOCK_SIZE / 2.0f;
	float topY = Define::LIMIT_POS_Y_HURDLE_TOP - Define::BLOCK_SIZE / 2.0f;
	float lineWidth = 0.04f;
	Vec3 bottomPos1 = Vec3{ -0.5f, bottomY, -0.5f };
	Vec3 bottomPos2 = Vec3{ 0.5f, bottomY, -0.5f };
	Vec3 bottomPos3 = Vec3{ 0.5f, bottomY, 0.5f };
	Vec3 bottomPos4 = Vec3{ -0.5f, bottomY, 0.5f };

	float light = 0.2f;

	//横線
	Box::FromPoints(bottomPos1 - Vec3(lineWidth / 2.0f, 0, lineWidth / 2.0f),
		bottomPos1 + Vec3(lineWidth / 2.0f, topY - bottomY, lineWidth / 2.0f)).draw(color.removeSRGBCurve() * light);
	Box::FromPoints(bottomPos2 - Vec3(lineWidth / 2.0f, 0, lineWidth / 2.0f),
		bottomPos2 + Vec3(lineWidth / 2.0f, topY - bottomY, lineWidth / 2.0f)).draw(color.removeSRGBCurve() * light);
	Box::FromPoints(bottomPos3 - Vec3(lineWidth / 2.0f, 0, lineWidth / 2.0f),
		bottomPos3 + Vec3(lineWidth / 2.0f, topY - bottomY, lineWidth / 2.0f)).draw(color.removeSRGBCurve() * light);
	Box::FromPoints(bottomPos4 - Vec3(lineWidth / 2.0f, 0, lineWidth / 2.0f),
		bottomPos4 + Vec3(lineWidth / 2.0f, topY - bottomY, lineWidth / 2.0f)).draw(color.removeSRGBCurve() * light);

	//横線
	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		Vec3 pos1 = bottomPos1 + Vec3(0, i * Define::BLOCK_SIZE, 0);
		Vec3 pos2 = bottomPos2 + Vec3(0, i * Define::BLOCK_SIZE, 0);
		Vec3 pos3 = bottomPos3 + Vec3(0, i * Define::BLOCK_SIZE, 0);
		Vec3 pos4 = bottomPos4 + Vec3(0, i * Define::BLOCK_SIZE, 0);

		Box::FromPoints(pos1 - Vec3(lineWidth / 2.0f, lineWidth / 2.0f, lineWidth / 2.0f),
						pos2 + Vec3(lineWidth / 2.0f, lineWidth / 2.0f, lineWidth / 2.0f)).draw(color.removeSRGBCurve() * light);

		Box::FromPoints(pos2 - Vec3(lineWidth / 2.0f, lineWidth / 2.0f, lineWidth / 2.0f),
						pos3 + Vec3(lineWidth / 2.0f, lineWidth / 2.0f, lineWidth / 2.0f)).draw(color.removeSRGBCurve() * light);

		Box::FromPoints(pos3 - Vec3(lineWidth / 2.0f, lineWidth / 2.0f, lineWidth / 2.0f),
						pos4 + Vec3(lineWidth / 2.0f, lineWidth / 2.0f, lineWidth / 2.0f)).draw(color.removeSRGBCurve() * light);

		Box::FromPoints(pos4 - Vec3(lineWidth / 2.0f, lineWidth / 2.0f, lineWidth / 2.0f),
						pos1 + Vec3(lineWidth / 2.0f, lineWidth / 2.0f, lineWidth / 2.0f)).draw(color.removeSRGBCurve() * light);
	}
}

void Player::updateInterval()
{
	m_fallTime = 0;
	m_fallValue = 0;

	m_smpFlyingBlockManager->updateInterval();
}

void Player::CreateBlock()
{
	if (m_headIndex == Define::BLOCK_NUM - 1)
	{
		//生成限界
		return;
	}

	{
		std::shared_ptr<PlayerBlock> smpHeadBlock = std::static_pointer_cast<PlayerBlock>(m_smpBlockUnit->GetObject(m_headIndex));
		smpHeadBlock->SetType(Block::BLOCK_PLAYER_BODY);
		smpHeadBlock->PlayerInit(false);
	}

	//1つ上に頭を移動
	int newHeadIndex = m_headIndex + 1;
	std::shared_ptr<PlayerBlock> smpNewHeadBlock = std::static_pointer_cast<PlayerBlock>(m_smpBlockUnit->GetObject(newHeadIndex));
	smpNewHeadBlock->SetType(Block::BLOCK_PLAYER_HEAD);
	smpNewHeadBlock->PlayerInit(true);
	m_headIndex = newHeadIndex;
}


void Player::DropBlock()
{
	int blockNum = 0;
	bool isblank = false;
	Array<int> dropIndex;

	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{

		std::shared_ptr<PlayerBlock> smpPlayerBlock = std::static_pointer_cast<PlayerBlock>(m_smpBlockUnit->GetObject(i));
		Block::TYPE type = smpPlayerBlock->GetType();
		if (type == Block::BLOCK_NONE)
		{
			isblank = true;
		}
		else
		{
			//元の位置を消す
			smpPlayerBlock->SetType(Block::BLOCK_NONE);

			if (isblank) //下が開いているなら
			{
				m_smpBlockUnit->GetObject(blockNum)->SetType(Block::BLOCK_PLAYER_BODY_DOWN);
			}
			else
			{
				m_smpBlockUnit->GetObject(blockNum)->SetType(Block::BLOCK_PLAYER_BODY);
			}

			if (type == Block::BLOCK_PLAYER_HEAD)
			{
				m_headIndex = blockNum;
				m_smpBlockUnit->GetObject(blockNum)->SetType(Block::BLOCK_PLAYER_HEAD);
			}

			blockNum++;
			isblank = false;
		}

	
		
	}

}


void Player::ClearBlock()
{



	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		std::shared_ptr<PlayerBlock> smpPlayerBlock = std::static_pointer_cast<PlayerBlock>(m_smpBlockUnit->GetObject(i));

		if (smpPlayerBlock->GetType() == Block::BLOCK_PLAYER_BODY)
		{
			//TODO
			std::shared_ptr<FlyingBlock> smpFlyingBlock = m_smpFlyingBlockManager->GetFlyingBlock();
			//smpFlyingBlock->SetType(Block::BLOCK_PLAYER_BODY);
			Vec3 pos = smpPlayerBlock->GetPosition();
			smpFlyingBlock->OverFlowInit(pos.y);
		}

		if (i == 0) 
		{
			smpPlayerBlock->SetType(Block::BLOCK_PLAYER_HEAD);
			smpPlayerBlock->PlayerInit(true);
			m_headIndex = 0;
		}
		else
		{
			smpPlayerBlock->SetType(Block::BLOCK_NONE);
		}

	}


}


void Player::CheckHit(const int* hitStatus)
{
	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		if (hitStatus[i] == Block::BLOCK_ENEMY_1 ||
			hitStatus[i] == Block::BLOCK_ENEMY_2 ||
			hitStatus[i] == Block::BLOCK_ENEMY_3 )
		{
			std::shared_ptr<PlayerBlock> smpPlayerBlock = std::static_pointer_cast<PlayerBlock>(m_smpBlockUnit->GetObject(i));
			if (smpPlayerBlock->GetType() != Block::BLOCK_NONE)
			{
				Vec3 pos = smpPlayerBlock->GetPosition();
				//m_smpFlyingBlockManager->GenerateFlyingBlock(Vec3(pos.x - 1, pos.y, pos.z));
				std::shared_ptr<FlyingBlock> smpFlyingBlock = m_smpFlyingBlockManager->GetFlyingBlock();
				smpFlyingBlock->SetType(Block::BLOCK_PLAYER_BODY);
				smpFlyingBlock->BlowInit(Vec3(pos.x - 1, pos.y, pos.z));

				smpPlayerBlock->SetType(Block::BLOCK_NONE); //当たった部分はNONEに
			}

		}
		else if (hitStatus[i] == Block::BLOCK_ENEMY_COIN)
		{
			//コイン
			Define::SCORE += 1;
		}

	}

}




//void Player::DropBlock()
//{
//	for (int i = 0; i < Define::BLOCK_NUM; i++)
//	{
//		std::shared_ptr<PlayerBlock> smpPlayerBlock = std::static_pointer_cast<PlayerBlock>(m_smpBlockUnit->GetObject(i));
//
//
//		Block::TYPE type = smpPlayerBlock->GetType();
//
//
//		if (type != Block::BLOCK_NONE)
//		{
//			if (i == 0) //一番下は移動なし
//			{
//				continue;
//			}
//			else
//			{
//				//下を確認
//				for (int j = i - 1; j >= 0; j--)
//				{
//					std::shared_ptr<PlayerBlock> smpBlockUnder = std::static_pointer_cast<PlayerBlock>(m_smpBlockUnit->GetObject(j));
//
//					if (smpBlockUnder->GetType() != Block::BLOCK_NONE)
//					{
//						if (j == i - 1)
//						{
//							//真下にブロックがある場合は変化なし
//							break;
//						}
//
//						//ブロックが存在する場合はその１つ上に移動
//						std::shared_ptr<PlayerBlock> smpBlockNext = std::static_pointer_cast<PlayerBlock>(m_smpBlockUnit->GetObject(j + 1));
//
//						smpBlockNext->SetType(type);
//						//元の位置を消す
//						smpPlayerBlock->SetType(Block::BLOCK_NONE);
//						//移動元情報入れる
//						//TODO
//						m_preIndex[j + 1] = i;
//
//						if (type == Block::BLOCK_PLAYER_HEAD)
//						{
//							m_headIndex = j + 1;
//						}
//
//						break;
//					}
//
//					//一番下までブロックが無かった場合
//					if (j == 0)
//					{
//						smpBlockUnder->SetType(type);
//						//元の位置を消す
//						smpPlayerBlock->SetType(Block::BLOCK_NONE);
//						//m_smpBlocks[i]->SetType(Block::BLOCK_NONE);
//						//移動元情報入れる
//						//TODO
//						m_preIndex[0] = i;
//
//						if (type == Block::BLOCK_PLAYER_HEAD)
//						{
//							m_headIndex = 0;
//						}
//
//						break;
//					}
//				}
//			}
//
//
//		}
//	}
//
//}

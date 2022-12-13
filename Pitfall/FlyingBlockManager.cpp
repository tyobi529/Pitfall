#include "stdafx.h"
#include "FlyingBlockManager.h"

#define SIZE Define::BLOCK_SIZE

FlyingBlockManager::FlyingBlockManager() 
{
	//飛ぶブロック10個作成しておく
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<Block> smpBlock = std::make_shared<Block>();
		smpBlock->SetType(Block::BLOCK_NONE);
		m_smpFlyingBlockArray << smpBlock;
	}
}

FlyingBlockManager::~FlyingBlockManager()
{

}

void FlyingBlockManager::update()
{


}


void FlyingBlockManager::draw() const
{

	//飛んでいるブロック
	for (auto itr = m_smpFlyingBlockArray.begin(); itr != m_smpFlyingBlockArray.end(); itr++)
	{
		if ((*itr)->GetType() != Block::BLOCK_NONE)
		{
			(*itr)->draw();
		}
	}
}

void FlyingBlockManager::GenerateFlyingBlock(Vec3 pos)
{
	std::shared_ptr<Block> smpFlyingBlock = GetFlyingBlock();
	smpFlyingBlock->SetType(Block::BLOCK_PLAYER_BODY); 
	smpFlyingBlock->SetPosition(pos.x, pos.y, pos.z);
	smpFlyingBlock->SetSize(1.0f);
}

std::shared_ptr<Block> FlyingBlockManager::GetFlyingBlock()
{
	//無効なものを探す
	for (auto itr = m_smpFlyingBlockArray.begin(); itr != m_smpFlyingBlockArray.end(); itr++)
	{
		if ((*itr)->GetType() == Block::BLOCK_NONE)
		{
			return *itr;
		}
	}

	//無効なものが無い場合生成
	std::shared_ptr<Block> smpEnemy = std::make_unique<Block>();
	m_smpFlyingBlockArray << smpEnemy;
	return smpEnemy;
}



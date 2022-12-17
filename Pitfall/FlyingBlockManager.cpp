#include "stdafx.h"
#include "FlyingBlockManager.h"

#define SIZE Define::BLOCK_SIZE

FlyingBlockManager::FlyingBlockManager() 
{
	//飛ぶブロック10個作成しておく
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<FlyingBlock> smpBlock = std::make_shared<FlyingBlock>();
		m_smpFlyingBlockArray << smpBlock;
	}
}

FlyingBlockManager::~FlyingBlockManager()
{

}

void FlyingBlockManager::update()
{
	for (auto itr = m_smpFlyingBlockArray.begin(); itr != m_smpFlyingBlockArray.end(); itr++)
	{
		(*itr)->update();
	}

}

void FlyingBlockManager::updateInterval()
{
	for (auto itr = m_smpFlyingBlockArray.begin(); itr != m_smpFlyingBlockArray.end(); itr++)
	{
		(*itr)->updateInterval();
	}

}


void FlyingBlockManager::draw() const
{

	for (auto itr = m_smpFlyingBlockArray.begin(); itr != m_smpFlyingBlockArray.end(); itr++)
	{
		(*itr)->draw();
	}
}

void FlyingBlockManager::GenerateFlyingBlock(Vec3 pos)
{
	std::shared_ptr<FlyingBlock> smpFlyingBlock = GetFlyingBlock();
	smpFlyingBlock->SetType(Block::BLOCK_PLAYER_BODY);
	smpFlyingBlock->FlyingInit(pos);
}

std::shared_ptr<FlyingBlock> FlyingBlockManager::GetFlyingBlock()
{
	//無効なものを探す
	for (auto itr = m_smpFlyingBlockArray.begin(); itr != m_smpFlyingBlockArray.end(); itr++)
	{
		if ((*itr)->GetState() == FlyingBlock::STATE_END)
		{
			return *itr;
		}
	}

	//無効なものが無い場合生成
	std::shared_ptr<FlyingBlock> smpEnemy = std::make_unique<FlyingBlock>();
	m_smpFlyingBlockArray << smpEnemy;
	return smpEnemy;
}



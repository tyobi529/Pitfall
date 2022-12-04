#include "stdafx.h"
#include "Player.h"

#include "Define.h"
#include "Block.h"

Player::Player()
{
	m_smpBlockUnit.reset();
	std::shared_ptr<ObjectUnit> smpObjectUnit = std::make_shared<ObjectUnit>();

	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		std::shared_ptr<Block> smpBlock = std::make_shared<Block>();
		smpObjectUnit->SetObject(i, smpBlock);
	}

	int a = 0;

	//m_smpBlockUnit = std::make_shared<BlockUnit>();

	//m_smpPlayerBlockUnit.reset();
	//m_smpPlayerBlockUnit = std::make_shared<BlockUnit>();
	//m_smpPlayerBlockUnit->PlayerInit();
	//m_smpPlayerBlockUnit->SetUnitIndex(Define::BLOCK_PLAYE_INDEX);
	////m_smpPlayerBlockUnit->GetBlock(BLOCK_NUM - 1)->SetType(Block::BLOCK_PLAYER_HEAD);
	//m_smpPlayerBlockUnit->DropBlock();
}

Player::~Player()
{

}

void Player::update()
{

}

void Player::draw()
{

}

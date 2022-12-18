﻿#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy() :
	m_isValid(false),
	m_count(0),
	m_endTime(0)
{
	m_smpBlockUnit.reset();
	m_smpBlockUnit = std::make_shared<BlockUnit>();

	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		std::shared_ptr<EnemyBlock> smpEnemyBlock = std::make_shared<EnemyBlock>();
		float posY = Define::LIMIT_POS_Y_HURDLE_BOTTOM + Define::BLOCK_SIZE * i;
		smpEnemyBlock->SetPosition(1000, posY); //初期位置指定
		if (!m_smpBlockUnit->SetObject(i, smpEnemyBlock))
			assert(false);

	}

}

Enemy::~Enemy() {

}


void Enemy::update()
{

	if (!m_isValid)
		return;

	//float difTime = m_endTime - Scene::Time();
	//for (int i = 0; i < Define::BLOCK_NUM; i++)
	//{
	//	std::shared_ptr<EnemyBlock> smpEnemyBlock = std::static_pointer_cast<EnemyBlock>(m_smpBlockUnit->GetObject(i));
	//	smpEnemyBlock->UpdatePos(difTime);
	//}

	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		std::shared_ptr<EnemyBlock> smpEnemyBlock = std::static_pointer_cast<EnemyBlock>(m_smpBlockUnit->GetObject(i));
		smpEnemyBlock->update();
	}
}

void Enemy::draw() const
{
	if (!m_isValid)
		return;

	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		std::shared_ptr<EnemyBlock> smpEnemyBlock = std::static_pointer_cast<EnemyBlock>(m_smpBlockUnit->GetObject(i));
		smpEnemyBlock->draw();
	}
}

void Enemy::updateInterval()
{
	if (!m_isValid)
		return;

	m_count--;

	//TODO
	//if (m_count == 0)
	//{
	//	m_isValid = false;
	//}
}


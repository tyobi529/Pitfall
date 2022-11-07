#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	//５つ生成しておく
	for (int i = 0; i < 5; i++)
	{
		std::shared_ptr<Enemy> smpEnemy = std::make_unique<Enemy>();
		m_smpEnemyArray << smpEnemy;
	}

}

EnemyManager::~EnemyManager() {

}


void EnemyManager::update()
{
	//有効なものだけ操作
	for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	{
		if ((*itr)->GetIsValid())
		{
			(*itr)->update();
		}
	}

}

void EnemyManager::draw() const
{
	//有効なものだけ操作
	for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	{
		if ((*itr)->GetIsValid())
		{
			(*itr)->draw();
		}
	}
}


void EnemyManager::CountDown() 
{
	//有効なものだけ操作
	for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	{
		if ((*itr)->GetIsValid())
		{
			if ((*itr)->CountDown())
			{
				//とりあえず消しておく
				(*itr)->SetIsValid(false);
			}
		}
	}
}

void EnemyManager::GenerateEnemy(int heightNum, int speed, float startTime)
{
	//無効なものを探す
	for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	{
		if (!(*itr)->GetIsValid())
		{
			(*itr)->Init(heightNum, speed, startTime);
			return;
		}
	}

	//無効なものが無い場合生成
	std::shared_ptr<Enemy> smpEnemy = std::make_unique<Enemy>();
	m_smpEnemyArray << smpEnemy;
	smpEnemy->Init(heightNum, speed, startTime);

}

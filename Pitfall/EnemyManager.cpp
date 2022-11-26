#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		m_hitStatus[i] = 0;
	}

	//５つ生成しておく
	//for (int i = 0; i < 5; i++)
	//{
	//	std::shared_ptr<Enemy> smpEnemy = std::make_unique<Enemy>();
	//	m_smpEnemyArray << smpEnemy;
	//}

	//最初に5個メモリを確保
	for (int i = 0; i < 5; i++)
	{
		std::shared_ptr<EnemyUnit> smpEnemyUnit = std::make_unique<EnemyUnit>();
		m_smpEnemyUnitArray << smpEnemyUnit;
	}

}

EnemyManager::~EnemyManager() {

}


void EnemyManager::update()
{
	//有効なものだけ操作
	//for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	//{
	//	if ((*itr)->GetIsValid())
	//	{
	//		(*itr)->update();
	//	}
	//}

	//位置更新
	for (auto itr = m_smpEnemyUnitArray.begin(); itr != m_smpEnemyUnitArray.end(); itr++)
	{
		//有効なものだけ操作
		if ((*itr)->m_isValid)
		{
			(*itr)->UpdateEnemyPos();
		}
	}

}

void EnemyManager::draw() const
{
	//有効なものだけ操作
	//for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	//{
	//	if ((*itr)->GetIsValid())
	//	{
	//		(*itr)->draw();
	//	}
	//}


	for (auto itr = m_smpEnemyUnitArray.begin(); itr != m_smpEnemyUnitArray.end(); itr++)
	{
		if ((*itr)->m_isValid)
		{
			(*itr)->draw();
		}
	}
}


void EnemyManager::CountDown() 
{
	//有効なものだけ操作
	//for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	//{
	//	if ((*itr)->GetIsValid())
	//	{
	//		if (!(*itr)->GetIsHit())
	//		{
	//			(*itr)->CountDown();
	//		}


	//		//if ((*itr)->CountDown())
	//		//{
	//			//とりあえず消しておく
	//			//(*itr)->SetIsValid(false);
	//		//}
	//	}
	//}
}

void EnemyManager::UpdateHitIndex()
{
	//初期化
	//for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	//{
	//	m_hitStatus[i] = 0;
	//}

	////有効なものだけ操作
	//for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	//{
	//	if ((*itr)->GetIsValid())
	//	{
	//		if ((*itr)->GetIsHit())
	//		{
	//			int index = (*itr)->GetHeightNum();
	//			if (m_hitStatus[index] != 0)
	//			{
	//				assert(false); //２つぶつかるものがある
	//			}

	//			m_hitStatus[index] = 1; //TODO １固定
	//		}

	//	}
	//}
}

void EnemyManager::Explosion()
{
	//有効なものだけ操作
	//for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	//{
	//	if ((*itr)->GetIsValid())
	//	{
	//		if ((*itr)->GetIsHit())
	//		{
	//			(*itr)->Explosion();
	//		}

	//	}
	//}
}

//void EnemyManager::GenerateEnemy(int heightNum, int speed, float startTime)
//{
//	////無効なものを探す
//	//for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
//	//{
//	//	if (!(*itr)->GetIsValid())
//	//	{
//	//		(*itr)->Init(heightNum, speed, startTime);
//	//		return;
//	//	}
//	//}
//
//	////無効なものが無い場合生成
//	//std::shared_ptr<Enemy> smpEnemy = std::make_unique<Enemy>();
//	//m_smpEnemyArray << smpEnemy;
//	//smpEnemy->Init(heightNum, speed, startTime);
//
//}

std::shared_ptr<EnemyManager::EnemyUnit> EnemyManager::GetEnemyUnit()
{
	//無効なものを探す
	for (auto itr = m_smpEnemyUnitArray.begin(); itr != m_smpEnemyUnitArray.end(); itr++)
	{
		if (!(*itr)->m_isValid)
		{
			return *itr;
		}
	}

	//無効なものが無い場合生成
	std::shared_ptr<EnemyUnit> smpEnemyUnit = std::make_unique<EnemyUnit>();
	m_smpEnemyUnitArray << smpEnemyUnit;
	return smpEnemyUnit;
}

void EnemyManager::EnemyUnitInit(std::shared_ptr<EnemyUnit> smpEnemyUnit, float startTime)
{
	smpEnemyUnit->m_isValid = true;
	smpEnemyUnit->m_count = 5; //TODO
	smpEnemyUnit->m_endTime = startTime + smpEnemyUnit->m_count * 1.0f;


	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		if (RandomBool(0.3))
		{
			float speed = Random(1.0, 3.0);
			smpEnemyUnit->m_smpEnemies[i].Init(speed);
		}
	}

}

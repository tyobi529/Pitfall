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
		(*itr)->UpdateEnemyPos();
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
		(*itr)->draw();
	}
}


void EnemyManager::updateEverySecond()
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

	for (auto itr = m_smpEnemyUnitArray.begin(); itr != m_smpEnemyUnitArray.end(); itr++)
	{
		(*itr)->CountDown();
	}

	UpdateHitStatus();
}


void EnemyManager::UpdateHitStatus()
{
	//初期化
	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		m_hitStatus[i] = 0;
	}

	//有効なものだけ操作
	for (auto itr = m_smpEnemyUnitArray.begin(); itr != m_smpEnemyUnitArray.end(); itr++)
	{
		if ((*itr)->m_isValid)
		{
			if ((*itr)->m_count == 0)
			{
				for (int i = 0; i < Define::BLOCK_NUM; i++)
				{
					if ((*itr)->m_smpEnemies[i].GetIsValid())
					{
						m_hitStatus[i] = 1; //TODO １固定
					}
				}

				//無効に
				(*itr)->m_isValid = false;

				break;
			}

		}
	}
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
	smpEnemyUnit->m_count = 10; //TODO
	smpEnemyUnit->m_endTime = startTime + smpEnemyUnit->m_count * 1.0f;

	float color_r = Random(0.0f, 1.0f);

	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		if (RandomBool(0.3))
		{
			//同じレーンにオブジェクトがあるか判定する
			int limitSpeedLevel = 0;
			for (auto itr = m_smpEnemyUnitArray.begin(); itr != m_smpEnemyUnitArray.end(); itr++)
			{
				if ((*itr)->m_isValid)
				{
					if ((*itr)->m_smpEnemies[i].GetIsValid())
					{
						int speedLevel = (*itr)->m_smpEnemies[i].GetSpeedLevel();
						if (speedLevel > limitSpeedLevel)
							limitSpeedLevel = speedLevel;
					}
				}
			}

			int speedLevel = 0;

			if (limitSpeedLevel > 0)
			{
				//limitSpeedより早くないと重なってしまう。
				speedLevel = Random(limitSpeedLevel, Define::SPEED_LEVEL_MAX);
			}
			else
			{
				speedLevel = Random(Define::SPEED_LEVEL_MIN, Define::SPEED_LEVEL_MAX);
			}

			//3段階
			//int tmp = Random(1, 3);
			//float speed = 0.5f * tmp;

			smpEnemyUnit->m_smpEnemies[i].Init(true, speedLevel);
			//TODO
			smpEnemyUnit->m_smpEnemies[i].SetColor(color_r);

		}
		else
		{
			smpEnemyUnit->m_smpEnemies[i].Init(false);
		}
	}

}

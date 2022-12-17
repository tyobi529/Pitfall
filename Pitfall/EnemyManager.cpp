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
		std::shared_ptr<Enemy> smpEnemy = std::make_unique<Enemy>();
		m_smpEnemyArray << smpEnemy;
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
	for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	{
		//(*itr)->UpdateEnemyPos();

		(*itr)->update();


		//if (!m_isValid)
		//	return;

		//float difTime = m_endTime - Scene::Time();
		//for (int i = 0; i < Define::BLOCK_NUM; i++)
		//{
		//	m_smpEnemies[i].UpdatePos(difTime);
		//}
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


	for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	{
		(*itr)->draw();
	}
}


void EnemyManager::updateInterval()
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

	for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	{
		(*itr)->updateInterval();
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
	for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	{
		if ((*itr)->m_isValid)
		{
			if ((*itr)->m_count == 0)
			{
				for (int i = 0; i < Define::BLOCK_NUM; i++)
				{

					//std::shared_ptr<EnemyBlock> smpEnemyBlock = std::static_pointer_cast<EnemyBlock>((*itr)->m_smpBlockUnit->GetObject(i));
					m_hitStatus[i] = (*itr)->m_smpBlockUnit->GetObject(i)->GetType();
					//if ((*itr)->m_smpEnemies[i].GetIsValid())
					//{
					//	m_hitStatus[i] = 1; //TODO １固定
					//}
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

std::shared_ptr<Enemy> EnemyManager::GetEnemy()
{
	//無効なものを探す
	for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	{
		if (!(*itr)->m_isValid)
		{
			return *itr;
		}
	}

	//無効なものが無い場合生成
	std::shared_ptr<Enemy> smpEnemy = std::make_unique<Enemy>();
	m_smpEnemyArray << smpEnemy;
	return smpEnemy;
}

void EnemyManager::EnemyInit(std::shared_ptr<Enemy> smpEnemy, float startTime)
{
	smpEnemy->m_isValid = true;
	smpEnemy->m_count = 20; //TODO
	smpEnemy->m_endTime = startTime + smpEnemy->m_count * Define::INTERVAL_TIME;

	float color_r = Random(0.0f, 1.0f);

	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		if (RandomBool(0.3))
		{
			//同じレーンにオブジェクトがあるか判定する
			int limitSpeedLevel = 0;
			for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
			{
				if ((*itr)->m_isValid)
				{
					if ((*itr)->m_smpBlockUnit->GetObject(i)->GetType() != Block::BLOCK_NONE)
					{
						std::shared_ptr<EnemyBlock> smpEnemyBlock = std::static_pointer_cast<EnemyBlock>((*itr)->m_smpBlockUnit->GetObject(i));
						int speedLevel = smpEnemyBlock->m_speedLevel;
						if (speedLevel > limitSpeedLevel)
							limitSpeedLevel = speedLevel;
					}

					//if ((*itr)->m_smpEnemies[i].GetIsValid())
					//{
					//	int speedLevel = (*itr)->m_smpEnemies[i].GetSpeedLevel();
					//	if (speedLevel > limitSpeedLevel)
					//		limitSpeedLevel = speedLevel;
					//}
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

			std::shared_ptr<EnemyBlock> smpEnemyBlock = std::static_pointer_cast<EnemyBlock>(smpEnemy->m_smpBlockUnit->GetObject(i));
			float posY = Define::LIMIT_POS_Y_HURDLE_BOTTOM + Define::BLOCK_SIZE * i;
			smpEnemyBlock->SetPosition(1000, posY); //初期位置指定
			smpEnemyBlock->SetSize(1.0f); //初期サイズ指定
			switch (speedLevel)
			{
			case 1:
				smpEnemyBlock->SetType(Block::BLOCK_ENEMY_1);
				break;
			case 2:
				smpEnemyBlock->SetType(Block::BLOCK_ENEMY_2);
				break;
			case 3:
				smpEnemyBlock->SetType(Block::BLOCK_ENEMY_3);
				break;
			default:
				assert(false);
				break;
			}
			smpEnemyBlock->m_speedLevel = speedLevel;

			//smpEnemyUnit->m_smpEnemies[i].Init(true, speedLevel);
			//TODO
			//smpEnemyUnit->m_smpEnemies[i].SetColor(color_r);

		}
		else
		{
			std::shared_ptr<EnemyBlock> smpEnemyBlock = std::static_pointer_cast<EnemyBlock>(smpEnemy->m_smpBlockUnit->GetObject(i));
			smpEnemyBlock->SetType(Block::BLOCK_NONE);
		}
	}

}

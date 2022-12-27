#include "EnemyManager.h"

EnemyManager::EnemyManager() :
	m_generateCount(0)
{
	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		m_indexArray << i;
	}

	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		m_hitStatus[i] = 0;
	}

	//for (int i = 0; i < Define::BLOCK_NUM; i++)
	//{
	//	m_GenerateTypes[i] = Block::BLOCK_NONE;
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
	//位置更新
	for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	{

		(*itr)->update();

	}

}

void EnemyManager::draw() const
{

	for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	{
		(*itr)->draw();
	}
}


void EnemyManager::updateInterval()
{

	for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	{
		(*itr)->updateInterval();
	}

	UpdateHitStatus();
}


void EnemyManager::UpdateHitStatus()
{
	//初期化
	for (int i = 0; i < Define::BLOCK_NUM; i++)
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

					m_hitStatus[i] = (*itr)->m_smpBlockUnit->GetObject(i)->GetType();
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
	//smpEnemy->m_count = 20; //TODO
	//smpEnemy->m_endTime = startTime + smpEnemy->m_count * Define::INTERVAL_SECOND;

	smpEnemy->m_count = Define::ENEMY_COUNT; 
	smpEnemy->m_endTime = startTime + (float)Define::ENEMY_COUNT * Define::INTERVAL_SECOND;



	//一旦初期化
	for (int i = 0; i < Define::BLOCK_NUM; i++)
	{
		std::shared_ptr<EnemyBlock> smpEnemyBlock = std::static_pointer_cast<EnemyBlock>(smpEnemy->m_smpBlockUnit->GetObject(i));
		smpEnemyBlock->SetType(Block::BLOCK_NONE);
	}

	//TODO
	int generateNum = 3;
	Array indexArray = m_indexArray.choice(generateNum);
	for (int i = 0; i < generateNum; i++)
	{
		int index = indexArray[i];
		std::shared_ptr<EnemyBlock> smpEnemyBlock = std::static_pointer_cast<EnemyBlock>(smpEnemy->m_smpBlockUnit->GetObject(index));
		float posY = Define::LIMIT_POS_Y_HURDLE_BOTTOM + Define::BLOCK_SIZE * index;
		smpEnemyBlock->SetPosition(1000, posY); //初期位置指定
		smpEnemyBlock->SetSize(1.0f); //初期サイズ指定

		//種類
		//同じindexで最も遅いブロックを探す
		int tmp = -1;
		Block::TYPE type = CheckSlowEnemyType(index);
		if (type == Block::BLOCK_ENEMY_1)
		{
			tmp = 1;
		}
		else if (type == Block::BLOCK_ENEMY_2)
		{
			tmp = Random(1, 2);
		}
		else
		{
			tmp = Random(1, 3);
		}
		
		//3段階
		//int tmp = Random(1, 3);
		//int tmp = Random(1, 4);
		//tmp = 3;
		switch (tmp)
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
		case 4:
			smpEnemyBlock->SetType(Block::BLOCK_ENEMY_COIN);
			break;
		default:
			assert(false);
			break;
		}
		smpEnemyBlock->SetTime(smpEnemy->m_endTime);
	}

	//for (int i = 0; i < Define::BLOCK_NUM; i++)
	//{
	//	if (RandomBool(0.3))
	//	{



	//		std::shared_ptr<EnemyBlock> smpEnemyBlock = std::static_pointer_cast<EnemyBlock>(smpEnemy->m_smpBlockUnit->GetObject(i));
	//		float posY = Define::LIMIT_POS_Y_HURDLE_BOTTOM + Define::BLOCK_SIZE * i;
	//		smpEnemyBlock->SetPosition(1000, posY); //初期位置指定
	//		smpEnemyBlock->SetSize(1.0f); //初期サイズ指定

	//		//3段階
	//		//int tmp = Random(1, 3);
	//		int tmp = Random(1, 4);
	//		tmp = 3;
	//		switch (tmp)
	//		{
	//		case 1:
	//			smpEnemyBlock->SetType(Block::BLOCK_ENEMY_1);
	//			break;
	//		case 2:
	//			smpEnemyBlock->SetType(Block::BLOCK_ENEMY_2);
	//			break;
	//		case 3:
	//			smpEnemyBlock->SetType(Block::BLOCK_ENEMY_3);
	//			break;
	//		case 4:
	//			smpEnemyBlock->SetType(Block::BLOCK_ENEMY_COIN);
	//			break;
	//		default:
	//			assert(false);
	//			break;
	//		}
	//		smpEnemyBlock->SetTime(smpEnemy->m_endTime);

	//	}
	//	else
	//	{
	//		std::shared_ptr<EnemyBlock> smpEnemyBlock = std::static_pointer_cast<EnemyBlock>(smpEnemy->m_smpBlockUnit->GetObject(i));
	//		smpEnemyBlock->SetType(Block::BLOCK_NONE);
	//	}
	//}

}

void EnemyManager::NextEnemy(float startTime)
{

	if (m_generateCount == 1)
	{
		m_generateCount = 0;
		EnemyInit(GetEnemy(), startTime);
	}
	else
	{
		m_generateCount++;
	}

}

Block::TYPE EnemyManager::CheckSlowEnemyType(int index)
{
	Block::TYPE type = Block::BLOCK_NONE;

	for (auto itr = m_smpEnemyArray.begin(); itr != m_smpEnemyArray.end(); itr++)
	{
		if ((*itr)->m_isValid)
		{
			std::shared_ptr<EnemyBlock> smpEnemyBlock = std::static_pointer_cast<EnemyBlock>((*itr)->m_smpBlockUnit->GetObject(index));
			if (smpEnemyBlock->GetType() != Block::BLOCK_NONE)
			{
				if (type == Block::BLOCK_NONE)
				{
					type = smpEnemyBlock->GetType();
				}
				else
				{
					if (type > smpEnemyBlock->GetType())
					{
						type = smpEnemyBlock->GetType();
					}
				}

			}
		}
	}

	return type;


}

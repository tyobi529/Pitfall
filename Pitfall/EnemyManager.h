#pragma once

#include <Siv3D.hpp>

#include "Define.h"
#include "Enemy.h"

class EnemyManager
{
public:

	EnemyManager();
	~EnemyManager();

	void update();
	void draw() const;

	void CountDown();

	void UpdateHitIndex();
	const int* const GetHitStatus(){ return m_hitStatus; };

	void Explosion();

	//void GenerateEnemy(int heightNum, int speed, float startTime);


	struct EnemyUnit
	{
		bool m_isValid;
		//float m_startTime;
		Enemy m_smpEnemies[Define::BLOCK_NUM];
		int m_count;
		float m_endTime;

		EnemyUnit() :
			m_isValid(false),
			m_count(0),
			m_endTime(0)
		{
			//indexだけ最初に入れる
			for (int i = 0; i < Define::BLOCK_NUM; i++)
			{
				m_smpEnemies[i].SetHeightNum(i);
			}
		};

		~EnemyUnit() {};

		void draw() const
		{
			for (int i = 0; i < Define::BLOCK_NUM; i++)
			{
				m_smpEnemies[i].draw();
			}
		};


		void UpdateEnemyPos()
		{
			float difTime = m_endTime - Scene::Time();
			for (int i = 0; i < Define::BLOCK_NUM; i++)
			{
				m_smpEnemies[i].UpdatePos(difTime);
			}
		};

		//void Init()
		//{
		//	m_isValid = true;

		//	//for (int i = 0; i < Define::BLOCK_NUM; i++)
		//	//	m_smpEnemies[i].Init();
		//}
	};

	std::shared_ptr<EnemyUnit> GetEnemyUnit();
	void EnemyUnitInit(std::shared_ptr<EnemyUnit> smpEnemyUnit, float startTime);

private:
	//Array<std::shared_ptr<Enemy>> m_smpEnemyArray;

	int m_hitStatus[Define::BLOCK_HURDLE_NUM]; //0何もなし。1:Hit

	//std::shared_ptr<EnemyUnit> m_smpEnemyUnits[5];
	Array<std::shared_ptr<EnemyUnit>> m_smpEnemyUnitArray;


};


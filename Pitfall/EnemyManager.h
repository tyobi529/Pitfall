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

	void updateEverySecond();

	void UpdateHitStatus();
	const int* const GetHitStatus(){ return m_hitStatus; };

	void Explosion();

	//void GenerateEnemy(int heightNum, int speed, float startTime);


	//struct EnemyUnit
	//{
	//	bool m_isValid;
	//	//float m_startTime;
	//	Enemy m_smpEnemies[Define::BLOCK_NUM];
	//	int m_count;
	//	float m_endTime;

	//	EnemyUnit() :
	//		m_isValid(false),
	//		m_count(0),
	//		m_endTime(0)
	//	{
	//		//indexだけ最初に入れる
	//		for (int i = 0; i < Define::BLOCK_NUM; i++)
	//		{
	//			//m_smpEnemies[i].SetHeightNum(i);
	//		}
	//	};

	//	~EnemyUnit() {};

	//	void draw() const
	//	{
	//		if (!m_isValid)
	//			return;

	//		for (int i = 0; i < Define::BLOCK_NUM; i++)
	//		{
	//			m_smpEnemies[i].draw();
	//		}
	//	};


	//	void UpdateEnemyPos()
	//	{
	//		if (!m_isValid)
	//			return;

	//		float difTime = m_endTime - Scene::Time();
	//		for (int i = 0; i < Define::BLOCK_NUM; i++)
	//		{
	//			m_smpEnemies[i].UpdatePos(difTime);
	//		}
	//	};

	//	//１秒ごとに呼ぶ
	//	void CountDown()
	//	{
	//		if (!m_isValid)
	//			return;

	//		m_count--;

	//		//TODO
	//		//if (m_count == 0)
	//		//{
	//		//	m_isValid = false;
	//		//}
	//	};

	//	//void Init()
	//	//{
	//	//	m_isValid = true;

	//	//	//for (int i = 0; i < Define::BLOCK_NUM; i++)
	//	//	//	m_smpEnemies[i].Init();
	//	//}
	//};

	//std::shared_ptr<EnemyUnit> GetEnemyUnit();
	//void EnemyUnitInit(std::shared_ptr<EnemyUnit> smpEnemyUnit, float startTime);

	std::shared_ptr<Enemy> GetEnemy();
	void EnemyInit(std::shared_ptr<Enemy> smpEnemy, float startTime);

private:

	int m_hitStatus[Define::BLOCK_HURDLE_NUM]; //0何もなし。1:Hit

	//Array<std::shared_ptr<EnemyUnit>> m_smpEnemyUnitArray;
	Array<std::shared_ptr<Enemy>> m_smpEnemyArray;


};


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


	std::shared_ptr<Enemy> GetEnemy();
	void EnemyInit(std::shared_ptr<Enemy> smpEnemy, float startTime);

private:

	int m_hitStatus[Define::BLOCK_HURDLE_NUM]; //0何もなし。1:Hit

	Array<std::shared_ptr<Enemy>> m_smpEnemyArray;


};


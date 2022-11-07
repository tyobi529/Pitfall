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


	void GenerateEnemy(int heightNum, int speed, float startTime);

private:
	Array<std::shared_ptr<Enemy>> m_smpEnemyArray;



};


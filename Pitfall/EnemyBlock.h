#pragma once
#include "Block.h"

class EnemyBlock : public Block
{
public:
	EnemyBlock();
	~EnemyBlock();

	void EnemyInit();

	void update() override;

	void UpdatePos(float difTime);

	int m_speedLevel;

private:
};


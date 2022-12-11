#pragma once
#include "Block.h"

class EnemyBlock : public Block
{
public:
	EnemyBlock();
	~EnemyBlock();

	void Init() override;

	void update() override;

	void UpdatePos(float difTime);

	int m_speedLevel;

private:
};


#pragma once
#include "Block.h"

class EnemyBlock : public Block
{
public:
	EnemyBlock();
	~EnemyBlock();

	enum STATE
	{
		STATE_IDLE,
		STATE_IN,
		STATE_DELAY,
		STATE_MAIN,
		STATE_END,
	};

	void EnemyInit();

	void update() override;

	void UpdatePos(float difTime);

	void SetState(STATE state) { m_state = state; };

	int m_speedLevel;

private:
	STATE m_state;
};


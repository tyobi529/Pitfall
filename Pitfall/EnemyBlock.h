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

	//void UpdatePos(float difTime);

	void SetState(STATE state) { m_state = state; };

	int m_speedLevel;

	void SetTime(float endTime);

private:
	STATE m_state;

	//追加
	float m_inStartTime;
	float m_delayStartTime;
	//float m_inEndTime;
	float m_moveStartTime;
	//float m_moveEndTime;

	float m_moveSecond; //動いてから当たるまでの時間
};


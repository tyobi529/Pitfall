#pragma once
#include "Block.h"

class EnemyBlock : public Block
{
public:
	EnemyBlock();
	~EnemyBlock();

	void EnemyInit();

	void update() override;


	void SetTime(float endTime);

private:

	//追加
	float m_inStartTime;
	float m_delayStartTime;
	//float m_inEndTime;
	float m_moveStartTime;
	//float m_moveEndTime;

	float m_moveSecond; //動いてから当たるまでの時間
};


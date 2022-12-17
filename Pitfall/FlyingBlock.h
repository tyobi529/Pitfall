#pragma once

#include "Block.h"

class FlyingBlock : public Block
{
public:
	enum STATE
	{
		STATE_MOVE_SLOW, 
		STATE_MOVE,
		STATE_END,
	};

	FlyingBlock();
	~FlyingBlock();

	void FlyingInit(Vec3 startPos);

	void update() override;
	void updateEverySecond();


	STATE GetState() { return m_state; };

private:
	STATE m_state;
	Vec3 m_startPos;
	float m_startTime;

	Vec3 m_rotSpeed; //回転速度（yを大きめに）
};


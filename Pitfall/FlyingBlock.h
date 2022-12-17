#pragma once

#include "Block.h"

class FlyingBlock : public Block
{
public:
	enum STATE
	{
		STATE_SLOW, 
		STATE_MAIN,
		STATE_END,
	};

	FlyingBlock();
	~FlyingBlock();

	void FlyingInit(Vec3 startPos);

	void update() override;

	STATE GetState() { return m_state; };

private:
	STATE m_state;
	Vec3 m_startPos;
	float m_startTime;
};


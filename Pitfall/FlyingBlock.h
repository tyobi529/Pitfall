#pragma once

#include "Block.h"

class FlyingBlock : public Block
{
public:
	enum STATE
	{
		//敵に当たって飛ぶブロック
		//STATE_BLOW_SLOW,
		STATE_BLOW,
		//リセット時にあふれるブロック
		STATE_OVERFLOW,

		STATE_END,
	};

	FlyingBlock();
	~FlyingBlock();

	void FlyingInit(Vec3 startPos);
	void OverFlowInit(Vec3 startPos);

	void update() override;
	void updateInterval();


	STATE GetState() { return m_state; };

private:
	STATE m_state;
	Vec3 m_startPos;
	float m_startTime;

	Vec3 m_rotSpeed; //回転速度（yを大きめに）

	Vec3 m_moveDir;
};


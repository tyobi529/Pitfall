#pragma once
//#include "Siv3D.hpp"
#include "Block.h"
#include "Tween.hpp"
#include "Define.h"

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

	struct Tweens
	{
		void start()
		{
			tweenPosX.start();
			tweenPosY.start();
			tweenPosZ.start();

			tweenRotVal.start();
		}

		bool update()
		{
			bool isEnd = true;

			isEnd &= !tweenPosX.update();
			isEnd &= !tweenPosY.update();
			isEnd &= !tweenPosZ.update();
			isEnd &= !tweenRotVal.update();

			if (isEnd) return false;

			return true;
		}

		Tween::Timeline tweenPosX;
		Tween::Timeline tweenPosY;
		Tween::Timeline tweenPosZ;

		Tween::Timeline tweenRotVal;

	};

private:
	STATE m_state;
	Vec3 m_startPos;
	float m_startTime;

	Vec3 m_rotSpeed; 

	std::unique_ptr<Tweens> m_smpTweens;
};


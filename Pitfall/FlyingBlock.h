#pragma once
//#include "Siv3D.hpp"
#include "Block.h"
#include "Tween.hpp"
#include "Define.h"

class FlyingBlock : public Block
{
public:

	FlyingBlock();
	~FlyingBlock();

	void BlowInit(Vec3 startPos);
	void OverFlowInit(float posY, double angle);

	void update() override;
	void updateInterval();


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

	bool m_isFlying;

private:

	Vec3 m_startPos;
	float m_startTime;

	Vec3 m_rotSpeed; 

	std::unique_ptr<Tweens> m_smpTweens;
};


#pragma once

#include "PlayerBlock.h"
#include "FlyingBlockManager.h"

class Player
{
public:

	Player();
	~Player();

	void update();
	void draw() const;
	void updateInterval();


	void CreateBlock();
	void DropBlock();
	void CheckHit(const int* hitStatus);

	std::shared_ptr<BlockUnit> m_smpBlockUnit;


private:
	std::shared_ptr<FlyingBlockManager> m_smpFlyingBlockManager;

	int m_preIndex[Define::BLOCK_NUM];
	int m_headIndex;

	float m_fallTime; //0.5秒以内で落ちる想定
	float m_fallValue;


};


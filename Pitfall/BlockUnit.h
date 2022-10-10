#pragma once

#include "Block.h"
#include "Define.h"

class BlockUnit
{
public:
	BlockUnit();
	~BlockUnit();

	void Init(float generatedTime, float generatedPosX = Define::BLOCK_GENERATED_POS_X);

	void update();
	void draw();

	void UpdatePos(float currentTime);
private:

	//std::vector<std::unique_ptr<Block>> m_blocks;


	std::unique_ptr<Block> m_blocks[Define::BLOCK_HURDLE_NUM];

	float m_generatedTime;
	float m_generatedPosX;
};


#pragma once

#include "Block.h"
#include "Define.h"

class BlockUnit
{
public:
	BlockUnit();
	~BlockUnit();

	void Init(Block::TYPE* types);

	void update();
	void draw();

	void UpdatePos(float moveX);

private:

	//std::vector<std::unique_ptr<Block>> m_blocks;

	std::unique_ptr<Block> m_tBlocks[Define::BLOCK_GROUND_TOP_NUM];//上の固定部分
	std::unique_ptr<Block> m_bBlocks[Define::BLOCK_GROUND_BOTTOM_NUM];//下の固定部分

	std::unique_ptr<Block> m_hBlocks[Define::BLOCK_HURDLE_NUM];//真ん中の可変部分

	//float m_generatedTime;
	//float m_generatedPosX;
	//float m_posX;


};


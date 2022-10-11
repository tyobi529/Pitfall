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


	std::unique_ptr<Block> m_smpBlocks[Define::BLOCK_HURDLE_NUM];//真ん中の可変部分


};


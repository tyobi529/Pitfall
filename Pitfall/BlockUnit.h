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

	//void SetType(int index, Block::TYPE type);

	Block::TYPE GetBlockType(int index) { return m_smpBlocks[index]->GetType(); };

private:

	//Block::TYPE m_types[Define::BLOCK_HURDLE_NUM];

	std::unique_ptr<Block> m_smpBlocks[Define::BLOCK_HURDLE_NUM];


};


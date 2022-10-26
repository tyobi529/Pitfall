#pragma once

#include "Block.h"


class StageManager
{
public:
	StageManager();
	~StageManager();

	void SetNextBlockUnit(Block::TYPE* pType);

private:

	//std::shared_ptr<Block::TYPE> m_smpBlockTypes[Define::BLOCK_HURDLE_NUM];
	Block::TYPE m_smpBlockTypes[Define::BLOCK_HURDLE_NUM];


	int m_count;
	int m_intervalCount;

	int m_preStep;

	int m_baseNum;

	int m_generateCount;
};


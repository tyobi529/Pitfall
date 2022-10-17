#pragma once

//#include "Block.h"
#include "PlayerBlock.h"
#include "Define.h"

class BlockUnit
{
public:
	BlockUnit();
	~BlockUnit();

	//void Init(Block::TYPE* types);

	void EnemyInit();
	void PlayerInit();

	void SetUnitIndex(int unitIndex) { m_unitIndex = unitIndex; };

	std::shared_ptr<Block> GetBlock(int colIndex) { return m_smpBlocks[colIndex]; };

	void update();
	void draw();
	void SetCenterPos(float difX, float playerMoveX, float fallValue = 0);

	Block::TYPE GetBlockType(int index) { return m_smpBlocks[index]->GetType(); };

	void SetPreIndex(int blockIndex, int preIndex) { m_preIndex[blockIndex] = preIndex; };

private:
	//int m_rowIndex; //逆だけど一旦
	int m_unitIndex;

	//Block::TYPE m_types[Define::BLOCK_HURDLE_NUM];

	//std::unique_ptr<Block> m_smpBlocks[Define::BLOCK_HURDLE_NUM];
	std::shared_ptr<Block> m_smpBlocks[Define::BLOCK_HURDLE_NUM];

	//std::pair<int, int> m_moveInfo;
	int m_preIndex[Define::BLOCK_HURDLE_NUM];
};


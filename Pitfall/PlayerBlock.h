#pragma once

#include "Block.h"

class PlayerBlock : public Block
{
public:
	PlayerBlock(int rowIndex, int colIndex);
	~PlayerBlock();

	void SetMoveInfo(int preColIndex);



	void update() override;

	void Init();

	bool GetIsMove() { return m_isMove; };
	void SetIsMove(bool isMove) { m_isMove = isMove; };


	int GetPreColIndex() { return m_preColIndex; };


private:

	bool m_isMove;
	float m_maxDifY;

	int m_preColIndex;

	//拡大
	bool m_isExpand;
};


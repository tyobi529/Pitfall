#pragma once

#include "Block.h"

class PlayerBlock : public Block
{
public:
	PlayerBlock(int rowIndex, int colIndex);
	~PlayerBlock();

	void SetMoveInfo(int preColIndex);

	//bool GetIsMove(float difY);

	bool GetIsMove() { return m_isMove; };
	void SetIsMove(bool isMove) { m_isMove = isMove; };


	//float GetDifY();

	int GetPreColIndex() { return m_preColIndex; };


private:

	bool m_isMove;
	float m_maxDifY;

	int m_preColIndex;

};


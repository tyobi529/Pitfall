#pragma once

#include "Define.h"

class Block
{
public:

	enum TYPE {
		BLOCK_NONE, //何もない
		BLOCK_GROUND, //固定の地面部分
		BLOCK_NORMAL,
		BLOCK_PLAYER_HEAD,
		BLOCK_PLAYER_BODY,

	};
	
	Block(int rowIndex, int colIndex);
	~Block();

	virtual void update();
	void draw();

	TYPE GetType() { return m_type; };
	void SetType(TYPE type) { m_type = type; };


	void SetCenterPos(float difX = 0, float difY = 0);


	void SetMoveInfo(int preColIndex);

	void Init();

	int GetPreColIndex() { return m_preColIndex; };

	bool GetIsMove() { return m_isMove; };
	void SetIsMove(bool isMove) { m_isMove = isMove; };

protected:
	const int m_rowIndex;
	const int m_colIndex;

	Vec3 m_centerPos;
	float m_size;

private:

	//属性情報だけ持つ
	TYPE m_type;



	bool m_isMove;

	int m_preColIndex;

	//拡大
	bool m_isExpand;



};


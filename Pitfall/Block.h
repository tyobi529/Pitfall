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


	Block(int index);

	~Block();


	virtual void Init();


	virtual void update();
	void draw() const;

	TYPE GetType() { return m_type; };
	void SetType(TYPE type) { m_type = type; };


	void SetCenterPos(float posX, float posY);

	void SetMoveInfo(int preIndex);

	int GetPreIndex() { return m_preIndex; };

	bool GetIsMove() { return m_isMove; };
	void SetIsMove(bool isMove) { m_isMove = isMove; };

	bool CheckMoveStatus(float fallValue);

protected:
	//const int m_rowIndex;
	const int m_index; //下から何番目か

	Vec3 m_centerPos;
	float m_size;

private:

	//属性情報だけ持つ
	TYPE m_type;



	bool m_isMove;

	int m_preIndex;




};


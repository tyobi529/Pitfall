#pragma once

#include "Object.h"
#include "Define.h"

class Block : public Object
{
public:

	enum TYPE {
		BLOCK_NONE, //何もない
		BLOCK_GROUND, //固定の地面部分
		BLOCK_NORMAL,
		BLOCK_HEAD,
		BLOCK_BONUS,
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


protected:
	const int m_index; //下から何番目か


private:

	//属性情報だけ持つ
	TYPE m_type;



};


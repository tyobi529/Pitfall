#pragma once
class Block
{
public:

	enum TYPE {
		BLOCK_NONE, //何もない
		BLOCK_GROUND, //固定の地面部分
		//BLOCK_HALL, //穴をあげられる部分
		BLOCK_NORMAL,
		BLOCK_PLAYE_HEAD,
		BLOCK_PLAYE_BODY,

	};
	
	Block();
	~Block();

	void draw();

	void SetType(TYPE type);

	void SetPos(Vec3 pos);

	TYPE GetType() { return m_type; };

private:

	//属性情報だけ持つ
	TYPE m_type;


	Vec3 m_centerPos;


};


#pragma once
class Block
{
public:

	enum TYPE {
		BLOCK_NONE, //何もない
		BLOCK_GROUND, //固定の地面部分
		BLOCK_HALL, //穴をあげられる部分
		BLOCK_NORMAL, 
	};
	
	Block(TYPE type);
	~Block();

	void draw();

	void SetPos(Vec3 pos);

private:

	//属性情報だけ持つ
	TYPE m_type;


	Vec3 m_centerPos;


};


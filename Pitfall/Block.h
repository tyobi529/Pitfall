#pragma once
class Block
{
public:

	enum TYPE {
		BLOCK_NONE, //何もない
		BLOCK_GROUND, //固定の地面部分
		//BLOCK_HALL, //穴をあげられる部分
		BLOCK_NORMAL,
		BLOCK_PLAYER_HEAD,
		BLOCK_PLAYER_BODY,

	};
	
	Block(int rowIndex, int colIndex);
	~Block();

	void draw();

	void SetType(TYPE type);

	//void SetPos(Vec3 pos);

	void SetPos(float difX);


	TYPE GetType() { return m_type; };

private:

	//属性情報だけ持つ
	TYPE m_type;

	const int m_rowIndex;
	const int m_colIndex;


	Vec3 m_centerPos;


};


#pragma once

#include "Define.h"

class Block
{
public:

	enum TYPE {
		BLOCK_NONE, 
		BLOCK_GROUND, //固定の地面部分
		BLOCK_NORMAL,
		BLOCK_HEAD,
		BLOCK_BONUS,
		BLOCK_PLAYER_HEAD,
		BLOCK_PLAYER_BODY,
		BLOCK_ENEMY_1,
		BLOCK_ENEMY_2,
		BLOCK_ENEMY_3,
		BLOCK_FLYING,
	};


	Block();

	virtual ~Block() {};


	virtual void update() {};
	void draw() const;

	void SetPosition(float x, float y = -1, float z = -1);
	Vec3 GetPosition() { return m_pos; };

	void MovePosition(float moveX, float moveY = 0, float moveZ = 0);

	void SetSize(float value) { m_size = value; };

	TYPE GetType() { return m_type; };
	void SetType(TYPE type) { m_type = type; };


protected:
	float m_size;

private:
	Vec3 m_pos;
	//属性情報だけ持つ
	TYPE m_type;



};



struct BlockUnit
{
public:

	BlockUnit()
	{
		Init();
	};

	virtual ~BlockUnit() {};

	void Init()
	{
		for (int i = 0; i < Define::BLOCK_NUM; i++)
			m_smpBlocks[i].reset();
	}

	std::shared_ptr<Block> GetObject(int index)
	{
		if (0 <= index && index < Define::BLOCK_NUM)
			return m_smpBlocks[index];
		else
			return nullptr;
	};

	bool SetObject(int index, std::shared_ptr<Block> smpObject)
	{
		if (0 <= index && index < Define::BLOCK_NUM)
		{
			m_smpBlocks[index] = smpObject;
			return true;
		}
		else
		{
			return false;
		}
	}



private:
	std::shared_ptr<Block> m_smpBlocks[Define::BLOCK_NUM];

};

#pragma once

#include "Define.h"

class Block
{
public:

	enum TYPE {
		BLOCK_NONE, 
		BLOCK_GROUND, //固定の地面部分
		BLOCK_HEAD,
		BLOCK_BONUS,
		BLOCK_PLAYER_HEAD,
		BLOCK_PLAYER_BODY,
		BLOCK_PLAYER_BODY_DOWN,
		BLOCK_ENEMY_1,
		BLOCK_ENEMY_2,
		BLOCK_ENEMY_3,
		BLOCK_ENEMY_COIN,
		BLOCK_FLYING,
	};


	Block();

	virtual ~Block() {};


	virtual void update() {};
	void draw() const;

	void SetPosition(float x, float y = -1, float z = -1);
	Vec3 GetPosition() { return m_pos; };

	//void MovePosition(float moveX, float moveY = 0, float moveZ = 0);
	void MovePosition(Vec3 val);


	void SetQuaternion(float x, float y = 0, float z = 0) { m_quaternion = (Quaternion::RotateX(x * 10_deg) * Quaternion::RotateY(y * 10_deg) * Quaternion::RotateZ(z * 10_deg)); };
	void SetQuaternion(Vec3 rot) { m_quaternion = (Quaternion::RotateX(rot.x * 10_deg) * Quaternion::RotateY(rot.y * 10_deg) * Quaternion::RotateZ(rot.z * 10_deg)); };
	//void Rotate(Vec3 rot);
	
	void SetSize(float value) { m_size = value; };

	TYPE GetType() { return m_type; };
	void SetType(TYPE type) { m_type = type; };


protected:
	TYPE m_type;
	float m_size;

private:
	Vec3 m_pos;

	Quaternion m_quaternion;


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

#pragma once

#include "Define.h"

class Object
{
public:

	Object() :
		m_pos(Vec3(0, 0, 0)),
		m_size(0)
	{};

	virtual ~Object(){};


	virtual void update() {};
	virtual void draw() const {};

	void SetPosition(float x, float y, float z = 0) { m_pos = Vec3(x, y, z); };
	void SetSize(float value) { m_size = value; };
	
protected:
	Vec3 m_pos;
	float m_size;

private:


};


struct ObjectUnit
{
public:

	ObjectUnit()
	{
		Init();
	};

	virtual ~ObjectUnit(){}; 

	void Init()
	{
		for (int i = 0; i < Define::BLOCK_NUM; i++)
			m_smpObjects[i].reset();
	}

	std::shared_ptr<Object> GetObject(int index)
	{
		if (0 <= index && index < Define::BLOCK_NUM)
			return m_smpObjects[index];
		else
			return nullptr;
	};

	bool SetObject(int index, std::shared_ptr<Object> smpObject)
	{
		if (0 <= index && index < Define::BLOCK_NUM)
		{
			m_smpObjects[index] = smpObject;
			return true;
		}
		else
		{
			return false;
		}
	}



private:
	std::shared_ptr<Object> m_smpObjects[Define::BLOCK_NUM];

};

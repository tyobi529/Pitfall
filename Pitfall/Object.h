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

	ObjectUnit(){};

	virtual ~ObjectUnit() = 0 {}; //純粋仮想デストラクタの定義が必要

	Object* GetObject(int index)
	{
		if (0 <= index && index < Define::BLOCK_NUM)
			return &m_objects[index];
		else
			return nullptr;
	};

private:
	Object m_objects[Define::BLOCK_NUM];

	//virtual void update() {};
	//virtual void draw() const = 0;


};

#pragma once
class Object
{
public:

	Object() :
		m_pos(Vec3(0, 0, 0)),
		m_size(0)
	{};

	virtual ~Object() = 0 {}; //純粋仮想デストラクタの定義が必要


	virtual void update() {};
	virtual void draw() const = 0;

	void SetPosition(float x, float y, float z = 0) { m_pos = Vec3(x, y, z); };
	void SetSize(float value) { m_size = value; };
	
protected:
	Vec3 m_pos;
	float m_size;

private:




};


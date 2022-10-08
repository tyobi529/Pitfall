#pragma once
class Wall
{
public:
	enum TYPE {
		NORMAL,
		DAMAGE,
		DASH,
	};


	Wall(TYPE type, float height, float posY, float generatedTime);
	~Wall();

	//void update();
	//void draw();

	const TYPE GetType() { return m_type; };
	//float GetBottomPosY(float currentTime); //描画する下端のy座標を返す

	const float GetPosY() { return m_posY; };
	void SetPosY(float posY) { m_posY = posY; };

	float GetHeight() { return m_height; };


private:
	TYPE m_type;
	float m_height;
	//float m_generatedPosY; //生成された位置
	float m_posY; //y座標
	float m_generatedTime; //生成された時間
};


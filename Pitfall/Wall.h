#pragma once
class Wall
{
public:
	enum TYPE {
		NORMAL,
		DAMAGE,
		DASH,
	};


	Wall(TYPE type, float height, float generatedPosY, float generatedTime);
	~Wall();

	void update();
	void draw();

	TYPE GetType() { return m_type; };
	float GetBottomPosY(float currentTime); //描画する下端のy座標を返す
	float GetHeight() { return m_height; };


private:
	TYPE m_type;
	float m_height;
	float m_generatedPosY; //生成された位置
	float m_generatedTime; //生成された時間
};


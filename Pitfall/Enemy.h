#pragma once

#include "Define.h"

class Enemy
{
public:

	Enemy();
	~Enemy();

	void Init(int heightNum, int speed, float startTime);

	void update();
	void draw() const;

	//１秒ごとに呼ぶ
	bool CountDown();

	const bool GetIsValid() { return m_isValid; };
	void SetIsValid(bool isValid) { m_isValid = isValid; };

private:
	bool m_isValid; //trueで有効。pool用
	int m_heightNum; //下からの番号
	int m_speed; //1秒にm_speed分m_countを減らす
	float m_startTime;
	int m_count; //1秒に1減らす。0の時衝突？小さいほどスピード早い
	float m_endTime; //m_startTime + count * 1s

	Vec3 m_pos;
};


#pragma once

#include "Define.h"

class Enemy
{
public:

	Enemy();
	~Enemy();

	//void Init(int heightNum, int speed, float startTime);
	void Init(float speed);

	void UpdatePos(float difTime);

	void update();
	void draw() const;

	//１秒ごとに呼ぶ
	void CountDown();


	void Explosion();

	const bool GetIsValid() { return m_isValid; };
	//const bool GetIsHit() { return m_isHit; };

	const int GetHeightNum() { return m_heightNum; };
	void SetHeightNum(int heightNum) { m_heightNum = heightNum; };

	void SetIsValid(bool isValid) { m_isValid = isValid; };

private:

	//Initで指定
	bool m_isValid; //trueで有効。pool用
	float m_endTime; //m_startTime + count * 1s
	float m_speed; //1秒にm_speed分m_countを減らす

	int m_heightNum; //下からの番号
	Vec3 m_pos;

	//不要
	//int m_count; //1秒に1減らす。0の時衝突？小さいほどスピード早い
	//float m_startTime;
	//bool m_isHit; //プレイヤーにぶつかっている


	//bool m_isValid; //trueで有効。pool用
	//int m_heightNum; //下からの番号
	//int m_speed; //1秒にm_speed分m_countを減らす
	//float m_startTime;
	//int m_count; //1秒に1減らす。0の時衝突？小さいほどスピード早い
	//float m_endTime; //m_startTime + count * 1s

	//bool m_isHit; //プレイヤーにぶつかっている

	//Vec3 m_pos;
};


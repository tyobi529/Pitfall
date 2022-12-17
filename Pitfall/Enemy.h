﻿#pragma once

#include "Define.h"
#include "EnemyBlock.h"

class Enemy
{
public:

	Enemy();
	~Enemy();

	void update();
	void draw() const;
	void updateInterval();

	bool m_isValid;
	int m_count;
	float m_endTime;
	std::shared_ptr<BlockUnit> m_smpBlockUnit;

private:


};


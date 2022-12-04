#pragma once

#include "Object.h"

class Player
{
public:

	Player();
	~Player();

	void update();
	void draw();

private:
	std::shared_ptr<ObjectUnit> m_smpBlockUnit;

};


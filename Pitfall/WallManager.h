#pragma once

#include "Wall.h"

class WallManager
{
public:

	WallManager();
	~WallManager();

	void draw();

	void UpdateWallPos(float deltaPosY);

private:

	std::vector<std::unique_ptr<Wall>> m_smpLeftWalls;
	std::vector<std::unique_ptr<Wall>> m_smpRightWalls;


};

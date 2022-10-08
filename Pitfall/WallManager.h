#pragma once

#include "Wall.h"

class WallManager
{
public:

	WallManager();
	~WallManager();

	void draw();

	void UpdateWallPos(float deltaPosY);

	//Wall* GetPlayerWallType(bool isLeft); //プレイヤーがいる場所の壁を返す。
	std::shared_ptr<Wall> GetPlayerWallType(bool isLeft); //プレイヤーがいる場所の壁を返す。


private:

	//std::vector<std::unique_ptr<Wall>> m_smpLeftWalls;
	//std::vector<std::unique_ptr<Wall>> m_smpRightWalls;

	std::vector<std::shared_ptr<Wall>> m_smpLeftWalls;
	std::vector<std::shared_ptr<Wall>> m_smpRightWalls;


};

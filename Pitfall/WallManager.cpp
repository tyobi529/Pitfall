#include "stdafx.h"
#include "WallManager.h"

#include "Define.h"

WallManager::WallManager()
{
	float posY = -50;
	for (int i = 0; i < 30; i++)
	{
		float height = 0.2f * (i + 1);

		Wall::TYPE type;

		if (i % 3 == 0)
		{
			type = Wall::NORMAL;
		}
		else if (i % 3 == 1)
		{
			type = Wall::DAMAGE;
		}
		else
		{
			type = Wall::DASH;
		}

		m_smpWalls.push_back(std::make_unique<Wall>(type, height, posY, 0.f));

		posY += height;
	}
}

WallManager::~WallManager()
{

}

void WallManager::draw()
{
	//とりあえず決め打ち
	float playerPosX = 3.0f;
	float wallWidth = 3.0f;
	float depthZ = 1.0f;


	for (auto itr = m_smpWalls.begin(); itr != m_smpWalls.end(); itr++)
	{
		//float bottomPosY = (*itr)->GetBottomPosY(0);
		float bottomPosY = (*itr)->GetPosY();
		float height = (*itr)->GetHeight();

		Vec3 pos1 = Vec3{ -playerPosX , bottomPosY, 0 };
		Vec3 pos2 = Vec3{ -playerPosX - wallWidth , bottomPosY + height, depthZ };

		switch ((*itr)->GetType())
		{
		case Wall::NORMAL:
			Box::FromPoints(pos1, pos2).draw(ColorF{ 0.8, 0.6, 0.4 });
			break;
		case Wall::DAMAGE:
			Box::FromPoints(pos1, pos2).draw(ColorF{ 0.6, 0.6, 0.4 });
			break;
		case Wall::DASH:
			Box::FromPoints(pos1, pos2).draw(ColorF{ 0.8, 0.4, 0.4 });
			break;
		default:
			break;
		}
	}
}

void WallManager::UpdateWallPos(float deltaPosY)
{
	//const float deltaTime = (float)Scene::DeltaTime();
	//const float deltaPosY = (float)Scene::DeltaTime() * wallSpeed;

	for (auto itr = m_smpWalls.begin(); itr != m_smpWalls.end(); itr++)
	{
		float currentPosY = (*itr)->GetPosY();
		(*itr)->SetPosY(currentPosY + deltaPosY);
	}
}

//void WallManager::update()
//{
//
//}
//
//
//void WallManager::draw()
//{
//	for (auto itr = m_smpWalls.begin(); itr != m_smpWalls.end(); itr++)
//	{
//		//float bottomPosY = (*itr)->GetBottomPosY(0);
//		float bottomPosY = (*itr)->GetBottomPosY(getData);
//		float height = (*itr)->GetHeight();
//
//		Vec3 pos1 = Vec3{ -playerPosX , bottomPosY, 0 };
//		Vec3 pos2 = Vec3{ -playerPosX - wallWidth , bottomPosY + height, depthZ };
//
//		switch ((*itr)->GetType())
//		{
//		case Wall::NORMAL:
//			Box::FromPoints(pos1, pos2).draw(ColorF{ 0.8, 0.6, 0.4 });
//			break;
//		case Wall::DAMAGE:
//			Box::FromPoints(pos1, pos2).draw(ColorF{ 0.6, 0.6, 0.4 });
//			break;
//		case Wall::DASH:
//			Box::FromPoints(pos1, pos2).draw(ColorF{ 0.8, 0.4, 0.4 });
//			break;
//		default:
//			break;
//		}
//	}
//}



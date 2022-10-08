﻿# include "GameScene.h"
//#include "Wall.h"

#include "Define.h"

Vec3 GetDirection(double angle)
{
	const Vec2 dir = Circular{ 1.0, angle };
	return{ dir.x, 0.0, -dir.y };
}

Vec3 GetFocusPosition(const Vec3& eyePosition, double angle)
{
	return (eyePosition + GetDirection(angle));
}

GameScene::GameScene(const InitData& init)
	: IScene{ init }
	, m_gameTime(0)
	, m_timeSpeed(0)
{


	//camera = BasicCamera3D{ renderTexture.size(), 30_deg, Vec3{ 0, 16, -32 }, GetFocusPosition(eyePosition, angle) };
	camera = BasicCamera3D{ renderTexture.size(), 30_deg, eyePosition, GetFocusPosition(eyePosition, angle) };

	playerMesh = Mesh{ MeshData::Pyramid(1.0, 1.0) };

	InitGame();

}

void GameScene::InitGame()
{
	m_gameTime = 0.0f;
	m_timeSpeed = Define::TIME_SPEED_FIRST;

	playerPos = Vec3(0, 0, 0);

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

void GameScene::update()
{
	//ゲーム中動かさないがデバック用にカメラの移動
	ClearPrint();
	const float deltaTime = (float)Scene::DeltaTime();
	m_gameTime += deltaTime * m_timeSpeed;

	const float speed = (float)(deltaTime * 2.0);



	if (KeyW.pressed())
	{
		eyePosition += (GetDirection(angle) * speed);
	}

	if (KeyA.pressed())
	{
		eyePosition += (GetDirection(angle - 90_deg) * speed);
	}

	if (KeyS.pressed())
	{
		eyePosition += (-GetDirection(angle) * speed);
	}

	if (KeyD.pressed())
	{
		eyePosition += (GetDirection(angle + 90_deg) * speed);
	}

	if (KeyLeft.pressed())
	{
		angle -= (deltaTime * 30_deg);

		if (angle < 0_deg)
		{
			angle += 360_deg;
		}
	}

	if (KeyRight.pressed())
	{
		angle += (deltaTime * 30_deg);

		if (360_deg < angle)
		{
			angle -= 360_deg;
		}
	}

	// 位置・注目点情報を更新
	camera.setView(eyePosition, GetFocusPosition(eyePosition, angle));
	Print << U"angle: {:.1f}°"_fmt(Math::ToDegrees(angle));
	Print << U"direction: {:.2f}"_fmt(GetDirection(angle));
	Print << U"eyePositon: {:.1f}"_fmt(camera.getEyePosition());
	Print << U"focusPosition: {:.1f}"_fmt(camera.getFocusPosition());
	Graphics3D::SetCameraTransform(camera);



	if (MouseL.up())
	{
		isLeft = !isLeft;
	}
	else if (MouseR.up())
	{
		// 右クリックでタイトル画面へ
		changeScene(State::Title);

		getData().lastGameScore = m_score;

		return;
	}

	if (isLeft)
	{
		playerPos = Vec3(-5, 0, 0);
	}
	else
	{
		playerPos = Vec3(5, 0, 0);
	}

}

void GameScene::draw() const
{
	//Scene::SetBackground(ColorF{ 0.2 });
	FontAsset(U"GameSceneScore")(m_score).draw(10, 10);


	// 3D 描画
	const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) }; //これより後に書く
	{

		//playerMesh.draw(playerPos, ColorF{ 0.8, 0.6, 0.4 });


		//デバッグ
		const int length = 30;
		Line3D{ Vec3{-length, 0, 0}, Vec3{length, 0, 0} }.draw();
		Line3D{ Vec3{0, -length, 0}, Vec3{0, length, 0} }.draw();

		//int size = 1;
		//float posX = 3;


		//左の壁
		/*float offsetY = -20;
		int height = 40;
		Box::FromPoints(Vec3{ -playerPosX, offsetY, 0 }, Vec3{ -playerPosX - wallWidth, offsetY + height, depthZ }).draw();
		Box::FromPoints(Vec3{ playerPosX, offsetY, 0 }, Vec3{ playerPosX + wallWidth, offsetY + height, depthZ }).draw();*/

		//プレイヤー
		if (isLeft)
		{
			Box::FromPoints(Vec3{ -playerPosX, 0, 0 }, Vec3{ -playerPosX + depthZ, depthZ, depthZ }).draw(ColorF{ 0.8, 0.9, 0.4 });
		}
		else
		{
			Box::FromPoints(Vec3{ playerPosX, 0, 0 }, Vec3{ playerPosX - depthZ, depthZ, depthZ }).draw(ColorF{ 0.8, 0.9, 0.4 });
		}

		for (auto itr = m_smpWalls.begin(); itr != m_smpWalls.end(); itr++)
		{
			//float bottomPosY = (*itr)->GetBottomPosY(0);
			float bottomPosY = (*itr)->GetBottomPosY(m_gameTime);
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

	// 3D シーンを 2D シーンに描画
	{
		Graphics3D::Flush();
		renderTexture.resolve();
		Shader::LinearToScreen(renderTexture);
	}
}




# include "GameScene.h"
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
	, m_deltaTime(0)
	, m_timeSpeed(0)
	, m_wallSpeed(0)
{


	//camera = BasicCamera3D{ renderTexture.size(), 30_deg, Vec3{ 0, 16, -32 }, GetFocusPosition(eyePosition, angle) };
	camera = BasicCamera3D{ renderTexture.size(), 30_deg, eyePosition, GetFocusPosition(eyePosition, angle) };

	playerMesh = Mesh{ MeshData::Pyramid(1.0, 1.0) };

	InitGame();

}

void GameScene::InitGame()
{
	m_gameTime = 0.0f;
	m_deltaTime = 0.0f;
	m_timeSpeed = 1.0f;

	m_wallSpeed = Define::WALL_SPEED_FIRST;

	playerPos = Vec3(0, 0, 0);


	m_smpWallManager.reset(new WallManager());

}



void GameScene::update()
{
	//ゲーム中動かさないがデバック用にカメラの移動
	ClearPrint();
	m_deltaTime = (float)Scene::DeltaTime() * m_timeSpeed;
	m_gameTime += m_deltaTime;

	//getData().UpdateTime(m_timeSpeed);

	//const float deltaTime = (float)Scene::DeltaTime();
	//const float deltaTime = getData().gameTime;
	//const float speed = (float)(m_deltaTime * 2.0);
	const float speed = m_deltaTime * 2.0;


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
		angle -= (m_deltaTime * 30_deg);

		if (angle < 0_deg)
		{
			angle += 360_deg;
		}
	}

	if (KeyRight.pressed())
	{
		angle += (m_deltaTime * 30_deg);

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


	//壁の位置更新
	float deltaPosY = m_deltaTime * m_wallSpeed;
	m_smpWallManager->UpdateWallPos(deltaPosY);

	std::shared_ptr<Wall> smpWall = m_smpWallManager->GetPlayerWallType(isLeft);
	Wall::TYPE type = smpWall->GetType();
	switch (type)
	{
	case Wall::NORMAL:
		Print << U"NORMAL";
		break;
	case Wall::DAMAGE:
		Print << U"DAMAGE";
		break;
	case Wall::DASH:
		Print << U"DASH";
		break;
	default:
		break;
	}

}

void GameScene::draw() const
{
	//Scene::SetBackground(ColorF{ 0.2 });
	FontAsset(U"GameSceneScore")(m_score).draw(10, 10);


	// 3D 描画
	const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) }; //これより後に書く
	{


		//デバッグ
		const int length = 30;
		Line3D{ Vec3{-length, 0, 0}, Vec3{length, 0, 0} }.draw();
		Line3D{ Vec3{0, -length, 0}, Vec3{0, length, 0} }.draw();


		//プレイヤー
		if (isLeft)
		{
			Box::FromPoints(Vec3{ -playerPosX, 0, 0 }, Vec3{ -playerPosX + depthZ, depthZ, depthZ }).draw(ColorF{ 0.8, 0.9, 0.4 });
		}
		else
		{
			Box::FromPoints(Vec3{ playerPosX, 0, 0 }, Vec3{ playerPosX - depthZ, depthZ, depthZ }).draw(ColorF{ 0.8, 0.9, 0.4 });
		}

		m_smpWallManager->draw();

	}

	// 3D シーンを 2D シーンに描画
	{
		Graphics3D::Flush();
		renderTexture.resolve();
		Shader::LinearToScreen(renderTexture);
	}
}




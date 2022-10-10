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
	, eyePosition(Define::EYE_POS)
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

	//playerPos = Vec3(0, 0, 0);


	m_smpWallManager.reset(new WallManager());

	m_smpPlayer.reset(new Player());

	//m_smpBlockUnit.reset(new BlockUnit());

	Block::TYPE types[Define::BLOCK_HURDLE_NUM] = {};
	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
	{
		if (i < Define::BLOCK_HURDLE_HALL_NUM)
		{
			types[i] = Block::BLOCK_HALL;
		}
		else if (i < Define::BLOCK_HURDLE_HALL_NUM + Define::BLOCK_HURDLE_CENTER_NUM)
		{
			types[i] = Block::BLOCK_NONE;
		}
		else
		{
			types[i] = Block::BLOCK_HALL;
		}
	}
	for (int i = 0; i < Define::BLOCK_H_NUM; i++)
	{
		m_blockUnits[i] = std::make_unique<BlockUnit>();
		m_blockUnits[i]->Init(types, m_gameTime, Define::BLOCK_SIZE * i);

	}

}



void GameScene::update()
{
	//ゲーム中動かさないがデバック用にカメラの移動
	ClearPrint();
	m_deltaTime = (float)Scene::DeltaTime() * m_timeSpeed;
	m_gameTime += m_deltaTime;

	//float addSpeed = 0.02f;
	//m_timeSpeed += m_deltaTime * addSpeed;

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

	if (KeyUp.pressed())
	{
		eyePosition.y += speed;
	}

	if (KeyDown.pressed())
	{
		eyePosition.y -= speed;
	}

	if (KeyLeft.pressed())
	{
		eyePosition.x -= speed;

		//angle -= (m_deltaTime * 30_deg);

		//if (angle < 0_deg)
		//{
		//	angle += 360_deg;
		//}
	}

	if (KeyRight.pressed())
	{
		eyePosition.x += speed;

		//angle += (m_deltaTime * 30_deg);

		//if (360_deg < angle)
		//{
		//	angle -= 360_deg;
		//}
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

	//if (isLeft)
	//{
	//	playerPos = Vec3(-5, 0, 0);
	//}
	//else
	//{
	//	playerPos = Vec3(5, 0, 0);
	//}




	//壁の位置更新
	//float deltaPosY = m_deltaTime * m_wallSpeed;
	//m_smpWallManager->UpdateWallPos(deltaPosY);

	m_smpPlayer->update();

	//m_smpBlockUnit->update();

	//for (auto itr = m_smpBlockUnit.begin(); itr != m_smpBlockUnit.end(); itr++)
	//{
	//	(*itr)->update();
	//}

	for (int i = 0; i < Define::BLOCK_H_NUM; i++)
	{
		//m_blockUnits[i]->UpdatePos(m_gameTime);
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

		int length = 30;
		Line3D{ Vec3{-length, 0, 0}, Vec3{length, 0, 0} }.draw(ColorF(0, 0, 0, 1));
		Line3D{ Vec3{0, -length, 0}, Vec3{0, length, 0} }.draw(ColorF(0, 0, 0, 1));
		for (int i = 1; i < 15; i++) //縦線
		{
			Line3D{ Vec3{i, -length, 0}, Vec3{i, length, 0} }.draw();
			Line3D{ Vec3{-i, -length, 0}, Vec3{-i, length, 0} }.draw();
		}
		for (int i = 1; i < 15; i++) //横線
		{
			Line3D{ Vec3{-length, i, 0}, Vec3{length, i, 0} }.draw();
			Line3D{ Vec3{-length, -i, 0}, Vec3{length, -i, 0} }.draw();
		}

		//プレイヤー
		//if (isLeft)
		//{
		//	//Box::FromPoints(Vec3{ -playerPosX, 0, 0 }, Vec3{ -playerPosX + depthZ, depthZ, depthZ }).draw(ColorF{ 0.8, 0.9, 0.4 });
		//	Box::FromPoints(Vec3{ -Define::PLAYER_POS.x, Define::PLAYER_POS.y, 0 }, Vec3{ -Define::PLAYER_POS.x + Define::DEPTH_Z, Define::PLAYER_POS.y + Define::DEPTH_Z, Define::DEPTH_Z }).draw(ColorF{ 0.8, 0.9, 0.4 });

		//}
		//else
		//{
		//	//Box::FromPoints(Vec3{ playerPosX, 0, 0 }, Vec3{ playerPosX - depthZ, depthZ, depthZ }).draw(ColorF{ 0.8, 0.9, 0.4 });
		//	Box::FromPoints(Vec3{ Define::PLAYER_POS.x, Define::PLAYER_POS.y, 0 }, Vec3{ Define::PLAYER_POS.x - Define::DEPTH_Z, Define::PLAYER_POS.y + Define::DEPTH_Z, Define::DEPTH_Z }).draw(ColorF{ 0.8, 0.9, 0.4 });
		//}

		//m_smpWallManager->draw();

		//Box::FromPoints(Vec3{ -Define::PLAYER_POS.x - 1.0f, i - 5.0f, 0 }, Vec3{ -Define::PLAYER_POS.x + Define::DEPTH_Z, Define::PLAYER_POS.y + Define::DEPTH_Z, Define::DEPTH_Z }).draw(ColorF{ 0.8, 0.9, 0.4 });
		//Vec3 pos1 = Vec3{ -Define::PLAYER_POS.x - 0.5f , -10.0f, -0.5f };
		//Vec3 pos2 = Vec3{ -Define::PLAYER_POS.x -0.5f - Define::WALL_WIDTH , 10.0f, 0.5f };
		//Box::FromPoints(pos1, pos2).draw(ColorF{ 0.8, 0.9, 0.4 });

		m_smpPlayer->draw();


	
		
		//m_smpBlockUnit->draw();
		//for (auto itr = m_smpBlockUnit.begin(); itr != m_smpBlockUnit.end(); itr++)
		//{
		//	(*itr)->draw();
		//}

		for (int i = 0; i < Define::BLOCK_H_NUM; i++)
		{
			m_blockUnits[i]->draw();
		}

		//Box::FromPoints(Vec3{ 0, 0, 0 }, Vec3{ 20, 5, 1 }).draw(TextureAsset(U"uvChecker"));

	}

	// 3D シーンを 2D シーンに描画
	{
		Graphics3D::Flush();
		renderTexture.resolve();
		Shader::LinearToScreen(renderTexture);
	}



	// 座標 (20, 40) を左上の基準位置にして、幅 400, 高さ 100 の長方形を描く
	//int size = 250;
	//Rect{ 0, Define::WIN_W - size, Define::WIN_H, size }.draw();
}

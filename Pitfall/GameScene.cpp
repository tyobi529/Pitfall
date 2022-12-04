# include "GameScene.h"
//#include "Wall.h"

#include "Define.h"

#define SIZE Define::BLOCK_SIZE
#define BLOCK_NUM Define::BLOCK_HURDLE_NUM
#define UNIT_NUM Define::BLOCK_H_NUM


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
	, m_blockIndex(0)
	, m_count(0)
	, m_isDebug(true)
	, m_tapCount(0)
	, m_timeCount(0)
	, m_fallTime(0)
	, m_fallValue(0)
	, m_nextEverySecondTime(0)
	, m_generateCount(0)
{

	//camera = BasicCamera3D{ renderTexture.size(), 30_deg, eyePosition, GetFocusPosition(eyePosition, angle) };
	camera = BasicCamera3D{ renderTexture.size(), 28_deg, eyePosition, GetFocusPosition(eyePosition, angle) };

	playerMesh = Mesh{ MeshData::Pyramid(1.0, 1.0) };


	m_smpEnemyManager.reset();
	m_smpEnemyManager = std::make_unique<EnemyManager>();


	InitGame();

	//Player* pPlayer = new Player();
	//int a = 0;
}

void GameScene::InitGame()
{
	m_gameTime = 0.0f;
	m_deltaTime = 0.0f;
	m_timeSpeed = 1.0f;

	m_wallSpeed = Define::WALL_SPEED_FIRST;



	m_smpWallManager.reset(new WallManager());

	//==== ブロック生成 =======
	m_smpPlayer.reset();
	m_smpPlayer = std::make_shared<Player>();
	m_smpPlayer->DropBlock();


	m_blockIndex = 0;
	m_count = 0;

	m_tapCount = 0;

	m_smpStageManager = std::make_unique<StageManager>();

	m_nextEverySecondTime = Scene::Time() + 1.0f;
}



void GameScene::update()
{
	if (Scene::Time() >= m_nextEverySecondTime)
	{
		updateEverySecond();
		m_nextEverySecondTime += 1.0f;
	}

	m_smpEnemyManager->update();

	//ゲーム中動かさないがデバック用にカメラの移動
	ClearPrint();
	m_deltaTime = (float)Scene::DeltaTime() * m_timeSpeed;
	m_gameTime += m_deltaTime;

	float addSpeed = 0.01f;
	m_timeSpeed += m_deltaTime * addSpeed;

	const float speed = m_deltaTime * 2.0;


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
	}

	if (KeyRight.pressed())
	{
		eyePosition.x += speed;
	}

	// 位置・注目点情報を更新
	camera.setView(eyePosition, GetFocusPosition(eyePosition, angle));
	//camera.setView(Vec3(eyePosition.x - m_playerMoveX, eyePosition.y, eyePosition.z), GetFocusPosition(eyePosition, angle));

	Print << U"Time: {:.1f}"_fmt(Scene::Time());

	Print << U"angle: {:.1f}°"_fmt(Math::ToDegrees(angle));
	Print << U"direction: {:.2f}"_fmt(GetDirection(angle));
	Print << U"eyePositon: {:.1f}"_fmt(camera.getEyePosition());
	Print << U"focusPosition: {:.1f}"_fmt(camera.getFocusPosition());
	Graphics3D::SetCameraTransform(camera);

	if (KeyD.up())
	{
		m_isDebug = !m_isDebug;
	}

	if (MouseL.up())
	{

		//プレイヤーのブロック増やす
		//m_smpPlayerBlockUnit->CreateBlock();
		m_smpPlayer->CreateBlock();


	}
	if (MouseR.up())
	{
		// 右クリックでタイトル画面へ
		changeScene(State::Title);

		getData().lastGameScore = m_score;

		return;
	}




	m_timeCount += Scene::DeltaTime();
	
	//m_smpPlayerBlockUnit->update();
	m_smpPlayer->update();



}

void GameScene::updateEverySecond()
{
	//落下量初期化
	m_fallTime = 0;
	m_fallValue = 0;
	m_timeCount = 0;


	m_smpEnemyManager->updateEverySecond();
	//m_smpPlayerBlockUnit->updateEverySecond();
	m_smpPlayer->updateEverySecond();


	//衝突判定
	const int* hitStatus = m_smpEnemyManager->GetHitStatus();

	//落とすのを1秒先にするために先にDropPlayerBlockを呼んでいる
	//m_smpPlayerBlockUnit->DropBlock();
	//m_smpPlayerBlockUnit->CheckHit(hitStatus);
	m_smpPlayer->DropBlock();
	m_smpPlayer->CheckHit(hitStatus);



	//m_smpEnemyManager->Explosion();


	//新しく生成
	if (m_generateCount == 1)
	{
		m_generateCount = 0;
		std::shared_ptr<EnemyManager::EnemyUnit> smpEnemyUnit = m_smpEnemyManager->GetEnemyUnit();
		m_smpEnemyManager->EnemyUnitInit(smpEnemyUnit, m_nextEverySecondTime);
	}
	else
	{
		m_generateCount++;
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
		if (m_isDebug)
		{
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
		}


		m_smpPlayer->draw();

		DrawStage();

		m_smpEnemyManager->draw();


	}

	// 3D シーンを 2D シーンに描画
	{
		Graphics3D::Flush();
		renderTexture.resolve();
		Shader::LinearToScreen(renderTexture);
	}

}

//
//void GameScene::DecideBlockType(Block::TYPE* pType, bool isNone, bool isHall)
//{
//	for (int i = 0; i < BLOCK_NUM; i++)
//	{
//		if (i < Define::BLOCK_HURDLE_HALL_NUM)
//		{
//			//pType[i] = Block::BLOCK_HALL;
//			pType[i] = Block::BLOCK_NORMAL;
//		}
//		else if (i < Define::BLOCK_HURDLE_HALL_NUM + Define::BLOCK_HURDLE_CENTER_NUM)
//		{
//			if (isNone)
//			{
//				pType[i] = Block::BLOCK_NONE;
//			}
//			else
//			{
//				if (RandomBool(0.8))
//				{
//					pType[i] = Block::BLOCK_NONE;
//				}
//				else
//				{
//					pType[i] = Block::BLOCK_NORMAL;
//				}
//			}
//
//
//		}
//		else
//		{
//			//pType[i] = Block::BLOCK_HALL;
//			pType[i] = Block::BLOCK_NORMAL;
//		}
//	}
//
//	if (isHall)
//	{
//		pType[1] = Block::BLOCK_NONE;
//	}
//	//return pType;
//}


void GameScene::DrawStage() const
{
	for (int i = 0; i < UNIT_NUM; i++)
	{
		float posX = SIZE * i;

		if (i == 0)
		{
			//上
			for (int j = 0; j < Define::BLOCK_GROUND_TOP_NUM; j++)
			{
				float posY = Define::LIMIT_POS_Y_HURDLE_TOP + SIZE * j;
				Box{ Vec3(posX, posY, 0), SIZE }.draw(TextureAsset(U"wood"));
			}
			//下
			for (int j = 0; j < Define::BLOCK_GROUND_BOTTOM_NUM; j++)
			{
				float posY = Define::LIMIT_POS_Y_STAGE_BOTTOM + SIZE * j;
				Box{ Vec3(posX, posY, 0), SIZE }.draw(TextureAsset(U"wood"));
			}
			continue;
		}

		//上
		for (int j = 0; j < Define::BLOCK_GROUND_TOP_NUM; j++)
		{
			float posY = Define::LIMIT_POS_Y_HURDLE_TOP + SIZE * j;
			Box{ Vec3(posX, posY, 0), SIZE }.draw(TextureAsset(U"wood"));
			Box{ Vec3(-posX, posY, 0), SIZE }.draw(TextureAsset(U"wood"));
		}
		//下
		for (int j = 0; j < Define::BLOCK_GROUND_BOTTOM_NUM; j++)
		{
			float posY = Define::LIMIT_POS_Y_STAGE_BOTTOM + SIZE * j;
			Box{ Vec3(posX, posY, 0), SIZE }.draw(TextureAsset(U"wood"));
			Box{ Vec3(-posX, posY, 0), SIZE }.draw(TextureAsset(U"wood"));
		}
	}


}

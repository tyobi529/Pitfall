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
{

	//camera = BasicCamera3D{ renderTexture.size(), 30_deg, eyePosition, GetFocusPosition(eyePosition, angle) };
	camera = BasicCamera3D{ renderTexture.size(), 28_deg, eyePosition, GetFocusPosition(eyePosition, angle) };

	playerMesh = Mesh{ MeshData::Pyramid(1.0, 1.0) };






	InitGame();

}

void GameScene::InitGame()
{
	m_gameTime = 0.0f;
	m_deltaTime = 0.0f;
	m_timeSpeed = 1.0f;

	m_wallSpeed = Define::WALL_SPEED_FIRST;



	m_smpWallManager.reset(new WallManager());

	//==== ブロック生成 =======
	m_smpPlayerBlockUnit.reset();
	m_smpPlayerBlockUnit = std::make_shared<BlockUnit>();
	m_smpPlayerBlockUnit->PlayerInit();
	m_smpPlayerBlockUnit->SetUnitIndex(Define::BLOCK_PLAYE_INDEX);
	m_smpPlayerBlockUnit->GetBlock(BLOCK_NUM - 1)->SetType(Block::BLOCK_PLAYER_HEAD);
	DropPlayerBlock(m_smpPlayerBlockUnit);

	m_smpEnemyBlockUnit.reset();
	m_smpEnemyBlockUnit = std::make_shared<BlockUnit>();
	m_smpEnemyBlockUnit->EnemyInit();
	m_smpEnemyBlockUnit->SetUnitIndex(Define::BLOCK_ENEMY_INDEX);
	m_smpEnemyBlockUnit->GetBlock(4)->SetType(Block::BLOCK_NORMAL);

	//=====================


	m_smpEnemy.reset();
	m_smpEnemy = std::make_unique<Enemy>();
	m_smpEnemy->Init(4, 1, Scene::Time());

	m_smpEnemy2.reset();
	m_smpEnemy2 = std::make_unique<Enemy>();
	m_smpEnemy2->Init(7, 2, Scene::Time());


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
		m_nextEverySecondTime += 1.0f;
		updateEverySecond();
	}
	m_smpEnemy->update();
	m_smpEnemy2->update();

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
		//m_tapCount++;

		//プレイヤーのブロック増やす
		int headIndex = -1;

		for (int i = 0; i < BLOCK_NUM; i++)
		{
			if (m_smpPlayerBlockUnit->GetBlock(i)->GetType() == Block::BLOCK_PLAYER_HEAD)
			{
				headIndex = i;
				break;
			}
		}

		if (headIndex == BLOCK_NUM - 1)
		{
			//生成限界
			return;
		}


		//if (smpCurrentEnemyBlock->GetType() != Block::BLOCK_NONE)
		//{
		//	//上にブロックがあれば生成しない。ここ書き方あってる？
		//	return;
		//}
		//else if (smpNextEnemyBlock->GetType() != Block::BLOCK_NONE &&
		//	!m_isHit)
		//{
		//	//右上にブロックがあれば生成しない。
		//	//hit中ならok
		//	return;
		//}
		//else
		{
			m_smpPlayerBlockUnit->GetBlock(headIndex)->Init();
			m_smpPlayerBlockUnit->GetBlock(headIndex)->SetType(Block::BLOCK_PLAYER_BODY);
			//1つ上に頭を移動
			//m_smpPlayerBlockUnit->GetBlock(headIndex + 1)->Init();
			m_smpPlayerBlockUnit->GetBlock(headIndex + 1)->SetType(Block::BLOCK_PLAYER_HEAD);
		}

	}
	if (MouseR.up())
	{
		// 右クリックでタイトル画面へ
		changeScene(State::Title);

		getData().lastGameScore = m_score;

		return;
	}




	m_timeCount += Scene::DeltaTime();
	if (m_timeCount > 3)
	{
		//落下量初期化
		m_fallTime = 0;
		m_fallValue = 0;
		m_timeCount = 0;


		//m_smpPlayerBlockUnit->GetBlock(1)->SetType(Block::BLOCK_NONE);
		//m_smpPlayerBlockUnit->GetBlock(2)->SetType(Block::BLOCK_NONE);

		for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
		{
			if (m_smpEnemyBlockUnit->GetBlock(i)->GetType() != Block::BLOCK_NONE)
			{
				m_smpPlayerBlockUnit->GetBlock(i)->SetType(Block::BLOCK_NONE);
				m_smpEnemyBlockUnit->GetBlock(i)->SetType(Block::BLOCK_NONE);
			}
		}

		DropPlayerBlock(m_smpPlayerBlockUnit);

		m_smpEnemyBlockUnit->GetBlock(0)->SetType(Block::BLOCK_NORMAL);
		m_smpEnemyBlockUnit->GetBlock(1)->SetType(Block::BLOCK_NORMAL);

		for (int i = 0; i < 4; i++)
		{
			int index = Random(2, Define::BLOCK_HURDLE_NUM - 1);
			m_smpEnemyBlockUnit->GetBlock(index)->SetType(Block::BLOCK_NORMAL);
		}
		
	}

	//仮
	m_fallTime += Scene::DeltaTime() * Define::BLOCK_SPEED;
	m_fallValue = (BLOCK_NUM - 1) * (m_fallTime * m_fallTime);


	m_smpPlayerBlockUnit->SetCenterPos(0, m_fallValue);
	m_smpPlayerBlockUnit->update();

	m_smpEnemyBlockUnit->SetCenterPos(0, m_fallValue);
	m_smpEnemyBlockUnit->update();

}

void GameScene::updateEverySecond()
{
	m_smpEnemy->CoundDown();
	m_smpEnemy2->CoundDown();

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


		m_smpPlayerBlockUnit->draw();
		m_smpEnemyBlockUnit->draw();

		DrawStage();

		m_smpEnemy->draw();
		m_smpEnemy2->draw();

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


void GameScene::DropPlayerBlock(std::shared_ptr<BlockUnit> blockUnit, Block::TYPE* types)
{
	//Block::TYPE targetTypes[BLOCK_NUM] = {};

	if (types == nullptr)
	{
		Block::TYPE emptyTypes[BLOCK_NUM] = {};
		for (int i = 0; i < BLOCK_NUM; i++)
		{
			if (blockUnit->GetBlock(i)->GetType() == Block::BLOCK_PLAYER_HEAD ||
				blockUnit->GetBlock(i)->GetType() == Block::BLOCK_PLAYER_BODY)
			{
				emptyTypes[i] = Block::BLOCK_NONE;
			}
			else
			{
				emptyTypes[i] = blockUnit->GetBlock(i)->GetType();
			}
		}
		types = emptyTypes;
	}



	for (int i = 0; i < BLOCK_NUM; i++)
	{
		Block::TYPE type = blockUnit->GetBlock(i)->GetType();
		if (type == Block::BLOCK_PLAYER_HEAD || type == Block::BLOCK_PLAYER_BODY)
		{
			//元の位置を先に削除
			blockUnit->GetBlock(i)->SetType(Block::BLOCK_NONE);

			if (i == 0)
			{
				blockUnit->GetBlock(0)->SetType(type);
				//移動先にブロックを入れる
				types[0] = type;

				//移動元情報入れる
				//blockUnit->GetBlock(0)->SetMoveInfo(i);
				blockUnit->SetPreIndex(0, i);
			}
			else
			{
				//下を確認
				for (int j = i - 1; j >= 0; j--)
				{
					if (types[j] != Block::BLOCK_NONE)
					{
						//ブロックが存在する場合はその１つ上に移動
						//真下にある場合は変化なし
						blockUnit->GetBlock(j + 1)->SetType(type);
						//移動先にブロックを入れる
						types[j + 1] = type;

						//移動元情報入れる
						//blockUnit->GetBlock(j + 1)->SetMoveInfo(i);
						blockUnit->SetPreIndex(j + 1, i);

						break;
					}
					if (j == 0)
					{
						blockUnit->GetBlock(0)->SetType(type);
						//移動先にブロックを入れる
						types[0] = type;

						//移動元情報入れる
						//blockUnit->GetBlock(0)->SetMoveInfo(i);
						blockUnit->SetPreIndex(0, i);

						break;
					}
				}
			}

			
		}
	}
}

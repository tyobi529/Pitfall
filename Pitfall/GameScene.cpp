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
	, m_difX(0)
	, m_count(0)
	, m_isDebug(false)
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



	m_smpWallManager.reset(new WallManager());

	//==== ブロック生成 =======
	m_smpEnemyBlockUnits.clear();
	m_smpPlayerBlockUnit.reset();

	for (int i = 0; i < UNIT_NUM; i++)
	{
		m_smpEnemyBlockUnits.push_back(std::make_shared<BlockUnit>());
		m_smpEnemyBlockUnits[i]->EnemyInit();
		m_smpEnemyBlockUnits[i]->SetUnitIndex(i);
	}

	m_smpPlayerBlockUnit = std::make_shared<BlockUnit>();
	m_smpPlayerBlockUnit->PlayerInit();
	m_smpPlayerBlockUnit->SetUnitIndex(Define::BLOCK_PLAYE_INDEX);


	//=====================

	//==== ブロック種類設定 =======
	for (int i = 0; i < UNIT_NUM; i++)
	{
		std::shared_ptr<BlockUnit> smpBlock = m_smpEnemyBlockUnits[i];

		Block::TYPE types[BLOCK_NUM] = {};
		DecideBlockType(types, true);
		for (int j = 0; j < BLOCK_NUM; j++)
		{
			smpBlock->GetBlock(j)->SetType(types[j]);
		}
	}


	for (int i = 3; i < BLOCK_NUM - 4; i++)
	{
		m_smpPlayerBlockUnit->GetBlock(i)->SetType(Block::BLOCK_PLAYER_BODY);
	}
	m_smpPlayerBlockUnit->GetBlock(BLOCK_NUM - 3)->SetType(Block::BLOCK_PLAYER_HEAD);
	//m_smpPlayerBlockUnit->GetBlock(BLOCK_NUM - 3)->SetType(Block::BLOCK_PLAYER_HEAD);


	m_difX = 0;

	m_blockIndex = 0;
	m_count = 0;
}



void GameScene::update()
{
	//ゲーム中動かさないがデバック用にカメラの移動
	ClearPrint();
	m_deltaTime = (float)Scene::DeltaTime() * m_timeSpeed;
	m_gameTime += m_deltaTime;

	//float addSpeed = 0.02f;
	//m_timeSpeed += m_deltaTime * addSpeed;

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
		for (int i = 0; i < BLOCK_NUM; i++)
		{
			std::shared_ptr<Block> smpPlayerBlock = m_smpPlayerBlockUnit->GetBlock(i);

			if (smpPlayerBlock->GetType() == Block::BLOCK_PLAYER_HEAD)
			{
				//std::shared_ptr<BlockUnit> smpenemyBlockUnit = m_smpEnemyBlocks[Define::BLOCK_PLAYE_INDEX]->
				std::shared_ptr<Block> smpCurrentEnemyBlock = m_smpEnemyBlockUnits[Define::BLOCK_PLAYE_INDEX]->GetBlock(i + 1);
				std::shared_ptr<Block> smpNextEnemyBlock = m_smpEnemyBlockUnits[Define::BLOCK_PLAYE_INDEX + 1]->GetBlock(i + 1);

				if (i == BLOCK_NUM - 1)
				{
					//生成限界
					break;
				}
				else if (smpCurrentEnemyBlock->GetType() != Block::BLOCK_NONE ||
					smpNextEnemyBlock->GetType() != Block::BLOCK_NONE)
				{
					//上にブロックがあれば生成しない。ここ書き方あってる？
					break;
				}
				else
				{
					smpPlayerBlock->SetType(Block::BLOCK_PLAYER_BODY);
					smpPlayerBlock->Init();
					//1つ上に頭を移動
					m_smpPlayerBlockUnit->GetBlock(i + 1)->SetType(Block::BLOCK_PLAYER_HEAD);
					break;
				}

			}
		}
	}
	if (MouseR.up())
	{
		// 右クリックでタイトル画面へ
		changeScene(State::Title);

		getData().lastGameScore = m_score;

		return;
	}


	//壁の位置更新
	//移動量計算
	m_difX -= m_deltaTime * Define::BLOCK_SPEED;

	//更新
	if (m_difX < -1.0f)
	{
		//横方向のindexをずらす
		std::rotate(m_smpEnemyBlockUnits.begin(), m_smpEnemyBlockUnits.begin() + 1, m_smpEnemyBlockUnits.end());
		//unitIndex更新
		for (int i = 0; i < UNIT_NUM; i++)
		{
			m_smpEnemyBlockUnits[i]->SetUnitIndex(i);
		}

		m_difX += 1.0f;


		if (m_count == 0)
		{
			std::shared_ptr<BlockUnit> smpBlockUnit = m_smpEnemyBlockUnits[UNIT_NUM - 1];

			Block::TYPE types[BLOCK_NUM] = {};
			DecideBlockType(types, false);
			for (int j = 0; j < BLOCK_NUM; j++)
			{
				smpBlockUnit->GetBlock(j)->SetType(types[j]);
			}

			m_count++;
		}
		else
		{
			std::shared_ptr<BlockUnit> smpBlockUnit = m_smpEnemyBlockUnits[UNIT_NUM - 1];

			Block::TYPE types[BLOCK_NUM] = {};
			DecideBlockType(types, true);
			for (int j = 0; j < BLOCK_NUM; j++)
			{
				smpBlockUnit->GetBlock(j)->SetType(types[j]);
			}

			if (m_count == 5)
			{
				m_count = 0;
			}
			else
			{
				m_count++;
			}
		}


		//============ プレイヤー ============
		//まずは横にスライド
		{
			//スライド判定先
			std::shared_ptr<BlockUnit> smpEnemyBlockUnit = m_smpEnemyBlockUnits[Define::BLOCK_PLAYE_INDEX];

			Block::TYPE types[BLOCK_NUM] = {};
			for (int i = 0; i < BLOCK_NUM; i++)
			{
				types[i] = smpEnemyBlockUnit->GetBlock(i)->GetType();
				if (m_smpPlayerBlockUnit->GetBlock(i)->GetType() != Block::BLOCK_NONE && types[i] != Block::BLOCK_NONE)
				{
					assert(false); //位置がかぶってスライドできない
				}
			}

			DropPlayerBlock(m_smpPlayerBlockUnit, types);
		}

		{
			//おいていったプレイヤーブロックを落とす
			DropPlayerBlock(m_smpEnemyBlockUnits[Define::BLOCK_PLAYE_INDEX - 1]);
		}
		


		//ぶつかったブロックを消す
		{
			//ぶつかる対象（プレイヤーの１つ先）
			std::shared_ptr<BlockUnit> smpEnemyBlockUnit = m_smpEnemyBlockUnits[Define::BLOCK_PLAYE_INDEX + 1];

			for (int i = 0; i < BLOCK_NUM; i++)
			{

				if (m_smpPlayerBlockUnit->GetBlock(i)->GetType() != Block::BLOCK_NONE)
				{

					if (smpEnemyBlockUnit->GetBlock(i)->GetType() != Block::BLOCK_NONE)
					{
						m_smpPlayerBlockUnit->GetBlock(i)->SetType(Block::BLOCK_NONE);

						m_smpEnemyBlockUnits[Define::BLOCK_PLAYE_INDEX]->GetBlock(i)->SetType(Block::BLOCK_PLAYER_BODY);

						
					}
				}

			}


		}
		

	

	}


	//縦移動計算
	float fallValue = (BLOCK_NUM - 1) * (-m_difX);

	//テスト
	for (int i = 0; i < UNIT_NUM; i++)
	{
		m_smpEnemyBlockUnits[i]->SetCenterPos(m_difX, fallValue);
	}
	m_smpPlayerBlockUnit->SetCenterPos(0, fallValue);


	//for (int i = 0; i < UNIT_NUM; i++)
	//{
	//	for (int j = 0; j < BLOCK_NUM; j++)
	//	{
	//		//落下中
	//		if (m_smpEnemyBlocks[i][j]->GetIsMove())
	//		{
	//			int preColIndex = m_smpEnemyBlocks[i][j]->GetPreColIndex();

	//			float difY = SIZE * (preColIndex - i) + fallValue;
	//			if (difY <= 0)
	//			{
	//				m_smpEnemyBlocks[i][j]->SetIsMove(false);
	//				m_smpEnemyBlocks[i][j]->SetCenterPos(m_difX);
	//			}
	//			else
	//			{
	//				m_smpEnemyBlocks[i][j]->SetCenterPos(m_difX, difY);
	//			}
	//		}
	//		else
	//		{
	//			m_smpEnemyBlocks[i][j]->SetCenterPos(m_difX);
	//		}
	//	}
	//}

	//for (int i = 0; i < BLOCK_NUM; i++)
	//{
	//	//落下中
	//	if (m_smpPlayerBlocks[i]->GetIsMove())
	//	{
	//		int preColIndex = m_smpPlayerBlocks[i]->GetPreColIndex();

	//		float difY = SIZE * (preColIndex - i) + fallValue;
	//		if (difY <= 0)
	//		{
	//			m_smpPlayerBlocks[i]->SetIsMove(false);
	//			m_smpPlayerBlocks[i]->SetCenterPos();
	//		}
	//		else
	//		{
	//			m_smpPlayerBlocks[i]->SetCenterPos(0, difY);
	//		}
	//	}
	//	else
	//	{
	//		m_smpPlayerBlocks[i]->SetCenterPos();
	//	}

	//}

	//ブロックのupdate
	for (int i = 0; i < UNIT_NUM; i++)
	{
		m_smpEnemyBlockUnits[i]->update();
	}

	m_smpPlayerBlockUnit->update();



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




		for (int i = 0; i < UNIT_NUM; i++)
		{
			m_smpEnemyBlockUnits[i]->draw();
		}

		m_smpPlayerBlockUnit->draw();
		
		DrawStage();
	}

	// 3D シーンを 2D シーンに描画
	{
		Graphics3D::Flush();
		renderTexture.resolve();
		Shader::LinearToScreen(renderTexture);
	}

}


void GameScene::DecideBlockType(Block::TYPE* pType, bool isNone)
{
	for (int i = 0; i < BLOCK_NUM; i++)
	{
		if (i < Define::BLOCK_HURDLE_HALL_NUM)
		{
			//pType[i] = Block::BLOCK_HALL;
			pType[i] = Block::BLOCK_NORMAL;
		}
		else if (i < Define::BLOCK_HURDLE_HALL_NUM + Define::BLOCK_HURDLE_CENTER_NUM)
		{
			if (isNone)
			{
				pType[i] = Block::BLOCK_NONE;
			}
			else
			{
				if (RandomBool())
				{
					pType[i] = Block::BLOCK_NONE;
				}
				else
				{
					pType[i] = Block::BLOCK_NORMAL;
				}
			}

		}
		else
		{
			//pType[i] = Block::BLOCK_HALL;
			pType[i] = Block::BLOCK_NORMAL;
		}
	}

	//return pType;
}


void GameScene::DrawStage() const
{
	for (int i = 0; i < UNIT_NUM; i++)
	{
		float posX = SIZE * i + m_difX;

		//上
		for (int j = 0; j < Define::BLOCK_GROUND_TOP_NUM; j++)
		{
			float posY = Define::LIMIT_POS_Y_HURDLE_TOP + SIZE * j;
			Box{ Vec3(posX + SIZE / 2.0f, posY + SIZE / 2.0f, SIZE / 2.0f), SIZE }.draw(TextureAsset(U"wood"));
		}
		//下
		for (int j = 0; j < Define::BLOCK_GROUND_BOTTOM_NUM; j++)
		{
			float posY = Define::LIMIT_POS_Y_STAGE_BOTTOM + SIZE * j;
			Box{ Vec3(posX + SIZE / 2.0f, posY + SIZE / 2.0f, SIZE / 2.0f), SIZE }.draw(TextureAsset(U"wood"));
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
					blockUnit->GetBlock(j + 1)->SetMoveInfo(i);

					//m_smpPlayerBlocks[j + 1]->SetMoveInfo(i);

					break;
				}
				if (j == 0)
				{
					blockUnit->GetBlock(0)->SetType(type);
					//m_smpPlayerBlocks[0]->SetType(type);
					//移動先にブロックを入れる
					types[0] = type;

					//移動元情報入れる
					blockUnit->GetBlock(0)->SetMoveInfo(i);
					break;
				}
			}
		}
	}
}

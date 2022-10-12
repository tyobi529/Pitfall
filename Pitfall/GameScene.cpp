# include "GameScene.h"
//#include "Wall.h"

#include "Define.h"


#define SIZE Define::BLOCK_SIZE

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
	, m_playerTypes{}
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

	//playerPos = Vec3(0, 0, 0);


	m_smpWallManager.reset(new WallManager());

	//m_smpPlayer.reset(new Player());

	//m_smpBlockUnit.reset(new BlockUnit());
	m_smpBlockUnits.clear();

	Block::TYPE types[Define::BLOCK_HURDLE_NUM] = {};
	DecideBlockType(types, true);
	for (int i = 0; i < Define::BLOCK_H_NUM; i++)
	{
		m_smpBlockUnits.push_back(std::make_unique<BlockUnit>());
		m_smpBlockUnits[i]->Init(types);
		m_smpBlockUnits[i]->UpdatePos(SIZE * i);
	}

	//テスト
	//types[3] = Block::BLOCK_NORMAL;
	//m_smpBlockUnits[Define::BLOCK_PLAYE_INDEX + 1]->Init(types);
	//types[3] = Block::BLOCK_NONE;
	//types[2] = Block::BLOCK_NORMAL;
	//m_smpBlockUnits[Define::BLOCK_PLAYE_INDEX + 2]->Init(types);
	

	//プレイヤー
	m_smpPlayerUnit = std::make_unique<BlockUnit>();
	m_playerTypes[3] = Block::BLOCK_PLAYE_BODY;
	m_playerTypes[4] = Block::BLOCK_PLAYE_BODY;
	m_playerTypes[6] = Block::BLOCK_PLAYE_BODY;
	m_playerTypes[7] = Block::BLOCK_PLAYE_BODY;
	m_playerTypes[9] = Block::BLOCK_PLAYE_HEAD;
	m_smpPlayerUnit->Init(m_playerTypes);


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
		for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
		{
			if (m_playerTypes[i] == Block::BLOCK_PLAYE_HEAD)
			{
				if (i == Define::BLOCK_HURDLE_NUM - 1)
				{
					//生成限界
					break;
				}
				else if (m_smpBlockUnits[Define::BLOCK_PLAYE_INDEX]->GetBlockType(i + 1) != Block::BLOCK_NONE ||
					m_smpBlockUnits[Define::BLOCK_PLAYE_INDEX + 1]->GetBlockType(i + 1) != Block::BLOCK_NONE)
				{
					//上にブロックがあれば生成しない。ここ書き方あってる？
					break;
				}
				else
				{
					m_playerTypes[i] = Block::BLOCK_PLAYE_BODY;
					m_playerTypes[i + 1] = Block::BLOCK_PLAYE_HEAD;
					m_smpPlayerUnit->Init(m_playerTypes);
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
	//float deltaPosY = m_deltaTime * m_wallSpeed;
	//m_smpWallManager->UpdateWallPos(deltaPosY);

	//m_smpPlayer->update();


	//移動量計算
	m_difX += m_deltaTime * Define::BLOCK_SPEED;

	//更新
	if (m_difX > 1.0f)
	{
		std::rotate(m_smpBlockUnits.begin(), m_smpBlockUnits.begin() + 1, m_smpBlockUnits.end());
		m_difX -= 1.0f;

		if (m_count == 0)
		{
			Block::TYPE types[Define::BLOCK_HURDLE_NUM] = {};
			DecideBlockType(types);
			m_smpBlockUnits[Define::BLOCK_H_NUM - 1]->Init(types);

			m_count++;
		}
		else
		{
			Block::TYPE types[Define::BLOCK_HURDLE_NUM] = {};
			DecideBlockType(types, true);
			m_smpBlockUnits[Define::BLOCK_H_NUM - 1]->Init(types);

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
		Block::TYPE types[Define::BLOCK_HURDLE_NUM] = {};
		for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
		{
			types[i] = m_smpBlockUnits[Define::BLOCK_PLAYE_INDEX]->GetBlockType(i);
			if (m_playerTypes[i] != Block::BLOCK_NONE && types[i] != Block::BLOCK_NONE)
			{
				assert(false); //位置がかぶってスライドできない
			}
		}
		for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
		{
			Block::TYPE type = m_playerTypes[i];
			if (type != Block::BLOCK_NONE)
			{
				//元の位置を先に削除
				m_playerTypes[i] = Block::BLOCK_NONE;
				//下を確認
				for (int j = i - 1; j >= 0; j--)
				{
					if (types[j] != Block::BLOCK_NONE)
					{
						//ブロックが存在する場合はその１つ上に移動
						//真下にある場合は変化なし
						m_playerTypes[j + 1] = type;
						//移動先にブロックを入れる
						types[j + 1] = type;
						break;
					}
					if (j == 0)
					{
						m_playerTypes[0] = type;
						//移動先にブロックを入れる
						types[0] = m_playerTypes[0];
						break;
					}
				}
			}
		}

		//ぶつかったブロックを消す
		for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
		{
			if (m_playerTypes[i] != Block::BLOCK_NONE)
			{
				if (m_smpBlockUnits[Define::BLOCK_PLAYE_INDEX + 1]->GetBlockType(i) != Block::BLOCK_NONE)
				{
					m_playerTypes[i] = Block::BLOCK_NONE;
				}
			}
		}

		m_smpPlayerUnit->Init(m_playerTypes);


	}

	for (int i = 0; i < Define::BLOCK_H_NUM; i++)
	{
		float posX = SIZE * i - m_difX;
		m_smpBlockUnits[i]->UpdatePos(posX);
	}

	m_smpPlayerUnit->UpdatePos(Define::PLAYER_POS_X);
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





		//m_smpPlayer->draw();



		for (int i = 0; i < Define::BLOCK_H_NUM; i++)
		{
			m_smpBlockUnits[i]->draw();
		}

		m_smpPlayerUnit->draw();
		
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
	for (int i = 0; i < Define::BLOCK_HURDLE_NUM; i++)
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
	for (int i = 0; i < Define::BLOCK_H_NUM; i++)
	{
		float posX = SIZE * i - m_difX;

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

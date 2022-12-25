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

	//const Vec2 dir = Circular{ 1.0, 30_deg };
	//return{ dir.x, 0.0, -dir.y };
	//return{ 0, -30_deg, 0 };
	//return{ 0, -dir.x, 0 };

}

Vec3 GetFocusPosition(const Vec3& eyePosition, double angle)
{
	//return (eyePosition + GetDirection(angle));
	Vec3 pos = Vec3(0, -0.1, 1).normalize();
	return (eyePosition + pos);

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
	, m_isDebug(false)
	, m_tapCount(0)
	, m_timeCount(0)
	, m_fallTime(0)
	, m_fallValue(0)
	, m_nextEverySecondTime(0)
	, m_generateCount(0)
{
	psBright = HLSL{ U"example/shader/hlsl/extract_bright_linear.hlsl", U"PS" }
	| GLSL{ U"example/shader/glsl/extract_bright_linear.frag", {{U"PSConstants2D", 0}} };

	gaussianA4 = RenderTexture{ renderTexture.size() / 4 };
	gaussianB4 = RenderTexture{ renderTexture.size() / 4 };
	gaussianA8 = RenderTexture{ renderTexture.size() / 8 };
	gaussianB8 = RenderTexture{ renderTexture.size() / 8 };
	gaussianA16 = RenderTexture{ renderTexture.size() / 16 };
	gaussianB16 = RenderTexture{ renderTexture.size() / 16 };

	//renderTexture = MSRenderTexture{ Scene::Size(), TextureFormat::R16G16B16A16_Float, HasDepth::Yes };

	camera = BasicCamera3D{ renderTexture.size(), 30_deg, eyePosition, GetFocusPosition(eyePosition, angle) };

	//右向き
	//eyePosition = Vec3(-7, 12, -35);
	//Vec3 targetDir = Vec3(0.25, 0, 1).normalize();

	//下向き
	//eyePosition = Vec3(2, 16, -32);
	//Vec3 targetDir = Vec3(0, -0.15, 1).normalize();

	//正面
	eyePosition = Vec3(2, 12, -32);
	Vec3 targetDir = Vec3(0, 0, 1).normalize();

	//右向き2
	//eyePosition = Vec3(-2, 12, -35);
	//Vec3 targetDir = Vec3(0.3, 0, 1).normalize();

	camera.setView(eyePosition, eyePosition + targetDir);

	playerMesh = Mesh{ MeshData::Pyramid(1.0, 1.0) };


	m_smpEnemyManager.reset();
	m_smpEnemyManager = std::make_unique<EnemyManager>();


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
	m_smpPlayer.reset();
	m_smpPlayer = std::make_shared<Player>();
	m_smpPlayer->DropBlock();


	m_blockIndex = 0;
	m_count = 0;

	m_tapCount = 0;

	//m_smpStageManager = std::make_unique<StageManager>();

	m_nextEverySecondTime = Scene::Time() + Define::INTERVAL_SECOND;
}



void GameScene::update()
{
	if (Scene::Time() >= m_nextEverySecondTime)
	{
		updateInterval();
		m_nextEverySecondTime += Define::INTERVAL_SECOND;
	}

	m_smpEnemyManager->update();

	//ゲーム中動かさないがデバック用にカメラの移動
	ClearPrint();
	m_deltaTime = (float)Scene::DeltaTime() * m_timeSpeed;
	m_gameTime += m_deltaTime;

	float addSpeed = 0.01f;
	m_timeSpeed += m_deltaTime * addSpeed;

	//const float speed = m_deltaTime * 2.0;


	//if (KeyUp.pressed())
	//{
	//	eyePosition.y += speed;
	//}

	//if (KeyDown.pressed())
	//{
	//	eyePosition.y -= speed;
	//}

	//if (KeyLeft.pressed())
	//{
	//	eyePosition.x -= speed;
	//}

	//if (KeyRight.pressed())
	//{
	//	eyePosition.x += speed;
	//}
	ClearPrint();
	const double deltaTime = Scene::DeltaTime();
	const double speed = (deltaTime * 2.0);



	// 位置・注目点情報を更新
	//camera.setView(eyePosition, GetFocusPosition(eyePosition, angle));
	//camera.setView(Vec3(eyePosition.x - m_playerMoveX, eyePosition.y, eyePosition.z), GetFocusPosition(eyePosition, angle));

	Print << U"Time: {:.1f}"_fmt(Scene::Time());

	Print << U"angle: {:.1f}°"_fmt(Math::ToDegrees(angle));
	Print << U"direction: {:.2f}"_fmt(GetDirection(angle));
	Print << U"eyePositon: {:.1f}"_fmt(camera.getEyePosition());
	Print << U"focusPosition: {:.1f}"_fmt(camera.getFocusPosition());

	//Print << U"SCORE: {:.1f}"_fmt(Define::SCORE);
	Print << Define::SCORE;


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
		//changeScene(State::Title);
		//getData().lastGameScore = m_score;


		m_smpPlayer->ClearBlock();

		return;
	}




	m_timeCount += Scene::DeltaTime();
	
	//m_smpPlayerBlockUnit->update();
	m_smpPlayer->update();

}

void GameScene::updateInterval()
{
	//落下量初期化
	m_fallTime = 0;
	m_fallValue = 0;
	m_timeCount = 0;


	m_smpEnemyManager->updateInterval();
	m_smpPlayer->updateInterval();


	//衝突判定
	const int* hitStatus = m_smpEnemyManager->GetHitStatus();

	//落とすのを1秒先にするために先にDropPlayerBlockを呼んでいる
	m_smpPlayer->DropBlock();
	m_smpPlayer->CheckHit(hitStatus);



	//新しく生成
	if (m_generateCount == 4)
	{

		m_generateCount = 0;
		std::shared_ptr<Enemy> smpEnemy = m_smpEnemyManager->GetEnemy();
		m_smpEnemyManager->EnemyInit(smpEnemy, m_nextEverySecondTime);
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
			Line3D{ Vec3{-length, 0, 0}, Vec3{length, 0, 0} }.draw(ColorF(0, 0, 0, 1).removeSRGBCurve() * 0.5f);
			Line3D{ Vec3{0, -length, 0}, Vec3{0, length, 0} }.draw(ColorF(0, 0, 0, 1).removeSRGBCurve() * 0.5f);
			for (int i = 1; i < 15; i++) //縦線
			{
				Line3D{ Vec3{i, -length, 0}, Vec3{i, length, 0} }.draw(ColorF(1, 1, 1, 1).removeSRGBCurve() * 0.5f);
				Line3D{ Vec3{-i, -length, 0}, Vec3{-i, length, 0} }.draw(ColorF(1, 1, 1, 1).removeSRGBCurve() * 0.5f);
			}
			for (int i = 1; i < 15; i++) //横線
			{
				Line3D{ Vec3{-length, i, 0}, Vec3{length, i, 0} }.draw(ColorF(1, 1, 1, 1).removeSRGBCurve() * 0.5f);
				Line3D{ Vec3{-length, -i, 0}, Vec3{length, -i, 0} }.draw(ColorF(1, 1, 1, 1).removeSRGBCurve() * 0.5f);
			}
		}


		m_smpPlayer->draw();

		DrawStage();

		m_smpEnemyManager->draw();


		const double t = Scene::Time();

		//oneSidedPlane.draw(5, 2, 0, uvChecker);
		bgPlane.draw(Vec3{ 2, 11, 2 }, Quaternion::RotateX(-90_deg), bgTex);


	}

	// 3D シーンを 2D シーンに描画
	{
		Graphics3D::Flush();
		renderTexture.resolve();
		Shader::LinearToScreen(renderTexture);
	}


	//const RenderTexture gaussianA4{ renderTexture.size() / 4 }, gaussianB4{ renderTexture.size() / 4 };
	//const RenderTexture gaussianA8{ renderTexture.size() / 8 }, gaussianB8{ renderTexture.size() / 8 };
	//const RenderTexture gaussianA16{ renderTexture.size() / 16 }, gaussianB16{ renderTexture.size() / 16 };

	// 高輝度部分を抽出
	{
		const ScopedCustomShader2D shader{ psBright };
		const ScopedRenderTarget2D target{ gaussianA4.clear(ColorF{0.0}) };
		renderTexture.scaled(0.25).draw();
	}

	// 高輝度部分のぼかしテクスチャの生成
	{
		Shader::GaussianBlur(gaussianA4, gaussianB4, gaussianA4);
		Shader::Downsample(gaussianA4, gaussianA8);
		Shader::GaussianBlur(gaussianA8, gaussianB8, gaussianA8);
		Shader::GaussianBlur(gaussianA8, gaussianB8, gaussianA8);
		Shader::Downsample(gaussianA8, gaussianA16);
		Shader::GaussianBlur(gaussianA16, gaussianB16, gaussianA16);
		Shader::GaussianBlur(gaussianA16, gaussianB16, gaussianA16);
		Shader::GaussianBlur(gaussianA16, gaussianB16, gaussianA16);
	}

	// Glow エフェクト
	{
		const ScopedRenderStates2D blend{ BlendState::AdditiveRGB };

		{
			const ScopedRenderTarget2D target{ gaussianA8 };
			gaussianA16.scaled(2.0).draw(ColorF{ 3.0 });
		}

		{
			const ScopedRenderTarget2D target{ gaussianA4 };
			gaussianA8.scaled(2.0).draw(ColorF{ 1.0 });
		}

		gaussianA4.resized(Scene::Size()).draw(ColorF{ 1.0 });
	}

}



void GameScene::DrawStage() const
{
	ColorF color = ColorF{ 1, 1, 1 };

	for (int i = 0; i < UNIT_NUM; i++)
	{
		float posX = SIZE * i;

		//上
		for (int j = 0; j < Define::BLOCK_GROUND_TOP_NUM; j++)
		{
			float posY = Define::LIMIT_POS_Y_HURDLE_TOP + SIZE * j;
			//Box{ Vec3(posX, posY, 0), SIZE }.draw(TextureAsset(U"wood"));
			//Box{ Vec3(-posX, posY, 0), SIZE }.draw(TextureAsset(U"wood"));
			Box{ Vec3(posX, posY, 0), SIZE }.draw(color.removeSRGBCurve() * 0.15f);
			Box{ Vec3(-posX, posY, 0), SIZE }.draw(color.removeSRGBCurve() * 0.15f);
		}
		//下
		for (int j = 0; j < Define::BLOCK_GROUND_BOTTOM_NUM; j++)
		{
			float posY = Define::LIMIT_POS_Y_STAGE_BOTTOM + SIZE * j;
			//Box{ Vec3(posX, posY, 0), SIZE }.draw(TextureAsset(U"wood"));
			//Box{ Vec3(-posX, posY, 0), SIZE }.draw(TextureAsset(U"wood"));
			Box{ Vec3(posX, posY, 0), SIZE }.draw(color.removeSRGBCurve() * 0.15f);
			Box{ Vec3(-posX, posY, 0), SIZE }.draw(color.removeSRGBCurve() * 0.15f);
		} 
	}


}

# pragma once
# include "Common.h"
#include <vector>
#include <memory>   // スマートポインタ
#include "Wall.h"

#include "WallManager.h"

#include "Player.h"

#include "BlockUnit.h"

// ゲームシーン
class GameScene : public App::Scene
{
public:

	GameScene(const InitData& init);

	void update() override;

	void draw() const override;

	void InitGame();

private:

	// ブロックのサイズ
	static constexpr Size BrickSize{ 40, 20 };

	// ボールの速さ
	static constexpr double Speed = 480.0;

	// ボールの速度
	Vec2 m_ballVelocity{ 0, -Speed };

	// ボール
	Circle m_ball{ 400, 400, 8 };

	// ブロックの配列
	Array<Rect> m_bricks;

	// 現在のゲームのスコア
	int32 m_score = 0;

	Rect getPaddle() const;


	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };

	Vec3 eyePosition;

	double angle = 0_deg;
	BasicCamera3D camera;

	//プレイヤー
	//Mesh playerMesh;

	//Vec3 playerPos;

	Mesh playerMesh;
	//Vec3 playerPos;

	int playerPosX = 3;
	int depthZ = 1;
	int wallWidth = 3;

	bool isLeft = true;

	//std::vector<Wall*> m_pWalls;

	//std::vector<std::shared_ptr<Wall>> vec = std::vector<std::shared_ptr<Wall>>();

	std::vector<std::unique_ptr<Wall>> m_smpWalls;


	//== 時間 ==
	float m_gameTime; //ゲームシーンの経過時間合計
	float m_deltaTime; //前フレームからの経過時間
	float m_timeSpeed; //時間経過速度（基本的に1）

	float m_wallSpeed;

	std::unique_ptr<WallManager> m_smpWallManager;

	std::unique_ptr<Player> m_smpPlayer;

	//std::unique_ptr<BlockUnit> m_smpBlockUnit;

	//std::vector<std::unique_ptr<BlockUnit>> m_smpBlockUnit;

	std::unique_ptr<BlockUnit> m_blockUnits[Define::BLOCK_H_NUM];


	const Texture woodTexture{ U"example/texture/wood.jpg", TextureDesc::MippedSRGB };

	int m_blockIndex;
};

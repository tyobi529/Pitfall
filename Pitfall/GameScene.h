# pragma once
# include "Common.h"
#include <vector>
#include <memory>   // スマートポインタ
#include "Wall.h"

#include "WallManager.h"

#include "Player.h"

#include "PlayerBlock.h"


#include "Enemy.h"
#include "EnemyManager.h"

// ゲームシーン
class GameScene : public App::Scene
{
public:

	GameScene(const InitData& init);

	void update() override;
	void updateInterval(); 

	void draw() const override;


	void InitGame();

	//void DecideBlockType(Block::TYPE* pType, bool isNone = false, bool isHall = false);

	void DrawStage() const;

	//void DropPlayerBlock(std::shared_ptr<BlockUnit> blockUnit, Block::TYPE* types = nullptr);

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


	//const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const ColorF backgroundColor = ColorF{ 0.02 }.removeSRGBCurve();

	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	//const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };

	Vec3 eyePosition;

	double angle = 0_deg;
	//double angle = 30_deg;

	BasicCamera3D camera;

	//プレイヤー
	//Mesh playerMesh;

	//Vec3 playerPos;

	Mesh playerMesh;
	//Vec3 playerPos;

	int playerPosX = 3;
	int depthZ = 1;

	std::vector<std::unique_ptr<Wall>> m_smpWalls;


	//== 時間 ==
	float m_gameTime; //ゲームシーンの経過時間合計
	float m_deltaTime; //前フレームからの経過時間
	float m_timeSpeed; //時間経過速度（基本的に1）

	float m_wallSpeed;

	std::unique_ptr<WallManager> m_smpWallManager;



	const Texture woodTexture{ U"example/texture/wood.jpg", TextureDesc::MippedSRGB };


	std::shared_ptr<Player> m_smpPlayer;


	//Block* m_pPlayerBlocks;


	int m_blockIndex;


	int m_count;

	bool m_isDebug;

	int m_tapCount;

	float m_fallTime;
	float m_fallValue;

	//const Mesh cylinder24{ MeshData::Cylinder(Vec3{0,0,0}, 0.5, 1, 24u) };

	float m_timeCount;

	std::unique_ptr<EnemyManager> m_smpEnemyManager;


	float m_nextEverySecondTime;

	PixelShader psBright;

	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R16G16B16A16_Float, HasDepth::Yes };
	RenderTexture gaussianA4, gaussianB4;
	RenderTexture gaussianA8, gaussianB8;
	RenderTexture gaussianA16, gaussianB16;


	const Mesh oneSidedPlane{ MeshData::OneSidedPlane(Vec2{ 6,2 }) };

	const Texture bgTex{ U"img/bg.png", TextureDesc::MippedSRGB };

	const Mesh bgPlane{ MeshData::OneSidedPlane(15) };

};

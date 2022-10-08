# pragma once
# include "Common.h"
#include <vector>
#include <memory>   // スマートポインタ
#include "Wall.h"
//class Wall;

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

	Vec3 eyePosition{ 0, 0, -25 };

	double angle = 0_deg;
	BasicCamera3D camera;

	//プレイヤー
	//Mesh playerMesh;

	//Vec3 playerPos;

	Mesh playerMesh;
	Vec3 playerPos;

	int playerPosX = 3;
	int depthZ = 1;
	int wallWidth = 3;

	bool isLeft = true;

	//std::vector<Wall*> m_pWalls;

	//std::vector<std::shared_ptr<Wall>> vec = std::vector<std::shared_ptr<Wall>>();

	std::vector<std::unique_ptr<Wall>> m_smpWalls;


	//ゲーム時間
	float m_gameTime;
	//時間経過速度
	float m_timeSpeed;
};

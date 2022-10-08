# pragma once
# include <Siv3D.hpp>

// シーンの名前
enum class State
{
	Title,
	Game,
};

// 共有するデータ
struct GameData
{
	//ゲーム時間
	float gameTime;
	//1フレームの経過時間
	float deltaTime;

	// 直前のゲームのスコア
	Optional<int32> lastGameScore;

	// ハイスコア
	Array<int32> highScores = { 50, 40, 30, 20, 10 };

	GameData() :
		gameTime(0),
		deltaTime(0)
	{
	}

	~GameData() {};

	void Init() {
		gameTime = 0;
		deltaTime = 0;
	}

	void UpdateTime(float timeSpeed = 1.0f)
	{
		deltaTime = timeSpeed * (float)Scene::DeltaTime();
		gameTime += deltaTime;
	}

};

using App = SceneManager<State, GameData>;

# include "Common.h"
# include "TitleScene.h"
# include "GameScene.h"

#include "Define.h"
#include "Tween.hpp"


void Main()
{
	Window::Resize(Define::WIN_H, Define::WIN_W);

	Define::RegisterTexture(); //テクスチャ登録

	FontAsset::Register(U"TitleFont", FontMethod::MSDF, 50, U"example/font/RocknRoll/RocknRollOne-Regular.ttf");
	FontAsset(U"TitleFont").setBufferThickness(4);
	FontAsset::Register(U"Menu", FontMethod::MSDF, 40, Typeface::Medium);
	FontAsset::Register(U"GameScore", 30, Typeface::Light);
	AudioAsset::Register(U"Brick", GMInstrument::Woodblock, PianoKey::C5, 0.2s, 0.1s);

	App manager;
	manager.add<TitleScene>(State::Title);
	manager.add<GameScene>(State::Game);

	// ゲームシーンから開始したい場合はこのコメントを外す
	manager.init(State::Game);


	//TODO
	Tween::Timeline timeline(0); // 初期値は0

	timeline.Init(100);

	timeline
		.then(200, 5.0s)     // 200まで5秒で動く
		.then(400, 5.0s)     // そこから400まで5秒で動く
		.wait(1.0s)          // 1秒待ち
		.then(600, 5.0s);    // そこから600まで5秒で動く

	timeline.start();



	while (System::Update())
	{
		//TODO
		 // 更新する
		timeline.update();

		ClearPrint();

		Print << timeline.elapsed();
		// .getValueか()演算子で値を取得
		Print << timeline();


		if (not manager.update())
		{
			break;
		}
	}
}

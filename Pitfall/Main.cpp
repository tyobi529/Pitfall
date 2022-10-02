# include "Common.h"
# include "TitleScene.h"
# include "GameScene.h"




void Main()
{
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


	Window::Resize(540, 960);


	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}

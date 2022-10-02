﻿# include "TitleScene.h"

TitleScene::TitleScene(const InitData& init)
	: IScene{ init } {}

void TitleScene::update()
{
	m_startTransition.update(m_startButton.mouseOver());
	m_rankingTransition.update(m_rankingButton.mouseOver());
	m_exitTransition.update(m_exitButton.mouseOver());

	if (m_startButton.mouseOver() || m_rankingButton.mouseOver() || m_exitButton.mouseOver())
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}

	if (m_startButton.leftClicked())
	{
		// ゲームシーンへ
		changeScene(State::Game);
	}
	else if (m_exitButton.leftClicked())
	{
		// 終了
		System::Exit();
	}
}

void TitleScene::draw() const
{
	Scene::SetBackground(ColorF{ 0.2, 0.8, 0.4 });

	FontAsset(U"TitleSceneFont")(U"BREAKOUT")
		.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 400, 100 });

	m_startButton.draw(ColorF{ 1.0, m_startTransition.value() }).drawFrame(2);
	m_rankingButton.draw(ColorF{ 1.0, m_rankingTransition.value() }).drawFrame(2);
	m_exitButton.draw(ColorF{ 1.0, m_exitTransition.value() }).drawFrame(2);

	FontAsset(U"Menu")(U"PLAY").drawAt(m_startButton.center(), ColorF{ 0.25 });
	FontAsset(U"Menu")(U"RANKING").drawAt(m_rankingButton.center(), ColorF{ 0.25 });
	FontAsset(U"Menu")(U"EXIT").drawAt(m_exitButton.center(), ColorF{ 0.25 });
}

#pragma once

class Define final {
public:
	const static int WIN_H;	//ウィンドウサイズ縦
	const static int WIN_W;	//ウィンドウサイズ横


	//============ GameScene ============
	//const static float TIME_SPEED_FIRST;	//最初の時間経過速度

	//player
	const static Vec3 PLAYER_POS; //右にいるときのプレイヤーの座標。右下手前の点。これを基準にwallも作る
	const static float PLAYER_WIDTH; //プレイヤーの横幅（x方向の長さ）
	const static float DEPTH_Z; //奥行。wallと共通

	//wall
	const static float WALL_WIDTH; //壁の横幅（x方向の長さ）
	const static float WALL_SPEED_FIRST; //最初の壁の落下速度

	//===================================


};

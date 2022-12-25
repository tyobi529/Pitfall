#pragma once

#include "Siv3D.hpp"

class Define final {
	
public:
	static void RegisterTexture();


	////可変
	//float playerMoveValue;

	//Define() :
	//	playerMoveValue(0)
	//{}

	//===================================
	const static int WIN_H;	//ウィンドウサイズ縦
	const static int WIN_W;	//ウィンドウサイズ横

	//カメラ位置
	const static Vec3 EYE_POS;

	//=============　定数 =================
	enum
	{
		BLOCK_GROUND_TOP_NUM = 5,
		BLOCK_GROUND_BOTTOM_NUM = 3,

		BLOCK_NUM = 10,

		BLOCK_V_NUM = BLOCK_GROUND_BOTTOM_NUM + BLOCK_NUM + BLOCK_GROUND_TOP_NUM,
		BLOCK_H_NUM = 20, //横に並ぶすべてのブロックの数

		BLOCK_PLAYE_INDEX = 0, //プレイヤーがいるブロックのindex（x方向）

	};

	const static float LIMIT_POS_Y_STAGE_BOTTOM;
	const static float LIMIT_POS_Y_HURDLE_BOTTOM;
	const static float LIMIT_POS_Y_HURDLE_TOP;
	const static float LIMIT_POS_Y_STAGE_TOP;

	const static float BLOCK_EXPAND_SPEED;


	const static float BLOCK_SIZE; //ブロックの一辺の長さ


	//player
	const static float PLAYER_POS_X; //プレイヤーのx座標。

	//===================================

	const static float INTERVAL_SECOND;

	//敵の移動
	const static float ENEMY_GENERATE_POS_X;
	const static float ENEMY_START_POS_X;
	const static float ENEMY_END_POS_X;

	const static int ENEMY_COUNT;

	const static float ENEMY_DELAY_SECOND;
	const static float ENEMY_MOVE_1_SECOND;
	const static float ENEMY_MOVE_2_SECOND;
	const static float ENEMY_MOVE_3_SECOND;

	const static float ENEMY_IN_SECOND;

	
	const static Duration FLYING_BLOW_SLOW_SECOND;
	const static Duration FLYING_BLOW_MOVE_SECOND;

	const static Duration FLYING_OVERFLOW_UP_SECOND;
	//const static Duration FLYING_OVERFLOW_DOWN_SECOND;

	const static double FLYING_OVERFLOW_ANGLE_MIN;
	const static double FLYING_OVERFLOW_ANGLE_MAX;
	const static double FLYING_OVERFLOW_ANGLE_PITCH;


	static int SCORE;

};

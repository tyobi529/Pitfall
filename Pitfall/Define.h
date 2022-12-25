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

		BLOCK_HURDLE_CENTER_NUM = 10,
		BLOCK_HURDLE_HALL_NUM = 0, //流れるブロックのうち、穴をあけられる部分

		BLOCK_HURDLE_NUM = BLOCK_HURDLE_CENTER_NUM + 2 * BLOCK_HURDLE_HALL_NUM,
		BLOCK_V_NUM = BLOCK_GROUND_BOTTOM_NUM + BLOCK_HURDLE_NUM + BLOCK_GROUND_TOP_NUM,
		BLOCK_H_NUM = 20, //横に並ぶすべてのブロックの数

		BLOCK_PLAYE_INDEX = 0, //プレイヤーがいるブロックのindex（x方向）
		//BLOCK_ENEMY_INDEX = 3, //プレイヤーがいるブロックのindex（x方向）

		ENEMY_MOVE_COUNT = 12,

		BLOCK_NUM = BLOCK_HURDLE_NUM,
	};

	const static float LIMIT_POS_Y_STAGE_BOTTOM;
	const static float LIMIT_POS_Y_HURDLE_BOTTOM;
	const static float LIMIT_POS_Y_HURDLE_TOP;
	const static float LIMIT_POS_Y_STAGE_TOP;


	const static float GROUND_POS_Y;

	const static float BLOCK_LIMIT_POS_X;
	const static float BLOCK_GENERATED_POS_X;

	const static float BLOCK_SPEED;
	const static float BLOCK_EXPAND_SPEED;



	//============ GameScene ============
	//const static float TIME_SPEED_FIRST;	//最初の時間経過速度

	const static float FIELD_RANGE_X;
	const static float FIELD_RANGE_Y;


	//const static int BLOCK_NUM_V; //縦方向のブロック数。BLOCK_HALL含む
	//const static int BLOCK_HALL_NUM; //穴が開けられる部分のブロックの数。

	const static float BLOCK_SIZE; //ブロックの一辺の長さ


	//player
	//const static Vec3 PLAYER_POS; //右にいるときのプレイヤーの座標。右下手前の点。これを基準にwallも作る
	const static float PLAYER_POS_X; //プレイヤーのx座標。

	const static float PLAYER_WIDTH; //プレイヤーの横幅（x方向の長さ）
	const static float DEPTH_Z; //奥行。wallと共通

	//wall
	const static float WALL_WIDTH; //壁の横幅（x方向の長さ）
	const static float WALL_SPEED_FIRST; //最初の壁の落下速度

	//===================================

	//TODO
	const static int START_POS_X;
	const static int END_POS_X;


	const static float BOTTOM_POS_Y;

	const static int SPEED_LEVEL_MIN;
	const static int SPEED_LEVEL_MAX;
	const static float SPEED_PER_LEVEL;

	const static float INTERVAL_SECOND;

	//敵の移動
	const static float ENEMY_GENERATE_POS_X;
	const static float ENEMY_START_POS_X;
	const static float ENEMY_END_POS_X;

	const static int ENEMY_COUNT;
	//const static int ENEMY_COUNT_IN;
	//const static int ENEMY_COUNT_DELAY;
	//const static int ENEMY_COUNT_MOVE_1;
	//const static int ENEMY_COUNT_MOVE_2;
	//const static int ENEMY_COUNT_MOVE_3;

	const static float ENEMY_DELAY_SECOND;
	const static float ENEMY_MOVE_1_SECOND;
	const static float ENEMY_MOVE_2_SECOND;
	const static float ENEMY_MOVE_3_SECOND;

	const static float ENEMY_IN_SECOND;

	const static Duration FLYING_BLOW_SLOW_SECOND;
	const static Duration FLYING_BLOW_MOVE_SECOND;

	static int SCORE;

};

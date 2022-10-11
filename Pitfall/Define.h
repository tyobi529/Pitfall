#pragma once


class Define final {
	
public:
	static void RegisterTexture();

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

		BLOCK_HURDLE_CENTER_NUM = 8,
		BLOCK_HURDLE_HALL_NUM = 2, //流れるブロックのうち、穴をあけられる部分

		BLOCK_HURDLE_NUM = BLOCK_HURDLE_CENTER_NUM + 2 * BLOCK_HURDLE_HALL_NUM,
		BLOCK_V_NUM = BLOCK_GROUND_BOTTOM_NUM + BLOCK_HURDLE_NUM + BLOCK_GROUND_TOP_NUM,
		BLOCK_H_NUM = 15, //横に並ぶすべてのブロックの数


	};

	const static float LIMIT_POS_Y_STAGE_BOTTOM;
	const static float LIMIT_POS_Y_HURDLE_BOTTOM;
	const static float LIMIT_POS_Y_HURDLE_TOP;
	const static float LIMIT_POS_Y_STAGE_TOP;


	const static float GROUND_POS_Y;

	const static float BLOCK_LIMIT_POS_X;
	const static float BLOCK_GENERATED_POS_X;

	const static float BLOCK_SPEED;



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


};

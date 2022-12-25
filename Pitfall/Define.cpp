#include "Define.h"


void Define::RegisterTexture()
{
	TextureAsset::Register(U"wood", U"example/texture/wood.jpg");

	TextureAsset::Register(U"uvChecker", U"example/texture/uv.png");

	TextureAsset::Register(U"green", U"img/Green.png");

	//25×25
	TextureAsset::Register(U"normal", U"img/normal.png");
	TextureAsset::Register(U"head", U"img/head.png");

	TextureAsset::Register(U"bg", U"img/bg.png");


//https://www.peko-step.com/tool/alphachannel.html

}


const int   Define::WIN_H = 540;		//ウィンドウサイズ縦
const int   Define::WIN_W = 960;		//ウィンドウサイズ横


//カメラ位置
//const Vec3 Define::EYE_POS = Vec3(2, 12, -35);
//const Vec3 Define::EYE_POS = Vec3(-13, 12, -30);
const Vec3 Define::EYE_POS = Vec3(-7, 12, -35);
//const Vec3 Define::EYE_POS = Vec3(2, 17, -35);
//const Vec3 Define::EYE_POS = Vec3(2, 6, -35);


const float Define::BLOCK_SIZE = 1.0f;

const float Define::LIMIT_POS_Y_STAGE_BOTTOM = 3.0f;
const float Define::LIMIT_POS_Y_HURDLE_BOTTOM = LIMIT_POS_Y_STAGE_BOTTOM + Define::BLOCK_SIZE * (float)Define::BLOCK_GROUND_BOTTOM_NUM;
const float Define::LIMIT_POS_Y_HURDLE_TOP = LIMIT_POS_Y_STAGE_BOTTOM + Define::BLOCK_SIZE * (float)(Define::BLOCK_GROUND_BOTTOM_NUM + Define::BLOCK_NUM);
const float Define::LIMIT_POS_Y_STAGE_TOP = LIMIT_POS_Y_STAGE_BOTTOM + Define::BLOCK_SIZE * (float)Define::BLOCK_V_NUM;


const float Define::BLOCK_EXPAND_SPEED = 5.0f;


//player
const float Define::PLAYER_POS_X = Define::BLOCK_SIZE * (float)BLOCK_PLAYE_INDEX;



//===================================


//１カウントの時間
const float Define::INTERVAL_SECOND = 0.5f;

//敵の移動
const float Define::ENEMY_GENERATE_POS_X = 8.0f;
const float Define::ENEMY_START_POS_X = 6.0f;
const float Define::ENEMY_END_POS_X = 1.0f;

const float Define::ENEMY_IN_SECOND = 0.5f;
const float Define::ENEMY_DELAY_SECOND = 0.5f;
const float Define::ENEMY_MOVE_1_SECOND = 4.0f;
const float Define::ENEMY_MOVE_2_SECOND = 3.0f;
const float Define::ENEMY_MOVE_3_SECOND = 2.0f;

//生成からぶつかるまでの全体カウント。一番遅いMOVE_1に合わせている
const int Define::ENEMY_COUNT = (ENEMY_IN_SECOND + ENEMY_DELAY_SECOND + ENEMY_MOVE_1_SECOND) / INTERVAL_SECOND + 1;


const Duration Define::FLYING_BLOW_SLOW_SECOND = (Duration)Define::INTERVAL_SECOND;
const Duration Define::FLYING_BLOW_MOVE_SECOND = 1.0s;

const Duration Define::FLYING_OVERFLOW_UP_SECOND = 0.2s;
const double Define::FLYING_OVERFLOW_ANGLE_MIN = 1.0f;
const double Define::FLYING_OVERFLOW_ANGLE_MAX = 9.0f;
const double Define::FLYING_OVERFLOW_ANGLE_PITCH = (FLYING_OVERFLOW_ANGLE_MAX - FLYING_OVERFLOW_ANGLE_MIN) / (double)Define::BLOCK_NUM;

int Define::SCORE = 0;

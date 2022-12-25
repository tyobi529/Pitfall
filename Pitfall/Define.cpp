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

//
//const Vec3 Define::EYE_POS = Vec3(2, 17, -35);
//const Vec3 Define::EYE_POS = Vec3(2, 6, -35);


const float Define::BLOCK_SIZE = 1.0f;

const float Define::LIMIT_POS_Y_STAGE_BOTTOM = 3.0f;
const float Define::LIMIT_POS_Y_HURDLE_BOTTOM = LIMIT_POS_Y_STAGE_BOTTOM + Define::BLOCK_SIZE * (float)Define::BLOCK_GROUND_BOTTOM_NUM;
const float Define::LIMIT_POS_Y_HURDLE_TOP = LIMIT_POS_Y_STAGE_BOTTOM + Define::BLOCK_SIZE * (float)(Define::BLOCK_GROUND_BOTTOM_NUM + Define::BLOCK_HURDLE_NUM);
const float Define::LIMIT_POS_Y_STAGE_TOP = LIMIT_POS_Y_STAGE_BOTTOM + Define::BLOCK_SIZE * (float)Define::BLOCK_V_NUM;

//const Texture woodTexture{ U"example/texture/wood.jpg", TextureDesc::MippedSRGB };
//const Texture woodTexture = Texture{ U"example/texture/wood.jpg", TextureDesc::MippedSRGB };

//============ GameScene ============
//const float Define::TIME_SPEED_FIRST = 1.0f;	//最初の時間経過速度

const float Define::FIELD_RANGE_X = 10.0f;
const float Define::FIELD_RANGE_Y = 10.0f;

const float Define::GROUND_POS_Y = 0.0f;

const float Define::BLOCK_LIMIT_POS_X = 0.0f;

const float Define::BLOCK_GENERATED_POS_X = Define::BLOCK_SIZE * (float)BLOCK_H_NUM;

const float Define::BLOCK_SPEED = 3.0f;

const float Define::BLOCK_EXPAND_SPEED = 5.0f;



//const int Define::BLOCK_NUM_V = 12; 
//const int Define::BLOCK_HALL_NUM = 2; //穴が開けられる部分のブロックの数。


//player
//const Vec3 Define::PLAYER_POS = Vec3(4, 0, 0); //右にいるときのプレイヤーの座標。右下手前の点。これを基準にwallも作る
const float Define::PLAYER_POS_X = Define::BLOCK_SIZE * (float)BLOCK_PLAYE_INDEX;

const float Define::PLAYER_WIDTH = 1.0f; //プレイヤーの横幅（x方向の長さ）
const float Define::DEPTH_Z = 1.0f; //奥行。wallと共通

//wall
const float Define::WALL_WIDTH = 3.0f; //壁の横幅（x方向の長さ）
const float Define::WALL_SPEED_FIRST = 3.0f; //最初の壁の落下速度

//===================================

//TODO
const int Define::END_POS_X = 1;
const int Define::START_POS_X = END_POS_X + Define::ENEMY_MOVE_COUNT;

const float Define::BOTTOM_POS_Y = LIMIT_POS_Y_STAGE_BOTTOM + Define::BLOCK_SIZE * (float)Define::BLOCK_GROUND_BOTTOM_NUM;

const int Define::SPEED_LEVEL_MIN = 1;
const int Define::SPEED_LEVEL_MAX = 3;//スピード3段階
//const float Define::SPEED_PER_LEVEL = 0.8f; //1段階で上がるスピード
const float Define::SPEED_PER_LEVEL = 0.3f; //1段階で上がるスピード

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


const Duration Define::FLYING_BLOW_SLOW_SECOND = 0.5s;
const Duration Define::FLYING_BLOW_MOVE_SECOND = 1.0s;

const Duration Define::FLYING_OVERFLOW_UP_SECOND = 0.2s;
//const Duration Define::FLYING_OVERFLOW_DOWN_SECOND = 0.5s;

int Define::SCORE = 0;

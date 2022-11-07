#include "Define.h"


void Define::RegisterTexture()
{
	TextureAsset::Register(U"wood", U"example/texture/wood.jpg");

	TextureAsset::Register(U"uvChecker", U"example/texture/uv.png");

	TextureAsset::Register(U"green", U"img/Green.png");

	//25×25
	TextureAsset::Register(U"normal", U"img/normal.png");
	TextureAsset::Register(U"head", U"img/head.png");

//https://www.peko-step.com/tool/alphachannel.html

}


const int   Define::WIN_H = 540;		//ウィンドウサイズ縦
const int   Define::WIN_W = 960;		//ウィンドウサイズ横


//カメラ位置
const Vec3 Define::EYE_POS = Vec3(2, 12, -35);

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
const int Define::START_POS_X = 11;
const int Define::END_POS_X = 1;

const float Define::BOTTOM_POS_Y = LIMIT_POS_Y_STAGE_BOTTOM + Define::BLOCK_SIZE * (float)Define::BLOCK_GROUND_BOTTOM_NUM;

#include "Define.h"

const int   Define::WIN_H = 540;		//ウィンドウサイズ縦
const int   Define::WIN_W = 960;		//ウィンドウサイズ横

//============ GameScene ============
//const float Define::TIME_SPEED_FIRST = 1.0f;	//最初の時間経過速度

//player
const Vec3 Define::PLAYER_POS = Vec3(4.0f, 2.0f, 0.0f); //右にいるときのプレイヤーの座標。右下手前の点。これを基準にwallも作る
const float Define::PLAYER_WIDTH = 1.0f; //プレイヤーの横幅（x方向の長さ）
const float Define::DEPTH_Z = 1.0f; //奥行。wallと共通

//wall
const float Define::WALL_WIDTH = 3.0f; //壁の横幅（x方向の長さ）
const float Define::WALL_SPEED_FIRST = 3.0f; //最初の壁の落下速度

//===================================

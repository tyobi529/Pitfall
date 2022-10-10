#include "stdafx.h"
#include "Player.h"

#include "Define.h"

Player::Player() :
	m_isLeft(true),
	m_blockNum(0)
{
	//m_pos.x = -m_pos.x;

	//m_blockNum = 3;
}

Player::~Player()
{

}

void Player::update()
{
	if (MouseL.up())
	{
		m_blockNum++;
	}
}

void Player::draw()
{

	//Vec3 playerPos = Vec3(Define::PLAYER_POS_X, Define::GROUND_POS_Y, 0.0f);
	//for (int i = 0; i < m_blockNum; i++)
	//{
	//	Vec3 pos1 = playerPos;
	//	Vec3 pos2 = Vec3(pos1.x + Define::PLAYER_WIDTH, pos1.y + Define::PLAYER_WIDTH, pos1.z + Define::DEPTH_Z);
	//	//Box::FromPoints(pos1, pos2).draw(ColorF{ 0.8, 0.6, 0.4 });
	//	Box::FromPoints(pos1, pos2).draw(woodTexture);
	//	playerPos.y += Define::PLAYER_WIDTH;
	//}

	//Vec3 headPos1 = playerPos;
	//Vec3 headPos2 = Vec3(headPos1.x + Define::PLAYER_WIDTH, headPos1.y + Define::PLAYER_WIDTH, headPos1.z + Define::DEPTH_Z);
	//Box::FromPoints(headPos1, headPos2).draw(ColorF{ 0.4, 0.9, 0.2 });


	Vec3 playerPos = Vec3(Define::PLAYER_POS_X, Define::GROUND_POS_Y + Define::BLOCK_HURDLE_HALL_NUM * 2, 0.0f);
	for (int i = 0; i < m_blockNum; i++)
	{
		Vec3 pos1 = playerPos;
		Vec3 pos2 = Vec3(pos1.x + Define::PLAYER_WIDTH, pos1.y + Define::PLAYER_WIDTH, pos1.z + Define::DEPTH_Z);
		//Box::FromPoints(pos1, pos2).draw(ColorF{ 0.8, 0.6, 0.4 });
		Box::FromPoints(pos1, pos2).draw(woodTexture);
		playerPos.y += Define::PLAYER_WIDTH;
	}

	Vec3 headPos1 = playerPos;
	Vec3 headPos2 = Vec3(headPos1.x + Define::PLAYER_WIDTH, headPos1.y + Define::PLAYER_WIDTH, headPos1.z + Define::DEPTH_Z);
	Box::FromPoints(headPos1, headPos2).draw(ColorF{ 0.4, 0.9, 0.2 });

}

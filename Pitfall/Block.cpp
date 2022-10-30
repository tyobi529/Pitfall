﻿#include "stdafx.h"
#include "Block.h"

#define SIZE Define::BLOCK_SIZE

Block::Block(int index) :
	m_index(index),
	m_type(TYPE::BLOCK_NONE),
	m_centerPos(Vec3(0, 0, 0)),
	m_size(Define::BLOCK_SIZE)
{
	Init();
}


Block::~Block()
{
}

void Block::Init()
{
	m_type = TYPE::BLOCK_NONE; //typeが消えるので注意
	m_centerPos = Vec3(0, 0, 0);
	//m_size = Define::BLOCK_SIZE;
}

void Block::update()
{

}

void Block::draw() const
{
	switch (m_type)
	{
	case Block::BLOCK_NONE:
		break;
	case Block::BLOCK_GROUND:
		Box{ m_centerPos, m_size }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
		//Box{ m_centerPos, m_size }.draw(TextureAsset(U"normal"));
		break;
	case Block::BLOCK_NORMAL:
		//Box{ m_centerPos, m_size }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
		Box{ m_centerPos, m_size }.draw(TextureAsset(U"normal"));
		break;
	case Block::BLOCK_HEAD:
		Box{ m_centerPos, m_size }.draw(TextureAsset(U"head"));
		break;
	case Block::BLOCK_BONUS:
		Box{ m_centerPos, 0.5 }.draw(ColorF{ 0.85, 0.7, 0 }.removeSRGBCurve());
		break;
	case Block::BLOCK_PLAYER_HEAD:
		Box{ m_centerPos, m_size }.draw(ColorF{ 0.2, 0.6, 0.4 }.removeSRGBCurve());
		break;
	case Block::BLOCK_PLAYER_BODY:
		Box{ m_centerPos, m_size }.draw(ColorF{ 0.6, 0.6, 0.3 }.removeSRGBCurve());
		break;
	default:
		break;
	}
}


void Block::SetCenterPos(float posX, float posY)
{
	//x, y, zをsizeの半分ずらす
	//float dif = Define::BLOCK_SIZE / 2.0f;
	float dif = 0;
	m_centerPos = Vec3(posX + dif, posY + dif, 0 + dif);

}


#include "stdafx.h"
#include "Block.h"

#include "Define.h"


Block::Block(int index) :
	m_index(index),
	m_type(TYPE::BLOCK_NONE),
	m_centerPos(Vec3(0, 0, 0))
{
}


Block::~Block()
{

}


void Block::draw()
{
	switch (m_type)
	{
	case Block::BLOCK_NONE:
		//Box{ m_centerPos, Define::BLOCK_SIZE }.draw(ColorF{ 0.8, 0.6, 0.4, 0.5f }.removeSRGBCurve());
		break;
	case Block::BLOCK_GROUND:
		Box{ m_centerPos, Define::BLOCK_SIZE }.draw(TextureAsset(U"wood"));
		break;
	//case Block::BLOCK_HALL:
	//	Box{ m_centerPos, Define::BLOCK_SIZE }.draw(ColorF{ 0, 0.5, 0 }.removeSRGBCurve());
	//	break;
	case Block::BLOCK_NORMAL:
		Box{ m_centerPos, Define::BLOCK_SIZE }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
		break;
	case Block::BLOCK_PLAYER_HEAD:
		Box{ m_centerPos, Define::BLOCK_SIZE }.draw(ColorF{ 0.2, 0.6, 0.4 }.removeSRGBCurve());
		break;
	case Block::BLOCK_PLAYER_BODY:
		Box{ m_centerPos, Define::BLOCK_SIZE }.draw(ColorF{ 0.6, 0.6, 0.3 }.removeSRGBCurve());
		break;
	default:
		break;
	}
}

void Block::SetType(TYPE type)
{
	m_type = type;
}

void Block::SetPos(Vec3 pos)
{
	//x, y, zをsizeの半分ずらす
	float dif = Define::BLOCK_SIZE / 2.0f;
	m_centerPos = Vec3(pos.x + dif, pos.y + dif, pos.z + dif);
}

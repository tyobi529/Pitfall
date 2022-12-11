#include "stdafx.h"
#include "Block.h"

#define SIZE Define::BLOCK_SIZE

Block::Block() :
	m_pos(Vec3(0, 0, 0)),
	m_size(0),
	m_type(TYPE::BLOCK_NONE)
{
}


void Block::draw() const
{
	switch (m_type)
	{
	case Block::BLOCK_NONE:
		break;
	case Block::BLOCK_GROUND:
		Box{ m_pos, m_size }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
		//Box{ m_centerPos, m_size }.draw(TextureAsset(U"normal"));
		break;
	case Block::BLOCK_NORMAL:
		//Box{ m_centerPos, m_size }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
		Box{ m_pos, m_size }.draw(TextureAsset(U"normal"));
		break;
	case Block::BLOCK_HEAD:
		Box{ m_pos, m_size }.draw(TextureAsset(U"head"));
		break;
	case Block::BLOCK_BONUS:
		Box{ m_pos, 0.5 }.draw(ColorF{ 0.85, 0.7, 0 }.removeSRGBCurve());
		break;
	case Block::BLOCK_PLAYER_HEAD:
		Box{ m_pos, m_size }.draw(ColorF{ 0.2, 0.6, 0.4 }.removeSRGBCurve());
		break;
	case Block::BLOCK_PLAYER_BODY:
		Box{ m_pos, m_size }.draw(ColorF{ 0.6, 0.6, 0.3 }.removeSRGBCurve());
		break;
	default:
		break;
	}
}

void Block::SetPosition(float x, float y, float z)
{
	float posX = x;
	//y,zは指定していないなら元の値を使う
	float posY = m_pos.y;
	if (y != -1) posY = y;
	float posZ = m_pos.z;
	if (z != -1) posZ = y;

	m_pos = Vec3(posX, posY, posZ);
}

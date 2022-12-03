#include "stdafx.h"
#include "Block.h"

#define SIZE Define::BLOCK_SIZE

Block::Block(int index) : Object()
	, m_index(index)
	, m_type(TYPE::BLOCK_NONE)
{
	Init();
}


Block::~Block()
{
}

void Block::Init()
{
	m_type = TYPE::BLOCK_NONE; //typeが消えるので注意
	m_pos = Vec3(0, 0, 0);
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



#include "stdafx.h"
#include "Block.h"


#define SIZE Define::BLOCK_SIZE

Block::Block(int rowIndex, int colIndex) :
	m_rowIndex(rowIndex),
	m_colIndex(colIndex),
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
		break;
	case Block::BLOCK_GROUND:
		Box{ m_centerPos, Define::BLOCK_SIZE }.draw(TextureAsset(U"wood"));
		break;
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

void Block::SetPos(float difX, float difY)
{
	//x, y, zをsizeの半分ずらす
	float posX = SIZE * m_rowIndex + difX;
	float posY = Define::LIMIT_POS_Y_HURDLE_BOTTOM + SIZE * m_colIndex + difY;
	float posZ = 0;

	float dif = Define::BLOCK_SIZE / 2.0f;
	m_centerPos = Vec3(posX + SIZE / 2.0f, posY + SIZE / 2.0f, posZ + SIZE / 2.0f);

}

//void Block::SetPos(Vec3 pos)
//{
//	//x, y, zをsizeの半分ずらす
//	float dif = Define::BLOCK_SIZE / 2.0f;
//	m_centerPos = Vec3(pos.x + dif, pos.y + dif, pos.z + dif);
//}

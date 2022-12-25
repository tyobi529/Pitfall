#include "stdafx.h"
#include "Block.h"

#define SIZE Define::BLOCK_SIZE

Block::Block() :
	m_pos(Vec3(0, 0, 0)),
	m_quaternion(),
	m_size(0),
	m_type(TYPE::BLOCK_NONE)
{
}

void Block::draw() const
{
	if (m_type == BLOCK_NONE)
	{

	}
	else if (m_type == BLOCK_GROUND)
	{
		Box{ m_pos, m_size }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());

	}
	else if (m_type == BLOCK_HEAD)
	{
		Box{ m_pos, m_size }.draw(TextureAsset(U"head"));

	}
	else if (m_type == BLOCK_BONUS)
	{
		Box{ m_pos, 0.5 }.draw(ColorF{ 0.85, 0.7, 0 }.removeSRGBCurve());

	}
	else if (m_type == BLOCK_PLAYER_HEAD)
	{
		//Box{ m_pos, m_size }.draw(ColorF{ 0.2, 0.6, 0.4 }.removeSRGBCurve());
		Box{ m_pos, m_size }.draw(ColorF{ 0.2, 0.6, 0.4 }.removeSRGBCurve() * 0.5f);

	}
	else if (m_type == BLOCK_PLAYER_BODY)
	{
		//Box{ m_pos, m_size }.draw(ColorF{ 0.6, 0.6, 0.3 }.removeSRGBCurve());
		Box{ m_pos, m_size }.draw(ColorF{ 0.6, 0.6, 0.3 }.removeSRGBCurve() * 0.5f);

	}
	else if (m_type == BLOCK_PLAYER_BODY_DOWN)
	{
		//Box{ m_pos, m_size }.draw(ColorF{ 0.6, 0.6, 0.3 }.removeSRGBCurve());
		Box{ m_pos, m_size }.draw(ColorF{ 0.6, 0.6, 0.3 }.removeSRGBCurve() * 0.7f);

	}
	else if (m_type == BLOCK_ENEMY_1)
	{
		PhongMaterial phong;
		phong.amibientColor = ColorF{ 1.0 };
		phong.diffuseColor = ColorF{ 0.0 };
		phong.emissionColor = ColorF{ 0.4, 0.4, 1.0 }.removeSRGBCurve() * 0.5f;
		Sphere{ m_pos, m_size / 2 }.draw(phong);

	}
	else if (m_type == BLOCK_ENEMY_2)
	{
		PhongMaterial phong;
		phong.amibientColor = ColorF{ 1.0 };
		phong.diffuseColor = ColorF{ 0.0 };
		phong.emissionColor = ColorF{ 0.4, 1.0, 0.4 }.removeSRGBCurve() * 0.5f;
		Sphere{ m_pos, m_size / 2 }.draw(phong);
	}
	else if (m_type == BLOCK_ENEMY_3)
	{
		PhongMaterial phong;
		phong.amibientColor = ColorF{ 1.0 };
		phong.diffuseColor = ColorF{ 0.0 };
		phong.emissionColor = ColorF{ 1.0, 0.4, 0.4 }.removeSRGBCurve() * 0.5f;
		Sphere{ m_pos, m_size / 2 }.draw(phong);
	}
	else if (m_type == BLOCK_ENEMY_COIN)
	{
		PhongMaterial phong;
		phong.amibientColor = ColorF{ 1.0 };
		phong.diffuseColor = ColorF{ 0.0 };
		phong.emissionColor = ColorF{ 0.7, 0.4, 0.4 }.removeSRGBCurve() * 0.5f;
		Sphere{ m_pos, m_size / 2 }.draw(phong);

	}
	else if (m_type == BLOCK_FLYING)
	{
		OrientedBox{ m_pos, 1, m_quaternion }.draw(ColorF{ 0.2, 0.6, 0.4 }.removeSRGBCurve());

	}


}

void Block::SetPosition(float x, float y, float z)
{
	float posX = x;
	//y,zは指定していないなら元の値を使う
	float posY = m_pos.y;
	if (y != -1) posY = y;
	float posZ = m_pos.z;
	if (z != -1) posZ = z;

	m_pos = Vec3(posX, posY, posZ);
}

//void Block::MovePosition(float moveX, float moveY, float moveZ)
//{
//	float posX = m_pos.x + moveX;
//	float posY = m_pos.y + moveY;
//	float posZ = m_pos.z + moveZ;
//
//	m_pos = Vec3(posX, posY, posZ);
//}


void Block::MovePosition(Vec3 val)
{
	float posX = m_pos.x + val.x;
	float posY = m_pos.y + val.y;
	float posZ = m_pos.z + val.z;

	m_pos = Vec3(posX, posY, posZ);
}

//
//void Block::Rotate(Vec3 rot)
//{
//	//RotateX
//	//m_quaternion = (Quaternion::RotateX(x * 20_deg) * Quaternion::RotateY(y * 20_deg) * Quaternion::RotateZ(z * 20_deg));
//	//void SetQuaternion(float x, float y = 0, float z = 0) { m_quaternion = (Quaternion::RotateX(x * 20_deg) * Quaternion::RotateY(y * 20_deg) * Quaternion::RotateZ(z * 20_deg)); };
//
//	m_quaternion = (Quaternion::RotateX(x * 20_deg) * Quaternion::RotateY(y * 20_deg) * Quaternion::RotateZ(z * 20_deg));
//
//	float x = m_quaternion.getX();
//	m_quaternion.RotateX(rot.x);
//	m_quaternion.RotateY(rot.y);
//	m_quaternion.RotateZ(rot.z);
//}

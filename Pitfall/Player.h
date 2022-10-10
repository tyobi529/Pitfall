#pragma once
class Player
{
public:

	Player();
	~Player();

	void update();
	void draw();

private:

	const Texture woodTexture{ U"example/texture/wood.jpg", TextureDesc::MippedSRGB };


	//Vec3 m_pos;
	bool m_isLeft;
	int m_blockNum;
};


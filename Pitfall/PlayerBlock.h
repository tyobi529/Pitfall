#pragma once

#include "Block.h"

class PlayerBlock : public Block
{
public:
	PlayerBlock();
	~PlayerBlock();

	void PlayerInit(bool isHead);


	void update() override;



private:

	//拡大
	bool m_isExpand;
	//倍率
	float m_sizeMag;
};


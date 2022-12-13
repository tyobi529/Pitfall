#pragma once

#include "Block.h"


class FlyingBlockManager
{
public:

	FlyingBlockManager();
	~FlyingBlockManager();

	void update();
	void draw() const;
	void updateEverySecond();

	void GenerateFlyingBlock(Vec3 pos);

	std::shared_ptr<Block> GetFlyingBlock();

private:
	Array<std::shared_ptr<Block>> m_smpFlyingBlockArray;

};


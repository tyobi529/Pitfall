#pragma once

#include "FlyingBlock.h"


class FlyingBlockManager
{
public:

	FlyingBlockManager();
	~FlyingBlockManager();

	void update();
	void draw() const;
	void updateInterval();

	void GenerateFlyingBlock(Vec3 pos);

	std::shared_ptr<FlyingBlock> GetFlyingBlock();

private:
	Array<std::shared_ptr<FlyingBlock>> m_smpFlyingBlockArray;

};


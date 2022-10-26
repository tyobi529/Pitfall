#include "stdafx.h"
#include "StageManager.h"


#define BLOCK_NUM Define::BLOCK_HURDLE_NUM


StageManager::StageManager() :
	m_count(0),
	m_intervalCount(0),
	m_preStep(0),
	m_baseNum(0),
	m_generateCount(0)
{

}

StageManager::~StageManager()
{
}



void StageManager::SetNextBlockUnit(Block::TYPE* pType)
{
	int currentStep = 0;

	m_generateCount++;

	if (m_count == m_baseNum)
	{
		//新しい基盤
		int maxStep = m_preStep + 2;
		if (maxStep >= BLOCK_NUM - 5)
		{
			maxStep = BLOCK_NUM - 5;
		}

		currentStep = Random(1, maxStep);
		//currentStep = 1;


		m_baseNum = Random(1, 10);
		m_count = 0;
		m_preStep = currentStep;

	}
	else
	{
		//１つ前と同じ基盤
		currentStep = m_preStep;

		m_count++;
	}

	//基盤部分
	for (int i = 0; i < currentStep; i++)
	{
		if (i < currentStep - 1)
		{
			pType[i] = Block::BLOCK_NORMAL;
		}
		else if (i == currentStep - 1)
		{
			pType[i] = Block::BLOCK_HEAD;
		}
		//else if (i == currentStep)
		//{
		//	pType[i] = Block::BLOCK_NONE;
		//}
	}

	//自由部分
	int normalCount = 0;

	bool isGimmick = false;
	if (m_generateCount > 5)
	{
		//最初3マスと最後はなし
		if (m_count <= 2 || m_count >= m_baseNum - 2)
		{
			//pType[i] = Block::BLOCK_NONE;
			isGimmick = false;
		}
		else
		{
			isGimmick = true;
		}
	}

	if (isGimmick)
	{
		int count = 0;
		bool isNone = false;
		for (int i = currentStep; i < BLOCK_NUM; i++)
		{
			//if (RandomBool())
			//{
			//	pType[i] = Block::BLOCK_NONE;
			//	isNone = true;
			//}
			//else
			//{
			//	pType[i] = Block::BLOCK_NORMAL;
			//}

			//if (!isNone && i == BLOCK_NUM - 1)
			//{
			//	pType[i] = Block::BLOCK_NONE;
			//}

			if (RandomBool(0.5 + 0.25 * count)) //ブロックが連続しすぎている場合も
			{
				pType[i] = Block::BLOCK_NONE;
				normalCount = 0;
				count = 0;
			}
			else
			{
				pType[i] = Block::BLOCK_NORMAL;
				normalCount++;
				count++;
			}


		}

		m_generateCount = 0;
	}
	else
	{
		for (int i = currentStep; i < BLOCK_NUM; i++)
		{
			pType[i] = Block::BLOCK_NONE;
		}

		m_generateCount++;
	}

	//for (int i = currentStep; i < BLOCK_NUM; i++)
	//{
	//	pType[i] = Block::BLOCK_NONE;

	//	//最初２マスと最後はなし
	//	if (m_count == 0 || m_count == 1 ||
	//		m_count == m_baseNum - 1 || m_count == m_baseNum)
	//	{
	//		pType[i] = Block::BLOCK_NONE;

	//	}
	//	else if (m_count % 3 == 1)
	//	{ 
	//		//if (RandomBool())
	//		//{
	//		//	pType[i] = Block::BLOCK_NONE;

	//		//}
	//		//else
	//		//{
	//		//	pType[i] = Block::BLOCK_NORMAL;
	//		//}

	//		if (RandomBool(0.2 * (normalCount + 1))) //ブロックが連続しすぎている場合も
	//		{
	//			pType[i] = Block::BLOCK_NONE;
	//			normalCount = 0;
	//		}
	//		else
	//		{
	//			pType[i] = Block::BLOCK_NORMAL;
	//			normalCount++;
	//		}
	//	}
	//}


}



//
//void StageManager::SetNextBlockUnit(Block::TYPE* pType)
//{
//	if (m_count == 0)
//	{
//		if (m_intervalCount > 0)
//		{
//			for (int i = 0; i < BLOCK_NUM; i++)
//			{
//				pType[i] = Block::BLOCK_NONE;
//			}
//			m_intervalCount--;
//			return;
//		}
//
//		int normalCount = 0;
//		int noneCount = 0;
//
//		//次のブロック決定
//		for (int i = 0; i < BLOCK_NUM; i++)
//		{
//			Block::TYPE type = Block::TYPE::BLOCK_NONE;
//
//			if (RandomBool(0.1 * i))
//			{
//				type = Block::BLOCK_NONE;
//
//			}
//			else
//			{
//				type = Block::BLOCK_NORMAL;
//			}
//
//		
//
//			//if (i == 0)
//			//{
//			//	type = Block::BLOCK_NORMAL;
//			//}
//			//else
//			//{
//
//			//	//1つ前を確認
//			//	//if (normalCount > 0) //１つ前がnormal
//			//	//{
//			//	//	if (RandomBool(0.25 * (normalCount - 1)))
//			//	//	{
//			//	//		type = Block::BLOCK_NONE;
//			//	//	}
//			//	//	else
//			//	//	{
//			//	//		type = Block::BLOCK_NORMAL;
//			//	//	}
//
//			//	//}
//			//	//else if (noneCount > 0) //1つ前がnone
//			//	//{
//			//	//	if (RandomBool(0.5 * (noneCount - 1)))
//			//	//	{
//			//	//		type = Block::BLOCK_NORMAL;
//			//	//	}
//			//	//	else
//			//	//	{
//			//	//		type = Block::BLOCK_NONE;
//			//	//	}
//			//	//}
//
//			//	if (m_smpBlockTypes[i - 1] == Block::BLOCK_NORMAL)
//			//	{
//			//		if (RandomBool(0.2))
//			//		{
//			//			type = Block::BLOCK_NORMAL;
//			//		}
//			//		else
//			//		{
//			//			type = Block::BLOCK_NONE;
//			//		}
//			//	}
//			//	else if(m_smpBlockTypes[i - 1] == Block::BLOCK_NONE)
//			//	{
//			//		if (RandomBool(0.8))
//			//		{
//			//			type = Block::BLOCK_NORMAL;
//			//		}
//			//		else
//			//		{
//			//			type = Block::BLOCK_NONE;
//			//		}
//			//	}
//
//			//}
//
//			//生成決定
//			m_smpBlockTypes[i] = type;
//			if (type == Block::BLOCK_NORMAL)
//			{
//				normalCount++;
//				noneCount = 0;
//			}
//			else if (type == Block::BLOCK_NONE)
//			{
//				normalCount = 0;
//				noneCount++;
//			}
//		}
//
//		if (RandomBool())
//		{
//			m_count = 1;
//		}
//		else
//		{
//			m_count = 0;
//		}
//
//		return;
//	}
//
//	for (int i = 0; i < BLOCK_NUM; i++)
//	{
//		pType[i] = m_smpBlockTypes[i];
//	}
//
//	m_count--;
//	if (m_count == 0)
//	{
//		if (RandomBool())
//		{
//			m_intervalCount = 3;
//		}
//		else
//		{
//			m_intervalCount = 4;
//		}
//	}
//}


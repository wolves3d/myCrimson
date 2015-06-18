#include "pch.h"
#include "quad_tree.h"



QuadTreeCell::QuadTreeCell(QuadTree * tree, QuadTreeCell * parentCell, uint childIndex)
	: m_Tree(tree)
	, m_ParentCell(parentCell)
{
	m_ChildCell[0] = NULL;
	m_ChildCell[1] = NULL;
	m_ChildCell[2] = NULL;
	m_ChildCell[3] = NULL;

	if (NULL == parentCell)
	{
		float treeWidth = tree->GetWidth();
		float treeHeight = tree->GetHeight();

		m_Min.setPoint(treeWidth * (-0.5f), treeHeight * (-0.5f));
		m_Max.setPoint(treeWidth * 0.5f, treeHeight * 0.5f);
	}
	else
	{
		CCPoint Diagonal = ccpSub(parentCell->m_Max, parentCell->m_Min);

		if (0 == childIndex)
		{
			m_Min = ccpAdd(parentCell->m_Min, ccpMult(Diagonal, 0.5f));
			m_Max = parentCell->m_Max;
		}
		else if (1 == childIndex)
		{
			m_Min.setPoint(parentCell->m_Min.x + (0.5f * Diagonal.x), parentCell->m_Min.y);
			m_Max.setPoint(parentCell->m_Max.x, parentCell->m_Max.y - (0.5f * Diagonal.y));
		}
		else if (2 == childIndex)
		{
			m_Min = parentCell->m_Min;
			m_Max = ccpSub(parentCell->m_Max, ccpMult(Diagonal, 0.5f));
		}
		else if (3 == childIndex)
		{
			m_Min.setPoint(parentCell->m_Min.x, parentCell->m_Min.y + (0.5f * Diagonal.y));
			m_Max.setPoint(parentCell->m_Max.x - (0.5f * Diagonal.x), parentCell->m_Max.y);
		}
	}
}


void QuadTreeCell::Devide()
{
	if (NULL != m_ChildCell[0]) // Is cell devided?
	{
		// Already devided, so devide children
		for (uint i = 0; i < 4; ++i)
		{
			m_ChildCell[i]->Devide();
		}

		return;
	}
	
	// Devide self
	for (uint i = 0; i < 4; ++i)
	{
		m_ChildCell[i] = new QuadTreeCell(m_Tree, this, i);
	}
}

void QuadTreeCell::DebugDraw(CCNode * nodeSpace)
{
	CCAffineTransform t = nodeSpace->nodeToParentTransform();
	const CCPoint worldMin = CCPointApplyAffineTransform(m_Min, t);
	const CCPoint worldMax = CCPointApplyAffineTransform(m_Max, t);

	const float cellHeight = (worldMax.y - worldMin.y);
	CCPoint vertices[] = {
		worldMin,
		ccpAdd(worldMin, ccp(0, cellHeight)),
		worldMax,
		ccpAdd(worldMax, ccp(0, -cellHeight)),
		worldMin };

	ccDrawColor4B(0xFF, 0xFF, 0xFF, 0xFF);
	glLineWidth(1);
	ccDrawPoly(vertices, 5, false);


	if (NULL != m_ChildCell[0])
	{
		for (uint i = 0; i < 4; ++i)
		{
			m_ChildCell[i]->DebugDraw(nodeSpace);
		}
	}
}
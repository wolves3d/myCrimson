#include "pch.h"
#include "quad_tree.h"


QuadTree::QuadTree(float width, float height, float cellSize)
	: m_Width(width)
	, m_Height(height)
	, m_CellSize(cellSize)
{
	m_Root = new QuadTreeCell(this, NULL, 0);

	uint depth = 3;
	while (depth--)
	{
		m_Root->Devide();
	}
}


QuadTree::~QuadTree()
{
	delete m_Root;
}


void QuadTree::DebugDraw(CCNode * nodeSpace)
{
	m_Root->DebugDraw(nodeSpace);
}
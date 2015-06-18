#ifndef __quad_tree_h_included__
#define __quad_tree_h_included__


#include "quad_tree_cell.h"



class QuadTree
{
public:
	QuadTree(float width, float height, float cellSize);
	~QuadTree();

	void AddNode();
	void OnNodeMoved(QuadTreeNode * node);

	float GetWidth() const { return m_Width; }
	float GetHeight() const { return m_Height; }
	float GetCellSize() const { return m_CellSize; }

	void DebugDraw(CCNode * nodeSpace);

private:

	QuadTreeCell * m_Root;
	float m_Width;
	float m_Height;
	float m_CellSize;
};


#endif // #ifndef __quad_tree_h_included__
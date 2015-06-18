#ifndef __quad_tree_cell_h_included__
#define __quad_tree_cell_h_included__


struct QuadTreeNode
{
};


class QuadTreeCell
{
public:
	QuadTreeCell(QuadTree * tree, QuadTreeCell * parentCell, uint childIndex);
	void Devide();

	void DebugDraw(CCNode * nodeSpace);

private:
	vector <QuadTreeNode *> m_NodeList;
	QuadTreeCell * m_ParentCell;
	QuadTreeCell * m_ChildCell[4];
	QuadTree * m_Tree;

	CCPoint m_Min;
	CCPoint m_Max;
};


#endif // #ifndef __quad_tree_cell_h_included__
#ifndef __uniform_grid_h_included__
#define __uniform_grid_h_included__


class UniformGrid
{
public:
	UniformGrid();
	void InitGridMap(const CCPoint & mapSize, float cellSize);

	void AddUnit(Unit * unit);
	void RemoveUnit(Unit * unit);

	void Collide(UnitVector * outVector, SortedListDelegate * delegate);

	void GetUnitsInRadius(UnitVector * outVector, const CCPoint & point, float radius);

private:

	void CellCoordFromMapPoint(int * outX, int * outY, const CCPoint & mapPoint);
	int GetCellIndex(const CCPoint & point);
	UnitVector * GetCell(int x, int y);

	UnitVector * m_GridArray;
	int m_Width, m_Height;
	float m_CellSize;
	CCSize m_MapSize;
};


#endif // #ifndef __uniform_grid_h_included__
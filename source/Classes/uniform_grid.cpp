#include "pch.h"
#include "enemy.h"
#include "uniform_grid.h"


UniformGrid::UniformGrid()
	: m_GridArray(NULL)
	, m_CellSize(0.0f)
	, m_Width(0)
	, m_Height(0)
{
}


void UniformGrid::InitGridMap(const CCPoint & mapSize, float cellSize)
{
	m_MapSize.setSize(mapSize.x, mapSize.y);
	m_CellSize = cellSize;
	m_Width = (int)ceilf((mapSize.x / m_CellSize));
	m_Height = (int)ceilf((mapSize.y / m_CellSize));

	const uint cellCount = (m_Width * m_Height);

	CC_SAFE_DELETE(m_GridArray);
	m_GridArray = new UnitVector[cellCount];
}


void UniformGrid::CellCoordFromMapPoint(int * outX, int * outY, const CCPoint & mapPoint)
{
	(*outX) = (int)floorf((mapPoint.x + (0.5f * m_MapSize.width)) / m_CellSize);
	(*outY) = (int)floorf((mapPoint.y + (0.5f * m_MapSize.height)) / m_CellSize);
}


int UniformGrid::GetCellIndex(const CCPoint & point)
{
	int x, y;
	CellCoordFromMapPoint(&x, &y, point);

	CC_ASSERT((x >= 0) && (x < m_Width));
	CC_ASSERT((y >= 0) && (y < m_Height));

	return ((y * m_Width) + x);
}


void UniformGrid::AddUnit(Unit * unit)
{
	const int currentIndex = unit->GetGridIndex();
	const int newIndex = GetCellIndex(unit->getPosition());

	if (-1 != currentIndex)
	{
		if (newIndex == currentIndex)
		{
			// Nothing to do, already in right place
			return;
		}
		else
		{
			// Got this unit but in wrong cell, so remove first
			RemoveUnit(unit);
		}
	}

	m_GridArray[newIndex].push_back(unit);
	unit->SetGridIndex(newIndex);
}


void UniformGrid::RemoveUnit(Unit * unit)
{
	const int Idx = unit->GetGridIndex();
	if (-1 != Idx)
	{
		UnitVector * cellList = (m_GridArray + Idx);
		UnitVector::iterator it = cellList->begin();

		while (cellList->end() != it)
		{
			if (unit == (*it))
			{
				cellList->erase(it);
				return;
			}

			++it;
		}
	}
}


void UniformGrid::Collide(UnitVector * outVector, SortedListDelegate * delegate)
{
	for (int y = 0; y < m_Height; ++y)
	{
		for (int x = 0; x < m_Width; ++x)
		{
			outVector->clear();

			UnitVector * cellList = GetCell(x, y);
			outVector->insert(outVector->end(), cellList->begin(), cellList->end());

			cellList = GetCell(x + 1, y);
			if (NULL != cellList)
			{
				outVector->insert(outVector->end(), cellList->begin(), cellList->end());
			}

			cellList = GetCell(x + 1, y + 1);
			if (NULL != cellList)
			{
				outVector->insert(outVector->end(), cellList->begin(), cellList->end());
			}

			cellList = GetCell(x, y + 1);
			if (NULL != cellList)
			{
				outVector->insert(outVector->end(), cellList->begin(), cellList->end());
			}
			
			if (outVector->size() > 0)
			{
				delegate->ProcessColliders(outVector);
			}
		}
	}
}


UnitVector * UniformGrid::GetCell(int x, int y)
{
	if (x < m_Width)
	{
		if (y < m_Height)
		{
			return (m_GridArray + ((y * m_Width) + x));
		}
	}

	return NULL;
}


void UniformGrid::GetUnitsInRadius(UnitVector * outVector, const CCPoint & point, float radius)
{
	const CCPoint radiusPoint(radius, radius);

	int minX, minY;
	CellCoordFromMapPoint(&minX, &minY, ccpSub(point, radiusPoint));
	minX = MAX(0, MIN(minX, (m_Width - 1)));
	minY = MAX(0, MIN(minY, (m_Height - 1)));

	int maxX, maxY;
	CellCoordFromMapPoint(&maxX, &maxY, ccpAdd(point, radiusPoint));
	maxX = MAX(0, MIN(maxX, (m_Width - 1)));
	maxY = MAX(0, MIN(maxY, (m_Height - 1)));

	//const float radiusSq = (radius * radius);
	outVector->clear();

	for (int y = minY; y <= maxY; ++y)
	{
		for (int x = minX; x <= maxX; ++x)
		{
			// FIXME: non optimal - square, refactor me
			UnitVector *  gridVector = GetCell(x, y);
			outVector->insert(outVector->end(), gridVector->begin(), gridVector->end());

			/*
			if (radiusSq < ccpDistanceSQ(point, ))
			{
				UnitVector *  gridVector = GetCell(x, y);
				outVector->insert(outVector->begin(), gridVector->begin(), gridVector->end());
			}
			*/
		}
	}
}
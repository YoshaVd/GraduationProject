#include "LevelGrid.h"

LevelGrid::LevelGrid(const int width, const int height):
	_width(width), _height(height)
{
	for (size_t col = 0; col < width; col++)
	{
		_tilesArr.push_back(vector<Tile>());
		for (size_t row = 0; row < height; row++)
		{
			_tilesArr[col].push_back(Tile());
		}
	}
}

LevelGrid::~LevelGrid()
{
	_tilesArr.clear();
}

void LevelGrid::SetFilled(const int x, const int y, const bool isFilled)
{
	if (!IsWithinBounds(x, y))
		return;

	if (x < _width && y < _height)
		_tilesArr[x][y]._isFilled = isFilled;
}

void LevelGrid::SetFilledArea(const FVector2D center, int width, int height, bool isFilled)
{
	for (size_t col = 0; col < width; col++)
	{
		for (size_t row = 0; row < height; row++)
		{
			int x = center.X - width / 2 + col;
			int y = center.Y - height / 2 + row;
			if (!IsWithinBounds(x, y))
				return;

			SetFilled(x, y, isFilled);
		}
	}
}

FVector2D LevelGrid::GetRandomPos(const int xOffset, const int yOffset)
{
	int randomCol = rand() % (_width - 2 * xOffset) + xOffset;
	int randomRow = rand() % (_height - 2 * yOffset) + yOffset;
	
	return FVector2D(randomRow, randomCol);
}

FVector2D LevelGrid::GetRandomPos(const bool isFilled, const int xOffset, const int yOffset)
{
	FVector2D pos;
	do
	{
		pos = GetRandomPos(xOffset, yOffset);
	} while (_tilesArr[pos.X][pos.Y]._isFilled != isFilled);

	return pos;
}

FVector2D LevelGrid::GetRandomPosFromSet(const vector<FVector2D>& positions)
{
	int randomNr = rand() % positions.size();
	return positions[randomNr];
}

vector<FVector2D> LevelGrid::GetAdjacentPositions(const FVector2D pos)
{
	vector<FVector2D> adjacentPositions;
	if(pos.X > 0)
		adjacentPositions.push_back(FVector2D(pos.X - 1, pos.Y));
	if (pos.X < _width - 1)
		adjacentPositions.push_back(FVector2D(pos.X + 1, pos.Y));
	if (pos.Y > 0)
		adjacentPositions.push_back(FVector2D(pos.X, pos.Y - 1));
	if (pos.Y < _height - 1)
		adjacentPositions.push_back(FVector2D(pos.X, pos.Y + 1));
	return adjacentPositions;
}

vector<FVector2D> LevelGrid::GetAdjacentPositions(const int x, const int y)
{
	return GetAdjacentPositions(FVector2D(x, y));
}

vector<FVector2D> LevelGrid::GetAllAdjacentPositions(const FVector2D pos)
{
	vector<FVector2D> adjacentPositions;
	FVector2D adjPos;
	for (size_t i = 0; i < 9; i++)
	{
		adjPos.X = pos.X + (i % 3) - 1;
		adjPos.Y = pos.Y + (i / 3) - 1;
		if (adjPos != pos && IsWithinBounds(adjPos))
			adjacentPositions.push_back(adjPos);
	}
	return adjacentPositions;
}

vector<FVector2D> LevelGrid::GetAllAdjacentPositions(const int x, const int y)
{
	return GetAllAdjacentPositions(FVector2D(x,y));
}

vector<FVector2D> LevelGrid::GetIsolatedPositions(vector<FVector2D> positions)
{
	vector<FVector2D> isolated;
	for (auto pos : positions)
	{
		if (IsIsolated(pos))
			isolated.push_back(pos);
	}
	return isolated;
}

vector<FVector2D> LevelGrid::GetIsolatedPositionsException(const vector<FVector2D> positions, const FVector2D exception)
{
	vector<FVector2D> isolated;
	for (auto pos : positions)
	{
		if (IsIsolatedException(pos,exception))
			isolated.push_back(pos);
	}
	return isolated;
}

bool LevelGrid::IsIsolated(const FVector2D pos)
{
	vector<FVector2D> adjacentPositions = GetAllAdjacentPositions(pos);
	for (size_t i = 0; i < adjacentPositions.size(); i++)
	{
		if (!_tilesArr[adjacentPositions[i].X][adjacentPositions[i].Y]._isFilled)
			return false;
	}
	return true;
}

bool LevelGrid::IsIsolated(const int x, const int y)
{
	return IsIsolated(FVector2D(x, y));
}

bool LevelGrid::IsIsolatedException(const FVector2D pos, const FVector2D exception)
{
	vector<FVector2D> adjacentPositions = GetAllAdjacentPositions(pos);
	for (auto p: adjacentPositions)
	{
		if (p != exception && !_tilesArr[p.X][p.Y]._isFilled)
			return false;
	}
	return true;
}

bool LevelGrid::IsWithinBounds(const FVector2D pos)
{
	if (pos.X >= 0 && pos.X < _width &&
		pos.Y >= 0 && pos.Y < _height)
		return true;

	// TODO: Error message
	return false;
}

bool LevelGrid::IsWithinBounds(const int x, const int y)
{
	return IsWithinBounds(FVector2D(x, y));
}
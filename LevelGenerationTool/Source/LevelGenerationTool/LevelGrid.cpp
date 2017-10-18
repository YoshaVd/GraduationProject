#include "LevelGrid.h"

LevelGrid::LevelGrid(const int width, const int height):
	_width(width), _height(height)
{
	for (size_t col = 0; col < width; col++)
	{
		_tiles.push_back(vector<Tile*>());
		for (size_t row = 0; row < height; row++)
		{
			_tiles[col].push_back(new Tile());
		}
	}

	_biasFactor = 100 * _width * _height;
}

LevelGrid::LevelGrid(vector<vector<Tile*>>& tiles)
{
	_width = tiles.size();
	_height = tiles[0].size();
	_tiles = tiles;
	_biasFactor = 100 * _width * _height;
}

LevelGrid::~LevelGrid()
{
	_tiles.clear();
}

void LevelGrid::SetFilled(const FVector2D pos, const bool isFilled)
{
	if (!IsWithinBounds(pos, FString("LevelGrid::SetFilled ||")))
		return;

	if (pos.X < _width && pos.Y < _height)
		_tiles[pos.X][pos.Y]->_isFilled = isFilled;
}

void LevelGrid::SetFilledArea(const FVector2D center, int width, int height, bool isFilled)
{
	for (size_t col = 0; col < width; col++)
	{
		for (size_t row = 0; row < height; row++)
		{
			int x = center.X - width / 2 + col;
			int y = center.Y - height / 2 + row;
			if (!IsWithinBounds(x, y, FString("LevelGrid::SetFilledArea ||")))
				return;

			SetFilled(FVector2D(x,y), isFilled);
		}
	}
}

void LevelGrid::SetFilledArea(const int top, const int right, const int bottom, const int left, bool isFilled)
{
	if (top < bottom || top >= _height || bottom < 0
		|| right < left || right >= _width || left < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("LevelGrid::SetFilledArea || Dimensions are out of bounds!"));
		return;
	}

	for (size_t col = 0; col < _width; col++)
	{
		for (size_t row = 0; row < _height; row++)
		{
			if (row >= bottom && row <= top && col >= left && col <= right)
			{
				_tiles[col][row]->_isFilled = isFilled;
			}
		}
	}
}

void LevelGrid::SetFilledSet(vector<vector<Tile*>> tiles, const bool isFilled)
{
	int width = tiles.size();
	if (tiles.size() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SetFilledSet:: tiles size is 0"));
		return;
	}
	int height = tiles[0].size();

	for (size_t col = 0; col < width; col++)
	{
		for (size_t row = 0; row < height; row++)
		{
			tiles[col][row]->_isFilled = isFilled;
		}
	}
}

void LevelGrid::AddChild(LevelGrid * grid)
{
	_childGrids.push_back(grid);
	grid->SetParent(this);
}

void LevelGrid::SetParent(LevelGrid * grid)
{
	_parentGrid = this;
}

bool LevelGrid::Split(const int sizeMin)
{
	// 50% chance to split vertically or horizontally
	// split grid in 2, taking into account the minimum size
	int rnd = rand() % 2;
	LevelGrid *subLeft(nullptr), *subRight(nullptr);
	if (rnd == 0 || _height / 2 < sizeMin) // vert split
	{
		if (_width / 2 < sizeMin) {
			UE_LOG(LogTemp, Warning, TEXT("LevelGrid::Split || Grid width is too small to split"));
			return false;
		}

		int splitX = rand() % (_width - 2 * sizeMin) + sizeMin;
		subLeft = CreateSubGrid(_height, splitX, 0, 0);
		subRight = CreateSubGrid(_height, _width, 0, splitX);
	}
	else if (rnd == 1 || _width / 2 < sizeMin) // hor split
	{
		if (_height / 2 < sizeMin) {
			UE_LOG(LogTemp, Warning, TEXT("LevelGrid::Split || Grid height is too small to split"));
			return false;
		}

		int splitY = rand() % (_height - 2 * sizeMin) + sizeMin;
		subLeft = CreateSubGrid(_height, _width, splitY, 0);
		subRight = CreateSubGrid(splitY, _width, 0, 0);
	}

	AddChild(subLeft);
	AddChild(subRight);
	return true;
}

LevelGrid * LevelGrid::CreateSubGrid(const int top, const int right, const int bottom, const int left)
{
	vector<vector<Tile*>> newTiles;
	for (size_t col = 0; col < _width; col++)
	{
		if (col >= left && col <= right)
			newTiles.push_back(vector<Tile*>());
		for (size_t row = 0; row < _height; row++)
		{
			if (row >= bottom && row <= top && col >= left && col <= right)
			{
				if (IsWithinBounds(FVector2D(col, row), FString("LevelGrid::CreateSubGrid ||")))
				{
					newTiles[col - left].push_back(_tiles[col][row]);
				}
			}
		}
	}

	return new LevelGrid(newTiles);
}


FVector2D LevelGrid::GetRandomPos(const int xOffset, const int yOffset)
{
	int randomCol = rand() % (_width - 2 * xOffset) + xOffset;
	int randomRow = rand() % (_height - 2 * yOffset) + yOffset;
	
	return FVector2D(randomRow, randomCol);
}

FVector2D LevelGrid::GetRandomPos(const bool isFilled, const int xOffset, const int yOffset)
{
	FVector2D pos(-1, -1);
	do
	{
		pos = GetRandomPos(xOffset, yOffset);
	} while (_tiles[pos.X][pos.Y]->_isFilled != isFilled);

	if (pos == FVector2D(-1, -1))
		UE_LOG(LogTemp, Error, TEXT("GetRandomPos:: no tile with isFilled = %s ws found"), isFilled);

	return pos;
}

FVector2D LevelGrid::GetRandomPosFromSet(const vector<FVector2D>& positions)
{
	int randomNr = rand() % positions.size();
	return positions[randomNr];
}

FVector2D LevelGrid::GetRandomPosFromSetBiased(const vector<FVector2D>& positions, const FVector2D biasTarget)
{
	if (positions.size() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetRandomPosFromSetBiased:: Set is empty"));
		return FVector2D(0, 0);
	}

	vector<int> distancesToTarget;
	float normalizer = 0;
	for (auto p : positions)
	{
		distancesToTarget.push_back(abs(biasTarget.X - p.X) + abs(biasTarget.Y - p.Y));
		normalizer += 1.0 / distancesToTarget[distancesToTarget.size() - 1];
	}

	int randomNr = rand() % 100;
	int rangeMin = 0;
	int rangeMax = 0;
	UE_LOG(LogTemp, Warning, TEXT("Random number: %d"), randomNr);
	UE_LOG(LogTemp, Warning, TEXT("Normalizer: %f"), normalizer);
	UE_LOG(LogTemp, Warning, TEXT("Amount of options: %d"), distancesToTarget.size());
	for (size_t i = 0; i < distancesToTarget.size(); i++)
	{
		rangeMin = rangeMax;
		rangeMax = rangeMin + 100.0 / distancesToTarget[i] / normalizer;

		if (randomNr > rangeMin && randomNr < rangeMax)
		{
			UE_LOG(LogTemp, Warning, TEXT("Option nr: %d"), i);
			UE_LOG(LogTemp, Warning, TEXT("Range: %d"), rangeMax - rangeMin);
			return positions[i];
		}
	}
	return FVector2D(0,0);
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

vector<FVector2D> LevelGrid::GetEmptyAdjacentPositions(const FVector2D pos)
{
	vector<FVector2D> adjacentPositions;
	if (pos.X > 0 && _tiles[pos.X - 1][pos.Y]->_isFilled)
		adjacentPositions.push_back(FVector2D(pos.X - 1, pos.Y));
	if (pos.X < _width - 1 && _tiles[pos.X + 1][pos.Y]->_isFilled)
		adjacentPositions.push_back(FVector2D(pos.X + 1, pos.Y));
	if (pos.Y > 0 && _tiles[pos.X][pos.Y - 1]->_isFilled)
		adjacentPositions.push_back(FVector2D(pos.X, pos.Y - 1));
	if (pos.Y < _height - 1 && _tiles[pos.X][pos.Y + 1]->_isFilled)
		adjacentPositions.push_back(FVector2D(pos.X, pos.Y + 1));
	return adjacentPositions;
}

vector<FVector2D> LevelGrid::GetAdjacentPositions(const int x, const int y)
{
	return GetAdjacentPositions(FVector2D(x, y));
}

vector<FVector2D> LevelGrid::GetSurroundingPositions(const FVector2D pos)
{
	vector<FVector2D> adjacentPositions;
	FVector2D adjPos;
	for (size_t i = 0; i < 9; i++)
	{
		adjPos.X = pos.X + (i % 3) - 1;
		adjPos.Y = pos.Y + (i / 3) - 1;
		if (adjPos != pos && IsWithinBounds(adjPos, FString("LevelGrid::GetSurroundingPositions ||")))
			adjacentPositions.push_back(adjPos);
	}
	return adjacentPositions;
}

vector<FVector2D> LevelGrid::GetSurroundingPositions(const int x, const int y)
{
	return GetSurroundingPositions(FVector2D(x,y));
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

vector<FVector2D> LevelGrid::GetIsolatedPositionsExclusion(const vector<FVector2D> positions, const FVector2D exclusion)
{
	//UE_LOG(LogTemp, Warning, TEXT("===== CURRENT: %f, %f ====="), exclusion.X, exclusion.Y);

	vector<FVector2D> isolated;
	for (auto pos : positions)
	{
		//UE_LOG(LogTemp, Warning, TEXT("=== ISOLATION CHECK POSITION: %f, %f ==="), pos.X, pos.Y);
		if (IsIsolatedExclusion(pos,exclusion))
			isolated.push_back(pos);
	}
	return isolated;
}

vector<FVector2D> LevelGrid::GetEmpties(const vector<FVector2D> positions)
{
	vector<FVector2D> empties;
	for (auto p : positions)
	{
		if (!_tiles[p.X][p.Y]->_isFilled)
			empties.push_back(p);
	}
	return empties;
}

bool LevelGrid::IsIsolated(const FVector2D pos)
{
	vector<FVector2D> adjacentPositions = GetSurroundingPositions(pos);
	for (auto p : adjacentPositions)
	{
		if (!_tiles[p.X][p.Y]->_isFilled)
			return false;
	}
	return true;
}

bool LevelGrid::IsIsolated(const int x, const int y)
{
	return IsIsolated(FVector2D(x, y));
}

bool LevelGrid::IsIsolatedExclusion(const FVector2D pos, const FVector2D e)
{
	//vector<FVector2D> emptiesNearPos = GetEmpties(GetSurroundingPositions(pos));
	//vector<FVector2D> emptiesAdjExclusion = GetEmpties(GetSurroundingPositions(e));
	//if (emptiesNearPos.size() < emptiesAdjExclusion.size() + 1)
	//	return true;
	//if (emptiesNearPos.size() == emptiesAdjExclusion.size() + 1) 
	//{
	//	int overlapCount = 0;
	//	if (pos.Y != e.Y)
	//	{
	//		if (IsWithinBounds(FVector2D(e.X - 1, e.Y)) && !_tiles[e.X - 1][e.Y]._isFilled) overlapCount++;
	//		if (IsWithinBounds(FVector2D(e.X + 1, e.Y)) && !_tiles[e.X + 1][e.Y]._isFilled) overlapCount++;
	//	}
	//	else if (pos.X != e.X)
	//	{
	//		if (IsWithinBounds(FVector2D(e.X, e.Y - 1)) && !_tiles[e.X][e.Y - 1]._isFilled) overlapCount++;
	//		if (IsWithinBounds(FVector2D(e.X, e.Y + 1)) && !_tiles[e.X][e.Y + 1]._isFilled) overlapCount++;
	//	}

	//	if (overlapCount == emptiesNearPos.size() - 1)
	//		return true;
	//}
	//return false;


	// If the amount of surrounding empty cells is smaller than 
	// the amount empty cells adjacent to the exception cell
	// the cell can be considered "isolated"
	int emptyCountNearPos = GetEmpties(GetSurroundingPositions(pos)).size() - 1;
	int emptyCountExclusion = GetEmpties(GetAdjacentPositions(e)).size();
	if (emptyCountNearPos <= emptyCountExclusion)
		return true;
	return false;
}

bool LevelGrid::IsWithinBounds(const FVector2D pos, const FString logInfo)
{
	if (pos.X >= 0 && pos.X < _width &&
		pos.Y >= 0 && pos.Y < _height)
		return true;

	UE_LOG(LogTemp, Warning, TEXT("%s Position[%d,%d] out of grid bounds."), *logInfo, pos.X, pos.Y);
	return false;
}

bool LevelGrid::IsWithinBounds(const int x, const int y, const FString logInfo)
{
	return IsWithinBounds(FVector2D(x, y), logInfo);
}

void LevelGrid::LogTiles()
{
	FString log;
	for (size_t col = 0; col < _width; col++)
	{
		for (size_t row = 0; row < _height; row++)
		{
			if (_tiles[col][row]->_isFilled)
				log += "#";
			else
				log += ".";
		}
		log += "\n";
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *log);
}

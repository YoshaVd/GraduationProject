#include "BaseGrid.h"
#include "LevelGenerationTool.h"

BaseGrid::BaseGrid(const int width, const int height) :
	_width(width), _height(height)
{
	for (size_t col = 0; col < width; col++)
	{
		_tiles.push_back(vector<Tile*>());
		for (size_t row = 0; row < height; row++)
		{
			_tiles[col].push_back(new Tile(FVector2D(col, row)));
		}
	}

	_biasFactor = 100 * _width * _height;
}

BaseGrid::BaseGrid(vector<vector<Tile*>>& tiles)
{
	_width = tiles.size();
	_height = tiles[0].size();
	_tiles = tiles;
	_biasFactor = 100 * _width * _height;
}

BaseGrid::BaseGrid(const BaseGrid & other)
{
	_width = other._width;
	_height = other._height;
	_baseColor = other._baseColor;
	_tiles = other._tiles;
	_biasFactor = other._biasFactor;
}

BaseGrid::~BaseGrid()
{
	_tiles.clear();
}

vector<vector<Tile*>> BaseGrid::GetTilesArea(const int bottom, const int left, const int top, const int right)
{
	vector<vector<Tile*>> areaTiles;

	if (top < bottom || top >= _height || bottom < 0 || right < left || right >= _width || left < 0) {
		UE_LOG(LogTemp, Error, TEXT("BaseGrid::GetTilesArea || Dimensions are out of bounds!"));
		return areaTiles;
	}

	for (size_t col = 0; col < _width; col++)
	{
		if (col >= left && col <= right)
			areaTiles.push_back(vector<Tile*>());
		for (size_t row = 0; row < _height; row++)
		{
			// Add the tiles inside the specified rect to the sub-grid tileset
			if (row >= bottom && row <= top && col >= left && col <= right)
			{
				if (IsWithinBounds(FVector2D(col, row), FString("BaseGrid::CreateSubGrid")))
				{
					areaTiles[col - left].push_back(_tiles[col][row]);
				}
			}
		}
	}
	return areaTiles;
}

void BaseGrid::SetFilled(const FVector2D pos, const bool isFilled)
{
	if (!IsWithinBounds(pos, FString("BaseGrid::SetFilled")))
		return;
	_tiles[pos.X][pos.Y]->_isFilled = isFilled;
}

void BaseGrid::SetFilledArea(const FVector2D center, int width, int height, bool isFilled)
{
	for (size_t col = 0; col < width; col++)
	{
		for (size_t row = 0; row < height; row++)
		{
			int x = center.X - width / 2 + col;
			int y = center.Y - height / 2 + row;
			if (!IsWithinBounds(x, y, FString("BaseGrid::SetFilledArea")))
				return;

			SetFilled(FVector2D(x, y), isFilled);
		}
	}
}

void BaseGrid::SetFilledArea(const int bottom, const int left, const int top, const int right, bool isFilled)
{
	if (top < bottom || top >= _height || bottom < 0 || right < left || right >= _width || left < 0) {
		UE_LOG(LogTemp, Error, TEXT("BaseGrid::SetFilledArea || Dimensions are out of bounds!"));
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

void BaseGrid::SetFilledTiles(vector<vector<Tile*>>& tiles, const bool isFilled)
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

void BaseGrid::SetFilledTiles(vector<Tile*>& tiles, const bool isFilled)
{
	for (auto t : tiles)
	{
		if (t != nullptr)
			t->_isFilled = isFilled;
	}
}

void BaseGrid::SetFilledPositions(vector<FVector2D> positions, const bool isFilled)
{
	for (auto p : positions)
	{
		if (IsWithinBounds(p, " BaseGrid::SetFilledPositions"))
			_tiles[p.X][p.Y]->_isFilled = isFilled;
	}
}

void BaseGrid::SetColor(const FVector2D pos, const FColor color)
{
	if (!IsWithinBounds(pos, FString("BaseGrid::SetFilled")))
		return;
	_tiles[pos.X][pos.Y]->_color = color;
}

void BaseGrid::SetColorArea(const int bottom, const int left, const int top, const int right, const FColor color)
{
	if (top < bottom || top >= _height || bottom < 0 || right < left || right >= _width || left < 0) {
		UE_LOG(LogTemp, Error, TEXT("BaseGrid::SetColorArea || Dimensions are out of bounds!"));
		return;
	}

	for (size_t col = 0; col < _width; col++)
	{
		for (size_t row = 0; row < _height; row++)
		{
			if (row >= bottom && row <= top && col >= left && col <= right)
				_tiles[col][row]->_color = color;
		}
	}
}

void BaseGrid::SetColorAll(const FColor color)
{
	for (size_t col = 0; col < _width; col++)
	{
		for (size_t row = 0; row < _height; row++)
		{
			if(IsWithinBounds(FVector2D(col, row), "BaseGrid::SetColorAll"))
				_tiles[col][row]->_color = color;
		}
	}
}

FVector2D BaseGrid::GetRandomPos(const int xOffset, const int yOffset)
{
	int randomCol = rand() % (_width - 2 * xOffset) + xOffset;
	int randomRow = rand() % (_height - 2 * yOffset) + yOffset;

	return FVector2D(randomRow, randomCol);
}

FVector2D BaseGrid::GetRandomPos(const bool isFilled, const int xOffset, const int yOffset)
{
	FVector2D pos(-1, -1);
	do
	{
		pos = GetRandomPos(xOffset, yOffset);
	} while (_tiles[pos.X][pos.Y]->_isFilled != isFilled);

	if (pos == FVector2D(-1, -1))
		UE_LOG(LogTemp, Error, TEXT("BaseGrid::GetRandomPos || No tile with isFilled = %s ws found"), isFilled);

	return pos;
}

FVector2D BaseGrid::GetRandomPosFromSet(const vector<FVector2D>& positions)
{
	int randomNr = rand() % positions.size();
	return positions[randomNr];
}

FVector2D BaseGrid::GetRandomPosFromSetBiased(const vector<FVector2D>& positions, const FVector2D biasTarget)
{
	if (positions.size() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("BaseGrid::GetRandomPosFromSetBiased || Set is empty"));
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
	return FVector2D(0, 0);
}

vector<FVector2D> BaseGrid::GetAdjacentPositions(const FVector2D pos)
{
	vector<FVector2D> adjacentPositions;
	if (pos.X > 0)
		adjacentPositions.push_back(FVector2D(pos.X - 1, pos.Y));
	if (pos.X < _width - 1)
		adjacentPositions.push_back(FVector2D(pos.X + 1, pos.Y));
	if (pos.Y > 0)
		adjacentPositions.push_back(FVector2D(pos.X, pos.Y - 1));
	if (pos.Y < _height - 1)
		adjacentPositions.push_back(FVector2D(pos.X, pos.Y + 1));
	return adjacentPositions;
}

vector<FVector2D> BaseGrid::GetEmptyAdjacentPositions(const FVector2D pos)
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

vector<FVector2D> BaseGrid::GetAdjacentPositions(const int x, const int y)
{
	return GetAdjacentPositions(FVector2D(x, y));
}

vector<FVector2D> BaseGrid::GetSurroundingPositions(const FVector2D pos)
{
	vector<FVector2D> adjacentPositions;
	FVector2D adjPos;
	for (size_t i = 0; i < 9; i++)
	{
		adjPos.X = pos.X + (i % 3) - 1;
		adjPos.Y = pos.Y + (i / 3) - 1;
		if (adjPos != pos && IsWithinBounds(adjPos, FString("NULL")))
			adjacentPositions.push_back(adjPos);
	}
	return adjacentPositions;
}

vector<FVector2D> BaseGrid::GetSurroundingPositions(const int x, const int y)
{
	return GetSurroundingPositions(FVector2D(x, y));
}

vector<FVector2D> BaseGrid::GetIsolatedPositions(vector<FVector2D> positions)
{
	vector<FVector2D> isolated;
	for (auto pos : positions)
	{
		if (IsIsolated(pos))
			isolated.push_back(pos);
	}
	return isolated;
}

vector<FVector2D> BaseGrid::GetIsolatedPositionsExclusion(const vector<FVector2D> positions, const FVector2D exclusion)
{
	vector<FVector2D> isolated;
	for (auto pos : positions)
	{
		if (IsIsolatedExclusion(pos, exclusion))
			isolated.push_back(pos);
	}
	return isolated;
}

vector<FVector2D> BaseGrid::GetEmpties(const vector<FVector2D> positions)
{
	vector<FVector2D> empties;
	for (auto p : positions)
	{
		if (!_tiles[p.X][p.Y]->_isFilled)
			empties.push_back(p);
	}
	return empties;
}

Tile * BaseGrid::GetRandomTileFromSet(const vector<Tile*> tiles)
{
	int randomNr = rand() % tiles.size();
	return tiles[randomNr];
}

Tile * BaseGrid::GetLeftTile(Tile * t)
{
	if (t->_x <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("BaseGrid::GetLeftTile || Out of bounds."),);
		return t;
	}
	return _tiles[t->_x - 1][t->_y];
}

Tile * BaseGrid::GetRightTile(Tile * t)
{
	if (t->_x >= _width - 1) {
		UE_LOG(LogTemp, Warning, TEXT("BaseGrid::GetRightTile || Out of bounds."), );
		return t;
	}
	return _tiles[t->_x + 1][t->_y];
}

Tile * BaseGrid::GetTopTile(Tile * t)
{
	if (t->_y >= _height - 1) {
		UE_LOG(LogTemp, Warning, TEXT("BaseGrid::GetTopTile || Out of bounds."), );
		return t;
	}
	return _tiles[t->_x][t->_y + 1];
}

Tile * BaseGrid::GetBottomTile(Tile * t)
{
	if (t->_y <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("BaseGrid::GetBottomTile || Out of bounds."), );
		return t;
	}
	return _tiles[t->_x][t->_y - 1];
}

Tile * BaseGrid::GetHorTile(Tile * t, const int offset)
{
	if (t->_x + offset > _width - 1 || t->_x + offset < 0) {
		UE_LOG(LogTemp, Warning, TEXT("BaseGrid::GetHorTile || Out of bounds."), );
		return t;
	}
	return _tiles[t->_x + offset][t->_y];
}

Tile * BaseGrid::GetVertTile(Tile * t, const int offset)
{
	if (t->_y + offset > _height - 1 || t->_x + offset < 0) {
		UE_LOG(LogTemp, Warning, TEXT("BaseGrid::GetVertTile || Out of bounds."), );
		return t;
	}
	return _tiles[t->_x][t->_y + offset];
}

Pair* BaseGrid::GetClosestStraightPair(vector<Tile*> setA, vector<Tile*> setB)
{
	int closestDistance = GetShortestDistanceStraight(setA, setB);
	vector<Pair*> closestPairs;
	for (auto a : setA)
	{
		for (auto b : setB)
		{
			if (a->_x == b->_x || a->_y == b->_y)
			{
				int distance = (a->_coordinates - b->_coordinates).Size();
				if (distance == closestDistance)
					closestPairs.push_back(new Pair(a, b));
			}
		}
	}
	if (closestPairs.size() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("BaseGrid::GetClosestStraightPair || No straight pair available."), );
		return nullptr;
	}
	int randomNr = rand() % closestPairs.size();
	return closestPairs[randomNr];
}

int BaseGrid::GetShortestDistanceStraight(vector<Tile*> setA, vector<Tile*> setB)
{
	int closestDistance = std::numeric_limits<int>::max();
	for (auto a : setA)
	{
		for (auto b : setB)
		{
			int distance = (a->_coordinates - b->_coordinates).Size();
			if (distance < closestDistance)
			{
				if (a->_x == b->_x || a->_y == b->_y)
				{
					closestDistance = distance;
				}
			}
		}
	}
	return closestDistance;
}

bool BaseGrid::IsIsolated(const FVector2D pos)
{
	vector<FVector2D> adjacentPositions = GetSurroundingPositions(pos);
	for (auto p : adjacentPositions)
	{
		if (!_tiles[p.X][p.Y]->_isFilled)
			return false;
	}
	return true;
}

bool BaseGrid::IsIsolated(const int x, const int y)
{
	return IsIsolated(FVector2D(x, y));
}

bool BaseGrid::IsIsolatedExclusion(const FVector2D pos, const FVector2D e)
{
	/* [WIP] Fix to avoid diagonal connections in the perfect maze algorithm */
	/*
	vector<FVector2D> emptiesNearPos = GetEmpties(GetSurroundingPositions(pos));
	vector<FVector2D> emptiesAdjExclusion = GetEmpties(GetSurroundingPositions(e));
	if (emptiesNearPos.size() < emptiesAdjExclusion.size() + 1)
	return true;
	if (emptiesNearPos.size() == emptiesAdjExclusion.size() + 1)
	{
	int overlapCount = 0;
	if (pos.Y != e.Y)
	{
	if (IsWithinBounds(FVector2D(e.X - 1, e.Y)) && !_tiles[e.X - 1][e.Y]._isFilled) overlapCount++;
	if (IsWithinBounds(FVector2D(e.X + 1, e.Y)) && !_tiles[e.X + 1][e.Y]._isFilled) overlapCount++;
	}
	else if (pos.X != e.X)
	{
	if (IsWithinBounds(FVector2D(e.X, e.Y - 1)) && !_tiles[e.X][e.Y - 1]._isFilled) overlapCount++;
	if (IsWithinBounds(FVector2D(e.X, e.Y + 1)) && !_tiles[e.X][e.Y + 1]._isFilled) overlapCount++;
	}

	if (overlapCount == emptiesNearPos.size() - 1)
	return true;
	}
	return false;
	*/


	// If the amount of surrounding empty cells is smaller than 
	// the amount empty cells adjacent to the exception cell
	// the cell can be considered "isolated"
	int emptyCountNearPos = GetEmpties(GetSurroundingPositions(pos)).size() - 1;
	int emptyCountExclusion = GetEmpties(GetAdjacentPositions(e)).size();
	if (emptyCountNearPos <= emptyCountExclusion)
		return true;
	return false;
}

bool BaseGrid::IsWithinBounds(const FVector2D pos, const FString logInfo)
{
	if (pos.X >= 0 && pos.X < _width &&
		pos.Y >= 0 && pos.Y < _height)
		return true;

	if (logInfo != "NULL")
		UE_LOG(LogTemp, Warning, TEXT("%s || Position[%f,%f] out of grid bounds."), *logInfo, pos.X, pos.Y);
	return false;
}

bool BaseGrid::IsWithinBounds(const int x, const int y, const FString logInfo)
{
	return IsWithinBounds(FVector2D(x, y), logInfo);
}

void BaseGrid::LogTiles()
{
	FString log;
	log += "GRID: \n";
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
	UE_LOG(LOG_LevelGenerator, Log, TEXT("%s"), *log);
}

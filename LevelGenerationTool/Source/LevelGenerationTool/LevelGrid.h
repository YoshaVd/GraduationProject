#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include <vector>
#include "Runtime/Core//Public/Math/Vector2D.h"

using namespace std;

/* grid class containing all the terrain and 
gameplay information necessary for building a level*/
class LEVELGENERATIONTOOL_API LevelGrid
{
public:
	LevelGrid(const int width, const int height);
	LevelGrid(vector<vector<Tile>>& tiles);
	~LevelGrid();

	vector<vector<Tile>>& GetTileLayout() { return _tiles; }
	void SetTiles(vector<vector<Tile>>& tiles) { _tiles = tiles; }
	int GetWidth() { return _width; }
	int GetHeight() { return _height; }
	
	// Tile manipulation functions
	void SetFilled(const int x, const int y, const bool isFilled = false);
	void SetFilledArea(const FVector2D center, int width, int height, bool isFilled = false);
	void SetFilledSet(vector<vector<Tile>> tiles, const bool isFilled = false);

	// Subgrid functions
	//void Split();
	LevelGrid* CreateSubGrid(const int top, const int right, const int bottom, const int left);

	// Get functions with requirements
	FVector2D GetRandomPos(const int xOffset = 0, const int yOffset = 0);
	FVector2D GetRandomPos(const bool isFilled, const int xOffset = 0, const int yOffset = 0);
	FVector2D GetRandomPosFromSet(const vector<FVector2D>& positions);
	FVector2D GetRandomPosFromSetBiased(const vector<FVector2D>& positions, const FVector2D biasTarget);

	vector<FVector2D> GetAdjacentPositions(const FVector2D pos);
	vector<FVector2D> GetEmptyAdjacentPositions(const FVector2D pos);
	vector<FVector2D> GetAdjacentPositions(const int x, const int y);
	vector<FVector2D> GetSurroundingPositions(const FVector2D pos);
	vector<FVector2D> GetSurroundingPositions(const int x, const int y);

	vector<FVector2D> GetIsolatedPositions(const vector<FVector2D> positions);
	vector<FVector2D> GetIsolatedPositionsExclusion(const vector<FVector2D> positions, const FVector2D exclusion);

	vector<FVector2D> GetEmpties(const vector<FVector2D> positions);

	// Tile checks
	bool IsIsolated(const FVector2D pos);
	bool IsIsolated(const int x, const int y);
	bool IsIsolatedExclusion(const FVector2D pos, const FVector2D exclusion);

	bool IsWithinBounds(const FVector2D pos);
	bool IsWithinBounds(const int x, const int y);

private:
	int _width, _height;
	int _biasFactor;
	vector<vector<Tile>> _tiles;
};

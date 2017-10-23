#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include <vector>
#include "Runtime/Core//Public/Math/Vector2D.h"
//#include "Room.h"

using namespace std;

/*	grid class containing all the terrain and
gameplay information necessary for building a level*/
class LEVELGENERATIONTOOL_API BaseGrid
{
public:
	BaseGrid(const int width, const int height);
	BaseGrid(vector<vector<Tile*>>& tiles);
	BaseGrid(const BaseGrid& other);
	~BaseGrid();

	// Tile get/set functions
	vector<vector<Tile*>>& GetTiles() { return _tiles; }
	vector<vector<Tile*>> GetTilesArea(const int bottom, const int left, const int top, const int right);
	void SetTiles(vector<vector<Tile*>>& tiles) { _tiles = tiles; }

	int GetWidth() { return _width; }
	int GetHeight() { return _height; }

	// Tile manipulation functions
	void SetFilled(const FVector2D pos, const bool isFilled = false);
	void SetFilledArea(const FVector2D center, int width, int height, bool isFilled = false);
	void SetFilledArea(const int bottom, const int left, const int top, const int right, bool isFilled = false);
	void SetFilledSet(vector<vector<Tile*>>& tiles, const bool isFilled = false);

	void SetColor(const FVector2D pos, const FColor color);
	void SetColorArea(const int bottom, const int left, const int top, const int right, const FColor color);
	void SetColorAll(const FColor color);

	// Get pos functions with requirements
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

	bool IsWithinBounds(const FVector2D pos, const FString logInfo = "");
	bool IsWithinBounds(const int x, const int y, const FString logInfo = "");

	// Debugging
	FColor GetBaseColor() { return _baseColor; }
	void SetBaseColor(const FColor& color) { _baseColor = color; }
	void LogTiles();

protected:
	int _width, _height;
	int _biasFactor;
	FColor _baseColor = FColor::Black;

	vector<vector<Tile*>> _tiles;
};

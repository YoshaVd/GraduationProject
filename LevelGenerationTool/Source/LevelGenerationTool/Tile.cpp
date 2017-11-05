#include "Tile.h"

Tile::Tile(const Tile & other)
{
	_isFilled = other._isFilled;
	_color = other._color;
	_x = other._x;
	_y = other._y;
	_state = other._state;
	_parent = other._parent;
}

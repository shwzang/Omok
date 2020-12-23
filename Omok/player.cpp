#include "Player.h"

player::player()
	: is_computer(false)
{
}

player::player(bool is_computer)
	: player()
{
	this->is_computer = is_computer;
}

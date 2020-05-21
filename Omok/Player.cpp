#include "Player.h"

Player::Player()
	:IsComputer( false )
{
}

Player::Player( bool IsComputer )
	: Player()
{
	this->IsComputer = IsComputer;
}
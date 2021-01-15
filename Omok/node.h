#pragma once

class node
{
public:
	node();

public:
	class stone* position;
	int value;
	int height;
	node* parent;
};

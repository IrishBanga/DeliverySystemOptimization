#include "utils.h"

/* WILL BE DEVELOPED IN LATER MILESTONES */
int validate(int weight, double volume, struct Point temp)
{
	int res = 0;
	/*if (weight >= 1 && weight <= 1000 && (volume == 0.25 || volume == 0.5 || volume == 1.0) && temp.col >= 0 && temp.col < MAP_COLS
		&& temp.row >= 0 && temp.row < MAP_ROWS)
	{
		res = 1;
	}*/
	if (weight < 1 || weight > 1000) 
	{
		res = INVALID_WEIGHT;
	}
	else if (volume != 0.25 && volume != 0.5 && volume != 1.0) 
	{
		res = INVALID_VOLUME;
	}
	else if (temp.col < 0 || temp.col >= MAP_COLS || temp.row < 0 || temp.row >= MAP_ROWS) 
	{
		res = INVALID_POINT;
	}
	else 
	{
		res = 0;
	}
	return res;
}
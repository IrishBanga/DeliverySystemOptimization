#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "utils.h"

int main(void)
{
	struct Map baseMap = populateMap();
	struct Route blueRoute, greenRoute, yellowRoute;
	blueRoute = getBlueRoute();
	struct Map routeMap = addRoute(&baseMap, &blueRoute);
	greenRoute = getGreenRoute();
	routeMap = addRoute(&routeMap, &greenRoute);
	yellowRoute = getYellowRoute();
	routeMap = addRoute(&routeMap, &yellowRoute);
	printMap(&routeMap, 1, 1); //currently, printMap has been modified to print rows with spaces before and after the identifying characters

	/* get input; initial validation within constraints */

	/* Run algorithm for deciding delivery truck; can reject unreachable destinations 
	*  This will also cover diversions related issues.
	*/

	/* Further checks to see if the fleet limit isn't exceeded.
	*  If so, store the incoming records for dispatch on next day
	*  otherwise proceeds normally and informs the user of the truck and the diversion if applicable
	*/

	/* The quit condition associated with the program is the user entering 0 0 x as input.
	* The program will display a message upon exit
	*/




	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
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
	

	struct Dispatch seneca;
	seneca.map = routeMap;
	/*seneca.current.B = (struct Truck){ 0, 0, getBlueRoute()};
	seneca.current.G = (struct Truck){ 0, 0, getGreenRoute()};
	seneca.current.Y = (struct Truck){ 0, 0, getYellowRoute()};*/ //corrected initialisation. This caused errors
	seneca.current.B.CurrentWeight = 0;
	seneca.current.B.CurrentVolume = 0;
	seneca.current.G.CurrentWeight = 0;
	seneca.current.G.CurrentVolume = 0;
	seneca.current.Y.CurrentWeight = 0;
	seneca.current.Y.CurrentVolume = 0;
	seneca.current.B.route = getBlueRoute();
	seneca.current.G.route = getGreenRoute();
	seneca.current.Y.route = getYellowRoute();
	seneca.nextDayOrders = 0;
	
	printMap(&routeMap, 1, 1); //currently, printMap has been modified to print rows with spaces before and after the identifying characters
	printf("=================\n"
		   "Seneca Deliveries\n"
		   "=================\n");
	int done = 0;
	int wt = 0;
	double vol = 0;
	char temp[4] =  "\0";
	struct Point check = {-1,-1};
	/* get input; initial validation within constraints */
	do 
	{
		printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
		scanf("%d %lf %[^\n]",&wt,&vol,temp); //ASSUMING ENTRY FORMAT "INT DOUBLE ALPHANUMERIC_DESTINATION\n"
		while (getchar() != '\n');
		if (wt == 0 && vol == 0 && temp[0] == 'x')
		{
			done = QUIT_CONDITION;
		}
		else
		{
			if (strlen(temp) >= 2)// validating destination
			{
				int index1=0;
				for (int i = 0; i < strlen(temp); i++)
				{
					if (!isalpha(temp[i]))
					{
						index1 = (index1 * 10) + ((int)(temp[i]) - '0');
					}
					else //if(i>0)
					{
						check.col = ((int)(temp[i]) - 'A');
					}
				}
				check.row = index1-1;
				
				int error= validate(wt, vol,check);
				if (!error) /* WILL IMPLEMENT A SPECIAL ERROR CODE MESSAGE LATER */
				{
					printf("Initial validation successful\n");
					struct OrderInfo order = { wt,vol,check,{-1,-1} };
					//run(&seneca, order); //used for testing purposes

					double dists[3][2];
					getTruckDistances2(dists, &seneca.current, order.destination);
					sortByLimitingFactor(dists,&seneca);
					struct OrderInfo* orderTemp = &order;
					done = findTruckAndDiversion(&seneca, dists, orderTemp);
					printf("No of points on diversion route %d\n", orderTemp->diversion.numPoints);
				}
				else if (error == INVALID_WEIGHT) 
				{
					printf("Invalid weight (must be 1-1000 Kg.)\n");
				}
				else if (error == INVALID_VOLUME) 
				{
					printf("Invalid size\n");
				}
				else if (error == INVALID_POINT) 
				{
					printf("Invalid destination\n");
				}
			}		
		}
	
	} while (done != QUIT_CONDITION && done != MAX_ORDERS);
	printf("Thanks for shipping with Seneca!");
	

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
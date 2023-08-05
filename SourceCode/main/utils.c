#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int validate(int weight, double volume, struct Point temp)
{
	int res = 0;
	struct Map Base = populateMap();
	struct Point invalid = { -1,-1 };
	if (weight < 1 || weight > 1000)
	{
		res = INVALID_WEIGHT;
	}
	else if (volume != 0.25 && volume != 0.5 && volume != 1.0)
	{
		res = INVALID_VOLUME;
	}
	else if (temp.col < 0 || temp.col >= MAP_COLS || temp.row < 0 || temp.row >= MAP_ROWS || Base.squares[temp.row][temp.col]!=1 || getPossibleMoves(&Base,temp,invalid).numPoints<1)
	{
		res = INVALID_POINT;
	}
	else
	{
		res = 0;
	}
	return res;
}

	double getSpaceRemaining(const struct Truck* truck)
	{
		double weightPercentageRemaining = (double)(1000 - truck->CurrentWeight) / 1000;
		double volumePercentageRemaining = (double)(36 - truck->CurrentVolume) / 36;
		double limitingFactor = (weightPercentageRemaining < volumePercentageRemaining) ? weightPercentageRemaining : volumePercentageRemaining;
		return limitingFactor;
	}

	struct Truck* getTruckByReference(struct Fleet* current, int routeSymbol)
	{
		struct Truck* fleet = (struct Truck*)current;
		int fleetSize = 3;
		int done = 0;
		struct Truck* res = NULL;
		for (int i = 0; i < fleetSize && !done; i++)
		{
			if (fleet[i].route.routeSymbol == routeSymbol)
			{
				res = &fleet[i];
				done = 1;
			}
		}
		return res;
	}

	void getTruckDistances2(double arr[][2], struct Fleet* current, struct Point destination)
	{
		int BCP = getClosestPoint(&current->B.route, destination);
		int GCP = getClosestPoint(&current->G.route, destination);
		int YCP = getClosestPoint(&current->Y.route, destination);
		//calculating ditance of closest point from dest.
		double BCPD = distance(&current->B.route.points[BCP], &destination);
		double GCPD = distance(&current->G.route.points[GCP], &destination);
		double YCPD = distance(&current->Y.route.points[YCP], &destination);
		arr[0][0] = BCPD;
		arr[0][1] = BLUE;
		arr[1][0] = GCPD;
		arr[1][1] = GREEN;
		arr[2][0] = YCPD;
		arr[2][1] = YELLOW; //including references to trucks with repective distances

		//sorting the array in ascending order of distance
		double temp[1][2];
		for (int i = 3 - 1; i > 0; i--)
		{
			for (int j = 0; j < i; j++)
			{
				if (arr[j][0] > arr[j + 1][0])
				{
					temp[0][0] = arr[j][0];
					temp[0][1] = arr[j][1];
					arr[j][0] = arr[j + 1][0];
					arr[j][1] = arr[j + 1][1];
					arr[j + 1][0] = temp[0][0];
					arr[j + 1][1] = temp[0][1];
				}
			}
		}
	}

	void sortByLimitingFactor(double dists[][2], struct Dispatch* org)
	{
		int i, j;
		double temp[1][2];

		for (i = 3 - 1; i > 0; i--) {
			for (j = 0; j < i; j++) {
				struct Truck* truck1 = getTruckByReference(&org->current, (int)dists[j][1]);
				struct Truck* truck2 = getTruckByReference(&org->current, (int)dists[j + 1][1]);
				double truck1Limit = getSpaceRemaining(truck1);
				double truck2Limit = getSpaceRemaining(truck2);
				//sorting array based on descending order of space remaining on the condition two adjoining elements are equidistant
				if ((dists[j][0] == dists[j + 1][0] && truck1Limit < truck2Limit)) {
					temp[0][0] = dists[j][0];
					temp[0][1] = dists[j][1];
					dists[j][0] = dists[j + 1][0];
					dists[j][1] = dists[j + 1][1];
					dists[j + 1][0] = temp[0][0];
					dists[j + 1][1] = temp[0][1];
				}
			}
		}
	}
	

	int findTruckAndDiversion(struct Dispatch* org, double dists[][2], struct OrderInfo* order)
	{
		char truckNames[3][7]; //can be avoided; will need  a way to incorporate directly into print statements;other macros possibly
		for (int i = 0; i < 3; i++)
		{
			if (dists[i][1] == BLUE)
			{
				strcpy(truckNames[i], "BLUE");
			}
			else if (dists[i][1] == GREEN)
			{
				strcpy(truckNames[i], "GREEN");
			}
			else if (dists[i][1] == YELLOW)
			{
				strcpy(truckNames[i], "YELLOW");
			}
		}
		int done = 0;
		for (int i = 0; i < 3 && !done; i++)
		{
			if (dists[i][0] == 1)
			{

				struct Truck* truck = getTruckByReference(&org->current, (int)dists[i][1]);
				if (truck->CurrentWeight + order->weight <= 1000 && truck->CurrentVolume + order->volume <= 36) {
					truck->CurrentVolume += order->volume;
					truck->CurrentWeight += order->weight;
					done = 1;
					printf("Ship on %s LINE, no diversion\n", truckNames[i]);
				}
				else
				{
					printf("BEYOND LIMIT FOR %s\n", truckNames[i]);
				}
			}
			else
			{
				struct Truck* truck = getTruckByReference(&org->current, (int)dists[i][1]);
				struct Route shortest = { {0,0},0,DIVERSION };
				struct Route* shortPtr = NULL;
				int shortestPoint = 0;

				if (truck->CurrentWeight + order->weight <= 1000 && truck->CurrentVolume + order->volume <= 36)
				{
					for (int i = 0; i < truck->route.numPoints; i++)
					{
						if (shortest.numPoints == 0)
						{
							shortest = shortestPath(&org->map,order->destination , truck->route.points[i]);
						}
						else
						{
							struct Route shortestTemp = { {0,0},0,DIVERSION };
							shortestTemp = shortestPath(&org->map, order->destination,truck->route.points[i] );
							if (shortestTemp.numPoints!=0 // && //shortestTemp.numPoints <= shortest.numPoints //not applicable since diagonals still travel more
								//&& //might be redundant or can cause logical error
								//(distance(&shortestTemp.points[0], &shortestTemp.points[shortestTemp.numPoints - 1]) <= (distance(&shortest.points[0], &shortest.points[shortest.numPoints - 1])))
								//(distance(&shortestTemp.points[0], &truck->route.points[i]) <= (distance(&shortest.points[0], &truck->route.points[i - 1])))
								)
							{
								double dist1 = 0.0, dist2 = 0.0; 
								for (int i = 1; i < shortest.numPoints; i++) 
								{
									dist1 += distance(&shortest.points[i - 1], &shortest.points[i]); //calculating the total ditance travelled on a path
								}
								for (int i = 1; i < shortestTemp.numPoints; i++) {
									dist2 += distance(&shortestTemp.points[i - 1], &shortestTemp.points[i]);
								}
								if (dist2 < dist1)
								{
									shortest = shortestTemp;
									shortestPoint = i;
								}
							}
						}
					}
					truck->CurrentVolume += order->volume;
					truck->CurrentWeight += order->weight;
					done = 1;
					//addPtToRoute(&order->diversion, truck->route.points[shortestPoint]);
					for (int i = 0; i < shortest.numPoints; i++) //copying the shortest route to the OrderInfo struct
					{
						addPtToRoute(&order->diversion, shortest.points[i]);
					}
					//addPtToRoute(&order->diversion, order->destination);
					order->diversion.routeSymbol = DIVERSION;

					printf("DIVERSION CALCULATED\n");
					printf("Ship on %s LINE,", truckNames[i]);


					/* OTHER CHANGES in DEVELOPMENT PROCESS ;NOT INCLUDED IN FINAL SOLUTION FOR - MS4 */
					//for (int p = 0; p < order->diversion.numPoints; p++) //printing diversion route
					//{
					//		int row= (int)(order->diversion.points[p].row)+1;
					//		printf(" %d%c%c", row, 'A' + order->diversion.points[p].col, (p != order->diversion.numPoints - 1)? ',' : '\n');
					//}
					
					
					for (int p =  order->diversion.numPoints-1; p >=0; p--) //printing diversion route
					{
						int row = (int)(order->diversion.points[p].row) + 1;
						printf(" %d%c%c", row, 'A' + order->diversion.points[p].col, (p != 0) ? ',' : '\n');
					}
				}
				else
				{
					printf("BEYOND LIMIT FOR %s\n", truckNames[i]);
				}

			}
			if (i == 2 && !done)
			{
				printf("FLEET LIMIT EXCEEDED\n");
				if (org->nextDayOrders < MAX_ORDERS) 
				{
					printf("ADDING ORDER INFO TO NEXT DAY\n");
				    org->ordersOtherDay[org->nextDayOrders++] = *order;
					done = ADDED_NEXT_DAY;
				}
				else
				{
					printf("REACHED THE LIMIT FOR NEXT DAY ORDERS.ORDER UNSUCCESSFUL!\nABORTING PROGRAM!\n");
					done = MAX_ORDERS;
				}
			}
			
		}
		return done;
	}

	void run(struct Dispatch* org, struct OrderInfo order) //for testing purposes only
	{
		double dists[3][2];
		getTruckDistances2(dists, &org->current, order.destination);
		sortByLimitingFactor(dists, org);
		struct OrderInfo* orderTemp = &order;
		int done = findTruckAndDiversion(org, dists, orderTemp);
		printf("No of points on diversion route %d\n", orderTemp->diversion.numPoints);
	}


	int integrateValidateAndGetTruckDistances2(struct Dispatch* org, struct OrderInfo order, double dists[][2]) //validate+truckDistances
	{
		int res = 0;
		int error = validate(order.weight, order.volume, order.destination);
		if (!error)
		{
			res = 1;
			getTruckDistances2(dists, &org->current, order.destination);
		}
		return res;
	}

	double integrateGetTruckByRefereceAndGetSpace(struct Fleet* fleet, int targetRouteSymbol) 
	{
		struct Truck* temp = getTruckByReference(fleet, targetRouteSymbol);
		double res = -55.0;
		if (temp) 
		{
			res = getSpaceRemaining(temp);
		}
		return res;
	}

	void integrateGetDistancesAndSortByLimitingFactor(struct Dispatch org, struct OrderInfo order, double dists[][2])
	{
		getTruckDistances2(dists, &org.current, order.destination);
		sortByLimitingFactor(dists, &org);
	}

	int integrateAllFunctions(struct Dispatch* org, struct OrderInfo* order)
	{
		int res = 0;
		int error = validate(order->weight, order->volume, order->destination);
		if (!error)
		{
			double dists[3][2];
			getTruckDistances2(dists, &org->current, order->destination);
			sortByLimitingFactor(dists, org);
			res = findTruckAndDiversion(org, dists, order);
		}
		else
		{
			res = error;
		}
		return res;
	}
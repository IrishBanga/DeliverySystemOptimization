#include <string.h>
#include "mapping.h"

#define INVALID_WEIGHT 1
#define INVALID_VOLUME 3
#define INVALID_POINT 5
#define MAX_ORDERS 432 //based on the scenario ((max volume allowed in trucks)*(number of trucks))/(least volume of package)=(36*3)/(0.25)
#define QUIT_CONDITION 79
#define ADDED_NEXT_DAY 59

/*
* struct OrderInfo- used to store info about a single order
*/
struct OrderInfo
{
	int weight; //stores the weight of an order in kg(s) must be less than 1000 kg
	double volume; //stores the size/volume in m^3 will either be 0.25, 0.5 or 1 m^3
	struct Point destination; //chnaged from previous scheme as destination is already converted to integer points(similar to a graph)
	struct Route diversion; //identifies the diversion that is associated with an order; will be determined by the algorithm to be developed in later milestones
};

/*
* struct Truck- Stores the current information about a truck
*/
struct Truck
{
	int CurrentWeight; //must be less than 1000 kg
	double CurrentVolume; //must be less than 36 m^3
	struct Route route; //stores the entire  route of the truck; will be fetched using getRoute() functions;
};

/*
* struct FLeet- stores info about all the trucks in the fleet (Three trucks in our case)
*/
struct Fleet 
{
	struct Truck G; //identifies the GREEN truck
	struct Truck B; //identifies the BLUE truck
	struct Truck Y; //identifies the YELLOW truck
};


/*
* struct Dispatch- used to store and maintain status of the dipatch system
*/
struct Dispatch 
{
	struct Map map; //stores the map with the buildings and route info - will be populated using already provided functions
	struct Fleet current;  //concerned with Fleet state of current day - can be all empty OR may fetch the pending orders from previous day from ordersOtherDay array
	struct OrderInfo ordersOtherDay[MAX_ORDERS];  //Ideally the program will terminate after limits are exceeded.
	//based on the rationale that users can enter as many orders until they decide to quit or until the max Limit of orders(432) is exceeded for the next day
	int nextDayOrders;
};

/*FUNCTIONS*/

/***
* See if packages meet the limitation requirements and return an integer based on validation success
* @param weight - weight of the order being tested (b/w 1 and 1000)
* @param volume - represents the volume of the order being validated (0.25 or 0.5 or 1)
* @param valid - represents the order destination (of type struct Point) to be validated
* @returns - an integer value that determines validation success and also provides an error code based on what parameter was invalid; SEE MACROS DEFINED ABOVE 
*/
int validate(int weight, double volume, struct Point valid);

/***
* Calculates the limiting factor for a truck by comparing percentages of current weight and current volume. //secondary factor after distances
* @param truck - a pointer to a struct Truck representing the truck for which the limiting factor is calculated
* @return - a double value representing the limiting factor, which is the smaller percentage between weight and volume
*/
double getSpaceRemaining(const struct Truck* truck);

/***
* Retrieves a truck from the fleet based on its route symbol.
* @param current - a pointer to a struct Fleet representing the fleet of trucks
* @param routeSymbol - an integer value representing the route symbol of the desired truck
* @return - a pointer to a struct Truck representing the truck with the matching route symbol, or NULL if not found
*/
struct Truck* getTruckByReference(struct Fleet* trucks, int routeSymbol);

/***
* Calculates the distances between the given destination point and the closest points on the routes of each truck in the fleet.
* Then it sorts the distances in ascending order along with corresponding truck color codes.
* @param arr - a 2D array representing the distances and color codes of the trucks
* @param current - a pointer to a struct Fleet representing the fleet of trucks
* @param destination - a struct Point representing the destination point
*/
void getTruckDistances2(double arr[][2], struct Fleet* current, struct Point destination);

/***
* Sort the truck distances based on the limiting factor (space remaining) of each truck.
* The function assumes that the array of distances is already sorted in ascending order.
* If two trucks have the same distance, their sorting is determined by the space remaining in descending order.
* @param dists - a 2D array representing the distances and truck color codes
* @param org - a pointer to a struct Dispatch representing the parent organization; used to make calls to other functions
*/
void sortByLimitingFactor(double dists[][2], struct Dispatch* org);

/***
* This function will attempt to assign an order to a truck in the dispatch organization, taking into consideration weight and volume limitations for the truck.
* It attempts to place the order in the most favourable truck first. If the truck can carry the order it further tries to calculate the route to destination.
* If the destination address is adjacent to any point on the truck's route it places the order and returns the success indicator, otherwise it moves to the 
* diversion calculations (a diversion route is calculated based on the shortest path from each truck's route to the destination).
* The diversion route is also stored in the order's diversion field; needed solely for ease in forming tests
* If no truck can accommodate the order and a diversion cannot be calculated, the order is placed in the ordersNextDay[] array.
* @param org - a pointer to a struct Dispatch representing the dispatch organization
* @param dists - a 2D array representing the distances and truck color codes; assumed to be sorted taking distances and limiting factors into consideration
* @param order - a pointer to a struct OrderInfo representing the order to be assigned
* @returns - an integer value indicating the success of assigning the order: 1 if assigned, 0 if not assigned, ADDED_NEXT_DAY if order added to next day array
*/
int findTruckAndDiversion(struct Dispatch* org, double dists[][2], struct OrderInfo* order);

void run(struct Dispatch* org, struct OrderInfo order); //integration purposes only -  logic moved to main
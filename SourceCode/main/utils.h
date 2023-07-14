#include "mapping.h"
#define INVALID_WEIGHT 1
#define INVALID_VOLUME 3
#define INVALID_POINT 5
/*
* Array sizes mentioned in document may be defined as macros in later milestones to be more informative.
* On hold, as current milestone required desgining data structures only.
*/

/*
* struct OrderInfo- used to store info about a single order
*/
struct OrderInfo
{
	int weight; //stores the weight of an order in kg(s) must be less than 1000 kg
	double volume; //stores the size/volume in m^3 will either be 0.25, 0.5 or 1 m^3
	char destIndex1; //holds the numeric index of the destination, will be between 1 and 25; has data type char to account for quit condition value 'x' 
	char destIndex2; //holds the alphabetic index of the destination, will be between A and Y   
	struct Route diversion; //identifies the diversion that is associated with an order; will be determined by the algorithm to be developed in later milestones
};

/*
* struct Truck- Stores the current information about a truck
*/
struct Truck
{
	int Curentweight; //must be less than 1000 kg
	int CurrentVolume; //must be less than 36 m^3 
	struct Route route; //stores the entire  route of the truck; will be fetched using getRoute() functions;
	struct OrderInfo orders[144]; //holds the order in the truck; array size is based on the volume constraints(i.e., max 36 m^3) and min volume of package(i.e., 0.25 m^3)
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
	
	//The OrderInfo array specified below may be dropped in later milestones as information about process of storing orders for next day is unclear from project instructions 	
	struct OrderInfo ordersOtherDay[20];  //size currently kept at 20; May change later; Ideally the program will terminate after limits are exceeded.
	
	//The validOrdersToday[] array is entirely optional; may be dropped in later milestones
	struct OrderInfo validOrdersToday[432]; //array size 432; based on the scenario ((max volume allowed in trucks)*(number of trucks))/(least volume of package)=(36*3)/(0.25)
};



/*FUNCTIONS*/

int validate(int weight, double volume, struct Point valid);

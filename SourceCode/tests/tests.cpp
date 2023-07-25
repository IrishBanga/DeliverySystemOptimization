#include "pch.h"
#include "CppUnitTest.h"
#include "tests.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace validateTests
{
	TEST_CLASS(BLACKBOXTESTS) {
public:
	////BB_TestDistance ; FOR DEMONSTRATION PURPOSE ONLY
	// TEST_METHOD(BB_TestDistance) //trying to test distance() function
	//{
	//	Point p1 = { 0,0 };
	//	Point p2 = { 3,4 };
	//	double actual = distance(&p1, &p2);
	//	Assert::AreEqual(5.0,actual);
	// }

	TEST_METHOD(BB_TestValidate1) // test validate() function with a valid input
	{
		Point p1 = { 3, 2 };
		int valid = validate(500, .5, p1);
		Assert::AreEqual(0, valid);
	}

	TEST_METHOD(BB_TestValidate2) // test validate() function with invalid weight
	{
		Point p1 = { 3, 4 };
		int invalid = validate(0, 0.5, p1);
		Assert::AreEqual(INVALID_WEIGHT, invalid);
	}

	TEST_METHOD(BB_TestValidate3) // Entering invalid volume
	{
		Point p1 = { 7, 5 };
		int invalid = validate(10, .26, p1);
		Assert::AreEqual(INVALID_VOLUME, invalid);
	}

	TEST_METHOD(BB_TestValidate4) // Entering invalid point (column)
	{
		Point p1 = { 6, 42 };
		int invalid = validate(10, .5, p1);
		Assert::AreEqual(INVALID_POINT, invalid);
	}

	TEST_METHOD(BB_TestValidate5) // Entering invalid point (row)
	{
		Point p1 = { 46, 2 };
		int invalid = validate(10, .5, p1);
		Assert::AreEqual(INVALID_POINT, invalid);
	}

	TEST_METHOD(BB_TestValidate6) // Entering all invalid parameters
	{
		Point p1 = { -1, -1 };
		int invalid = validate(1500, 1.5, p1);
		Assert::AreNotEqual(0, invalid); // error code returned may differ based on the way function sets them;hence confirming that it is not a success (i.e, 0 is not returned)
	}
	};

	TEST_CLASS(WhiteboxTests)
	{
		TEST_METHOD(WB_TestValidate_1)
		{
			Point p1 = { 3, -1 };
			int invalid = validate(500, .5, p1);
			Assert::AreEqual(INVALID_POINT, invalid);

		}
		TEST_METHOD(WB_TestValidate_2)
		{

			Point p1 = { 3, 2 };
			int invalid = validate(0, .5, p1);
			Assert::AreEqual(INVALID_WEIGHT, invalid);
		}
		TEST_METHOD(WB_TestValidate_3)
		{

			Point p1 = { 3, 2 };
			int valid = validate(500, .5, p1);
			Assert::AreEqual(0, valid);
		}
	};
}

namespace getSpaceRemainingtests
{
	TEST_CLASS(BlackboxTests)
	{
	public:
		TEST_METHOD(BB_TestGetSpaceRemaining1) // trying to test getSpaceRemaining() function
		{
			Truck truck;
			truck.CurrentWeight = 500;
			truck.CurrentVolume = 10;
			double result = getSpaceRemaining(&truck);
			double expected = 0.5;
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(BB_TestGetSpaceRemaining2)
		{
			Truck truck;
			truck.CurrentWeight = 800;
			truck.CurrentVolume = 24;
			double result = getSpaceRemaining(&truck);
			double expected = 0.2;
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(BB_TestGetSpaceRemaining3)
		{
			Truck truck;
			truck.CurrentWeight = 1000;
			truck.CurrentVolume = 24;
			double result = getSpaceRemaining(&truck);
			double expected = 0.0;
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(BB_TestGetSpaceRemaining4)
		{
			Truck truck;
			truck.CurrentWeight = 800;
			truck.CurrentVolume = 36;
			double result = getSpaceRemaining(&truck);
			double expected = 0.0;
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(BB_TestGetSpaceRemaining5)
		{
			Truck truck;
			truck.CurrentWeight = 801;
			truck.CurrentVolume = 25;
			double result = getSpaceRemaining(&truck);
			double expected = 0.199;
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(BB_TestGetSpaceRemaining6)
		{
			Truck truck;
			truck.CurrentWeight = 801;
			truck.CurrentVolume = 24;
			double result = getSpaceRemaining(&truck);
			double expected = 0.199;
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(BB_TestGetSpaceRemaining7)
		{
			Truck truck;
			truck.CurrentWeight = 800;
			truck.CurrentVolume = 25;
			double result = getSpaceRemaining(&truck);
			double expected = 0.2;
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(BB_TestGetSpaceRemaining8)
		{
			Truck truck;
			truck.CurrentWeight = 1000;
			truck.CurrentVolume = 36;
			double result = getSpaceRemaining(&truck);
			double expected = 0.0;
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(BB_TestGetSpaceRemaining9)
		{
			Truck truck;
			truck.CurrentWeight = 1000;
			truck.CurrentVolume = 24;
			double result = getSpaceRemaining(&truck);
			double expected = 0.0;
			Assert::AreEqual(expected, result);
		}
	};

	TEST_CLASS(WhiteboxTests)
	{
	public:
		TEST_METHOD(WB_TestGetSpaceRemaining1)
		{
			Truck truck;
			truck.CurrentWeight = 500;
			truck.CurrentVolume = 18;
			double result = getSpaceRemaining(&truck);
			double expected = 0.5;
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(WB_TestGetSpaceRemaining2)
		{
			Truck truck;
			truck.CurrentWeight = 0;
			truck.CurrentVolume = 0;
			double result = getSpaceRemaining(&truck);
			double expected = 1;
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(WB_TestGetSpaceRemaining3)
		{
			Truck truck;
			truck.CurrentWeight = 1;
			truck.CurrentVolume = 0.25;
			double result = getSpaceRemaining(&truck);
			double expected = (36 - 0.25) / 36;
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(WB_TestGetSpaceRemaining4)
		{
			Truck truck;
			truck.CurrentWeight = 999;
			truck.CurrentVolume = 35.75;
			double result = getSpaceRemaining(&truck);
			double expected = 0.001;
			Assert::AreEqual(expected, result);
		}
	};
}

namespace getTrucksByReferencetests
{
	TEST_CLASS(BlackboxTests) {
		TEST_METHOD(BB_TestGetTruckByReference1) {
			struct Fleet current;
			current.G.route.routeSymbol = 4;
			current.B.route.routeSymbol = 2;
			current.Y.route.routeSymbol = 8;

			struct Fleet* fleetCopy = &current;
			struct Truck* result = getTruckByReference(fleetCopy, 4);

			struct Truck* expected = &current.G;
			Assert::AreEqual(&expected->route.routeSymbol, &result->route.routeSymbol);
		}

		TEST_METHOD(BB_TestGetTruckByReference2)
		{
			struct Fleet current;
			current.G.route.routeSymbol = 4;
			current.B.route.routeSymbol = 2;
			current.Y.route.routeSymbol = 8;

			struct Fleet* fleetCopy = &current;
			struct Truck* result = getTruckByReference(fleetCopy, 2);

			struct Truck* expected = &current.B;
			Assert::AreEqual(&expected->route.routeSymbol, &result->route.routeSymbol);
		}

		TEST_METHOD(BB_TestGetTruckByReference3)
		{
			struct Fleet current;
			current.G.route.routeSymbol = 4;
			current.B.route.routeSymbol = 2;
			current.Y.route.routeSymbol = 8;

			struct Fleet* fleetCopy = &current;
			struct Truck* result = getTruckByReference(fleetCopy, 8);

			struct Truck* expected = &current.Y;
			Assert::AreEqual(&expected->route.routeSymbol, &result->route.routeSymbol);
		}

		TEST_METHOD(BB_TestGetTruckByReference4)
		{
			struct Fleet current;
			current.G.route.routeSymbol = 4;
			current.B.route.routeSymbol = 2;
			current.Y.route.routeSymbol = 8;

			struct Fleet* fleetCopy = &current;
			struct Truck* result = getTruckByReference(fleetCopy, 0);

			Assert::IsNull(result);
		}

		TEST_METHOD(BB_TestGetTruckByReference5)
		{
			struct Fleet current;
			current.G.route.routeSymbol = -1;
			current.B.route.routeSymbol = 0;

			struct Fleet* fleetCopy = &current;
			struct Truck* result = getTruckByReference(fleetCopy, -1);

			struct Truck* expected = &current.G;
			Assert::AreEqual(&expected->route.routeSymbol, &result->route.routeSymbol);
		}

		TEST_METHOD(BB_TestGetTruckByReference6)
		{
			struct Fleet current;
			current.G.route.routeSymbol = -1;
			current.B.route.routeSymbol = 0;
			current.Y.route.routeSymbol = 8;

			struct Fleet* fleetCopy = &current;
			struct Truck* result = getTruckByReference(fleetCopy, 0);

			struct Truck* expected = &current.B;
			Assert::AreEqual(&expected->route.routeSymbol, &result->route.routeSymbol);
		}

		TEST_METHOD(BB_TestGetTruckByReference7)
		{
			struct Fleet current;
			current.G.route = getGreenRoute();
			current.G.route.routeSymbol = 8;
			current.B.route = getBlueRoute();
			current.B.route.routeSymbol = 8;
			current.Y.route = getYellowRoute();
			current.Y.route.routeSymbol = 8;

			struct Fleet* fleetCopy = &current;
			struct Truck* result = getTruckByReference(fleetCopy, 8);

			struct Truck* expected = &current.G;
			Assert::AreEqual(&expected->route.routeSymbol, &result->route.routeSymbol);
			Assert::AreEqual(&expected->route.points[15].row, &result->route.points[15].row);
		}

		TEST_METHOD(BB_TestGetTruckByReference8)
		{
			struct Fleet current; // define fleet struct that nests each truck

			current.G.route = getGreenRoute(); // ensure each truck has a routeSymbol
			current.G.route.routeSymbol = 8;
			current.B.route = getBlueRoute();
			current.B.route.routeSymbol = 8;
			current.Y.route = getYellowRoute();
			current.Y.route.routeSymbol = 8;

			struct Fleet* fleetCopy = &current;												// make fleet copy
			struct Truck* result = getTruckByReference(fleetCopy, 8); // call function with routeSymbol param

			struct Truck* expected = &current.B; // define expected result
			Assert::AreNotEqual(&expected->route.routeSymbol, &result->route.routeSymbol);
			Assert::AreNotEqual(&expected->route.points[15].row, &result->route.points[15].row);
		}
	};

	TEST_CLASS(WhiteboxTests)
	{

	public:
		// Find truck with only 1 truck in fleet
		TEST_METHOD(WB_TestGetTruckByReference1)
		{

			struct Fleet current;
			current.G.route.routeSymbol = 2;
			current.B.route.routeSymbol = -1;
			current.Y.route.routeSymbol = -1;

			struct Fleet* fleetCopy = &current;
			struct Truck* result = getTruckByReference(fleetCopy, 2);

			struct Truck* expected = &current.G;

			Assert::AreEqual(&expected->route.routeSymbol, &result->route.routeSymbol);
			Assert::IsNotNull(result);
		}

		// Return NULL when Fleet is empty (no trucks)
		TEST_METHOD(WB_TestGetTruckByReference2)
		{
			struct Fleet nullFleet;// = NULL;
			nullFleet.G.route.routeSymbol = NULL;
			nullFleet.B.route.routeSymbol = NULL;
			nullFleet.Y.route.routeSymbol = NULL;
			struct Truck* result = getTruckByReference(&nullFleet, 2);

			Assert::IsNull(result);
		}
	};
}

namespace getTruckDistances2tests
{
	TEST_CLASS(BlackboxTests) {
		TEST_METHOD(BB_getTruckDistances2_1) {
			double distances[3][2];
			struct Fleet current;

			current.B.route = getBlueRoute();
			current.G.route = getGreenRoute();
			current.Y.route = getYellowRoute();

			struct Point destination = { 11, 11 };

			getTruckDistances2(distances, &current, destination);

			double closest1Distance = distance(&current.B.route.points[21], &destination); // 11, 10
			double closest2Distance = distance(&current.G.route.points[15], &destination);
			double closest3Distance = distance(&current.Y.route.points[34], &destination);
			int closest1Color = BLUE;
			int closest2Color = GREEN;
			int closest3Color = YELLOW;

			Assert::AreEqual(closest1Distance, distances[0][0]);
			Assert::AreEqual(closest1Color, (int)(distances[0][1]));
			Assert::AreEqual(closest2Distance, distances[1][0]);
			Assert::AreEqual(closest2Color, (int)(distances[1][1]));
			Assert::AreEqual(closest3Distance, distances[2][0]);
			Assert::AreEqual(closest3Color, (int)(distances[2][1]));
		}
		TEST_METHOD(BB_getTruckDistances2_2)
		{
			double distances[3][2];
			struct Fleet current;

			current.B.route = getBlueRoute();
			current.G.route = getGreenRoute();
			current.Y.route = getYellowRoute();

			struct Point destination = { 6, 4 };

			getTruckDistances2(distances, &current, destination);

			double closest2Distance = distance(&current.B.route.points[8], &destination);
			double closest3Distance = distance(&current.G.route.points[8], &destination);
			double closest1Distance = distance(&current.Y.route.points[9], &destination);
			int closest2Color = BLUE;
			int closest3Color = GREEN;
			int closest1Color = YELLOW;

			Assert::AreEqual(closest1Distance, distances[0][0]);
			Assert::AreEqual(closest1Color, (int)(distances[0][1]));
			Assert::AreEqual(closest2Distance, distances[1][0]);
			Assert::AreEqual(closest2Color, (int)(distances[1][1]));
			Assert::AreEqual(closest3Distance, distances[2][0]);
			Assert::AreEqual(closest3Color, (int)(distances[2][1]));
		}

		TEST_METHOD(BB_getTruckDistances2_3)
		{
			double distances[3][2];
			struct Fleet current;

			current.B.route = getBlueRoute();
			current.G.route = getGreenRoute();
			current.Y.route = getYellowRoute();

			struct Point destination = { 7, 1 };

			getTruckDistances2(distances, &current, destination);

			double closest2Distance = distance(&current.B.route.points[5], &destination);
			double closest3Distance = distance(&current.G.route.points[5], &destination);
			double closest1Distance = distance(&current.Y.route.points[10], &destination);
			int closest2Color = BLUE;
			int closest3Color = GREEN;
			int closest1Color = YELLOW;

			Assert::AreEqual(closest1Distance, distances[0][0]);
			Assert::AreEqual(closest1Color, (int)(distances[0][1]));
			Assert::AreEqual(closest2Distance, distances[1][0]);
			Assert::AreEqual(closest2Color, (int)(distances[1][1]));
			Assert::AreEqual(closest3Distance, distances[2][0]);
			Assert::AreEqual(closest3Color, (int)(distances[2][1]));
		}
		TEST_METHOD(BB_getTruckDistances2_4)
		{
			double distances[3][2];
			struct Fleet current;

			current.B.route = getBlueRoute();
			current.G.route = getGreenRoute();
			current.Y.route = getYellowRoute();

			struct Point destination = { 13, 6 };

			getTruckDistances2(distances, &current, destination);

			double closest1Distance = distance(&current.B.route.points[23], &destination);
			double closest3Distance = distance(&current.G.route.points[10], &destination);
			double closest2Distance = distance(&current.Y.route.points[12], &destination);
			int closest1Color = BLUE;
			int closest3Color = GREEN;
			int closest2Color = YELLOW;

			Assert::AreEqual(closest1Distance, distances[0][0]);
			Assert::AreEqual(closest1Color, (int)(distances[0][1]));
			Assert::AreEqual(closest2Distance, distances[1][0]);
			Assert::AreEqual(closest2Color, (int)(distances[1][1]));
			Assert::AreEqual(closest3Distance, distances[2][0]);
			Assert::AreEqual(closest3Color, (int)(distances[2][1]));
		}

		TEST_METHOD(BB_getTruckDistances2_5)
		{
			double distances[3][2];
			struct Fleet current;

			current.B.route = getBlueRoute();
			current.G.route = getGreenRoute();
			current.Y.route = getYellowRoute();

			struct Point destination = { 16, 8 };

			getTruckDistances2(distances, &current, destination);

			double closest1Distance = distance(&current.B.route.points[26], &destination);
			double closest3Distance = distance(&current.G.route.points[12], &destination);
			double closest2Distance = distance(&current.Y.route.points[31], &destination);
			int closest1Color = BLUE;
			int closest3Color = GREEN;
			int closest2Color = YELLOW;

			Assert::AreEqual(closest1Distance, distances[0][0]);
			Assert::AreEqual(closest1Color, (int)(distances[0][1]));
			Assert::AreEqual(closest2Distance, distances[1][0]);
			Assert::AreEqual(closest2Color, (int)(distances[1][1]));
			Assert::AreEqual(closest3Distance, distances[2][0]);
			Assert::AreEqual(closest3Color, (int)(distances[2][1]));
		}
		TEST_METHOD(BB_getTruckDistances2_6)
		{
			double distances[3][2];
			struct Fleet current;

			current.B.route = getBlueRoute();
			current.G.route = getGreenRoute();
			current.Y.route = getYellowRoute();

			struct Point destination = { 6, 18 };

			getTruckDistances2(distances, &current, destination);

			double closest2Distance = distance(&current.B.route.points[20], &destination);
			double closest1Distance = distance(&current.G.route.points[33], &destination);
			double closest3Distance = distance(&current.Y.route.points[41], &destination);
			int closest2Color = BLUE;
			int closest1Color = GREEN;
			int closest3Color = YELLOW;

			Assert::AreEqual(closest1Distance, distances[0][0]);
			Assert::AreEqual(closest1Color, (int)(distances[0][1]));
			Assert::AreEqual(closest2Distance, distances[1][0]);
			Assert::AreEqual(closest2Color, (int)(distances[1][1]));
			Assert::AreEqual(closest3Distance, distances[2][0]);
			Assert::AreEqual(closest3Color, (int)(distances[2][1]));
		}
		TEST_METHOD(BB_getTruckDistances2_7)
		{
			double distances[3][2];
			struct Fleet current;

			current.B.route = getBlueRoute();
			current.G.route = getGreenRoute();
			current.Y.route = getYellowRoute();

			struct Point destination = { 21, 19 };

			getTruckDistances2(distances, &current, destination);

			double closest2Distance = distance(&current.B.route.points[36], &destination);
			double closest3Distance = distance(&current.G.route.points[36], &destination);
			double closest1Distance = distance(&current.Y.route.points[42], &destination);
			int closest2Color = BLUE;
			int closest3Color = GREEN;
			int closest1Color = YELLOW;

			Assert::AreEqual(closest1Distance, distances[0][0]);
			Assert::AreEqual(closest1Color, (int)(distances[0][1]));
			Assert::AreEqual(closest2Distance, distances[1][0]);
			Assert::AreEqual(closest2Color, (int)(distances[1][1]));
			Assert::AreEqual(closest3Distance, distances[2][0]);
			Assert::AreEqual(closest3Color, (int)(distances[2][1]));
		}
	}
	;

	TEST_CLASS(WhiteboxTests) {

public:
	TEST_METHOD(WB_getTruckDistances2_1) {
		double sortedArr[3][2];

		struct Fleet current;
		current.B.route = getBlueRoute();
		current.G.route = getGreenRoute();
		current.Y.route = getYellowRoute();

		struct Point destination = { 21, 1 };
		getTruckDistances2(sortedArr, &current, destination);

		int BCP = getClosestPoint(&current.B.route, destination);
		int GCP = getClosestPoint(&current.G.route, destination);
		int YCP = getClosestPoint(&current.Y.route, destination);

		double B_dist = distance(&current.B.route.points[BCP], &destination); // second nearest (17, 10)
		double G_dist = distance(&current.G.route.points[GCP], &destination); // farthest
		double Y_dist = distance(&current.Y.route.points[YCP], &destination); // nearest (19, 1)

		Assert::AreEqual(Y_dist, sortedArr[0][0]);
		Assert::AreEqual(B_dist, sortedArr[1][0]);
		Assert::AreEqual(G_dist, sortedArr[2][0]);

		// check colours
		Assert::AreEqual(8, (int)(sortedArr[0][1])); // yellow code 8
		Assert::AreEqual(2, (int)(sortedArr[1][1])); // blue code 2
		Assert::AreEqual(4, (int)(sortedArr[2][1])); // green code 4
	}

	TEST_METHOD(WB_getTruckDistances2_2)
	{
		double sortedArr[3][2];

		struct Fleet current;
		current.B.route = getBlueRoute();
		current.G.route = getGreenRoute();
		current.Y.route = getYellowRoute();

		struct Point destination = { 2, 16 };
		getTruckDistances2(sortedArr, &current, destination);

		int BCP = getClosestPoint(&current.B.route, destination);
		int GCP = getClosestPoint(&current.G.route, destination);
		int YCP = getClosestPoint(&current.Y.route, destination);

		double B_dist = distance(&current.B.route.points[BCP], &destination);
		double G_dist = distance(&current.G.route.points[GCP], &destination);
		double Y_dist = distance(&current.Y.route.points[YCP], &destination);

		Assert::AreEqual(G_dist, sortedArr[0][0]);
		Assert::AreEqual(B_dist, sortedArr[1][0]);
		Assert::AreEqual(Y_dist, sortedArr[2][0]);

		// check colours
		Assert::AreEqual(4, (int)(sortedArr[0][1])); // green
		Assert::AreEqual(2, (int)(sortedArr[1][1])); // blue
		Assert::AreEqual(8, (int)(sortedArr[2][1])); // yellow
	}

	TEST_METHOD(WB_getTruckDistances2_3)
	{
		double sortedArr[3][2];

		struct Fleet current;
		current.B.route = getBlueRoute();
		current.G.route = getGreenRoute();
		current.Y.route = getYellowRoute();

		struct Point destination = { 6, 8 };
		getTruckDistances2(sortedArr, &current, destination);

		int BCP = getClosestPoint(&current.B.route, destination);
		int GCP = getClosestPoint(&current.G.route, destination);
		int YCP = getClosestPoint(&current.Y.route, destination);

		double B_dist = distance(&current.B.route.points[BCP], &destination);
		double G_dist = distance(&current.G.route.points[GCP], &destination);
		double Y_dist = distance(&current.Y.route.points[YCP], &destination);

		// check distances
		Assert::AreEqual(B_dist, sortedArr[0][0]);
		Assert::AreEqual(G_dist, sortedArr[1][0]);
		Assert::AreEqual(Y_dist, sortedArr[2][0]);

		// check colours
		Assert::AreEqual(2, (int)(sortedArr[0][1])); // blue
		Assert::AreEqual(4, (int)(sortedArr[1][1])); // green
		Assert::AreEqual(8, (int)(sortedArr[2][1])); // yellow
	}

	TEST_METHOD(WB_getTruckDistances2_4) {
		double sortedArr[3][2];

		struct Fleet current;
		current.B.route = getBlueRoute();
		current.G.route = getGreenRoute();
		current.Y.route = getYellowRoute();

		struct Point destination = { 11, 24 };
		getTruckDistances2(sortedArr, &current, destination);

		int BCP = getClosestPoint(&current.B.route, destination);
		int GCP = getClosestPoint(&current.G.route, destination);
		int YCP = getClosestPoint(&current.Y.route, destination);

		double B_dist = distance(&current.B.route.points[BCP], &destination); 
		double G_dist = distance(&current.G.route.points[GCP], &destination); 
		double Y_dist = distance(&current.Y.route.points[YCP], &destination); 

		Assert::AreEqual(G_dist, sortedArr[0][0]);
		Assert::AreEqual(B_dist, sortedArr[1][0]);
		Assert::AreEqual(Y_dist, sortedArr[2][0]);

		Assert::AreEqual(GREEN, (int)(sortedArr[0][1])); // green
		Assert::AreEqual(BLUE, (int)(sortedArr[1][1])); // blue
		Assert::AreEqual(YELLOW, (int)(sortedArr[2][1])); // yellow
	}

	TEST_METHOD(WB_getTruckDistances2_5) {
		double sortedArr[3][2];

		struct Fleet current;
		current.B.route = getBlueRoute();
		current.G.route = getGreenRoute();
		current.Y.route = getYellowRoute();

		struct Point destination = { 22, 21 };
		getTruckDistances2(sortedArr, &current, destination);

		int BCP = getClosestPoint(&current.B.route, destination);
		int GCP = getClosestPoint(&current.G.route, destination);
		int YCP = getClosestPoint(&current.Y.route, destination);

		double B_dist = distance(&current.B.route.points[BCP], &destination); // second nearest (17, 10)
		double G_dist = distance(&current.G.route.points[GCP], &destination); // farthest
		double Y_dist = distance(&current.Y.route.points[YCP], &destination); // nearest (19, 1)

		Assert::AreEqual(Y_dist, sortedArr[0][0]);
		Assert::AreEqual(B_dist, sortedArr[1][0]);
		Assert::AreEqual(G_dist, sortedArr[2][0]);

		// check colours
		Assert::AreEqual(YELLOW, (int)(sortedArr[0][1])); // yellow code 8
		Assert::AreEqual(BLUE, (int)(sortedArr[1][1])); // blue code 2
		Assert::AreEqual(GREEN, (int)(sortedArr[2][1])); // green code 4
	}

	TEST_METHOD(WB_getTruckDistances2_6) {
		double sortedArr[3][2];

		struct Fleet current;
		current.B.route = getBlueRoute();
		current.G.route = getGreenRoute();
		current.Y.route = getYellowRoute();

		struct Point destination = { 14, 11 };
		getTruckDistances2(sortedArr, &current, destination);

		int BCP = getClosestPoint(&current.B.route, destination);
		int GCP = getClosestPoint(&current.G.route, destination);
		int YCP = getClosestPoint(&current.Y.route, destination);

		double B_dist = distance(&current.B.route.points[BCP], &destination); // second nearest (17, 10)
		double G_dist = distance(&current.G.route.points[GCP], &destination); // farthest
		double Y_dist = distance(&current.Y.route.points[YCP], &destination); // nearest (19, 1)

		Assert::AreEqual(B_dist, sortedArr[0][0]);
		Assert::AreEqual(Y_dist, sortedArr[1][0]);
		Assert::AreEqual(G_dist, sortedArr[2][0]);

		// check colours
		Assert::AreEqual(BLUE, (int)(sortedArr[0][1])); // blue code 2
		Assert::AreEqual(YELLOW, (int)(sortedArr[1][1])); // yellow code 8
		Assert::AreEqual(GREEN, (int)(sortedArr[2][1])); // green code 4
	}
	TEST_METHOD(WB_getTruckDistances2_7) {
		double sortedArr[3][2];

		struct Fleet current;
		current.B.route = getBlueRoute();
		current.G.route = getGreenRoute();
		current.Y.route = getYellowRoute();

		struct Point destination = { 15, 6 };
		getTruckDistances2(sortedArr, &current, destination);

		int BCP = getClosestPoint(&current.B.route, destination);
		int GCP = getClosestPoint(&current.G.route, destination);
		int YCP = getClosestPoint(&current.Y.route, destination);

		double B_dist = distance(&current.B.route.points[BCP], &destination);
		double G_dist = distance(&current.G.route.points[GCP], &destination);
		double Y_dist = distance(&current.Y.route.points[YCP], &destination);

		Assert::AreEqual(B_dist, sortedArr[0][0]);
		Assert::AreEqual(Y_dist, sortedArr[1][0]);
		Assert::AreEqual(G_dist, sortedArr[2][0]);

		// check colours
		Assert::AreEqual(BLUE, (int)(sortedArr[0][1])); // blue code 2
		Assert::AreEqual(YELLOW, (int)(sortedArr[1][1])); // yellow code 8
		Assert::AreEqual(GREEN, (int)(sortedArr[2][1])); // green code 4
	}
	TEST_METHOD(WB_getTruckDistances2_8) {
		double sortedArr[3][2];

		struct Fleet current;
		current.B.route = getBlueRoute();
		current.G.route = getGreenRoute();
		current.Y.route = getYellowRoute();

		struct Point destination = { 1, 2 };
		getTruckDistances2(sortedArr, &current, destination);

		int BCP = getClosestPoint(&current.B.route, destination);
		int GCP = getClosestPoint(&current.G.route, destination);
		int YCP = getClosestPoint(&current.Y.route, destination);

		double B_dist = distance(&current.B.route.points[BCP], &destination); 
		double G_dist = distance(&current.G.route.points[GCP], &destination); 
		double Y_dist = distance(&current.Y.route.points[YCP], &destination); 

		Assert::AreEqual(B_dist, sortedArr[0][0]);
		Assert::AreEqual(G_dist, sortedArr[1][0]);
		Assert::AreEqual(Y_dist, sortedArr[2][0]);

		// check colours
		Assert::AreEqual(BLUE, (int)(sortedArr[0][1])); // blue code 2
		Assert::AreEqual(GREEN, (int)(sortedArr[1][1])); // green code 4
		Assert::AreEqual(YELLOW, (int)(sortedArr[2][1])); // yellow code 8
	}
	}
	;
}

namespace sortByLimitingFactorTests
{
	TEST_CLASS(BLACKBOXTESTS)
	{
	public:
		TEST_METHOD(BB_sortByLimitingFactor1) // truck fully limited, but no equal dists
		{
			double dists[3][2];
			struct Dispatch org;

			org.current.B.CurrentWeight = 0.0;
			org.current.B.CurrentVolume = 0.0;
			org.current.G.CurrentWeight = 625.0;
			org.current.G.CurrentVolume = 35.0;
			org.current.Y.CurrentWeight = 99.0;
			org.current.Y.CurrentVolume = 12.0;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[0][0] = 12.4;
			dists[0][1] = BLUE;
			dists[1][0] = 10.6;
			dists[1][1] = GREEN;
			dists[2][0] = 13.5;
			dists[2][1] = YELLOW;

			int i, j;
			double temp[1][2];

			for (i = 3 - 1; i > 0; i--)
			{
				for (j = 0; j < i; j++)
				{
					if (dists[j][0] > dists[j + 1][0])
					{
						temp[0][0] = dists[j][0];
						temp[0][1] = dists[j][1];
						dists[j][0] = dists[j + 1][0];
						dists[j][1] = dists[j + 1][1];
						dists[j + 1][0] = temp[0][0];
						dists[j + 1][1] = temp[0][1];
					}
				}
			}

			sortByLimitingFactor(dists, &org);

			double expectedDists[3][2] = {
				{10.6, GREEN},
				{12.4, BLUE},
				{13.5, YELLOW}
			};

			for (i = 0; i < 3; i++)
			{
				Assert::AreEqual(expectedDists[i][0], dists[i][0]);
				Assert::AreEqual((int)expectedDists[i][1], (int)dists[i][1]);
			}
		}

		TEST_METHOD(BB_sortByLimitingFactor2) // same limits, but different dists
		{
			double dists[3][2];
			struct Dispatch org;

			org.current.B.CurrentWeight = 200.0;
			org.current.B.CurrentVolume = 10.0;
			org.current.G.CurrentWeight = 200.0;
			org.current.G.CurrentVolume = 10.0;
			org.current.Y.CurrentWeight = 200.0;
			org.current.Y.CurrentVolume = 10.0;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[0][0] = 5.5;
			dists[0][1] = BLUE;
			dists[1][0] = 10.2;
			dists[1][1] = GREEN;
			dists[2][0] = 15.9;
			dists[2][1] = YELLOW;

			sortByLimitingFactor(dists, &org);

			double expectedDists[3][2] = {
				{5.5, BLUE},
				{10.2, GREEN},
				{15.9, YELLOW}
			};

			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(expectedDists[i][0], dists[i][0]);
				Assert::AreEqual((int)expectedDists[i][1], (int)dists[i][1]);
			}
		}

		TEST_METHOD(BB_sortByLimitingFactor3) // different limitations and same distance
		{
			double dists[3][2];
			struct Dispatch org;

			org.current.B.CurrentWeight = 500.0;
			org.current.B.CurrentVolume = 10.0;
			org.current.G.CurrentWeight = 625.0;
			org.current.G.CurrentVolume = 10.0;
			org.current.Y.CurrentWeight = 800.0;
			org.current.Y.CurrentVolume = 12.0;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[0][0] = 10.0;
			dists[0][1] = BLUE;
			dists[1][0] = 10.0;
			dists[1][1] = GREEN;
			dists[2][0] = 12.0;
			dists[2][1] = YELLOW;

			sortByLimitingFactor(dists, &org);

			double expectedDists[3][2] = {
				{10.0, BLUE},
				{10.0, GREEN},
				{12.0, YELLOW}
			};

			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(expectedDists[i][0], dists[i][0]);
				Assert::AreEqual((int)expectedDists[i][1], (int)dists[i][1]);
			}
		}

		TEST_METHOD(BB_sortByLimitingFactor4) // different volume limitation and same distance
		{
			double dists[3][2];
			struct Dispatch org;

			org.current.B.CurrentWeight = 400.0;
			org.current.B.CurrentVolume = 15.0;
			org.current.G.CurrentWeight = 625.0;
			org.current.G.CurrentVolume = 23.0;
			org.current.Y.CurrentWeight = 625.0;
			org.current.Y.CurrentVolume = 12.0;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[0][0] = 5.0;
			dists[0][1] = BLUE;
			dists[1][0] = 10.0;
			dists[1][1] = GREEN;
			dists[2][0] = 10.0;
			dists[2][1] = YELLOW;

			sortByLimitingFactor(dists, &org);

			double expectedDists[3][2] = {
				{5.0, BLUE},
				{10.0, YELLOW},
				{10.0, GREEN}
			};

			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(expectedDists[i][0], dists[i][0]);
				Assert::AreEqual((int)expectedDists[i][1], (int)dists[i][1]);
			}
		}

		TEST_METHOD(BB_sortByLimitingFactor5) // empty trucks remain the same order
		{
			double dists[3][2];
			struct Dispatch org;

			org.current.B.CurrentWeight = 1000.0;
			org.current.B.CurrentVolume = 36.0;
			org.current.G.CurrentWeight = 1000.0;
			org.current.G.CurrentVolume = 36.0;
			org.current.Y.CurrentWeight = 1000.0;
			org.current.Y.CurrentVolume = 36.0;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[0][0] = 3.14;
			dists[0][1] = BLUE;
			dists[1][0] = 3.14;
			dists[1][1] = GREEN;
			dists[2][0] = 3.14;
			dists[2][1] = YELLOW;

			sortByLimitingFactor(dists, &org);

			double expectedDists[3][2] = {
				{3.14, BLUE},
				{3.14, GREEN},
				{3.14, YELLOW}
			};

			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(expectedDists[i][0], dists[i][0]);
				Assert::AreEqual((int)expectedDists[i][1], (int)dists[i][1]);
			}
		}
	};

	TEST_CLASS(WhiteboxTests)
	{
	public:
		TEST_METHOD(WB_SortByLimitingFactor1)
		{
			double dists[3][2];
			struct Dispatch org;

			org.current.B.CurrentWeight = 0.0;
			org.current.B.CurrentVolume = 0.0;
			org.current.G.CurrentWeight = 0.0;
			org.current.G.CurrentVolume = 0.0;
			org.current.Y.CurrentWeight = 0.0;
			org.current.Y.CurrentVolume = 0.0;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[0][0] = 0.0;
			dists[0][1] = BLUE;
			dists[1][0] = 0.0;
			dists[1][1] = GREEN;
			dists[2][0] = 0.0;
			dists[2][1] = YELLOW;

			sortByLimitingFactor(dists, &org);

			double expectedDists[3][2] = {
				{0.0, BLUE},
				{0.0, GREEN},
				{0.0, YELLOW}
			};

			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(expectedDists[i][0], dists[i][0]);
				Assert::AreEqual((int)expectedDists[i][1], (int)dists[i][1]);
			}
		}

		TEST_METHOD(WB_SortByLimitingFactor2)
		{
			double dists[3][2];
			struct Dispatch org;

			org.current.B.CurrentWeight = 500.0;
			org.current.B.CurrentVolume = 10.0;
			org.current.G.CurrentWeight = 625.0;
			org.current.G.CurrentVolume = 10.0;
			org.current.Y.CurrentWeight = 800.0;
			org.current.Y.CurrentVolume = 12.0;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[0][0] = 25;
			dists[0][1] = BLUE;
			dists[1][0] = 25;
			dists[1][1] = GREEN;
			dists[2][0] = 25;
			dists[2][1] = YELLOW;

			sortByLimitingFactor(dists, &org);

			double expectedDists[3][2] = {
				{25, BLUE},
				{25, GREEN},
				{25, YELLOW}
			};

			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(expectedDists[i][0], dists[i][0]);
				Assert::AreEqual((int)expectedDists[i][1], (int)dists[i][1]);
			}
		}

		TEST_METHOD(WB_SortByLimitingFactor3)
		{
			double dists[3][2];
			struct Dispatch org;

			org.current.B.CurrentWeight = 500.0;
			org.current.B.CurrentVolume = 10.0;
			org.current.G.CurrentWeight = 625.0;
			org.current.G.CurrentVolume = 10.0;
			org.current.Y.CurrentWeight = 800.0;
			org.current.Y.CurrentVolume = 12.0;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[0][0] = 35.35;
			dists[0][1] = BLUE;
			dists[1][0] = 35.35;
			dists[1][1] = GREEN;
			dists[2][0] = 35.35;
			dists[2][1] = YELLOW;

			sortByLimitingFactor(dists, &org);

			double expectedDists[3][2] = {
				{35.35, BLUE},
				{35.35, GREEN},
				{35.35, YELLOW}
			};

			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(expectedDists[i][0], dists[i][0]);
				Assert::AreEqual((int)expectedDists[i][1], (int)dists[i][1]);
			}
		}

		TEST_METHOD(WB_SortByLimitingFactor4)
		{
			double dists[3][2];
			struct Dispatch org;

			org.current.B.CurrentWeight = 0.0;
			org.current.B.CurrentVolume = 0.0;
			org.current.G.CurrentWeight = 0.0;
			org.current.G.CurrentVolume = 0.0;
			org.current.Y.CurrentWeight = 800.0;
			org.current.Y.CurrentVolume = 12.0;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[0][0] = 35.35;
			dists[0][1] = BLUE;
			dists[1][0] = 35.35;
			dists[1][1] = GREEN;
			dists[2][0] = 35.35;
			dists[2][1] = YELLOW;

			sortByLimitingFactor(dists, &org);

			double expectedDists[3][2] = {
				{35.35, BLUE},
				{35.35, GREEN},
				{35.35, YELLOW}
			};

			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(expectedDists[i][0], dists[i][0]);
				Assert::AreEqual((int)expectedDists[i][1], (int)dists[i][1]);
			}
		}
	};
}


namespace findTruckAndDiversiontests
{
	TEST_CLASS(BlackboxTests) {
		TEST_METHOD(BB_findTruckAndDiversion_1) {
			double dists[3][2];
			struct Dispatch org;
			org.map = populateMap();

			org.current.B.CurrentWeight = 0;
			org.current.B.CurrentVolume = 0;
			org.current.G.CurrentWeight = 0;
			org.current.G.CurrentVolume = 0;
			org.current.Y.CurrentWeight = 0;
			org.current.Y.CurrentVolume = 0;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[0][0] = 1.0;
			dists[0][1] = BLUE;
			dists[1][0] = 7.0;
			dists[1][1] = GREEN;
			dists[2][0] = 8.0;
			dists[2][1] = YELLOW;

			struct OrderInfo order = { 20, .5, {11, 11}, {-1, -1} };
			struct OrderInfo* orderTemp = &order;
			int done = findTruckAndDiversion(&org, dists, &order);

			Assert::AreEqual(1, done);
			Assert::AreEqual(20, org.current.B.CurrentWeight);
			Assert::AreEqual(0.5, org.current.B.CurrentVolume);

		}

		TEST_METHOD(BB_findTruckAndDiversion_2)
		{
			double dists[3][2];
			struct Dispatch org;
			org.map = populateMap();

			org.current.B.CurrentWeight = 0;
			org.current.B.CurrentVolume = 0;
			org.current.G.CurrentWeight = 0;
			org.current.G.CurrentVolume = 0;
			org.current.Y.CurrentWeight = 0;
			org.current.Y.CurrentVolume = 0;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[1][0] = 2.2360679774997898;
			dists[1][1] = BLUE;
			dists[2][0] = 14.0;
			dists[2][1] = GREEN;
			dists[0][0] = 1.0;
			dists[0][1] = YELLOW;

			struct OrderInfo order = { 500, .25, {18, 8}, {-1, -1} };
			struct OrderInfo* orderTemp = &order;
			int done = findTruckAndDiversion(&org, dists, &order);

			Assert::AreEqual(1, done);
			Assert::AreEqual(500, org.current.Y.CurrentWeight);
			Assert::AreEqual(.25, org.current.Y.CurrentVolume);
		}

		TEST_METHOD(BB_findTruckAndDiversion_3)
		{
			double dists[3][2];
			struct Dispatch org;
			org.map = populateMap();

			org.current.B.CurrentWeight = 0;
			org.current.B.CurrentVolume = 0;
			org.current.G.CurrentWeight = 0;
			org.current.G.CurrentVolume = 0;
			org.current.Y.CurrentWeight = 0;
			org.current.Y.CurrentVolume = 0;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[1][0] = 9;
			dists[1][1] = BLUE;
			dists[0][0] = 1;
			dists[0][1] = GREEN;
			dists[2][0] = 11;
			dists[2][1] = YELLOW;

			struct OrderInfo order = { 1000, 1, {8, 24}, {-1, -1} };
			struct OrderInfo* orderTemp = &order;
			int done = findTruckAndDiversion(&org, dists, &order);

			Assert::AreEqual(1, done);
			Assert::AreEqual(1000, org.current.G.CurrentWeight);
			Assert::AreEqual(1.0, org.current.G.CurrentVolume);
		}
		TEST_METHOD(BB_findTruckAndDiversion_2_1)
		{
			double dists[3][2];
			struct Dispatch org;
			org.map = populateMap();

			org.current.B.CurrentWeight = 20;
			org.current.B.CurrentVolume = 0.5;
			org.current.G.CurrentWeight = 0;
			org.current.G.CurrentVolume = 0;
			org.current.Y.CurrentWeight = 0;
			org.current.Y.CurrentVolume = 0;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[1][0] = 10.0;
			dists[1][1] = BLUE;
			dists[0][0] = 2.0;
			dists[0][1] = GREEN;
			dists[2][0] = 12.0;
			dists[2][1] = YELLOW;

			struct OrderInfo order = { 200, 1, {7, 24}, {-1, -1} };
			struct OrderInfo* orderTemp = &order;
			int done = findTruckAndDiversion(&org, dists, orderTemp);

			Assert::AreEqual(1, done);
			Assert::AreEqual(200, org.current.G.CurrentWeight);
			Assert::AreEqual(1.0, org.current.G.CurrentVolume);
			Assert::AreEqual(7, orderTemp->diversion.numPoints);
			Assert::AreEqual((char)DIVERSION, orderTemp->diversion.routeSymbol);

			Route expectedDiversion =
			{
					{
							{6, 19}, // 7T
							{6, 20}, // 7U
							{6, 21}, // 7V
							{6, 22}, // 7W
							{6, 23}, // 7X
							{6, 24}, // 7Y
							{7, 24}	 // 8Y
					},
					7,
					DIVERSION };

			for (int i = 0; i < 7; i++)
			{
				int res = eqPt(expectedDiversion.points[i], order.diversion.points[(7 - 1) - i]);
				Assert::AreEqual(1, res);
			}
		}

		TEST_METHOD(BB_findTruckAndDiversion_2_2)
		{
			double dists[3][2];
			struct Dispatch org;
			org.map = populateMap();

			org.current.B.CurrentWeight = 20;
			org.current.B.CurrentVolume = 0.5;
			org.current.G.CurrentWeight = 200;
			org.current.G.CurrentVolume = 1;
			org.current.Y.CurrentWeight = 0;
			org.current.Y.CurrentVolume = 0;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[1][0] = 10.0;
			dists[1][1] = BLUE;
			dists[0][0] = 2.0;
			dists[0][1] = GREEN;
			dists[2][0] = 12.0;
			dists[2][1] = YELLOW;

			struct OrderInfo order = { 500, 1, {7, 24}, {-1, -1} };
			struct OrderInfo* orderTemp = &order;
			int done = findTruckAndDiversion(&org, dists, orderTemp);

			Assert::AreEqual(1, done);
			Assert::AreEqual(700, org.current.G.CurrentWeight);
			Assert::AreEqual(2.0, org.current.G.CurrentVolume);
			Assert::AreEqual(7, orderTemp->diversion.numPoints);
			Assert::AreEqual((char)DIVERSION, orderTemp->diversion.routeSymbol);

			Route expectedDiversion =
			{
					{
							{6, 19}, // 7T
							{6, 20}, // 7U
							{6, 21}, // 7V
							{6, 22}, // 7W
							{6, 23}, // 7X
							{6, 24}, // 7Y
							{7, 24}	 // 8Y
					},
					7,
					DIVERSION };

			for (int i = 0; i < 7; i++)
			{
				int res = eqPt(expectedDiversion.points[i], order.diversion.points[(7 - 1) - i]);
				Assert::AreEqual(1, res);
			}
		}

		TEST_METHOD(BB_findTruckAndDiversion_2_3)
		{
			double dists[3][2];
			struct Dispatch org;
			org.map = populateMap();

			org.current.B.CurrentWeight = 20;
			org.current.B.CurrentVolume = 0.5;
			org.current.G.CurrentWeight = 200;
			org.current.G.CurrentVolume = 1;
			org.current.Y.CurrentWeight = 0;
			org.current.Y.CurrentVolume = 0;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[0][0] = 4.0;
			dists[0][1] = BLUE;
			dists[1][0] = 4.0;
			dists[1][1] = GREEN;
			dists[2][0] = 6.0;
			dists[2][1] = YELLOW;

			struct OrderInfo order = { 500, 1, {13, 20}, {-1, -1} };
			struct OrderInfo* orderTemp = &order;
			int done = findTruckAndDiversion(&org, dists, orderTemp);

			Assert::AreEqual(1, done);
			Assert::AreEqual(520, org.current.B.CurrentWeight);
			Assert::AreEqual(1.5, org.current.B.CurrentVolume);
			Assert::AreEqual(6, orderTemp->diversion.numPoints);
			Assert::AreEqual((char)DIVERSION, orderTemp->diversion.routeSymbol);

			Route expectedDiversion =
			{
					{
							{17, 21}, // 18V
							{16, 21}, // 17V
							{15, 21}, // 16V
							{14, 21}, // 15V
							{13, 21}, // 14V
							{13, 20}, // 14U
					},
					6,
					DIVERSION };

			for (int i = 0; i < 6; i++)
			{
				int res = eqPt(expectedDiversion.points[i], order.diversion.points[(6 - 1) - i]);
				Assert::AreEqual(1, res);
			}
		}

		TEST_METHOD(BB_findTruckAndDiversion_2_4)
		{
			double dists[3][2];
			struct Dispatch org;
			org.map = populateMap();

			org.current.B.CurrentWeight = 520;
			org.current.B.CurrentVolume = 1.5;
			org.current.G.CurrentWeight = 200;
			org.current.G.CurrentVolume = 1;
			org.current.Y.CurrentWeight = 0;
			org.current.Y.CurrentVolume = 0;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[0][0] = 4.0;
			dists[0][1] = BLUE;
			dists[1][0] = 4.0;
			dists[1][1] = GREEN;
			dists[2][0] = 6.0;
			dists[2][1] = YELLOW;

			struct OrderInfo order = { 500, 1, {13, 20}, {-1, -1} };
			struct OrderInfo* orderTemp = &order;
			int done = findTruckAndDiversion(&org, dists, orderTemp);

			Assert::AreEqual(1, done);
			Assert::AreEqual(700, org.current.G.CurrentWeight);
			Assert::AreEqual(2.0, org.current.G.CurrentVolume);
			Assert::AreEqual(6, orderTemp->diversion.numPoints);
			Assert::AreEqual((char)DIVERSION, orderTemp->diversion.routeSymbol);

			Route expectedDiversion =
			{
					{
							{9, 21},	// 10V
							{10, 21}, // 11V
							{11, 21}, // 12V
							{12, 21}, // 13V
							{13, 21}, // 14V
							{13, 20}, // 14U
					},
					6,
					DIVERSION };

			for (int i = 0; i < 6; i++)
			{
				int res = eqPt(expectedDiversion.points[i], order.diversion.points[(6 - 1) - i]);
				Assert::AreEqual(1, res);
			}
		}

		TEST_METHOD(BB_findTruckAndDiversion_2_5)
		{
			double dists[3][2];
			struct Dispatch org;
			org.map = populateMap();

			org.current.B.CurrentWeight = 520;
			org.current.B.CurrentVolume = 1.5;
			org.current.G.CurrentWeight = 200;
			org.current.G.CurrentVolume = 1;
			org.current.Y.CurrentWeight = 0;
			org.current.Y.CurrentVolume = 0;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[1][0] = 5.0;
			dists[1][1] = BLUE;
			dists[2][0] = 13.0;
			dists[2][1] = GREEN;
			dists[0][0] = 3.0;
			dists[0][1] = YELLOW;

			struct OrderInfo order = { 666, .25, {22, 22}, {-1, -1} };
			struct OrderInfo* orderTemp = &order;
			int done = findTruckAndDiversion(&org, dists, orderTemp);

			Assert::AreEqual(1, done);
			Assert::AreEqual(666, org.current.Y.CurrentWeight);
			Assert::AreEqual(.25, org.current.Y.CurrentVolume);
			Assert::AreEqual(4, orderTemp->diversion.numPoints);
			Assert::AreEqual((char)DIVERSION, orderTemp->diversion.routeSymbol);

			Route expectedDiversion =
			{
					{
							{19, 22}, // 20W
							{20, 22}, // 21W
							{21, 22}, // 22W
							{22, 22}, // 23W
					},
					4,
					DIVERSION };

			for (int i = 0; i < 4; i++)
			{
				int res = eqPt(expectedDiversion.points[i], order.diversion.points[(4 - 1) - i]);
				Assert::AreEqual(1, res);
			}
		}

		TEST_METHOD(BB_findTruckAndDiversion_2_6) // Testing the outcome in case the fleet limit is exceeded.
		{
			double dists[3][2];
			struct Dispatch org;
			org.map = populateMap();

			org.current.B.CurrentWeight = 520;
			org.current.B.CurrentVolume = 1.5;
			org.current.G.CurrentWeight = 400;
			org.current.G.CurrentVolume = 1;
			org.current.Y.CurrentWeight = 666;
			org.current.Y.CurrentVolume = .25;

			org.current.B.route = getBlueRoute();
			org.current.G.route = getGreenRoute();
			org.current.Y.route = getYellowRoute();

			dists[1][0] = 5.0;
			dists[1][1] = BLUE;
			dists[2][0] = 13.0;
			dists[2][1] = GREEN;
			dists[0][0] = 3.0;
			dists[0][1] = YELLOW;

			org.nextDayOrders = 0;

			struct OrderInfo order = { 666, .25, {22, 22}, {-1, -1} };
			struct OrderInfo* orderTemp = &order;
			int done = findTruckAndDiversion(&org, dists, orderTemp);

			Assert::AreEqual(ADDED_NEXT_DAY, done);
			Assert::AreEqual(666, org.current.Y.CurrentWeight);
			Assert::AreEqual(.25, org.current.Y.CurrentVolume);
			Assert::AreNotEqual(4, orderTemp->diversion.numPoints);
			Assert::AreNotEqual((char)DIVERSION, orderTemp->diversion.routeSymbol);

			Route expectedDiversion =
			{
					{
							{19, 22}, // 12V
							{20, 22}, // 13V
							{21, 22}, // 14V
							{22, 22}, // 14U
					},
					4,
					DIVERSION };

			for (int i = 0; i < 4; i++)
			{
				int res = eqPt(expectedDiversion.points[i], order.diversion.points[(4 - 1) - i]);
				Assert::AreNotEqual(1, res);
			}

			// The order information should  be stored in the ordersOtherDay[] array
			Assert::AreEqual(org.ordersOtherDay[0].volume, orderTemp->volume);
			Assert::AreEqual(org.ordersOtherDay[0].weight, orderTemp->weight);
			int res = eqPt(org.ordersOtherDay[0].destination, orderTemp->destination);
			Assert::AreEqual(1, res);
		}
	}
	;

	TEST_CLASS(WhiteboxTests) {
public:

	TEST_METHOD(WB_findTruckAndDiversion_1) // Testing the outcome in case the fleet limit is exceeded but not the order limit(of 432) for next day .
	{
		double dists[3][2];
		struct Dispatch org;
		org.map = populateMap();

		org.current.B.CurrentWeight = 1000;
		org.current.B.CurrentVolume = 1.5;
		org.current.G.CurrentWeight = 1000;
		org.current.G.CurrentVolume = 1;
		org.current.Y.CurrentWeight = 1000;
		org.current.Y.CurrentVolume = .25;

		org.current.B.route = getBlueRoute();
		org.current.G.route = getGreenRoute();
		org.current.Y.route = getYellowRoute();

		dists[1][0] = 5.0;
		dists[1][1] = BLUE;
		dists[2][0] = 13.0;
		dists[2][1] = GREEN;
		dists[0][0] = 3.0;
		dists[0][1] = YELLOW;

		org.nextDayOrders = MAX_ORDERS-1;

		struct OrderInfo order = { 666, .25, {22, 22}, {-1, -1} };
		struct OrderInfo* orderTemp = &order;
		int done = findTruckAndDiversion(&org, dists, orderTemp);

		Assert::AreEqual(ADDED_NEXT_DAY, done);
		// The order information should  be stored in the ordersOtherDay[] array
		Assert::AreEqual(org.ordersOtherDay[org.nextDayOrders-1].volume, orderTemp->volume);
		Assert::AreEqual(org.ordersOtherDay[org.nextDayOrders-1].weight, orderTemp->weight);
		int res = eqPt(org.ordersOtherDay[org.nextDayOrders-1].destination, orderTemp->destination);
		Assert::AreEqual(1, res);
	}
	TEST_METHOD(WB_findTruckAndDiversion_2) // Testing the outcome in case the fleet limit as well as the order limit(of 432) for next day is exceeded.
	{
		double dists[3][2];
		struct Dispatch org;
		org.map = populateMap();

		org.current.B.CurrentWeight = 1000;
		org.current.B.CurrentVolume = 1.5;
		org.current.G.CurrentWeight = 1000;
		org.current.G.CurrentVolume = 1;
		org.current.Y.CurrentWeight = 1000;
		org.current.Y.CurrentVolume = .25;

		org.current.B.route = getBlueRoute();
		org.current.G.route = getGreenRoute();
		org.current.Y.route = getYellowRoute();

		dists[1][0] = 5.0;
		dists[1][1] = BLUE;
		dists[2][0] = 13.0;
		dists[2][1] = GREEN;
		dists[0][0] = 3.0;
		dists[0][1] = YELLOW;

		org.nextDayOrders = MAX_ORDERS;

		struct OrderInfo order = { 666, .25, {22, 22}, {-1, -1} };
		struct OrderInfo* orderTemp = &order;
		int done = findTruckAndDiversion(&org, dists, orderTemp);

		Assert::AreEqual(MAX_ORDERS, done);
	}

	TEST_METHOD(WB_findTruckAndDiversion_3) //demonstrating and testing example from project document
	{
		double dists[3][2];
		struct Dispatch org;
		org.map = populateMap();

		org.current.B.CurrentWeight = 200;
		org.current.B.CurrentVolume = 0.5;
		org.current.G.CurrentWeight = 799;
		org.current.G.CurrentVolume = 1;
		org.current.Y.CurrentWeight = 0;
		org.current.Y.CurrentVolume = 0;

		org.current.B.route = getBlueRoute();
		org.current.G.route = getGreenRoute();
		org.current.Y.route = getYellowRoute();

		dists[1][0] = 10.0;
		dists[1][1] = BLUE;
		dists[0][0] = 2.0;
		dists[0][1] = GREEN;
		dists[2][0] = 12.0;
		dists[2][1] = YELLOW;

		struct OrderInfo order = { 500, 1, {7, 24}, {-1, -1} };
		struct OrderInfo* orderTemp = &order;
		int done = findTruckAndDiversion(&org, dists, orderTemp);

		Assert::AreEqual(1, done);
		Assert::AreEqual(700, org.current.B.CurrentWeight);
		Assert::AreEqual(1.5, org.current.B.CurrentVolume);
		Assert::AreEqual(15, orderTemp->diversion.numPoints);
		Assert::AreEqual((char)DIVERSION, orderTemp->diversion.routeSymbol);

		Route expectedDiversion =
		{
			{
				{17, 21},  // 18V
				{16, 21},  // 17V
		        {15, 21},  // 16V
				{14, 21},  // 15V
				{13, 21},  // 14V
				{12, 21},  // 13V
				{11, 21},  // 12V
				{10, 21},  // 11V
				{9, 21},   // 10V
				{8, 21},   // 9V
				{7, 21},   // 8V
				{6, 22},   // 7W
				{6, 23},   // 7X
				{6, 24},   // 7Y
				{7, 24}    // 8Y
			},
			15,
			DIVERSION };

		for (int i = 0; i < 15; i++)
		{
			int res = eqPt(expectedDiversion.points[i], order.diversion.points[(15 - 1) - i]);
			Assert::AreEqual(1, res);
		}
	}

	TEST_METHOD(WB_findTruckAndDiversion_4) //calculating diversion for yellow route
	{
		double dists[3][2];
		struct Dispatch org;
		org.map = populateMap();

		org.current.B.CurrentWeight = 0;
		org.current.B.CurrentVolume = 0;
		org.current.G.CurrentWeight = 0;
		org.current.G.CurrentVolume = 0;
		org.current.Y.CurrentWeight = 0;
		org.current.Y.CurrentVolume = 0;

		org.current.B.route = getBlueRoute();
		org.current.G.route = getGreenRoute();
		org.current.Y.route = getYellowRoute();

		dists[1][0] = 6.0;
		dists[1][1] = BLUE;
		dists[2][0] = 14.0;
		dists[2][1] = GREEN;
		dists[0][0] = 4.0;
		dists[0][1] = YELLOW;

		struct OrderInfo order = { 500, 1, {23, 24}, {-1, -1} };
		struct OrderInfo* orderTemp = &order;
		int done = findTruckAndDiversion(&org, dists, orderTemp);

		Assert::AreEqual(1, done);
		Assert::AreEqual(500, org.current.Y.CurrentWeight);
		Assert::AreEqual(1.0, org.current.Y.CurrentVolume);
		Assert::AreEqual(10, orderTemp->diversion.numPoints);
		Assert::AreEqual((char)DIVERSION, orderTemp->diversion.routeSymbol);

		Route expectedDiversion =
		{
			{
				{19, 20},  // 20U
				{20, 20},  // 21U
				{21, 20},  // 22U
				{22, 20},  // 23U
				{23, 20},  // 24U
				{24, 21},  // 25V
				{24, 22},  // 25W
				{24, 23},  // 25X
				{24, 24},  // 25Y
				{23, 24}   // 24Y
			},
			10,
			DIVERSION };

		for (int i = 0; i < 10; i++)
		{
			int res = eqPt(expectedDiversion.points[i], order.diversion.points[(10 - 1) - i]);
			Assert::AreEqual(1, res);
		}
	}

	TEST_METHOD(WB_findTruckAndDiversion_5) //calculating diversion other trucks with the edge location, similar to earlier test case
	{
		double dists[3][2];
		struct Dispatch org;
		org.map = populateMap();

		org.current.B.CurrentWeight = 0;
		org.current.B.CurrentVolume = 0;
		org.current.G.CurrentWeight = 0;
		org.current.G.CurrentVolume = 0;
		org.current.Y.CurrentWeight = 700;
		org.current.Y.CurrentVolume = 15;

		org.current.B.route = getBlueRoute();
		org.current.G.route = getGreenRoute();
		org.current.Y.route = getYellowRoute();

		dists[1][0] = 6.0;
		dists[1][1] = BLUE;
		dists[2][0] = 14.0;
		dists[2][1] = GREEN;
		dists[0][0] = 4.0;
		dists[0][1] = YELLOW;

		struct OrderInfo order = { 500, 1, {23, 24}, {-1, -1} };
		struct OrderInfo* orderTemp = &order;
		int done = findTruckAndDiversion(&org, dists, orderTemp);

		Assert::AreEqual(1, done);
		Assert::AreEqual(500, org.current.B.CurrentWeight);
		Assert::AreEqual(1.0, org.current.B.CurrentVolume);
		Assert::AreEqual(16, orderTemp->diversion.numPoints);
		Assert::AreEqual((char)DIVERSION, orderTemp->diversion.routeSymbol);

		Route expectedDiversion =
		{
			{
				{17, 12},  // 18M
				{18, 12},  // 19M
				{19, 13},  // 20N
				{20, 14},  // 21O
				{21, 15},  // 22P
				{22, 15},  // 23P
				{23, 16},  // 24Q
				{23, 17},  // 24R
				{23, 18},  // 24S
				{23, 19},  // 24T
				{23, 20},  // 24U
				{24, 21},  // 25V
				{24, 22},  // 25W
				{24, 23},  // 25X
				{24, 24},  // 25Y
				{23, 24}   // 24Y
			},
			16,
			DIVERSION };

		for (int i = 0; i < 16; i++)
		{
			int res = eqPt(expectedDiversion.points[i], order.diversion.points[(16 - 1) - i]);
			Assert::AreEqual(1, res);
		}
	}
	};
}

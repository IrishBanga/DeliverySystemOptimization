#include "pch.h"
#include "CppUnitTest.h"
#include "tests.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(tests)
	{
	public:
		
		TEST_METHOD(TestDistance) //trying to test distance() function
		{
			Point p1 = { 0,0 };
			Point p2 = { 3,4 };
			double actual = distance(&p1, &p2);
			Assert::AreEqual(5.0,actual);
		}

		TEST_METHOD(TestValidate) //trying to test validate() function
		{
			Point p1 = { 0,0 };
			Point p2 = { 3,4 };
			int valid = validate(1,1,p1);
			Assert::AreEqual(1, valid);
		}

		TEST_METHOD(TestValidate2) //trying to test validate() function
		{
			Point p1 = { 0,0 };
			Point p2 = { 3,4 };
			int valid = validate(10, 1, p2);
			Assert::AreEqual(1, valid);
		}


		TEST_METHOD(TestValidate3) //trying to test validate() function
		{
			Point p1 = { 0,0 };
			Point p2 = { 3,4 };
			int invalid = validate(10, .26, p2);
			Assert::AreNotEqual(1, invalid);
		}

		TEST_METHOD(TestValidate4) //trying to test validate() function
		{
			Point p1 = { 0,0 };
			Point p2 = { 26,4 };
			int invalid = validate(10, .5, p2);
			Assert::AreNotEqual(1, invalid);
		}
	};
}

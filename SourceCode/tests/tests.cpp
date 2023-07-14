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
	};
}

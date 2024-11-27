#include <gtest/gtest.h>
#include <string>
#include <cstdint>
#include <sstream>
#include <list>
#include "print_ip.h"
using namespace std;

TEST(PrintIp, AllTasks) {
	std::string s;
	{
		std::stringstream ss;
		print_ip(int8_t{ -1 }, ss); // 255
		std::getline(ss, s, '\n');
		EXPECT_EQ("255", s);
	}

	{
		std::stringstream ss;
		print_ip(int16_t{ 0 }, ss); // 0.0
		std::getline(ss, s, '\n');
		EXPECT_EQ("0.0", s);
	}

	{
		std::stringstream ss;
		print_ip(int32_t{ 2130706433 }, ss); // 127.0.0.1
		std::getline(ss, s, '\n');
		EXPECT_EQ("127.0.0.1", s);
	}

	{
		std::stringstream ss;
		print_ip(int64_t{ 8875824491850138409 }, ss);// 123.45.67.89.101.112.131.41
		std::getline(ss, s, '\n');
		EXPECT_EQ("123.45.67.89.101.112.131.41", s);
	}

	{
		std::stringstream ss;
		print_ip(std::string{ "Hello, World!" }, ss); // Hello, World!
		std::getline(ss, s, '\n');
		EXPECT_EQ("Hello, World!", s);
	}

	{
		std::stringstream ss;
		print_ip(std::vector<int>{100, 200, 300, 400}, ss); // 100.200.300.400
		std::getline(ss, s, '\n');
		EXPECT_EQ("100.200.300.400", s);
	}
 	
	{
		std::stringstream ss;
		print_ip(std::list<short>{400, 300, 200, 100}, ss); // 400.300.200.100
		std::getline(ss, s, '\n');
		EXPECT_EQ("400.300.200.100", s);
	}

	{
		std::stringstream ss;
		print_ip(std::make_tuple(123, 456, 789, 0), ss); // 123.456.789.0

		// this will fail
		//print_ip(std::make_tuple("123", 456.5, 789, 0), ss); // 123.456.789.0

		std::getline(ss, s, '\n');
		EXPECT_EQ("123.456.789.0", s);
	}
}

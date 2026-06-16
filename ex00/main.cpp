#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include "easyfind.hpp"

static void printResult(bool passed, const std::string &context)
{
	std::cout << (passed ? "[OK]   " : "[FAIL] ") << context << std::endl;
}

int main(void)
{
	// --- vector: find existing value ---
	{
		std::vector<int> v;
		v.push_back(10);
		v.push_back(20);
		v.push_back(30);
		try {
			std::vector<int>::iterator it = easyfind(v, 20);
			printResult(*it == 20, "vector: find existing value (20)");
		} catch (std::exception &e) {
			printResult(false, "vector: find existing value (20)");
		}
	}

	// --- vector: find non-existing value, expect exception ---
	{
		std::vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		try {
			easyfind(v, 99);
			printResult(false, "vector: find non-existing value (99) should throw");
		} catch (std::exception &e) {
			printResult(true, "vector: find non-existing value (99) threw as expected");
		}
	}

	// --- deque: find existing value ---
	{
		std::deque<int> d;
		d.push_back(5);
		d.push_back(15);
		d.push_back(25);
		try {
			std::deque<int>::iterator it = easyfind(d, 15);
			printResult(*it == 15, "deque: find existing value (15)");
		} catch (std::exception &e) {
			printResult(false, "deque: find existing value (15)");
		}
	}

	// --- list: find existing value ---
	{
		std::list<int> l;
		l.push_back(100);
		l.push_back(200);
		l.push_back(300);
		try {
			std::list<int>::iterator it = easyfind(l, 300);
			printResult(*it == 300, "list: find existing value (300)");
		} catch (std::exception &e) {
			printResult(false, "list: find existing value (300)");
		}
	}

	// --- empty container: should throw ---
	{
		std::vector<int> empty;
		try {
			easyfind(empty, 42);
			printResult(false, "empty vector: should throw");
		} catch (std::exception &e) {
			printResult(true, "empty vector: threw as expected");
		}
	}

	return 0;
}

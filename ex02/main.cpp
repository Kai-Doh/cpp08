#include <iostream>
#include <list>
#include <string>
#include "MutantStack.hpp"

int main()
{
	// --- Spec test ---
	std::cout << "=== Spec test ===" << std::endl;
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;  // 17
	mstack.pop();
	std::cout << mstack.size() << std::endl; // 1
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);

	MutantStack<int>::iterator it  = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}

	std::stack<int> s(mstack);  // verify MutantStack converts to std::stack
	std::cout << "std::stack size after copy: " << s.size() << std::endl;

	// --- Equivalent std::list test (same output expected) ---
	std::cout << std::endl << "=== std::list equivalent ===" << std::endl;
	std::list<int> lst;
	lst.push_back(5);
	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	lst.push_back(0);

	std::list<int>::iterator lit  = lst.begin();
	std::list<int>::iterator lite = lst.end();
	while (lit != lite)
	{
		std::cout << *lit << std::endl;
		++lit;
	}

	// --- Non-int type test ---
	std::cout << std::endl << "=== MutantStack<std::string> ===" << std::endl;
	MutantStack<std::string> sstack;
	sstack.push("hello");
	sstack.push("world");
	sstack.push("42");
	std::cout << "top: " << sstack.top() << std::endl;
	MutantStack<std::string>::iterator sit  = sstack.begin();
	MutantStack<std::string>::iterator site = sstack.end();
	while (sit != site)
	{
		std::cout << *sit << std::endl;
		++sit;
	}
	std::cout << "OK" << std::endl;

	// --- Copy construction test ---
	std::cout << std::endl << "=== Copy construction ===" << std::endl;
	MutantStack<int> mstack2(mstack);
	MutantStack<int>::iterator it2  = mstack2.begin();
	MutantStack<int>::iterator ite2 = mstack2.end();
	while (it2 != ite2)
	{
		std::cout << *it2 << std::endl;
		++it2;
	}
	std::cout << "OK" << std::endl;

	// --- Assignment test ---
	std::cout << std::endl << "=== Assignment ===" << std::endl;
	MutantStack<int> mstack3;
	mstack3 = mstack;
	MutantStack<int>::iterator it3  = mstack3.begin();
	MutantStack<int>::iterator ite3 = mstack3.end();
	while (it3 != ite3)
	{
		std::cout << *it3 << std::endl;
		++it3;
	}
	std::cout << "OK" << std::endl;

	// --- const_iterator test ---
	std::cout << std::endl << "=== const_iterator ===" << std::endl;
	const MutantStack<int> cmstack(mstack);
	MutantStack<int>::const_iterator cit  = cmstack.begin();
	MutantStack<int>::const_iterator cite = cmstack.end();
	while (cit != cite)
	{
		std::cout << *cit << std::endl;
		++cit;
	}
	std::cout << "OK" << std::endl;

	return 0;
}

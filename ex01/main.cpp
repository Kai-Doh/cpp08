#include <iostream>
#include <vector>
#include <list>
#include "Span.hpp"

static void printResult(const std::string &label, bool passed)
{
    std::cout << "[" << (passed ? "OK" : "FAIL") << "] " << label << std::endl;
}

int main(void)
{
    // --- Test from spec ---
    std::cout << "=== Spec test ===" << std::endl;
    {
        Span sp(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        std::cout << sp.shortestSpan() << std::endl;   // expected: 2
        std::cout << sp.longestSpan()  << std::endl;   // expected: 14
        printResult("shortestSpan == 2", sp.shortestSpan() == 2);
        printResult("longestSpan == 14", sp.longestSpan() == 14);
    }

    // --- Span with 0 capacity: addNumber throws ---
    std::cout << "\n=== Zero-capacity Span ===" << std::endl;
    {
        Span sp(0);
        try
        {
            sp.addNumber(42);
            printResult("addNumber on full span throws", false);
        }
        catch (const std::exception &e)
        {
            printResult("addNumber on full span throws", true);
        }
    }

    // --- 1 element: shortestSpan / longestSpan throw ---
    std::cout << "\n=== Single-element Span ===" << std::endl;
    {
        Span sp(5);
        sp.addNumber(7);
        try
        {
            sp.shortestSpan();
            printResult("shortestSpan with 1 element throws", false);
        }
        catch (const std::exception &e)
        {
            printResult("shortestSpan with 1 element throws", true);
        }
        try
        {
            sp.longestSpan();
            printResult("longestSpan with 1 element throws", false);
        }
        catch (const std::exception &e)
        {
            printResult("longestSpan with 1 element throws", true);
        }
    }

    // --- Range-based add with vector iterators ---
    std::cout << "\n=== Range add (vector, 100 numbers) ===" << std::endl;
    {
        std::vector<int> src;
        for (int i = 0; i < 100; ++i)
            src.push_back(i * 3);

        Span sp(200);
        sp.addRange(src.begin(), src.end());

        // shortest: 3 (consecutive multiples of 3), longest: 99*3 = 297
        printResult("shortestSpan == 3",  sp.shortestSpan() == 3);
        printResult("longestSpan == 297", sp.longestSpan() == 297);
    }

    // --- Range-based add with list iterators ---
    std::cout << "\n=== Range add (list, 5 numbers) ===" << std::endl;
    {
        std::list<int> lst;
        lst.push_back(1);
        lst.push_back(100);
        lst.push_back(50);
        lst.push_back(75);
        lst.push_back(25);

        Span sp(10);
        sp.addRange(lst.begin(), lst.end());
        printResult("shortestSpan == 24", sp.shortestSpan() == 24);  // 50-26? no: sorted: 1,25,50,75,100 → 25-1=24
        printResult("longestSpan == 99",  sp.longestSpan() == 99);
    }

    // --- 10 000 numbers ---
    std::cout << "\n=== 10 000 numbers ===" << std::endl;
    {
        Span sp(10000);
        for (int i = 0; i < 10000; ++i)
            sp.addNumber(i * 7 + (i % 13));   // pseudo-random-ish spread

        std::cout << "shortestSpan: " << sp.shortestSpan() << std::endl;
        std::cout << "longestSpan:  " << sp.longestSpan()  << std::endl;
        printResult("no throw on 10 000 elements", true);
    }

    // --- Orthodox Canonical Form: copy and assignment ---
    std::cout << "\n=== Copy / Assignment ===" << std::endl;
    {
        Span original(5);
        original.addNumber(1);
        original.addNumber(5);
        original.addNumber(3);

        Span copy(original);
        printResult("copy shortestSpan == 2", copy.shortestSpan() == 2);
        printResult("copy longestSpan == 4",  copy.longestSpan() == 4);

        Span assigned(10);
        assigned = original;
        printResult("assigned shortestSpan == 2", assigned.shortestSpan() == 2);
        printResult("assigned longestSpan == 4",  assigned.longestSpan() == 4);

        // Mutating original should not affect copy
        original.addNumber(100);
        printResult("copy independent after mutation", copy.longestSpan() == 4);
    }

    return 0;
}

#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>

class Span
{
public:
    Span(unsigned int n);
    Span(const Span &other);
    Span &operator=(const Span &other);
    ~Span();

    void addNumber(int n);
    int  shortestSpan() const;
    int  longestSpan() const;

    template <typename Iterator>
    void addRange(Iterator first, Iterator last)
    {
        while (first != last)
        {
            addNumber(*first);
            ++first;
        }
    }

private:
    unsigned int        _max;
    std::vector<int>    _numbers;
};

#endif

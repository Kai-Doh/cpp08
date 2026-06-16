#include "Span.hpp"

Span::Span(unsigned int n) : _max(n) {}

Span::Span(const Span &other) : _max(other._max), _numbers(other._numbers) {}

Span &Span::operator=(const Span &other)
{
    if (this != &other)
    {
        _max = other._max;
        _numbers = other._numbers;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int n)
{
    if (_numbers.size() >= _max)
        throw std::runtime_error("Span is full");
    _numbers.push_back(n);
}

int Span::shortestSpan() const
{
    if (_numbers.size() < 2)
        throw std::runtime_error("Not enough numbers to find a span");

    std::vector<int> sorted(_numbers);
    std::sort(sorted.begin(), sorted.end());

    int shortest = sorted[1] - sorted[0];
    for (std::size_t i = 2; i < sorted.size(); ++i)
    {
        int diff = sorted[i] - sorted[i - 1];
        if (diff < shortest)
            shortest = diff;
    }
    return shortest;
}

int Span::longestSpan() const
{
    if (_numbers.size() < 2)
        throw std::runtime_error("Not enough numbers to find a span");

    int mn = *std::min_element(_numbers.begin(), _numbers.end());
    int mx = *std::max_element(_numbers.begin(), _numbers.end());
    return mx - mn;
}

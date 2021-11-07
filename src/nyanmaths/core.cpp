#include <cmath>
#include <stdexcept>

#include <nyanmaths/core.hpp>


////////////////////////// Algorithms //////////////////////////


double nm::pythagore (double a, double b, double greatest)
{
    if (greatest != 0.0 && (a <= greatest || b <= greatest))
        throw std::invalid_argument("Invalid argument in pythagore(a, b, greatest) : greatest must be the greatest one");

    else if (a < 0.0 || b < 0.0 || greatest < 0.0)
        throw std::invalid_argument("Invalid argument in pythagore(a, b, greatest) : all arguments must be positive");

    else if (!(a + b) || !(b + greatest) || !(a + greatest))
        throw std::invalid_argument("Invalid argument(s) in pythagore(a, b, greatest) : only one argument should be null");

    else if ((!a) ^ (!b) ^ (!greatest))
    {
        if (!greatest)
            return sqrt (a * a + b * b);

        else if (!a)
            return sqrt(greatest * greatest - b * b);

        else
            return sqrt(greatest * greatest - a * a);
    }
    else
    {
        if (a * a + b * b == greatest * greatest)
            return 1;

        return 0;
    }
}

std::vector<uint64_t>* nm::divisors (uint64_t x)
{
    if (x == 0)
        throw std::invalid_argument("Exception in nm::divisors : do you really want a vector with all the divisors of 0 ?");


    std::vector<uint64_t>* divisorsList(new std::vector<uint64_t>{x});

    for (uint64_t divisor(x / 2) ; divisor != 0 ; divisor--)
        if (x % divisor == 0)
            divisorsList->push_back(divisor);


    return divisorsList;
}

bool nm::prime (uint64_t x)
{
    if (x < 2)
        return false;

    else if (x < 4)
        return true;

    else if (x % 2 == 0)
        return false;

    else
    {
        const uint64_t seekCeil(x / 2);
        for (uint64_t div(3) ; div < seekCeil ; div += 2)
            if (x % div == 0)
                return false;

        return true;
    }
}

uint64_t nm::collatz (uint64_t x, uint64_t index)
{
    while (index != 0)
    {
        if (x % 2)
            x = x * 3 + 1;

        else
            x /= 2;

        index--;
    }

    return x;
}
std::vector<uint64_t>* nm::collatz (uint64_t x)
{
    if (x == 0)
        throw std::invalid_argument("Exception in nm::collatz : 0 does not have a Collatz continuation");

    std::vector<uint64_t>* continuation(new std::vector<uint64_t>{x});

    while (x != 1)
    {
        if (x % 2 == 0)
            x /= 2;

        else
            x = x * 3 + 1;

        continuation->push_back(x);
    }

    return continuation;
}

uint64_t nm::fibonacci (uint64_t index)
{
    if (index == 0)
        return 0;

    else if (index < 3)
        return 1;

    else
    {
        uint64_t a(1), b(1), swap;
        for (index -= 2 ; index != 0 ; index--)
        {
            swap = b;
            b = a + b;
            a = swap;
        }

        return b;
    }
}


uint64_t nm::factorial (uint16_t x)
{
    uint64_t result(1);
    for (uint16_t n(2) ; n <= x ; n++)
        result *= n;

    return result;
}

double nm::power (double x, int64_t n)
{
    if (x == 0.0 && n == 0)
        throw std::invalid_argument("Exception in nm::power : Impossible to compute 0 to the power 0");

    if (n == 0)
        return 1.0;

    if (x == 0.0)
        return 0.0;

    bool negativePower(false);
    if (n < 0)
    {
        negativePower = true;
        n = -n;
    }

    double result(1);
    while (n != 0)
    {
        result *= x;
        n--;
    }


    return negativePower ? 1.0 / result : result;
}

double nm::inverse (double x)
{
    if (x == 0.0)
        throw std::invalid_argument("Exception in nm::inverse : division by zero");

    return 1.0 / x;
}
std::complex<double> nm::inverse (const std::complex<double>& x)
{
    if (x.real() == 0.0 && x.imag() == 0.0)
        throw std::invalid_argument("Exception in nm::inverse : division by zero");

    const double denom(x.real() * x.real() + x.imag() * x.imag());
    return std::complex<double>(x.real() / denom, -x.imag() / denom);
}

double nm::root (double x, double n)
{
    return pow(x, 1.0 / n);
}
std::complex<double> nm::root (const std::complex<double>& x, const std::complex<double>& n)
{
    return pow(x, 1.0 / n);
}

double nm::square (double x)
{
    return x * x;
}
uint64_t nm::square (int64_t x)
{
    return nm::square(uint64_t(x));
}
uint64_t nm::square (uint64_t x)
{
    return x * x;
}
std::complex<double> nm::square (const std::complex<double>& x)
{
    return x * x;
}


double nm::cube (double x)
{
    return x * x * x;
}
int64_t nm::cube (int64_t x)
{
    return x * x * x;
}
uint64_t nm::cube (uint64_t x)
{
    return x * x * x;
}
std::complex<double> nm::cube (const std::complex<double>& x)
{
    return x * x * x;
}

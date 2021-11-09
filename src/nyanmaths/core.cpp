#include <cmath>
#include <stdexcept>

#include <nyanmaths/core.hpp>


////////////////////////// Actually quite everything //////////////////////////


nm::Error nm::pythagore (double& a, double& b, double& greatest)
{
    if (a < 0.0 || b < 0.0 || greatest < 0.0)
        return nm::Error::InvalidMeasurement;

    if (greatest != 0.0 && (a < greatest || b < greatest))
        return nm::Error::InvalidMeasurement;

    if (a + b == 0.0 || a + greatest == 0.0 || b + greatest == 0.0)
        return nm::Error::LogicError;


    if ((a == 0.0) ^ (b == 0.0) ^ (greatest == 0.0))
    {
        if (greatest == 0.0)
            greatest = sqrt(nm::square(a) + nm::square(b));

        else if (a == 0.0)
            a = sqrt(nm::square(greatest) - nm::square(b));

        else
            b = sqrt(nm::square(greatest) - nm::square(a));

        return nm::Error::NoError;
    }
    else
    {
        if (nm::square(a) + nm::square(b) == nm::square(greatest))
            return nm::Error::NoError;

        return nm::Error::LogicError;
    }
}

std::vector<uint64_t>* nm::divisors (const uint64_t x)
{
    if (x == 0u)
        throw std::invalid_argument("Exception in nm::divisors : do you really want a vector with all the divisors of 0 ?");


    std::vector<uint64_t>* divisorsList(new std::vector<uint64_t>{x});

    for (uint64_t divisor(x / 2u) ; divisor != 0u ; divisor--)
        if (x % divisor == 0u)
            divisorsList->push_back(divisor);


    return divisorsList;
}

bool nm::prime (const uint64_t x)
{
    if (x < 2u)
        return false;

    else if (x < 4u)
        return true;

    else if (x % 2u == 0u)
        return false;

    else
    {
        const uint64_t seekCeil(x / 2u);
        for (uint64_t div(3u) ; div < seekCeil ; div += 2u)
            if (x % div == 0u)
                return false;

        return true;
    }
}

uint64_t nm::collatz (uint64_t x, uint64_t index)
{
    while (index != 0u)
    {
        if (x % 2u)
            x = x * 3u + 1u;

        else
            x /= 2u;

        index--;
    }

    return x;
}
std::vector<uint64_t>* nm::collatz (uint64_t x)
{
    if (x == 0u)
        throw std::invalid_argument("Exception in nm::collatz : 0 does not have a Collatz continuation");

    std::vector<uint64_t>* continuation(new std::vector<uint64_t>{x});

    while (x != 1u)
    {
        if (x % 2u == 0u)
            x /= 2u;

        else
            x = x * 3u + 1u;

        continuation->push_back(x);
    }

    return continuation;
}

uint64_t nm::fibonacci (uint64_t index)
{
    if (index == 0u)
        return 0u;

    else if (index < 3u)
        return 1u;

    else
    {
        uint64_t a(1u), b(1u), swap;
        for (index -= 2u ; index != 0u ; index--)
        {
            swap = b;
            b = a + b;
            a = swap;
        }

        return b;
    }
}


uint64_t nm::factorial (const uint16_t x)
{
    uint64_t result(1u);
    for (uint16_t n(2u) ; n <= x ; n++)
        result *= n;

    return result;
}

double nm::power (const double x, int64_t exposant)
{
    if (x == 0.0 && exposant == 0)
        throw std::invalid_argument("Exception in nm::power : Impossible to compute 0 to the power 0");

    if (exposant == 0)
        return 1.0;

    if (x == 0.0)
        return 0.0;

    bool negativePower(false);
    if (exposant < 0)
    {
        negativePower = true;
        exposant = -exposant;
    }

    double result(1);
    while (exposant != 0)
    {
        result *= x;
        exposant--;
    }


    return negativePower ? 1.0 / result : result;
}

double nm::inverse (const double x)
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

double nm::root (const double x, const double n)
{
    return pow(x, 1.0 / n);
}
std::complex<double> nm::root (const std::complex<double>& x, const std::complex<double>& n)
{
    return pow(x, 1.0 / n);
}

double nm::square (const double x)
{
    return x * x;
}
uint64_t nm::square (const int64_t x)
{
    return nm::square(uint64_t(std::abs(x)));
}
uint64_t nm::square (const uint64_t x)
{
    return x * x;
}
std::complex<double> nm::square (const std::complex<double>& x)
{
    return x * x;
}

double nm::cube (const double x)
{
    return x * x * x;
}
int64_t nm::cube (const int64_t x)
{
    return x * x * x;
}
uint64_t nm::cube (const uint64_t x)
{
    return x * x * x;
}
std::complex<double> nm::cube (const std::complex<double>& x)
{
    return x * x * x;
}

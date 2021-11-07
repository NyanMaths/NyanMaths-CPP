#include <cmath>
#include <stdexcept>

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/ball.hpp>


////////////////////////// Ball members //////////////////////////


nm::Ball::Ball () : Ellipsoid()
{
    // Nothing to be done here
}

nm::Ball::Ball (const double radius, const nm::MeasurementUnit unit) : Ellipsoid(radius, unit)
{
    // Nothing to be done here
}

nm::Ball::Ball (const Ellipsoid& ellipsoid) : Ellipsoid(ellipsoid.a())
{
    if (ellipsoid.a() != ellipsoid.b() || ellipsoid.a() != ellipsoid.c())
        throw std::logic_error("Exception in nm::Ball::nm::Ball : non-constant radius");
}

nm::Ball::~Ball ()
{
    // Nothing to be done here
}

std::string nm::Ball::whatIsThis () const
{
    return "ball";
}


double nm::Ball::radius (const nm::MeasurementUnit unit) const
{
    return convert(_a, metre, unit);
}
double nm::Ball::diameter (const nm::MeasurementUnit unit) const
{
    return convert(_a * 2.0, metre, unit);
}

double nm::Ball::surface (const nm::MeasurementUnit unit) const
{
    return convert(_a * _a * nm::consts::tau * 2.0, metre, unit, 2);
}

double nm::Ball::volume (const nm::MeasurementUnit unit) const
{
    return convert(_a * _a * _a * 2.0 * nm::consts::tau / 3.0, metre, unit, 3);
}


nm::Error nm::Ball::setA (const double newA, const nm::MeasurementUnit unit)
{
    if (newA < 0.0)
        return nm::Error::InvalidMeasurement;

    _a = convert(newA, unit, metre);
    _b = _a;
    _c = _a;
    return nm::Error::NoError;
}
nm::Error nm::Ball::setB (const double newB, const nm::MeasurementUnit unit)
{
    if (newB < 0.0)
        return nm::Error::InvalidMeasurement;

    _a = convert(newB, unit, metre);
    _b = _a;
    _c = _a;
    return nm::Error::NoError;
}
nm::Error nm::Ball::setC (const double newC, const nm::MeasurementUnit unit)
{
    if (newC < 0.0)
        return nm::Error::InvalidMeasurement;

    _a = convert(newC, unit, metre);
    _b = _a;
    _c = _a;
    return nm::Error::NoError;
}

nm::Error nm::Ball::setRadius (const double newRadius, const nm::MeasurementUnit unit)
{
    if (newRadius < 0.0)
        return nm::Error::InvalidMeasurement;

    _a = convert(newRadius, unit, metre);
    _b = _a;
    _c = _a;
    return nm::Error::NoError;
}
nm::Error nm::Ball::setDiameter (const double newDiameter, const nm::MeasurementUnit unit)
{
    if (newDiameter < 0.0)
        return nm::Error::InvalidMeasurement;

    _a = convert(0.5 * newDiameter, unit, metre);
    _b = _a;
    _c = _a;
    return nm::Error::NoError;
}

nm::Error nm::Ball::setSurface (const double newSurface, const nm::MeasurementUnit unit)
{
    if (newSurface < 0.0)
        return nm::Error::InvalidMeasurement;

    _a = convert(sqrt(0.5 * newSurface / nm::consts::tau), unit, metre);
    _b = _a;
    _c = _a;
    return nm::Error::NoError;
}

nm::Error nm::Ball::setVolume (const double newVolume, const nm::MeasurementUnit unit)
{
    if (newVolume < 0.0)
        return nm::Error::InvalidMeasurement;

    _a = convert(pow(1.5 * newVolume / nm::consts::tau, 1.0 / 3.0), unit, metre);
    _b = _a;
    _c = _a;
    return nm::Error::NoError;
}


////////////////////////// Operators //////////////////////////


nm::Ball& nm::Ball::operator*= (const double n)
{
    if (n < 0.0)
        throw std::invalid_argument("Exception in nm::Ball::operator*= : invalid coefficient");

    _a *= n;
    _b *= n;
    _c *= n;

    return *this;
}

nm::Ball& nm::Ball::operator/= (const double n)
{
    if (n <= 0.0)
        throw std::invalid_argument("Exception in nm::Ball::operator/= : invalid coefficient");

    _a /= n;
    _b /= n;
    _c /= n;

    return *this;
}


nm::Ball operator* (nm::Ball a, const double n)
{
    a *= n;
    return a;
}
nm::Ball operator* (const double n, nm::Ball a)
{
    a *= n;
    return a;
}

nm::Ball operator/ (nm::Ball a, const double n)
{
    a *= n;
    return a;
}


bool operator== (const nm::Ball& a, const nm::Ball& b)
{
    return a.radius() == b.radius();
}
bool operator!= (const nm::Ball& a, const nm::Ball& b)
{
    return a.radius() != b.radius();
}

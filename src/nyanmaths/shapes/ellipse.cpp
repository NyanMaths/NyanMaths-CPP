#include <cmath>
#include <stdexcept>

#include <nyanmaths/shapes/disk.hpp>
#include <nyanmaths/shapes/ellipse.hpp>


////////////////////////// Ellipse members //////////////////////////


nm::Ellipse::Ellipse () :
    _a(defaultMeasurement(metre)),
    _b(defaultMeasurement(metre))
{
    // Nothing to be done here
}

nm::Ellipse::Ellipse (const double a, const double b, const nm::MeasurementUnit unit) :
    _a(convert(a, unit, metre)),
    _b(convert(b, unit, metre))
{
    if (a < 0.0 || b < 0.0)
        throw std::invalid_argument("Exception in nm::Ellipse::Ellipse : invalid measurements");
}

nm::Ellipse::Ellipse (const double radius, const nm::MeasurementUnit unit) :
    _a(convert(radius, unit, metre)),
    _b(_a)
{
    if (radius < 0.0)
        throw std::invalid_argument("Exception in nm::Ellipse::Ellipse : invalid radius");
}

nm::Ellipse::Ellipse (const nm::Disk& disk) :
    _a(disk.a(metre)),
    _b(_a)
{
    // Nothing to be done here
}

nm::Ellipse::~Ellipse ()
{
    // Nothing to be done here
}

std::string nm::Ellipse::whatIsThis () const
{
    if (isDisk())
        return "disk";

    return "ellipse";
}


double nm::Ellipse::a (const nm::MeasurementUnit unit) const
{
    return convert(_a, metre, unit);
}
double nm::Ellipse::b (const nm::MeasurementUnit unit) const
{
    return convert(_b, metre, unit);
}

double nm::Ellipse::perimeter (const nm::MeasurementUnit unit) const
{
    return convert(nm::consts::tau * sqrt((_a * _a + _b * _b) * 0.5), metre, unit);
}

double nm::Ellipse::surface (const nm::MeasurementUnit unit) const
{
    return convert(nm::consts::pi * _a * _b, metre, unit, 2);
}

double nm::Ellipse::linearEccentricity () const
{
    return sqrt(_a * _a - _b * _b);
}
double nm::Ellipse::eccentricity () const
{
    return linearEccentricity() / _a;
}


nm::Error nm::Ellipse::setA (const double newA, const nm::MeasurementUnit unit)
{
    if (newA < 0.0)
        return nm::Error::InvalidMeasurement;

    _a = convert(newA, unit, metre);
    return nm::Error::NoError;
}
nm::Error nm::Ellipse::setB (const double newB, const nm::MeasurementUnit unit)
{
    if (newB < 0.0)
        return nm::Error::InvalidMeasurement;

    _b = convert(newB, unit, metre);
    return nm::Error::NoError;
}

nm::Error nm::Ellipse::setPerimeter (const double newPerimeter, const nm::MeasurementUnit unit)
{
    if (newPerimeter < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentPerimeter(perimeter(unit));

    if (currentPerimeter == newPerimeter)
        return nm::Error::NoError;

    if (_a == 0.0 && _b == 0.0)
        return nm::Error::ImpossibleScaling;


    const double n(newPerimeter / currentPerimeter);
    _a *= n;
    _b *= n;
    return nm::Error::NoError;
}

nm::Error nm::Ellipse::setSurface (const double newSurface, const nm::MeasurementUnit unit)
{
    if (newSurface < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentSurface(surface(unit));

    if (currentSurface == newSurface)
        return nm::Error::NoError;

    if (_a == 0.0 || _b == 0.0)
        return nm::Error::ImpossibleScaling;


    const double n(sqrt(newSurface / currentSurface));
    _a *= n;
    _b *= n;
    return nm::Error::NoError;
}


bool nm::Ellipse::isDisk () const
{
    return _a == _b;
}


////////////////////////// Operators //////////////////////////


nm::Ellipse& nm::Ellipse::operator*= (const double n)
{
    if (n < 0.0)
        throw std::invalid_argument("Exception in nm::Ellipse::operator*= : invalid coefficient");

    _a *= n;
    _b *= n;

    return *this;
}

nm::Ellipse& nm::Ellipse::operator/= (const double n)
{
    if (n <= 0.0)
        throw std::invalid_argument("Exception in nm::Ellipse::operator/= : invalid coefficient");

    _a /= n;
    _b /= n;

    return *this;
}


nm::Ellipse operator* (nm::Ellipse a, const double n)
{
    a *= n;
    return a;
}
nm::Ellipse operator* (const double n, nm::Ellipse a)
{
    a *= n;
    return a;
}

nm::Ellipse operator/ (nm::Ellipse a, const double n)
{
    a /= n;
    return a;
}


bool operator== (const nm::Ellipse& a, const nm::Ellipse& b)
{
    return a.a() == b.a() && a.b() == b.b();
}

bool operator!= (const nm::Ellipse& a, const nm::Ellipse& b)
{
    return a.a() != b.a() || a.b() != b.b();
}

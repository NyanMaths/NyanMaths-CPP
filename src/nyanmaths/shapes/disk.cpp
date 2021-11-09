#include <cmath>
#include <stdexcept>

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/disk.hpp>


////////////////////////// Disk members //////////////////////////


nm::Disk::Disk () : Ellipse()
{
    // Nothing to be done here
}

nm::Disk::Disk (const double radius, const nm::MeasurementUnit unit) : Ellipse(radius, unit)
{
    // Nothig to be done here
}

nm::Disk::Disk (const nm::Ellipse& ellipse) : Ellipse(ellipse.a())
{
    if (ellipse.a() != ellipse.b())
        throw std::logic_error("Exception in nm::Disk::nm::Disk : non-constant radius");
}

nm::Disk::~Disk ()
{
    // Nothing to be done here
}

std::string nm::Disk::whatIsThis () const
{
    return "disk";
}


double nm::Disk::radius (const nm::MeasurementUnit unit) const
{
    return nm::convert(_a, metre, unit);
}
double nm::Disk::diameter (const nm::MeasurementUnit unit) const
{
    return nm::convert(_a * 2.0, metre, unit);
}

double nm::Disk::perimeter (const nm::MeasurementUnit unit) const
{
    return nm::convert(_a * nm::consts::tau, metre, unit);
}

double nm::Disk::surface (const nm::MeasurementUnit unit) const
{
    return nm::convert(nm::consts::pi * _a * _a, metre, unit, 2);
}


nm::Error nm::Disk::setA (const double newA, const nm::MeasurementUnit unit)
{
    if (newA < 0.0)
        return nm::Error::InvalidMeasurement;

    _a = nm::convert(newA, unit, metre);
    _b = _a;
    return nm::Error::NoError;
}
nm::Error nm::Disk::setB (const double newB, const nm::MeasurementUnit unit)
{
    if (newB < 0.0)
        return nm::Error::InvalidMeasurement;

    _a = nm::convert(newB, unit, metre);
    _b = _a;
    return nm::Error::NoError;
}

nm::Error nm::Disk::setRadius (const double newRadius, const nm::MeasurementUnit unit)
{
    if (newRadius < 0.0)
        return nm::Error::InvalidMeasurement;

    _a = nm::convert(newRadius, unit, metre);
    _b = _a;
    return nm::Error::NoError;
}
nm::Error nm::Disk::setDiameter (const double newDiameter, const nm::MeasurementUnit unit)
{
    if (newDiameter < 0.0)
        return nm::Error::InvalidMeasurement;

    _a = nm::convert(newDiameter * 0.5, unit, metre);
    _b = _a;
    return nm::Error::NoError;
}

nm::Error nm::Disk::setPerimeter (const double newPerimeter, const nm::MeasurementUnit unit)
{
    if (newPerimeter < 0.0)
        return nm::Error::InvalidMeasurement;

    _a = nm::convert(newPerimeter / nm::consts::tau, unit, metre);
    _b = _a;
    return nm::Error::NoError;
}

nm::Error nm::Disk::setSurface (const double newSurface, const nm::MeasurementUnit unit)
{
    if (newSurface < 0.0)
        return nm::Error::InvalidMeasurement;

    _a = nm::convert(sqrt(newSurface / nm::consts::pi), unit, metre);
    _b = _a;
    return nm::Error::NoError;
}


////////////////////////// Operators //////////////////////////


nm::Disk& nm::Disk::operator*= (const double n)
{
    if (n < 0.0)
        throw std::invalid_argument("Exception in nm::Disk::operator*= : invalid coefficient");

    _a *= n;
    _b *= n;

    return *this;
}

nm::Disk& nm::Disk::operator/= (const double n)
{
    if (n <= 0.0)
        throw std::invalid_argument("Exception in nm::Disk::operator/= : invalid coefficient");

    _a /= n;
    _b /= n;

    return *this;
}


nm::Disk operator* (nm::Disk a, const double n)
{
    a *= n;
    return a;
}

nm::Disk operator* (const double n, nm::Disk a)
{
    a *= n;
    return a;
}

nm::Disk operator/ (nm::Disk a, const double n)
{
    a /= n;
    return a;
}


bool operator== (const nm::Disk& a, const nm::Disk& b)
{
    return a.radius() == b.radius();
}

bool operator!= (const nm::Disk& a, const nm::Disk& b)
{
    return a.radius() != b.radius();
}

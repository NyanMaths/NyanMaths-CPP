#include <cmath>
#include <stdexcept>

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/disk.hpp>
#include <nyanmaths/shapes/rectangle.hpp>
#include <nyanmaths/shapes/square.hpp>


////////////////////////// Square members //////////////////////////


nm::Square::Square () : Rectangle()
{
    // Nothing to be done here
}

nm::Square::Square (const double side, const nm::MeasurementUnit unit) : Rectangle(side, unit)
{
    // Nothing to be done here
}

nm::Square::Square (const nm::Rectangle& rectangle) : Rectangle(rectangle)
{
    // Nothing to be done here
}

nm::Square::~Square ()
{
    // Nothing to be done here
}

std::string nm::Square::whatIsThis () const
{
    return "square";
}


double nm::Square::side (const nm::MeasurementUnit unit) const
{
    return nm::convert(_length, metre, unit);
}

double nm::Square::apothem (const nm::MeasurementUnit unit) const
{
    return nm::convert(_length * 0.5, metre, unit);
}

double nm::Square::diagonal (const nm::MeasurementUnit unit) const
{
    return nm::convert(_length * sqrt(2.0), metre, unit);
}

double nm::Square::perimeter (const nm::MeasurementUnit unit) const
{
    return nm::convert(4.0 * _length, metre, unit);
}

double nm::Square::surface (const nm::MeasurementUnit unit) const
{
    return nm::convert(nm::square(_length), metre, unit, 2u);
}

nm::Disk nm::Square::incircle () const
{
    return nm::Disk(diagonal(metre) * 0.5, metre);
}


nm::Error nm::Square::setLength (const double newLength, const nm::MeasurementUnit unit)
{
    if (newLength < 0.0)
        return nm::Error::InvalidMeasurement;

    _length = nm::convert(newLength, unit, metre);
    _width = _length;
    return nm::Error::NoError;
}
nm::Error nm::Square::setWidth (const double newWidth, const nm::MeasurementUnit unit)
{
    if (newWidth < 0.0)
        return nm::Error::InvalidMeasurement;

    _length = nm::convert(newWidth, unit, metre);
    _width = _length;
    return nm::Error::NoError;
}

nm::Error nm::Square::setSide (const double newSide, const nm::MeasurementUnit unit)
{
    if (newSide < 0.0)
        return nm::Error::InvalidMeasurement;

    _length = nm::convert(newSide, unit, metre);
    _width = _length;
    return nm::Error::NoError;
}

nm::Error nm::Square::setApothem (const double newApothem, const nm::MeasurementUnit unit)
{
    if (newApothem < 0.0)
        return nm::Error::InvalidMeasurement;

    _length = nm::convert(newApothem * 2.0, unit, metre);
    _width = _length;
    return nm::Error::NoError;
}

nm::Error nm::Square::setDiagonal (const double newDiagonal, const nm::MeasurementUnit unit)
{
    if (newDiagonal < 0.0)
        return nm::Error::InvalidMeasurement;

    _length = nm::convert(newDiagonal / sqrt(2.0), unit, metre);
    _width = _length;
    return nm::Error::NoError;
}

nm::Error nm::Square::setPerimeter (const double newPerimeter, const nm::MeasurementUnit unit)
{
    if (newPerimeter < 0.0)
        return nm::Error::InvalidMeasurement;

    _length = nm::convert(newPerimeter * 0.25, unit, metre);
    _width = _length;
    return nm::Error::NoError;
}

nm::Error nm::Square::setSurface (const double newSurface, const nm::MeasurementUnit unit)
{
    if (newSurface < 0.0)
        return nm::Error::InvalidMeasurement;

    _length = nm::convert(sqrt(newSurface), unit, metre);
    _width = _length;
    return nm::Error::NoError;
}

void nm::Square::setIncircle (const nm::Disk& newIncircle)
{
    _length = newIncircle.diameter(metre);
    _width = _length;
}


////////////////////////// Operators //////////////////////////


nm::Square& nm::Square::operator*= (const double n)
{
    if (n < 0.0)
        throw std::invalid_argument("Exception in nm::Square::operator*= : invalid coefficient");

    _length *= n;
    _width *= n;

    return *this;
}

nm::Square& nm::Square::operator/= (const double n)
{
    if (n <= 0.0)
        throw std::invalid_argument("Exception in nm::Square::operator/= : invalid coefficient");

    _length /= n;
    _width /= n;

    return *this;
}


nm::Square operator* (nm::Square a, const double n)
{
    a *= n;
    return a;
}
nm::Square operator* (const double n, nm::Square a)
{
    a *= n;
    return a;
}

nm::Square operator/ (nm::Square a, const double n)
{
    a /= n;
    return a;
}


bool operator== (const nm::Square& a, const nm::Square& b)
{
    return a.side() == b.side();
}

bool operator!= (const nm::Square& a, const nm::Square& b)
{
    return a.side() != b.side();
}

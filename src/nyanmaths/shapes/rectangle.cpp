#include <cmath>
#include <stdexcept>

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/disk.hpp>
#include <nyanmaths/shapes/square.hpp>
#include <nyanmaths/shapes/rectangle.hpp>


////////////////////////// Rectangle members //////////////////////////


nm::Rectangle::Rectangle () :
    _length(defaultMeasurement(metre)),
    _width(defaultMeasurement(metre))
{
    // Nothing to be done here
}

nm::Rectangle::Rectangle (const double length, const double width, const nm::MeasurementUnit unit) :
    _length(convert(length, unit, metre)),
    _width(convert(width, unit, metre))
{
    if (length < 0.0 || width < 0.0)
        throw std::invalid_argument("Exception in nm::Rectangle::Rectangle : invalid measurements");
}

nm::Rectangle::Rectangle (const double side, const nm::MeasurementUnit unit) :
    _length(convert(side, unit, metre)),
    _width(_length)
{
    if (side < 0.0)
        throw std::invalid_argument("Exception in nm::Rectangle::Rectangle : invalid side");
}

nm::Rectangle::Rectangle (const nm::Square& square) :
    _length(square.side(metre)),
    _width(_length)
{
    // Nothing to be done here
}

nm::Rectangle::~Rectangle ()
{
    // Nothing to be done here
}

std::string nm::Rectangle::whatIsThis () const
{
    if (isSquare())
        return "square";

    return "rectangle";
}


double nm::Rectangle::length (const nm::MeasurementUnit unit) const
{
    return convert(_length, metre, unit);
}
double nm::Rectangle::width (const nm::MeasurementUnit unit) const
{
    return convert(_width, metre, unit);
}

double nm::Rectangle::diagonal (const nm::MeasurementUnit unit) const
{
    return convert(sqrt(nm::square(_length) + nm::square(_width)), metre, unit);
}

double nm::Rectangle::perimeter (const nm::MeasurementUnit unit) const
{
    return convert(2.0 * (_length + _width), metre, unit);
}

double nm::Rectangle::surface (const nm::MeasurementUnit unit) const
{
    return convert(_length * _width, metre, unit, 2u);
}

nm::Disk nm::Rectangle::circumcircle () const
{
    return nm::Disk(diagonal(metre) * 0.5, metre);
}


nm::Error nm::Rectangle::setLength (const double newLength, const nm::MeasurementUnit unit)
{
    if (newLength < 0.0)
        return nm::Error::InvalidMeasurement;

    _length = convert(newLength, unit, metre);
    return nm::Error::NoError;
}
nm::Error nm::Rectangle::setWidth (const double newWidth, const nm::MeasurementUnit unit)
{
    if (newWidth < 0.0)
        return nm::Error::InvalidMeasurement;

    _width = convert(newWidth, unit, metre);
    return nm::Error::NoError;
}

nm::Error nm::Rectangle::setDiagonal (const double newDiagonal, const nm::MeasurementUnit unit)
{
    if (newDiagonal < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentDiagonal(diagonal(unit));

    if (newDiagonal == currentDiagonal)
        return nm::Error::NoError;

    if (_length == 0.0 && _width == 0.0)
        return nm::Error::ImpossibleScaling;


    const double n(newDiagonal / currentDiagonal);
    _length *= n;
    _width *= n;
    return nm::Error::NoError;
}

nm::Error nm::Rectangle::setPerimeter (const double newPerimeter, const nm::MeasurementUnit unit)
{
    if (newPerimeter < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentPerimeter(perimeter(unit));

    if (newPerimeter == currentPerimeter)
        return nm::Error::NoError;

    if (_length == 0.0 && _width == 0.0)
        return nm::Error::ImpossibleScaling;


    const double n(newPerimeter / currentPerimeter);
    _length *= n;
    _width *= n;
    return nm::Error::NoError;
}

nm::Error nm::Rectangle::setSurface (const double newSurface, const nm::MeasurementUnit unit)
{
    if (newSurface < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentSurface(surface(unit));

    if (newSurface == currentSurface)
        return nm::Error::NoError;

    if (_length == 0.0 || _width == 0.0)
        return nm::Error::ImpossibleScaling;


    const double n(sqrt(newSurface / currentSurface));
    _length *= n;
    _width *= n;
    return nm::Error::NoError;
}

nm::Error nm::Rectangle::setCircumcircle (const nm::Disk& newCircumcircle)
{
    const double currentDiagonal(diagonal(metre));

    if (newCircumcircle.diameter(metre) == currentDiagonal)
        return nm::Error::NoError;

    if (_length == 0.0 && _width == 0.0)
        return nm::Error::ImpossibleScaling;


    const double n(newCircumcircle.diameter(metre) / currentDiagonal);
    _length *= n;
    _width *= n;
    return nm::Error::NoError;
}


bool nm::Rectangle::isGolden () const
{
    if (_width == 0.0)
        return false;

    return double(uint64_t(_length / _width * 1000.0 + 0.5)) / 1000.0 == 1.618;
}

bool nm::Rectangle::isSquare () const
{
    return _length == _width;
}


////////////////////////// Operators //////////////////////////


nm::Rectangle& nm::Rectangle::operator*= (const double n)
{
    if (n < 0.0)
        throw std::invalid_argument("Exception in nm::Rectangle::operator*= : invalid coefficient");

    _length *= n;
    _width *= n;

    return *this;
}

nm::Rectangle& nm::Rectangle::operator/= (const double n)
{
    if (n <= 0.0)
        throw std::invalid_argument("Exception in nm::Rectangle::operator/= : invalid coefficient");

    _length /= n;
    _width /= n;

    return *this;
}


nm::Rectangle operator* (nm::Rectangle a, const double n)
{
    a *= n;
    return a;
}
nm::Rectangle operator* (const double n, nm::Rectangle a)
{
    a *= n;
    return a;
}

nm::Rectangle operator/ (nm::Rectangle a, const double n)
{
    a /= n;
    return a;
}


bool operator== (const nm::Rectangle& a, const nm::Rectangle& b)
{
    return a.length() == b.length() && a.width() == b.width();
}

bool operator!= (const nm::Rectangle& a, const nm::Rectangle& b)
{
    return a.length() != b.length() || a.width() != b.width();
}


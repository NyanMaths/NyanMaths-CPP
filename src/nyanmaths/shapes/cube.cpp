#include <cmath>
#include <stdexcept>

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/square.hpp>
#include <nyanmaths/shapes/ball.hpp>
#include <nyanmaths/shapes/cuboid.hpp>
#include <nyanmaths/shapes/cube.hpp>


////////////////////////// Cube members //////////////////////////


nm::Cube::Cube () : nm::Cuboid()
{
    // Nothing to be done here
}

nm::Cube::Cube (const double edge, const nm::MeasurementUnit unit) : nm::Cuboid(edge, unit)
{
    // Nothing to be done here
}

nm::Cube::Cube (const nm::Cuboid& cuboid) : nm::Cuboid(cuboid)
{
    // Nothing to be done here
}

nm::Cube::~Cube ()
{
    // Nothing to be done here
}

std::string nm::Cube::whatIsThis () const
{
    return "cube";
}


double nm::Cube::edge (const nm::MeasurementUnit unit) const
{
    return convert(_length, metre, unit);
}

double nm::Cube::diagonal (const nm::MeasurementUnit unit) const
{
    return convert(_length * sqrt(3.0), metre, unit);
}

double nm::Cube::surface (const nm::MeasurementUnit unit) const
{
    return convert(nm::square(_length) * 6.0, metre, unit, 2u);
}

nm::Ball nm::Cube::insphere () const
{
    return nm::Ball(_length * 0.5, metre);
}

nm::Square nm::Cube::face () const
{
    return nm::Square(_length, metre);
}


nm::Error nm::Cube::setLength (const double newLength, const nm::MeasurementUnit unit)
{
    if (newLength < 0.0)
        return nm::Error::InvalidMeasurement;

    _length = convert(newLength, unit, metre);
    _width = _length;
    _height = _length;
    return nm::Error::NoError;
}
nm::Error nm::Cube::setWidth (const double newWidth, const nm::MeasurementUnit unit)
{
    if (newWidth < 0.0)
        return nm::Error::InvalidMeasurement;

    _length = convert(newWidth, unit, metre);
    _width = _length;
    _height = _length;
    return nm::Error::NoError;
}
nm::Error nm::Cube::setHeight (const double newHeight, const nm::MeasurementUnit unit)
{
    if (newHeight < 0.0)
        return nm::Error::InvalidMeasurement;

    _length = convert(newHeight, unit, metre);
    _width = _length;
    _height = _length;
    return nm::Error::NoError;
}
nm::Error nm::Cube::setEdge (const double newEdge, const nm::MeasurementUnit unit)
{
    if (newEdge < 0.0)
        return nm::Error::InvalidMeasurement;

    _length = convert(newEdge, unit, metre);
    _width = _length;
    _height = _length;
    return nm::Error::NoError;
}

nm::Error nm::Cube::setDiagonal (const double newDiagonal, const nm::MeasurementUnit unit)
{
    if (newDiagonal < 0.0)
        return nm::Error::InvalidMeasurement;

    _length = convert(newDiagonal / sqrt(3.0), unit, metre);
    _width = _length;
    _height = _length;
    return nm::Error::NoError;
}

nm::Error nm::Cube::setSurface (const double newSurface, const nm::MeasurementUnit unit)
{
    if (newSurface < 0.0)
        return nm::Error::InvalidMeasurement;

    _length = convert(sqrt(newSurface / 6.0), unit, metre);
    _width = _length;
    _height = _length;
    return nm::Error::NoError;
}

nm::Error nm::Cube::setVolume (const double newVolume, const nm::MeasurementUnit unit)
{
    if (newVolume < 0.0)
        return nm::Error::InvalidMeasurement;

    _length = convert(pow(newVolume, 1.0 / 3.0), unit, metre);
    _width = _length;
    _height = _length;
    return nm::Error::NoError;
}

void nm::Cube::setInsphere (const nm::Ball& newInsphere)
{
    _length = newInsphere.diameter(metre);
    _width = _length;
    _height = _length;
}


////////////////////////// Operators //////////////////////////


nm::Cube& nm::Cube::operator*= (const double n)
{
    if (n < 0.0)
        throw std::invalid_argument("Exception in nm::Cube::operator*= : invalid coefficient");

    _length *= n;
    _width *= n;
    _height *= n;

    return *this;
}

nm::Cube& nm::Cube::operator/= (const double n)
{
    if (n <= 0.0)
        throw std::invalid_argument("Exception in nm::Cube::operator/= : invalid coefficient");

    _length /= n;
    _width /= n;
    _height *= n;

    return *this;
}


nm::Cube operator* (nm::Cube a, const double n)
{
    a *= n;
    return a;
}
nm::Cube operator* (const double n, nm::Cube a)
{
    a *= n;
    return a;
}

nm::Cube operator/ (nm::Cube a, const double n)
{
    a /= n;
    return a;
}


bool operator== (const nm::Cube& a, const nm::Cube& b)
{
    return a.edge() == b.edge();
}

bool operator!= (const nm::Cube& a, const nm::Cube& b)
{
    return a.edge() != b.edge();
}

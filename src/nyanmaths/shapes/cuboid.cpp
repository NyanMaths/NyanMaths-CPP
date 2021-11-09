#include <cmath>
#include <stdexcept>

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/ellipsoid.hpp>
#include <nyanmaths/shapes/ball.hpp>
#include <nyanmaths/shapes/cube.hpp>
#include <nyanmaths/shapes/cuboid.hpp>


////////////////////////// nm::Cuboid members //////////////////////////


nm::Cuboid::Cuboid () :
    _length(defaultMeasurement(metre)),
    _width(defaultMeasurement(metre))
{
    // Nothing to be done here
}

nm::Cuboid::Cuboid (const double length, const double width, const double height, const nm::MeasurementUnit unit) :
    _length(nm::convert(length, unit, metre)),
    _width(nm::convert(width, unit, metre)),
    _height(_length)
{
    if (length < 0.0 || width < 0.0 || height < 0.0)
        throw std::invalid_argument("Exception in nm::Cuboid::Cuboid : invalid measurements");
}

nm::Cuboid::Cuboid (const double edge, const nm::MeasurementUnit unit) :
    _length(nm::convert(edge, unit, metre)),
    _width(_length),
    _height(_length)
{
    if (edge < 0.0)
        throw std::invalid_argument("Exception in nm::Cuboid::Cuboid : invalid edge");
}

nm::Cuboid::Cuboid (const nm::Cube& cube) :
    _length(cube.edge(metre)),
    _width(_length),
    _height(_length)
{
    // Nothing to be done here
}

nm::Cuboid::~Cuboid ()
{
    // Nothing to be done here
}

std::string nm::Cuboid::whatIsThis () const
{
    if (isCube())
        return "cube";

    return "cuboid";
}


double nm::Cuboid::length (const nm::MeasurementUnit unit) const
{
    return nm::convert(_length, metre, unit);
}
double nm::Cuboid::width (const nm::MeasurementUnit unit) const
{
    return nm::convert(_width, metre, unit);
}
double nm::Cuboid::height (const nm::MeasurementUnit unit) const
{
    return nm::convert(_height, metre, unit);
}

double nm::Cuboid::diagonal (const nm::MeasurementUnit unit) const
{
    return nm::convert(sqrt(nm::square(_length) + nm::square(_width) + nm::square(_height)), metre, unit);
}

double nm::Cuboid::surface (const nm::MeasurementUnit unit) const
{
    return nm::convert(2.0 * (_length * _width + _length * _height + _width * _height), metre, unit, 2u);
}

double nm::Cuboid::volume (const nm::MeasurementUnit unit) const
{
    return nm::convert(_length * _width * _height, metre, unit, 3u);
}

nm::Ellipsoid nm::Cuboid::inscribedEllipsoid () const
{
    return nm::Ellipsoid(_length * 0.5, _width * 0.5, _height * 0.5, metre);
}

nm::Ball nm::Cuboid::circumsphere () const
{
    return nm::Ball(diagonal(metre) * 0.5, metre);
}


nm::Error nm::Cuboid::setLength (const double newLength, const nm::MeasurementUnit unit)
{
    if (newLength < 0.0)
        return nm::Error::InvalidMeasurement;

    _length = nm::convert(newLength, unit, metre);
    return nm::Error::NoError;
}
nm::Error nm::Cuboid::setWidth (const double newWidth, const nm::MeasurementUnit unit)
{
    if (newWidth < 0.0)
        return nm::Error::InvalidMeasurement;

    _width = nm::convert(newWidth, unit, metre);
    return nm::Error::NoError;
}
nm::Error nm::Cuboid::setHeight (const double newHeight, const nm::MeasurementUnit unit)
{
    if (newHeight < 0.0)
        return nm::Error::InvalidMeasurement;

    _height = nm::convert(newHeight, unit, metre);
    return nm::Error::NoError;
}

nm::Error nm::Cuboid::setDiagonal (const double newDiagonal, const nm::MeasurementUnit unit)
{
    if (newDiagonal < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentDiagonal(diagonal(unit));

    if (newDiagonal == currentDiagonal)
        return nm::Error::NoError;

    if (_length == 0.0 && _width == 0.0 && _height == 0.0)
        return nm::Error::ImpossibleScaling;


    const double n(newDiagonal / currentDiagonal);
    _length *= n;
    _width *= n;
    _height *= n;
    return nm::Error::NoError;
}

nm::Error nm::Cuboid::setSurface (const double newSurface, const nm::MeasurementUnit unit)
{
    if (newSurface < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentSurface(surface(unit));

    if (newSurface == currentSurface)
        return nm::Error::NoError;

    if (_length == 0.0 && _width == 0.0 && _height == 0.0)
        return nm::Error::ImpossibleScaling;


    const double n(sqrt(newSurface / currentSurface));
    _length *= n;
    _width *= n;
    _height *= n;
    return nm::Error::NoError;
}

nm::Error nm::Cuboid::setVolume (const double newVolume, const nm::MeasurementUnit unit)
{
    if (newVolume < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentVolume(volume(unit));

    if (newVolume == currentVolume)
        return nm::Error::NoError;

    if (_length == 0.0 || _width == 0.0 || _height == 0.0)
        return nm::Error::ImpossibleScaling;


    const double n(pow(newVolume / currentVolume, 1.0 / 3.0));
    _length *= n;
    _width *= n;
    _height *= n;
    return nm::Error::NoError;
}

void nm::Cuboid::setInscribedEllipsoid (const nm::Ellipsoid& newInscribedEllipsoid)
{
    _length = newInscribedEllipsoid.a(metre) * 0.5;
    _width = newInscribedEllipsoid.b(metre) * 0.5;
    _height = newInscribedEllipsoid.b(metre) * 0.5;
}

nm::Error nm::Cuboid::setCircumsphere (const nm::Ball& newCircumsphere)
{
    const double currentDiagonal(diagonal(metre));

    if (currentDiagonal == newCircumsphere.diameter(metre))
        return nm::Error::NoError;

    if (_length == 0.0 && _width == 0.0 && _height == 0.0)
        return nm::Error::ImpossibleScaling;


    const double n(newCircumsphere.diameter(metre) / currentDiagonal);
    _length *= n;
    _width *= n;
    _height *= n;
    return nm::Error::NoError;
}


bool nm::Cuboid::isCube () const
{
    return _length == _width && _length == _height;
}


////////////////////////// Operators //////////////////////////


nm::Cuboid& nm::Cuboid::operator*= (const double n)
{
    if (n < 0.0)
        throw std::invalid_argument("Exception in nm::Cuboid::operator*= : invalid coefficient");

    _length *= n;
    _width *= n;
    _height *= n;

    return *this;
}

nm::Cuboid& nm::Cuboid::operator/= (const double n)
{
    if (n <= 0.0)
        throw std::invalid_argument("Exception in nm::Cuboid::operator/= : invalid coefficient");

    _length /= n;
    _width /= n;
    _height /= n;

    return *this;
}


nm::Cuboid operator* (nm::Cuboid a, const double n)
{
    a *= n;
    return a;
}
nm::Cuboid operator* (const double n, nm::Cuboid a)
{
    a *= n;
    return a;
}

nm::Cuboid operator/ (nm::Cuboid a, const double n)
{
    a /= n;
    return a;
}


bool operator== (const nm::Cuboid& a, const nm::Cuboid& b)
{
    return a.length() == b.length() && a.width() == b.width() && a.height() == b.height();
}

bool operator!= (const nm::Cuboid& a, const nm::Cuboid& b)
{
    return a.length() != b.length() || a.width() != b.width() || a.height() != b.height();
}


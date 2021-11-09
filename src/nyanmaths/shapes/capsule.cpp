#include <cmath>
#include <stdexcept>

#include <nyanmaths/shapes/ball.hpp>
#include <nyanmaths/shapes/cylinder.hpp>
#include <nyanmaths/shapes/capsule.hpp>


////////////////////////// Capsule members //////////////////////////


nm::Capsule::Capsule () : _radius(defaultMeasurement(metre)), _length(defaultMeasurement(metre))
{
    // Nothing to be done here
}

nm::Capsule::Capsule (const double radius, const double length, const nm::MeasurementUnit unit) :
    _radius(nm::convert(radius, unit, metre)),
    _length(nm::convert(length, unit, metre))
{
    if (radius < 0.0)
        throw std::invalid_argument("Exception in nm::Capsule::Capsule : invalid radius");

    if (length < radius * 2.0)
        throw std::invalid_argument("Exception in nm::Capsule::Capsule : invalid length");
}

nm::Capsule::Capsule (const nm::Cylinder& trunk) :
    _radius(trunk.radius(metre)),
    _length(trunk.height(metre) + _radius * 2.0)
{
    // Nothing to be done here
}

nm::Capsule::Capsule (const nm::Ball& ball) :
    _radius(ball.radius(metre)),
    _length(_radius * 2.0)
{
    // Nothing to be done here
}

nm::Capsule::~Capsule ()
{
    // Nothing to be done here
}

std::string nm::Capsule::whatIsThis () const
{
    if (isBall())
        return "ball";

    return "capsule";
}


double nm::Capsule::radius (const nm::MeasurementUnit unit) const
{
    return nm::convert(_radius, metre, unit);
}
double nm::Capsule::diameter (const nm::MeasurementUnit unit) const
{
    return nm::convert(_radius * 2.0, metre, unit);
}

double nm::Capsule::length (const nm::MeasurementUnit unit) const
{
    return nm::convert(_length, metre, unit);
}

nm::Cylinder nm::Capsule::trunk () const
{
    return nm::Cylinder(_radius, _length - _radius * 2.0, metre);
}

double nm::Capsule::tipSurface (const nm::MeasurementUnit unit) const
{
    return nm::convert(consts::tau * nm::square(_radius), metre, unit, 2u);
}
double nm::Capsule::surface (const nm::MeasurementUnit unit) const
{
    return nm::convert(tipSurface(metre) * 2.0 + trunk().lateralSurface(metre), metre, unit, 2u);
}

double nm::Capsule::tipVolume (const nm::MeasurementUnit unit) const
{
    return nm::convert(consts::tau * nm::cube(_radius) / 3.0, metre, unit, 3u);
}
double nm::Capsule::volume (const nm::MeasurementUnit unit) const
{
    return nm::convert(tipVolume(metre) * 2.0 + trunk().volume(metre), metre, unit);
}


nm::Error nm::Capsule::setRadius (const double newRadius, const nm::MeasurementUnit unit)
{
    if (newRadius < 0.0 || newRadius * 2.0 < _length)
        return nm::Error::InvalidMeasurement;

    _radius = nm::convert(newRadius, unit, metre);
    return nm::Error::NoError;
}
nm::Error nm::Capsule::setDiameter (double newDiameter, const nm::MeasurementUnit unit)
{
    if (newDiameter < 0.0 || newDiameter < _length)
        return nm::Error::InvalidMeasurement;

    _radius = nm::convert(newDiameter * 0.5, unit, metre);
    return nm::Error::NoError;
}

nm::Error nm::Capsule::setLength (const double newLength, const nm::MeasurementUnit unit)
{
    if (newLength < _radius * 2.0)
        return nm::Error::InvalidMeasurement;

    _length = nm::convert(newLength, unit, metre);
    return nm::Error::NoError;
}

void nm::Capsule::setTrunk (const nm::Cylinder& newTrunk)
{
    _radius = newTrunk.radius(metre);
    _length = newTrunk.height(metre) + newTrunk.radius(metre) * 2.0;
}

nm::Error nm::Capsule::setTipSurface (const double newTipSurface, const nm::MeasurementUnit unit)
{
    if (newTipSurface < 0.0)
        return nm::Error::InvalidMeasurement;

    return setRadius(sqrt(newTipSurface / nm::consts::tau), unit);
}
nm::Error nm::Capsule::setSurface (const double newSurface, const nm::MeasurementUnit unit)
{
    if (newSurface < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentSurface(surface(unit));

    if (newSurface == currentSurface)
        return nm::Error::NoError;

    if (_radius == 0.0 && _length == 0.0)
        return nm::Error::ImpossibleScaling;


    const double n(sqrt(newSurface / currentSurface));
    _radius *= n;
    _length *= n;
    return nm::Error::NoError;
}

nm::Error nm::Capsule::setTipVolume (const double newTipVolume, const nm::MeasurementUnit unit)
{
    if (newTipVolume < 0.0)
        return nm::Error::InvalidMeasurement;

    return setRadius(pow(3.0 * newTipVolume / consts::tau, 1.0 / 3.0), unit);
}
nm::Error nm::Capsule::setVolume (const double newVolume, const nm::MeasurementUnit unit)
{
    if (newVolume < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentVolume(volume(unit));

    if (newVolume == currentVolume)
        return nm::Error::NoError;

    if (_radius == 0.0 && _length == 0.0)
        return nm::Error::ImpossibleScaling;


    const double n(pow(newVolume / currentVolume, 1.0 / 3.0));
    _length *= n;
    _radius *= n;
    return nm::Error::NoError;
}


bool nm::Capsule::isBall () const
{
    return _length == _radius * 2.0;
}


////////////////////////// Operators //////////////////////////


nm::Capsule& nm::Capsule::operator*= (const double n)
{
    if (n < 0.0)
        throw std::invalid_argument("Exception in nm::Capsule::operator*= : invalid coefficient");

    _radius *= n;
    _length *= n;

    return *this;
}

nm::Capsule& nm::Capsule::operator/= (const double n)
{
    if (n <= 0.0)
        throw std::invalid_argument("Exception in nm::Capsule::operator/= : invalid coefficient");

    _radius /= n;
    _length /= n;

    return *this;
}


nm::Capsule operator* (nm::Capsule a, const double n)
{
    a *= n;
    return a;
}
nm::Capsule operator* (const double n, nm::Capsule a)
{
    a *= n;
    return a;
}

nm::Capsule operator/ (nm::Capsule a, const double n)
{
    a /= n;
    return a;
}


bool operator== (const nm::Capsule& a, const nm::Capsule& b)
{
    return a.radius() == b.radius() && a.length() == b.length();
}

bool operator!= (const nm::Capsule& a, const nm::Capsule& b)
{
    return a.radius() != b.radius() || a.length() != b.length();
}



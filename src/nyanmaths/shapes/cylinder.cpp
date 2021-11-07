#include <cmath>
#include <stdexcept>

#include <nyanmaths/shapes/prism.hpp>
#include <nyanmaths/shapes/disk.hpp>
#include <nyanmaths/shapes/cylinder.hpp>


////////////////////////// Cylinder members //////////////////////////


nm::Cylinder::Cylinder () :
    _radius(defaultMeasurement(metre)),
    _height(defaultMeasurement(metre))
{
    // Nothing to be done here
}

nm::Cylinder::Cylinder (const double radius, const double height, const nm::MeasurementUnit unit) :
    _radius(convert(radius, unit, metre)),
    _height(convert(height, unit, metre))
{
    if (radius < 0.0 || height < 0.0)
        throw std::invalid_argument("Exception in nm::Cylinder::Cylinder : invalid measurements");
}

nm::Cylinder::~Cylinder ()
{
    // Nothing to be done here
}

std::string nm::Cylinder::whatIsThis () const
{
    return "cylinder";
}


double nm::Cylinder::radius (const nm::MeasurementUnit unit) const
{
    return convert(_radius, metre, unit);
}
nm::Disk nm::Cylinder::base () const
{
    return nm::Disk(_radius, metre);
}

double nm::Cylinder::height (const nm::MeasurementUnit unit) const
{
    return convert(_height, metre, unit);
}

double nm::Cylinder::lateralSurface (const nm::MeasurementUnit unit) const
{
    return convert(_radius * nm::consts::tau * _height, metre, unit, 2u);
}
double nm::Cylinder::surface (const nm::MeasurementUnit unit) const
{
    return convert(_radius * nm::consts::tau * _height + nm::square(_radius) * nm::consts::tau, metre, unit, 2u);
}

double nm::Cylinder::volume (const nm::MeasurementUnit unit) const
{
    return convert(nm::square(_radius) * nm::consts::pi * _height, metre, unit, 3u);
}


nm::Error nm::Cylinder::setRadius (const double newRadius, const nm::MeasurementUnit unit)
{
    if (newRadius < 0.0)
        return nm::Error::InvalidMeasurement;

    _radius = convert(newRadius, unit, metre);
    return nm::Error::NoError;
}
void nm::Cylinder::setBase (const nm::Disk& newBase)
{
    _radius = newBase.radius(metre);
}

nm::Error nm::Cylinder::setHeight (const double newHeight, const nm::MeasurementUnit unit)
{
    if (newHeight < 0.0)
        return nm::Error::InvalidMeasurement;

    _height = convert(newHeight, unit, metre);
    return nm::Error::NoError;
}

nm::Error nm::Cylinder::setLateralSurface (const double newLateralSurface, const nm::MeasurementUnit unit)
{
    if (newLateralSurface < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentLateralSurface(lateralSurface(unit));

    if (newLateralSurface == currentLateralSurface)
        return nm::Error::NoError;

    if (_radius == 0.0 || _height == 0.0)
        return Error::ImpossibleScaling;


    const double n(sqrt(newLateralSurface / currentLateralSurface));
    _radius *= n;
    _height *= n;
    return nm::Error::NoError;
}
nm::Error nm::Cylinder::setSurface (const double newSurface, const nm::MeasurementUnit unit)
{
    if (newSurface < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentSurface(surface(unit));

    if (newSurface == currentSurface)
        return nm::Error::NoError;

    if (_radius == 0.0)
        return Error::ImpossibleScaling;


    const double n(sqrt(newSurface / currentSurface));
    _radius *= n;
    _height *= n;
    return nm::Error::NoError;
}

nm::Error nm::Cylinder::setVolume (const double newVolume, const nm::MeasurementUnit unit)
{
    if (newVolume < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentVolume(volume(unit));

    if (newVolume == currentVolume)
        return nm::Error::NoError;

    if (_radius == 0.0 || _height == 0.0)
        return Error::ImpossibleScaling;


    const double n(pow(newVolume / currentVolume, 1.0 / 3.0));
    _radius *= n;
    _height *= n;
    return nm::Error::NoError;
}


////////////////////////// Operators //////////////////////////


nm::Cylinder& nm::Cylinder::operator*= (const double n)
{
    if (n < 0.0)
        throw std::invalid_argument("Exception in nm::Cylinder::operator*= : invalid coefficient");

    _radius *= n;
    _height *= n;

    return *this;
}

nm::Cylinder& nm::Cylinder::operator/= (const double n)
{
    if (n <= 0.0)
        throw std::invalid_argument("Exception in nm::Cylinder::operator/= : invalid coefficient");

    _radius /= n;
    _height /= n;

    return *this;
}


nm::Cylinder operator* (nm::Cylinder a, const double n)
{
    a *= n;
    return a;
}
nm::Cylinder operator* (const double n, nm::Cylinder a)
{
    a *= n;
    return a;
}

nm::Cylinder operator/ (nm::Cylinder a, const double n)
{
    a /= n;
    return a;
}


bool operator== (const nm::Cylinder& a, const nm::Cylinder& b)
{
    return a.radius() == b.radius() && a.height() == b.height();
}

bool operator!= (const nm::Cylinder& a, const nm::Cylinder& b)
{
    return a.radius() != b.radius() || a.height() != b.height();
}


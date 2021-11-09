#include <cmath>
#include <stdexcept>

#include <nyanmaths/shapes/shape2d.hpp>
#include <nyanmaths/shapes/prism.hpp>


////////////////////////// Prism members //////////////////////////


nm::Prism::Prism (nm::Shape2D* const base, const double height, const nm::MeasurementUnit unit) :
    _base(base),
    _height(nm::convert(height, unit, metre))
{
    if (height < 0.0)
        throw std::invalid_argument("Exception in nm::Prism::Prism : invalid height");
}

nm::Prism::~Prism ()
{
    // Nothing to be done here
}

std::string nm::Prism::whatIsThis () const
{
    return "prism (base : " + _base->whatIsThis() + ")";
}


nm::Shape2D* nm::Prism::base () const
{
    return _base;
}

double nm::Prism::height (const nm::MeasurementUnit unit) const
{
    return nm::convert(_height, metre, unit);
}

double nm::Prism::lateralSurface (const nm::MeasurementUnit unit) const
{
    return nm::convert(_base->perimeter() * _height, metre, unit, 2u);
}
double nm::Prism::surface (const nm::MeasurementUnit unit) const
{
    return nm::convert(_base->perimeter() * _height + _base->surface() * 2.0, metre, unit, 2u);
}

double nm::Prism::volume (const nm::MeasurementUnit unit) const
{
    return nm::convert(_base->surface() * _height, metre, unit, 3u);
}


nm::Error nm::Prism::setHeight (const double newHeight, const nm::MeasurementUnit unit)
{
    if (newHeight < 0.0)
        return nm::Error::InvalidMeasurement;

    _height = nm::convert(newHeight, unit, metre);
    return nm::Error::NoError;
}

nm::Error nm::Prism::setLateralSurface (const double newLateralSurface, const nm::MeasurementUnit unit)
{
    if (newLateralSurface < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentLateralSurface(lateralSurface(unit));

    if (newLateralSurface == currentLateralSurface)
        return nm::Error::NoError;


    try
    {
        const double n(sqrt(newLateralSurface / currentLateralSurface));
        *_base *= n;
        _height *= n;
    }
    catch (...)
    {
        return nm::Error::ImpossibleScaling;
    }
    return nm::Error::NoError;
}
nm::Error nm::Prism::setSurface (const double newSurface, const nm::MeasurementUnit unit)
{
    if (newSurface < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentSurface(surface(unit));

    if (newSurface == currentSurface)
        return nm::Error::NoError;


    try
    {
        const double n(sqrt(newSurface / currentSurface));
        *_base *= n;
        _height *= n;
    }
    catch (...)
    {
        return nm::Error::ImpossibleScaling;
    }
    return nm::Error::NoError;
}

nm::Error nm::Prism::setVolume (const double newVolume, const nm::MeasurementUnit unit)
{
    if (newVolume < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentVolume(volume(unit));

    if (newVolume == currentVolume)
        return nm::Error::NoError;


    try
    {
        const double n(pow(newVolume / currentVolume, 1.0 / 3.0));
        *_base *= n;
        _height *= n;
    }
    catch (...)
    {
        return nm::Error::ImpossibleScaling;
    }
    return nm::Error::NoError;
}


////////////////////////// Operators //////////////////////////


nm::Prism& nm::Prism::operator*= (const double n)
{
    if (n < 0.0)
        throw std::invalid_argument("Exception in nm::Prism::operator*= : invalid coefficient");

    *_base *= n;
    _height *= n;

    return *this;
}

nm::Prism& nm::Prism::operator/= (const double n)
{
    if (n <= 0.0)
        throw std::invalid_argument("Exception in nm::Prism::operator/= : invalid coefficient");

    *_base /= n;
    _height /= n;

    return *this;
}


nm::Prism operator* (nm::Prism a, const double n)
{
    a *= n;
    return a;
}

nm::Prism operator* (const double n, nm::Prism a)
{
    a *= n;
    return a;
}

nm::Prism operator/ (nm::Prism a, const double n)
{
    a /= n;
    return a;
}

/*
bool operator== (const nm::Prism& a, const nm::Prism& b)
{
    return a.radius() == b.radius();
}

bool operator!= (const nm::Prism& a, const nm::Prism& b)
{
    return a.radius() != b.radius();
}
*/

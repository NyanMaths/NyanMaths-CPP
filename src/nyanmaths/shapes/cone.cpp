#include <cmath>
#include <stdexcept>

#include <nyanmaths/shapes/disk.hpp>
#include <nyanmaths/shapes/cone.hpp>


////////////////////////// Cone members //////////////////////////


nm::Cone::Cone () :
    _radius(defaultMeasurement(metre)),
    _height(defaultMeasurement(metre))
{
    // Nothing to be done here
}

nm::Cone::Cone (const double radius, const double height, const nm::MeasurementUnit unit) :
    _radius(nm::convert(radius, unit, metre)),
    _height(nm::convert(height, unit, metre))
{
    if (radius < 0.0 || height < 0.0)
        throw std::invalid_argument("Exception in nm::Cone::Cone : invalid measurements");
}

nm::Cone::~Cone ()
{
    // Nothing to be done here
}

std::string nm::Cone::whatIsThis () const
{
    return "cone";
}


double nm::Cone::radius (const nm::MeasurementUnit unit) const
{
    return nm::convert(_radius, metre, unit);
}
double nm::Cone::diameter (const nm::MeasurementUnit unit) const
{
    return nm::convert(_radius * 2.0, metre, unit);
}
nm::Disk nm::Cone::base () const
{
    return nm::Disk(_radius, metre);
}

double nm::Cone::height (const nm::MeasurementUnit unit) const
{
    return nm::convert(_height, metre, unit);
}
double nm::Cone::slantHeight (const nm::MeasurementUnit unit) const
{
    return nm::convert(sqrt(nm::square(_radius) + nm::square(_height)), metre, unit);
}

double nm::Cone::lateralSurface (const nm::MeasurementUnit unit) const
{
    return nm::convert(nm::consts::pi * _radius * slantHeight(), metre, unit, 2u);
}
double nm::Cone::surface (const nm::MeasurementUnit unit) const
{
    return nm::convert(nm::consts::pi * nm::square(_radius) + lateralSurface(), metre, unit, 2u);
}

double nm::Cone::volume (const nm::MeasurementUnit unit) const
{
    return nm::convert(nm::consts::pi * nm::square(_radius) * _height / 3.0, metre, unit, 3u);
}


nm::Error nm::Cone::setRadius (const double newRadius, const nm::MeasurementUnit unit)
{
    if (newRadius < 0.0)
        return nm::Error::InvalidMeasurement;

    _radius = nm::convert(newRadius, unit, metre);
    return nm::Error::NoError;
}
void nm::Cone::setBase (const nm::Disk& newBase)
{
    _radius = newBase.radius(metre);
}

nm::Error nm::Cone::setHeight (const double newHeight, const nm::MeasurementUnit unit)
{
    if (newHeight < 0.0)
        return nm::Error::InvalidMeasurement;

    _height = nm::convert(newHeight, unit, metre);
    return nm::Error::NoError;
}
nm::Error nm::Cone::setSlantHeight (const double newSlantHeight, const nm::MeasurementUnit unit)
{
    if (newSlantHeight < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentSlantHeight(slantHeight(unit));

    if (newSlantHeight == currentSlantHeight)
        return nm::Error::NoError;

    if (_radius == 0.0 && _height == 0.0)
        return Error::ImpossibleScaling;


    const double n(newSlantHeight / currentSlantHeight);
    _radius *= n;
    _height *= n;
    return nm::Error::NoError;
}

nm::Error nm::Cone::setLateralSurface (const double newLateralSurface, const nm::MeasurementUnit unit)
{
    if (newLateralSurface < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentLateralSurface(lateralSurface(unit));

    if (newLateralSurface == currentLateralSurface)
        return nm::Error::NoError;

    if (_radius == 0.0)
        return Error::ImpossibleScaling;


    const double n(sqrt(newLateralSurface / currentLateralSurface));
    _radius *= n;
    _height *= n;
    return nm::Error::NoError;
}
nm::Error nm::Cone::setSurface (const double newSurface, const nm::MeasurementUnit unit)
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

nm::Error nm::Cone::setVolume (const double newVolume, const nm::MeasurementUnit unit)
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


nm::Cone& nm::Cone::operator*= (const double n)
{
    if (n < 0.0)
        throw std::invalid_argument("Exception in nm::Cone::operator*= : invalid coefficient");

    _radius *= n;
    _height *= n;

    return *this;
}

nm::Cone& nm::Cone::operator/= (const double n)
{
    if (n <= 0.0)
        throw std::invalid_argument("Exception in nm::Cone::operator/= : invalid coefficient");

    _radius /= n;
    _height /= n;

    return *this;
}


nm::Cone operator* (nm::Cone a, const double n)
{
    a *= n;
    return a;
}
nm::Cone operator* (const double n, nm::Cone a)
{
    a *= n;
    return a;
}

nm::Cone operator/ (nm::Cone a, const double n)
{
    a /= n;
    return a;
}


bool operator== (const nm::Cone& a, const nm::Cone& b)
{
    return a.radius() == b.radius() && a.height() == b.height();
}

bool operator!= (const nm::Cone& a, const nm::Cone& b)
{
    return a.radius() != b.radius() || a.height() != b.height();
}


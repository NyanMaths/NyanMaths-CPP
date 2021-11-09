#include <cmath>
#include <stdexcept>

#include <nyanmaths/shapes/ball.hpp>
#include <nyanmaths/shapes/ellipsoid.hpp>


////////////////////////// nm::Ellipsoid members //////////////////////////


nm::Ellipsoid::Ellipsoid () : _a(defaultMeasurement()), _b(defaultMeasurement()), _c(defaultMeasurement())
{
    // Nothing to be done here
}

nm::Ellipsoid::Ellipsoid (const double a, const double b, const double c, const nm::MeasurementUnit unit) :
    _a(nm::convert(a, unit, metre)),
    _b(nm::convert(b, unit, metre)),
    _c(nm::convert(c, unit, metre))
{
    if (a < 0.0 || b < 0.0 || c < 0.0)
        throw std::invalid_argument("Exception in nm::Ellipsoid::Ellipsoid : invalid measurements");
}

nm::Ellipsoid::Ellipsoid (const double radius, const nm::MeasurementUnit unit) :
    _a(nm::convert(radius, unit, metre)),
    _b(_a),
    _c(_a)
{
    if (radius < 0.0)
        throw std::invalid_argument("Exception in nm::Ellipsoid::Ellipsoid : invalid radius");
}

nm::Ellipsoid::Ellipsoid (const Ball& ball) :
    _a(ball.a(metre)),
    _b(_a),
    _c(_a)
{
    // Nothing to be done here
}

nm::Ellipsoid::~Ellipsoid ()
{
    // Nothing to be done here
}

std::string nm::Ellipsoid::whatIsThis () const
{
    if (isBall())
        return "ball";

    return "ellipsoid";
}


double nm::Ellipsoid::a (const nm::MeasurementUnit unit) const
{
    return nm::convert(_a, metre, unit);
}
double nm::Ellipsoid::b (const nm::MeasurementUnit unit) const
{
    return nm::convert(_b, metre, unit);
}
double nm::Ellipsoid::c (const nm::MeasurementUnit unit) const
{
    return nm::convert(_c, metre, unit);
}

double nm::Ellipsoid::surface (const nm::MeasurementUnit unit) const
{
    if (_a != _b && _a != _c)
        throw std::logic_error("Exception in nm::Ellipsoid::surface : unable to compute if object is not ball-like");

    return nm::convert(_a * _a * nm::consts::tau * 2.0, metre, unit, 2u);
}

double nm::Ellipsoid::volume (const nm::MeasurementUnit unit) const
{
    return nm::convert(_a * _b * _c * nm::consts::tau * 2.0 / 3.0, metre, unit, 3u);
}


nm::Error nm::Ellipsoid::setA (const double newA, const nm::MeasurementUnit unit)
{
    if (newA < 0.0)
        return nm::Error::InvalidMeasurement;

    _a = nm::convert(newA, unit, metre);
    return nm::Error::NoError;
}
nm::Error nm::Ellipsoid::setB (const double newB, const nm::MeasurementUnit unit)
{
    if (newB < 0.0)
        return nm::Error::InvalidMeasurement;

    _b = nm::convert(newB, unit, metre);
    return nm::Error::NoError;
}
nm::Error nm::Ellipsoid::setC (const double newC, const nm::MeasurementUnit unit)
{
    if (newC < 0.0)
        return nm::Error::InvalidMeasurement;

    _c = nm::convert(newC, unit, metre);
    return nm::Error::NoError;
}

nm::Error nm::Ellipsoid::setSurface (const double newSurface, const nm::MeasurementUnit unit)
{
    if (newSurface < 0.0)
        return nm::Error::InvalidMeasurement;

    if (!(_a == _b && _a == _c))
        return nm::Error::ImpossibleScaling;

    const double currentSurface(surface(unit));

    if (currentSurface == newSurface)
        return nm::Error::NoError;

    if (_a == 0.0)
        return nm::Error::ImpossibleScaling;


    const double n(sqrt(newSurface / currentSurface));
    _a *= n;
    _b *= n;
    _c *= n;
    return nm::Error::NoError;
}

nm::Error nm::Ellipsoid::setVolume (const double newVolume, const nm::MeasurementUnit unit)
{
    if (newVolume < 0.0)
        return nm::Error::InvalidMeasurement;

    const double currentVolume(volume(unit));

    if (newVolume == currentVolume)
        return nm::Error::NoError;

    if (_a == 0.0 || _b == 0.0 || _c == 0.0)
        return nm::Error::ImpossibleScaling;


    const double n(pow(newVolume / currentVolume, 1.0 / 3.0));
    _a *= n;
    _b *= n;
    _c *= n;
    return nm::Error::NoError;
}


bool nm::Ellipsoid::isBall () const
{
    return _a == _b && _a == _c;
}


////////////////////////// Operators //////////////////////////


nm::Ellipsoid& nm::Ellipsoid::operator*= (const double n)
{
    if (n < 0.0)
        throw std::invalid_argument("Exception in nm::Ellipsoid::operator*= : invalid coefficient");

    _a *= n;
    _b *= n;
    _c *= n;

    return *this;
}

nm::Ellipsoid& nm::Ellipsoid::operator/= (const double n)
{
    if (n <= 0.0)
        throw std::invalid_argument("Exception in nm::Ellipsoid::operator/= : invalid coefficient");

    _a /= n;
    _b /= n;
    _c /= n;

    return *this;
}


nm::Ellipsoid operator* (nm::Ellipsoid a, const double n)
{
    a *= n;
    return a;
}
nm::Ellipsoid operator* (const double n, nm::Ellipsoid a)
{
    a *= n;
    return a;
}

nm::Ellipsoid operator/ (nm::Ellipsoid a, const double n)
{
    a /= n;
    return a;
}


bool operator== (const nm::Ellipsoid& a, const nm::Ellipsoid& b)
{
    return a.a() == b.a() && a.b() == b.b() && a.c() == b.c();
}

bool operator!= (const nm::Ellipsoid& a, const nm::Ellipsoid& b)
{
    return !(a == b);
}

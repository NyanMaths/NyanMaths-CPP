#include <cmath>
#include <stdexcept>

#include <nyanmaths/angle.hpp>


////////////////////////// Define static const members //////////////////////////


nm::Angle::Unit nm::Angle::_defaultUnit(nm::Angle::Unit::Radian);


////////////////////////// Angle members //////////////////////////


nm::Angle::Angle () : _value(0.0)
{
    // Nothing to be done here
}

nm::Angle::Angle (const double value, const nm::Angle::Unit unit)
{
    if (unit == nm::Angle::Unit::Radian)
        _value = value;

    else if (unit == nm::Angle::Unit::Degree)
        _value = value * consts::pi / 180.0;

    else if (unit == nm::Angle::Unit::Gradian)
        _value = value * consts::pi * 0.005;

    else
        _value = value * consts::tau;
}


double nm::Angle::value (const nm::Angle::Unit convertUnit, const bool mainValue) const
{
    double convertedValue(_value);

    if (mainValue)
        while (convertedValue >= consts::tau)
            convertedValue -= consts::tau;

    if (convertUnit == nm::Angle::Unit::Degree)
        convertedValue = _value * 180.0 / consts::pi;

    else if (convertUnit == nm::Angle::Unit::Gradian)
        convertedValue = _value * 200.0 / consts::pi;

    else if (convertUnit == nm::Angle::Unit::Turn)
        convertedValue = _value / consts::tau;


    return convertedValue;
}
nm::Error nm::Angle::setValue (const double newValue, const nm::Angle::Unit newUnit)
{
    if (newValue < 0.0)
        return nm::Error::InvalidValue;


    if (newUnit == nm::Angle::Unit::Radian)
        _value = newValue;

    else if (newUnit == nm::Angle::Unit::Degree)
        _value = newValue * consts::pi / 180.0;

    else if (newUnit == nm::Angle::Unit::Gradian)
        _value = newValue * consts::pi * 0.005;

    else
        _value = newValue * consts::tau;


    return nm::Error::NoError;
}


nm::Angle::Unit nm::Angle::defaultUnit ()
{
    return _defaultUnit;
}
void nm::Angle::setDefaultUnit (nm::Angle::Unit newDefaultUnit)
{
    _defaultUnit = newDefaultUnit;
}


////////////////////////// Operators //////////////////////////


nm::Angle& nm::Angle::operator+= (const nm::Angle& n)
{
    _value += n.value();
    return *this;
}

nm::Angle& nm::Angle::operator-= (const nm::Angle& n)
{
    _value -= n.value();
    return *this;
}

nm::Angle& nm::Angle::operator*= (const double n)
{
    if (n < 0.0)
        throw std::invalid_argument("Exception in nm::Angle::operator*= : invalid coefficient");

    _value *= n;
    return *this;
}

nm::Angle& nm::Angle::operator/= (const double n)
{
    if (n <= 0.0)
        throw std::invalid_argument("Exception in nm::Angle::operator/= : invalid coefficient");

    _value /= n;
    return *this;
}


nm::Angle operator+ (nm::Angle a, const nm::Angle& b)
{
    a += b;
    return a;
}

nm::Angle operator- (nm::Angle a, const nm::Angle& b)
{
    a -= b;
    return a;
}

nm::Angle operator* (nm::Angle a, const double b)
{
    a *= b;
    return a;
}
nm::Angle operator* (const double a, nm::Angle b)
{
    b *= a;
    return b;
}

nm::Angle operator/ (nm::Angle a, const double b)
{
    a /= b;
    return a;
}


nm::Angle operator- (const nm::Angle& n)
{
    return nm::Angle(-n.value());
}


////////////////////////// Circular trigonometric functions //////////////////////////


double sin (const nm::Angle& x)
{
    return std::sin(x.value(nm::Angle::Unit::Radian));
}
nm::Angle nm::asin (const double x)
{
    return nm::Angle(std::asin(x));
}

double cos (const nm::Angle& x)
{
    return std::cos(x.value(nm::Angle::Unit::Radian));
}
nm::Angle nm::acos (const double x)
{
    return nm::Angle(std::acos(x));
}

double tan (const nm::Angle& x)
{
    return std::tan(x.value(nm::Angle::Unit::Radian));
}
nm::Angle nm::atan (const double x)
{
    return nm::Angle(std::atan(x));
}

double cot (const nm::Angle& x)
{
    return 1.0 / std::tan(x.value(nm::Angle::Unit::Radian));
}
nm::Angle nm::acot (const double x)
{
    return nm::Angle(std::atan(1.0 / x));
}

double sec (const nm::Angle& x)
{
    return 1.0 / std::cos(x.value(nm::Angle::Unit::Radian));
}
nm::Angle nm::asec (const double x)
{
    return nm::Angle(std::acos(1.0 / x));
}

double csc (const nm::Angle& x)
{
    return 1.0 / std::sin(x.value(nm::Angle::Unit::Radian));
}
nm::Angle nm::acsc (const double x)
{
    return nm::Angle(std::asin(1.0 / x));
}


////////////////////////// Hyperbolic trigonometric functions //////////////////////////


double sinh (const nm::Angle& x)
{
    return std::sinh(x.value(nm::Angle::Unit::Radian));
}
nm::Angle nm::asinh (const double x)
{
    return nm::Angle(std::asinh(x));
}

double cosh (const nm::Angle& x)
{
    return std::cosh(x.value(nm::Angle::Unit::Radian));
}
nm::Angle nm::acosh (const double x)
{
    return nm::Angle(std::acosh(x));
}

double tanh (const nm::Angle& x)
{
    return std::tanh(x.value(nm::Angle::Unit::Radian));
}
nm::Angle nm::atanh (const double x)
{
    return nm::Angle(std::atanh(x));
}

double coth (const nm::Angle& x)
{
    return 1.0 / std::tanh(x.value(nm::Angle::Unit::Radian));
}
nm::Angle nm::acoth (const double x)
{
    return nm::Angle(std::atanh(1.0 / x));
}

double sech (const nm::Angle& x)
{
    return 1.0 / std::cosh(x.value(nm::Angle::Unit::Radian));
}
nm::Angle nm::asech (const double x)
{
    return nm::Angle(std::acosh(1.0 / x));
}

double csch (const nm::Angle& x)
{
    return 1.0 / std::sinh(x.value(nm::Angle::Unit::Radian));
}
nm::Angle nm::acsch (const double x)
{
    return nm::Angle(std::asinh(1.0 / x));
}

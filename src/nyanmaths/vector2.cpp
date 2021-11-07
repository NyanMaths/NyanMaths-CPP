#include <cmath>
#include <stdexcept>

#include <nyanmaths/vector2.hpp>


////////////////////////// Vector2 members //////////////////////////


nm::Vector2::Vector2 () : _x(0.0), _y(0.0)
{
    // Nothing to be done here
}

nm::Vector2::Vector2 (const double x, const double y) :
    _x(x),
    _y(y)
{
    // Nothing to be done here
}

nm::Vector2::~Vector2 ()
{
    // Nothing to be done here, again
}


double nm::Vector2::x () const
{
    return _x;
}
double nm::Vector2::y () const
{
    return _y;
}

double nm::Vector2::length () const
{
    return sqrt(nm::square(_x) + nm::square(_y));
}


bool nm::Vector2::isNull () const
{
    return _x == 0.0 && _y == 0.0;
}

bool nm::Vector2::isCollinear (const nm::Vector2& n) const
{
    return _x / n.x() == _y / n.y();
}


void nm::Vector2::setX (const double newX)
{
    _x = newX;
}
void nm::Vector2::setY (const double newY)
{
    _y = newY;
}

nm::Error nm::Vector2::setLength (const double newLength)
{
    if (newLength < 0.0)
        return nm::Error::InvalidValue;

    const double currentLength(length());

    if (newLength == currentLength)
        return nm::Error::NoError;

    if (_x == 0.0 && _y == 0.0)
        return nm::Error::ImpossibleScaling;


    const double n(newLength / currentLength);
    _x *= n;
    _y *= n;
    return nm::Error::NoError;
}


////////////////////////// Operators //////////////////////////


nm::Vector2& nm::Vector2::operator+= (const nm::Vector2& n)
{
    _x += n.x();
    _y += n.y();

    return *this;
}

nm::Vector2& nm::Vector2::operator-= (const nm::Vector2& n)
{
    _x -= n.x();
    _y -= n.y();

    return *this;
}

nm::Vector2& nm::Vector2::operator*= (const double n)
{
    _x *= n;
    _y *= n;

    return *this;
}

nm::Vector2& nm::Vector2::operator/= (const double n)
{
    if (n == 0.0)
        throw std::invalid_argument("Exception in nm::Vector2::operator/= : division by zero");

    _x /= n;
    _y /= n;

    return *this;
}


nm::Vector2 operator+ (nm::Vector2 a, const nm::Vector2& b)
{
    a += b;
    return a;
}

nm::Vector2 operator- (nm::Vector2 a, const nm::Vector2& b)
{
    a -= b;
    return a;
}

nm::Vector2 operator- (const nm::Vector2& n)
{
    return nm::Vector2(-n.x(), -n.y());
}

nm::Vector2 operator* (nm::Vector2 a, const double b)
{
    a *= b;
    return a;
}
nm::Vector2 operator* (const double a, nm::Vector2 b)
{
    b *= a;
    return b;
}

double operator* (const nm::Vector2& a, const nm::Vector2& b)
{
    return a.x() * b.x() + a.y() * b.y();
}

nm::Vector2 operator/ (nm::Vector2 a, const double b)
{
    a /= b;
    return a;
}


bool operator== (const nm::Vector2& a, const nm::Vector2& b)
{
    return a.x() == b.x() && a.y() == b.y();
}

bool operator!= (const nm::Vector2& a, const nm::Vector2& b)
{
    return !(a == b);
}


///////////// Stream operator


std::ostream& operator<< (std::ostream& stream, const nm::Vector2& n)
{
    stream<<'('<<n.x()<<' '<<n.y()<<')';

    return stream;
}

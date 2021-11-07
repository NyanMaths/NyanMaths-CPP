#include <cmath>
#include <stdexcept>

#include <nyanmaths/vector3.hpp>


////////////////////////// Vector3 members //////////////////////////


nm::Vector3::Vector3 () : _x(0.0), _y(0.0), _z(0.0)
{
    // Nothing to be done here
}

nm::Vector3::Vector3 (const double x, const double y, const double z) :
    _x(x),
    _y(y),
    _z(z)
{
    // Nothing to be done here
}

nm::Vector3::~Vector3 ()
{
    // Nothing to be done here, again
}


double nm::Vector3::x () const
{
    return _x;
}
double nm::Vector3::y () const
{
    return _y;
}
double nm::Vector3::z () const
{
    return _z;
}

double nm::Vector3::length () const
{
    return sqrt(nm::square(_x) + nm::square(_y) + nm::square(_z));
}


bool nm::Vector3::isNull () const
{
    return _x == 0.0 && _y == 0.0 && _z == 0.0;
}

bool nm::Vector3::isCollinear (const nm::Vector3& n) const
{
    return _x / n.x() == _y / n.y() && _x / n.x() == _z / n.z();
}


void nm::Vector3::setX (const double newX)
{
    _x = newX;
}
void nm::Vector3::setY (const double newY)
{
    _y = newY;
}
void nm::Vector3::setZ (const double newZ)
{
    _z = newZ;
}

nm::Error nm::Vector3::setLength (const double newLength)
{
    if (newLength < 0.0)
        return nm::Error::InvalidValue;

    const double currentLength(length());

    if (newLength == currentLength)
        return nm::Error::NoError;

    if (_x == 0.0 && _y == 0.0 && _z == 0.0)
        return nm::Error::ImpossibleScaling;


    const double n(newLength / currentLength);
    _x *= n;
    _y *= n;
    _z *= n;
    return nm::Error::NoError;
}


////////////////////////// Operators //////////////////////////


nm::Vector3& nm::Vector3::operator+= (const nm::Vector3& n)
{
    _x += n.x();
    _y += n.y();
    _z += n.z();

    return *this;
}

nm::Vector3& nm::Vector3::operator-= (const nm::Vector3& n)
{
    _x -= n.x();
    _y -= n.y();
    _z -= n.z();

    return *this;
}

nm::Vector3& nm::Vector3::operator*= (const double n)
{
    _x *= n;
    _y *= n;
    _z *= n;

    return *this;
}

nm::Vector3& nm::Vector3::operator/= (const double n)
{
    if (n == 0.0)
        throw std::invalid_argument("Exception in nm::Vector3::operator/= : division by zero");

    _x /= n;
    _y /= n;
    _z /= n;

    return *this;
}


nm::Vector3 operator+ (nm::Vector3 a, const nm::Vector3& b)
{
    a += b;
    return a;
}

nm::Vector3 operator- (nm::Vector3 a, const nm::Vector3& b)
{
    a -= b;
    return a;
}

nm::Vector3 operator- (const nm::Vector3& n)
{
    return nm::Vector3(-n.x(), -n.y(), -n.z());
}

nm::Vector3 operator* (nm::Vector3 a, const double b)
{
    a *= b;
    return a;
}
nm::Vector3 operator* (const double a, nm::Vector3 b)
{
    b *= a;
    return b;
}

double operator* (const nm::Vector3& a, const nm::Vector3& b)
{
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

nm::Vector3 operator/ (nm::Vector3 a, const double b)
{
    a /= b;
    return a;
}


bool operator== (const nm::Vector3& a, const nm::Vector3& b)
{
    return a.x() == b.x() && a.y() == b.y() && a.z() == b.z();
}

bool operator!= (const nm::Vector3& a, const nm::Vector3& b)
{
    return !(a == b);
}


///////////// Stream operator


std::ostream& operator<< (std::ostream& stream, const nm::Vector3& n)
{
    stream<<'('<<n.x()<<' '<<n.y()<<' '<<n.z()<<')';

    return stream;
}

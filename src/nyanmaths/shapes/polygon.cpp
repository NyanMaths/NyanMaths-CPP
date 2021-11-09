#include <cmath>
#include <stdexcept>

#include <nyanmaths/shapes/disk.hpp>
#include <nyanmaths/shapes/square.hpp>
#include <nyanmaths/shapes/polygon.hpp>


////////////////////////// Define static const members //////////////////////////


const std::map<uint64_t, std::string> nm::Polygon::names
{
    { 3u, "equilateral triangle" },
    { 4u, "square" },
    { 5u, "pentagon" },
    { 6u, "hexagon" },
    { 7u, "heptagon" },
    { 8u, "octagon" },
    { 9u, "nonagon" },
    { 10u, "decagon" },
    { 11u, "hendecagon" },
    { 12u, "dodecagon" },
    { 13u, "tridecagon" },
    { 14u, "teradecagon" },
    { 15u, "pentadecagon" },
    { 16u, "hexadecagon" },
    { 17u, "heptadecagon" },
    { 18u, "octadecagon" },
    { 19u, "ennadecagon" },
    { 20u, "icosagon" },
    { 30u, "triacontagon" },
    { 40u, "tetracontagon" },
    { 50u, "pentacontagon" },
    { 60u, "hexacontagon" },
    { 70u, "heptacontagon" },
    { 80u, "octacontagon" },
    { 90u, "ennacontagon" },
    { 100u, "hectogon" },
    { 1000u, "chiliagon" },
    { 10000u, "myriagon" },
    { 100000u, "decamyriagon" },
    { 1000000u, "megagon" },
    { 1000000000u, "gigagon" },
    { 1000000000000u, "teragon" },
    { 1000000000000000u, "petagon" },
    { 1000000000000000000u, "exagon" }
    // No more zeros allowed ? Too bad...
};


////////////////////////// Polygon members //////////////////////////


nm::Polygon::Polygon () :
    _numberOfSides(3u),
    _side(defaultMeasurement(metre))
{
    // Nothing to be done here
}

nm::Polygon::Polygon (const uint64_t numberOfSides, const double side, const nm::MeasurementUnit unit) :
    _numberOfSides(numberOfSides),
    _side(nm::convert(side, unit, metre))
{
    if (numberOfSides < 3u)
        throw std::logic_error("Exception in nm::Polygon::Polygon : invalid number of sides");

    if (side < 0.0)
        throw std::invalid_argument("Exception in nm::Polygon::Polygon : invalid side length");
}

nm::Polygon::Polygon (const nm::Square& square) :
    _numberOfSides(4u),
    _side(square.side(metre))
{
    // Nothing to be done here
}

nm::Polygon::~Polygon ()
{
    // Nothing to be done here
}

std::string nm::Polygon::whatIsThis () const
{
    try
    {
        return names.at(_numberOfSides);
    }
    catch (const std::out_of_range&)
    {
        return "regular polygon";
    }
}


uint64_t nm::Polygon::numberOfSides () const
{
    return _numberOfSides;
}

uint64_t nm::Polygon::numberOfDiagonals () const
{
    return 0.5 * _numberOfSides * (_numberOfSides - 3u);
}

double nm::Polygon::side (const nm::MeasurementUnit unit) const
{
    return nm::convert(_side, metre, unit);
}

double nm::Polygon::apothem (const nm::MeasurementUnit unit) const
{
    return nm::convert(_side / tan(nm::consts::pi / _numberOfSides) * 0.5, metre, unit);
}

double nm::Polygon::perimeter (const nm::MeasurementUnit unit) const
{
    return nm::convert(_numberOfSides * _side, metre, unit);
}

double nm::Polygon::surface (const nm::MeasurementUnit unit) const
{
    return nm::convert(apothem() * perimeter() * 0.5, metre, unit, 2u);
}

nm::Disk nm::Polygon::incircle () const
{
    return nm::Disk(apothem());
}

nm::Disk nm::Polygon::circumcircle () const
{
    return nm::Disk(_side * 0.5 / sin(nm::consts::pi / _numberOfSides), metre);
}


nm::Error nm::Polygon::setNumberOfSides (const uint64_t newNumberOfSides)
{
    if (newNumberOfSides < 3u)
        return nm::Error::InvalidValue;

    _numberOfSides = newNumberOfSides;
    return nm::Error::NoError;
}

nm::Error nm::Polygon::setNumberOfDiagonals (const uint64_t newNumberOfDiagonals)
{
    if (nm::square(uint64_t(sqrt(newNumberOfDiagonals * 8u + 9u))) != newNumberOfDiagonals * 8u + 9u)
        return nm::Error::InvalidValue;

    _numberOfSides = (3u + uint64_t(sqrt(newNumberOfDiagonals * 8u + 9u))) / 2u;
    return nm::Error::NoError;
}

nm::Error nm::Polygon::setSide (const double newSide, const nm::MeasurementUnit unit)
{
    if (newSide < 0.0)
        return nm::Error::InvalidMeasurement;

    _side = nm::convert(newSide, unit, metre);
    return nm::Error::NoError;
}

nm::Error nm::Polygon::setApothem (const double newApothem, const nm::MeasurementUnit unit)
{
    if (newApothem < 0.0)
        return nm::Error::InvalidMeasurement;

    _side = nm::convert(newApothem * 2.0 * tan(nm::consts::pi / _numberOfSides), unit, metre);
    return nm::Error::NoError;
}

nm::Error nm::Polygon::setPerimeter (const double newPerimeter, const nm::MeasurementUnit unit)
{
    if (newPerimeter < 0.0)
        return nm::Error::InvalidMeasurement;

    _side = nm::convert(newPerimeter / _numberOfSides, unit, metre);
    return nm::Error::NoError;
}

nm::Error nm::Polygon::setSurface (const double newSurface, const nm::MeasurementUnit unit)
{
    if (newSurface < 0.0)
        return nm::Error::InvalidMeasurement;

    _side = nm::convert(sqrt((tan(nm::consts::pi / _numberOfSides) * newSurface / _numberOfSides)) * 2.0, unit, metre);
    return nm::Error::NoError;
}

void nm::Polygon::setIncircle (const nm::Disk& d)
{
    _side = d.radius(metre) * tan(nm::consts::pi / _numberOfSides) * 2.0;
}

void nm::Polygon::setCircumcircle (const Disk& d)
{
    _side = d.radius(metre) * sin(nm::consts::pi / _numberOfSides) * 2.0;
}


////////////////////////// Operators //////////////////////////


nm::Polygon& nm::Polygon::operator*= (const double n)
{
    if (n < 0.0)
        throw std::invalid_argument("Exception in nm::Polygon::operator*= : invalid coefficient");

    _side *= n;

    return *this;
}

nm::Polygon& nm::Polygon::operator/= (const double n)
{
    if (n <= 0.0)
        throw std::invalid_argument("Exception in nm::Polygon::operator/= : invalid coefficient");

    _side /= n;

    return *this;
}


nm::Polygon operator* (nm::Polygon a, const double n)
{
    a *= n;
    return a;
}
nm::Polygon operator* (const double n, nm::Polygon a)
{
    a *= n;
    return a;
}

nm::Polygon operator/ (nm::Polygon a, const double n)
{
    a *= n;
    return a;
}


bool operator== (const nm::Polygon& a, const nm::Polygon& b)
{
    return a.numberOfSides() == b.numberOfSides() && a.side() == b.side();
}

bool operator!= (const nm::Polygon& a, const nm::Polygon& b)
{
    return !(a == b);
}

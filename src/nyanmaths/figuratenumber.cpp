#include <cmath>
#include <stdexcept>

#include <nyanmaths/figuratenumber.hpp>


////////////////////////// FigurateNumber members //////////////////////////


nm::FigurateNumber::FigurateNumber (uint64_t type, uint64_t index) :
    _type(type),
    _index(index)
{
    if (type < 3u)
        throw std::invalid_argument("Exception in nm::FigurateNumber::FigurateNumber : invalid type");
}

nm::FigurateNumber::~FigurateNumber ()
{
    // Nothing to be done here
}


uint64_t nm::FigurateNumber::type () const
{
    return _type;
}
uint64_t nm::FigurateNumber::index () const
{
    return _index;
}

uint64_t nm::FigurateNumber::value () const
{
    if (_index == 0u)
        return 0u;

    return ((_type - 2u) * nm::square(_index) - (int64_t(_type) - 4) * _index) / 2u;
}


nm::Error nm::FigurateNumber::setType (const uint64_t newType)
{
    if (newType < 3u)
        return nm::Error::InvalidValue;

    _type = newType;
    return nm::Error::NoError;
}

void nm::FigurateNumber::setIndex (const uint64_t newIndex)
{
    _index = newIndex;
}


nm::Error nm::FigurateNumber::setValue (uint64_t newValue)
{
    const long double newIndex((sqrt(8.0 * (_type - 2.0) * newValue + (_type - 4.0) * (_type - 4.0)) + _type - 4.0) / (2.0 * _type - 4.0));

    if (newIndex != floor(newIndex))
        return nm::Error::InvalidValue;


    _index = newIndex;
    return nm::Error::NoError;
}


////////////////////////// Operators //////////////////////////


bool operator== (const nm::FigurateNumber& a, const nm::FigurateNumber& b)
{
    return a.type() == b.type() && a.index() == b.index();
}

bool operator!= (const nm::FigurateNumber& a, const nm::FigurateNumber& b)
{
    return a.type() != b.type() || a.index() != b.index();
}


std::ostream& operator<< (std::ostream& outputStream, const nm::FigurateNumber& n)
{
    outputStream<<n.value();

    return outputStream;
}

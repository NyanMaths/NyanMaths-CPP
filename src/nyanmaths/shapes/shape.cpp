#include <stdexcept>

#include <nyanmaths/shapes/shape.hpp>


////////////////////////// Define static const members //////////////////////////


const std::map<nm::MeasurementUnit::Name, long double> nm::MeasurementUnit::value
{
    { nm::MeasurementUnit::Name::Metre, 1.0 },
    { nm::MeasurementUnit::Name::Inch, 0.0254 },
    { nm::MeasurementUnit::Name::Foot, 0.3048 },
    { nm::MeasurementUnit::Name::Yard, 0.9144 },
    { nm::MeasurementUnit::Name::Mile, 1609.344 },
    { nm::MeasurementUnit::Name::NauticalMile, 1852.0 },
    { nm::MeasurementUnit::Name::League, 4828.032 },
    { nm::MeasurementUnit::Name::PlanckLength, 1.616255e-35 },
    { nm::MeasurementUnit::Name::Angstrom, 10e-10 },
    { nm::MeasurementUnit::Name::UA, 149597870000.0 },
    { nm::MeasurementUnit::Name::LY, 9460730472580800.0 },
    { nm::MeasurementUnit::Name::Parsec, 30856775670528308.0 }
};

nm::MeasurementUnit nm::Shape::_defaultMeasurementUnit(nm::MeasurementUnit::Metre, nm::MeasurementUnit::NoMultiplier);
double nm::Shape::_defaultMeasurement(0.0);

const nm::MeasurementUnit nm::Shape::metre{ nm::MeasurementUnit::Metre, nm::MeasurementUnit::NoMultiplier };


////////////////////////// MeasurementUnit members //////////////////////////


nm::MeasurementUnit::MeasurementUnit () : name(nm::Shape::defaultMeasurementUnit().name), multiplier(nm::Shape::defaultMeasurementUnit().multiplier)
{
    // Nothing to be done here
}

nm::MeasurementUnit::MeasurementUnit (const nm::MeasurementUnit::Name name, const nm::MeasurementUnit::Multiplier multiplier) :
    name(name),
    multiplier(multiplier)
{
    // Nothing to be done here
}

nm::MeasurementUnit::~MeasurementUnit ()
{
    // Nothing to be done here once again
}


////////////////////////// Shape stuff //////////////////////////


nm::Shape::~Shape ()
{
    // Nothing to be done here
}

std::string nm::Shape::whatIsThis () const
{
    return "shape";
}


nm::MeasurementUnit nm::Shape::defaultMeasurementUnit ()
{
    return _defaultMeasurementUnit;
}
void nm::Shape::setDefaultMeasurementUnit (const nm::MeasurementUnit newDefaultMeasurementUnit)
{
    _defaultMeasurementUnit = newDefaultMeasurementUnit;
}

double nm::Shape::defaultMeasurement (const nm::MeasurementUnit unit)
{
    return convert(_defaultMeasurement, metre, unit);
}
nm::Error nm::Shape::setDefaultMeasurement (const double newDefaultMeasurement, const nm::MeasurementUnit unit)
{
    if (newDefaultMeasurement < 0.0)
        return Error::InvalidMeasurement;

    _defaultMeasurement = convert(newDefaultMeasurement, unit, metre);
    return Error::NoError;
}


double nm::Shape::convert (const double value, const nm::MeasurementUnit from, const nm::MeasurementUnit to, const uint64_t dimension)
{
    if (from.name == to.name && from.multiplier == to.multiplier)
        return value;

    return value * nm::power(10.0, dimension * (from.multiplier - to.multiplier)) * nm::power(nm::MeasurementUnit::value.at(from.name) / nm::MeasurementUnit::value.at(to.name), dimension);
}

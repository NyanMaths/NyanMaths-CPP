#include <nyanmaths/shapes/shape.hpp>
#include <nyanmaths/shapes/shape3d.hpp>
#include <nyanmaths/unit.hpp>


////////////////////////// Define static const members //////////////////////////


const std::map<nm::MeasurementUnit::Name, long double> nm::MeasurementUnit::value
{
    { nm::MeasurementUnit::Metre, 1.0l },
    { nm::MeasurementUnit::Inch, 0.0254l },
    { nm::MeasurementUnit::Foot, 0.3048l },
    { nm::MeasurementUnit::Yard, 0.9144l },
    { nm::MeasurementUnit::Mile, 1609.344l },
    { nm::MeasurementUnit::NauticalMile, 1852.0l },
    { nm::MeasurementUnit::League, 4828.032l },
    { nm::MeasurementUnit::PlanckLength, 1.616255e-35l },
    { nm::MeasurementUnit::Angstrom, 10e-10l },
    { nm::MeasurementUnit::UA, 149597870000.0l },
    { nm::MeasurementUnit::LY, 9460730472580800.0l },
    { nm::MeasurementUnit::Parsec, 30856775670528308.0l }
};

const std::map<nm::MassUnit::Name, long double> nm::MassUnit::value
{
    { nm::MassUnit::Gram, 1.0e-3l },
    { nm::MassUnit::Tonne, 1.0e+3l },
    { nm::MassUnit::PlanckMass, 2.18e-8l },
    { nm::MassUnit::SolarMass, 1.98847e+30l },
    { nm::MassUnit::Dalton, 1.66e-27l },
    { nm::MassUnit::Slug, 1.459390e+1l },
    { nm::MassUnit::Pound, 0.45359237l },
};


////////////////////////// Unit members //////////////////////////


nm::Unit::~Unit ()
{
    // Nothing to be done here
}


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


////////////////////////// MassUnit members //////////////////////////


nm::MassUnit::MassUnit () : name(nm::Shape3D::defaultMassUnit().name), multiplier(nm::Shape3D::defaultMassUnit().multiplier)
{
    // Nothing to be done here
}

nm::MassUnit::MassUnit (const nm::MassUnit::Name name, const nm::MassUnit::Multiplier multiplier) :
    name(name),
    multiplier(multiplier)
{
    // Nothing to be done here
}

nm::MassUnit::~MassUnit ()
{
    // Nothing to be done here once again
}


////////////////////////// Conversions //////////////////////////


double nm::convert (const double value, const nm::MeasurementUnit from, const nm::MeasurementUnit to, const uint64_t dimension)
{
    if (from.name == to.name && from.multiplier == to.multiplier)
        return value;

    return value * nm::power(10.0, dimension * (from.multiplier - to.multiplier)) * nm::power(nm::MeasurementUnit::value.at(from.name) / nm::MeasurementUnit::value.at(to.name), dimension);
}

double nm::convert (const double value, const nm::MassUnit from, const nm::MassUnit to)
{
    if (from.name == to.name && from.multiplier == to.multiplier)
        return value;

    return value * nm::power(10.0, from.multiplier - to.multiplier) * nm::MassUnit::value.at(from.name) / nm::MassUnit::value.at(to.name);
}

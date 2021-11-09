#include <stdexcept>

#include <nyanmaths/shapes/shape.hpp>


////////////////////////// Define static const members //////////////////////////


nm::MeasurementUnit nm::Shape::_defaultMeasurementUnit(nm::MeasurementUnit::Metre, nm::MeasurementUnit::No);
double nm::Shape::_defaultMeasurement(0.0);

const nm::MeasurementUnit nm::Shape::metre{ nm::MeasurementUnit::Metre, nm::MeasurementUnit::No };


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
    return nm::convert(_defaultMeasurement, metre, unit);
}
nm::Error nm::Shape::setDefaultMeasurement (const double newDefaultMeasurement, const nm::MeasurementUnit unit)
{
    if (newDefaultMeasurement < 0.0)
        return Error::InvalidMeasurement;

    _defaultMeasurement = nm::convert(newDefaultMeasurement, unit, metre);
    return Error::NoError;
}

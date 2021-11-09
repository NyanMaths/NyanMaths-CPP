#include <nyanmaths/shapes/shape3d.hpp>


nm::Shape3D::~Shape3D ()
{
    // Nothing to be done here
}

std::string nm::Shape3D::whatIsThis () const
{
    return "three-dimensional shape";
}


nm::MassUnit nm::Shape3D::defaultMassUnit ()
{
    return _defaultMassUnit;
}
void nm::Shape3D::setDefaultMassUnit (const nm::MassUnit newDefaultMassUnit)
{
    _defaultMassUnit = newDefaultMassUnit;
}

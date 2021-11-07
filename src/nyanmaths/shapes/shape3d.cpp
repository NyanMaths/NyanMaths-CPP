#include <nyanmaths/shapes/shape3d.hpp>


nm::Shape3D::~Shape3D ()
{
    // Nothing to be done here
}

std::string nm::Shape3D::whatIsThis () const
{
    return "three-dimensional shape";
}

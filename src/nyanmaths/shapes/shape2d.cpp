#include <nyanmaths/shapes/shape2d.hpp>


nm::Shape2D::~Shape2D ()
{
    // Nothing to be done here
}

std::string nm::Shape2D::whatIsThis () const
{
    return "two-dimensional shape";
}

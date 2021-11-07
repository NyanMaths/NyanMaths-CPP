#ifndef SHAPE3D_HPP
#define SHAPE3D_HPP

/*
Here is defined the base class for all tree-dimensional shapes like cubes or prisms.
The aim is to put here everything that is common to all kind of these shapes,
I found the surface and the volume for these ones, but feel free to add more !

Besides, this means that if you make a class inheriting Shape3D, you will need to implement
these properties unless you would get an abstract class.
*/

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/shape.hpp>


namespace nm
{
    class Shape3D : public nm::Shape
    {
        public:
            virtual ~Shape3D() override = 0;

            virtual std::string whatIsThis() const override;


            virtual double surface(nm::MeasurementUnit unit = nm::Shape::defaultMeasurementUnit()) const = 0;
            virtual double volume(nm::MeasurementUnit unit = nm::Shape::defaultMeasurementUnit()) const = 0;

            virtual nm::Error setSurface(double, nm::MeasurementUnit unit = nm::Shape::defaultMeasurementUnit()) = 0;
            virtual nm::Error setVolume(double, nm::MeasurementUnit unit = nm::Shape::defaultMeasurementUnit()) = 0;
    };
}


#endif  // SHAPE3D_HPP

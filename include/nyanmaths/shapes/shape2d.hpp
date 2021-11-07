#ifndef SHAPE2D_HPP
#define SHAPE2D_HPP

/*
Here is defined the base class for all two-dimensional shapes like squares or disks.
The aim is to put here everything that is common to all kind of these shapes,
I found the perimeter and the surface for these ones, but feel free to add more !

Besides, this means that if you make a class inheriting Shape2D, you will need to implement
these properties unless you would get an abstract class.
*/

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/shape.hpp>


namespace nm
{
    class Shape2D : public nm::Shape
    {
        public:
            virtual ~Shape2D() override = 0;

            virtual std::string whatIsThis() const override;


            virtual double perimeter(nm::MeasurementUnit unit = defaultMeasurementUnit()) const = 0;
            virtual double surface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const = 0;

            virtual nm::Error setPerimeter(double, nm::MeasurementUnit unit = defaultMeasurementUnit()) = 0;
            virtual nm::Error setSurface(double, nm::MeasurementUnit unit = defaultMeasurementUnit()) = 0;
    };
}


#endif  // SHAPE2D_HPP

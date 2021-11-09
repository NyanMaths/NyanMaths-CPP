#ifndef SHAPE_HPP
#define SHAPE_HPP

/*
All units-related stuff is declared and/or defined in this header in addition to the base class for shapes.

Feel free to add other units, for example the arm after inches and feet :
you just would need to add an Arm entry to nm::MeasurementUnit::Name enum
and add its value in metres to the nm::MeasurementUnit::value map.
Nothing to change elsewhere, but you will need to rebuild the library.

Here is also defined the base class for all kind of shapes, you should make yours inherit it
or Shape2D/3D, which is more compatibility-friendly. You may not need to write other classes like Shape5D
unless for really specific needs, Shape should do the job rightly.
*/

#include <map>
#include <cinttypes>

#include <nyanmaths/core.hpp>
#include <nyanmaths/unit.hpp>


namespace nm
{
    class Shape
    {
        public:
            virtual ~Shape() = 0;

            virtual std::string whatIsThis() const;


            virtual nm::Shape& operator*=(double) = 0;
            virtual nm::Shape& operator/=(double) = 0;


            static double defaultMeasurement(nm::MeasurementUnit unit = defaultMeasurementUnit());
            static nm::Error setDefaultMeasurement(double, nm::MeasurementUnit unit = defaultMeasurementUnit());

            static nm::MeasurementUnit defaultMeasurementUnit();
            static void setDefaultMeasurementUnit(nm::MeasurementUnit);


        private:
            static nm::MeasurementUnit _defaultMeasurementUnit;
            static double _defaultMeasurement;


        protected:
            // Often used in shapes, use it insthead of instanciating it once again ;-)
            static const nm::MeasurementUnit metre;
    };  /// Class Shape
}  /// Namespace nm


#endif  // SHAPE_HPP

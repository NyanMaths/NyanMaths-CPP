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


namespace nm
{
    class MeasurementUnit
    {
        public:
            enum Name : uint8_t
            {
                Metre,
                Inch,
                Foot,
                Yard,
                Mile,
                NauticalMile,
                League,
                PlanckLength,
                Angstrom,
                UA,
                LY,
                Parsec
            };
            enum Multiplier : int8_t
            {
                Yocto = -24,
                Zepto = -21,
                Atto = -18,
                Femto = -15,
                Pico = -12,
                Nano = -9,
                Micro = -6,
                Milli = -3,
                Centi = -2,
                Deci = -1,
                NoMultiplier = 0,
                Deca = 1,
                Hecto = 2,
                Kilo = 3,
                Mega = 6,
                Giga = 9,
                Tera = 12,
                Peta = 15,
                Exa = 18,
                Zetta = 21,
                Yotta = 24
            };
            static const std::map<MeasurementUnit::Name, long double> value;


            // Constructor
            explicit MeasurementUnit();
            explicit MeasurementUnit(MeasurementUnit::Name, MeasurementUnit::Multiplier multiplier = NoMultiplier);

            virtual ~MeasurementUnit();


            // Data members ; no encapsulation needed
            MeasurementUnit::Name name;
            MeasurementUnit::Multiplier multiplier;
    };


    class Shape
    {
        public:
            virtual ~Shape() = 0;

            virtual std::string whatIsThis() const;


            virtual nm::Shape& operator*=(double) = 0;
            virtual nm::Shape& operator/=(double) = 0;


            static double defaultMeasurement(MeasurementUnit unit = defaultMeasurementUnit());
            static nm::Error setDefaultMeasurement(double, MeasurementUnit unit = defaultMeasurementUnit());

            static nm::MeasurementUnit defaultMeasurementUnit();
            static void setDefaultMeasurementUnit(nm::MeasurementUnit);


        private:
            static nm::MeasurementUnit _defaultMeasurementUnit;
            static double _defaultMeasurement;


        protected:
            static double convert(double, nm::MeasurementUnit, nm::MeasurementUnit, uint64_t dimension = 1);

            // Often used in shapes, use it insthead of instanciating it once again ;-)
            static const nm::MeasurementUnit metre;
    };
}


#endif  // SHAPE_HPP

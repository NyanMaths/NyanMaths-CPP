#ifndef UNIT_HPP
#define UNIT_HPP

#include <cinttypes>
#include <map>


namespace nm
{
    class Unit
    {
        public:
            virtual ~Unit() = 0;

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
                No = 0,
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
    };  /// Class Unit

    class MeasurementUnit : public nm::Unit
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
            static const std::map<nm::MeasurementUnit::Name, long double> value;


            // Constructor
            explicit MeasurementUnit();
            explicit MeasurementUnit(nm::MeasurementUnit::Name, nm::Unit::Multiplier multiplier = nm::Unit::No);

            virtual ~MeasurementUnit() override;


            // Data members ; no encapsulation needed
            nm::MeasurementUnit::Name name;
            nm::Unit::Multiplier multiplier;
    };  /// Class MeasurementUnit

    class MassUnit : public nm::Unit
    {
        public:
            enum Name
            {
                Gram,
                Tonne,
                PlanckMass,
                SolarMass,
                Dalton,
                Slug,
                Pound
            };
            static const std::map<nm::MassUnit::Name, long double> value;


            // Constructor
            explicit MassUnit();
            explicit MassUnit(nm::MassUnit::Name, nm::Unit::Multiplier multiplier = nm::Unit::No);

            virtual ~MassUnit() override;


            // Data members ; no encapsulation needed
            nm::MassUnit::Name name;
            nm::Unit::Multiplier multiplier;
    };  /// Class MassUnit

    double convert(double, nm::MeasurementUnit, nm::MeasurementUnit, uint64_t dimension = 1u);
    double convert(double, nm::MassUnit, nm::MassUnit);
}  /// Namespace nm


#endif  // UNIT_HPP

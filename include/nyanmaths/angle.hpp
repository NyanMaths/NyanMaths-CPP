#ifndef ANGLE_HPP
#define ANGLE_HPP

#include <iostream>
#include <string>

#include <nyanmaths/core.hpp>


namespace nm
{
    class Angle
    {
        public:
            enum class Unit : uint8_t
            {
                Radian,
                Degree,
                Gradian,
                Turn
            };

            explicit Angle();
            explicit Angle(double value, nm::Angle::Unit unit = defaultUnit());

            virtual ~Angle();


            double value(nm::Angle::Unit unit = defaultUnit(), bool mainValue = false) const;
            nm::Error setValue(double newValue, nm::Angle::Unit unit = defaultUnit());


            bool isAcute() const;
            bool isRight() const;
            bool isObtuse() const;
            bool isStraight() const;
            bool isReflex() const;


            nm::Angle& operator+=(const nm::Angle&);
            nm::Angle& operator+=(double);

            nm::Angle& operator-=(const nm::Angle&);
            nm::Angle& operator-=(double);

            nm::Angle& operator*=(double);

            nm::Angle& operator/=(double);


            static nm::Angle::Unit defaultUnit();
            static void setDefaultUnit(nm::Angle::Unit);


        private:
            double _value;

            static nm::Angle::Unit _defaultUnit;
    };  /// Class Angle


    double sin(const nm::Angle&);
    double cos(const nm::Angle&);
    double tan(const nm::Angle&);
    double cot(const nm::Angle&);
    double sec(const nm::Angle&);
    double csc(const nm::Angle&);
    nm::Angle asin(double);
    nm::Angle acos(double);
    nm::Angle atan(double);
    nm::Angle acot(double);
    nm::Angle asec(double);
    nm::Angle acsc(double);

    double sinh(const nm::Angle&);
    double cosh(const nm::Angle&);
    double tanh(const nm::Angle&);
    double coth(const nm::Angle&);
    double sech(const nm::Angle&);
    double csch(const nm::Angle&);
    nm::Angle asinh(double);
    nm::Angle acosh(double);
    nm::Angle atanh(double);
    nm::Angle acoth(double);
    nm::Angle asech(double);
    nm::Angle acsch(double);
}  /// Namespace nm


nm::Angle operator+(nm::Angle, const nm::Angle&);
nm::Angle operator-(nm::Angle, const nm::Angle&);

nm::Angle operator*(nm::Angle, double);
nm::Angle operator*(double, nm::Angle);

nm::Angle operator/(nm::Angle, double);

nm::Angle operator-(const nm::Angle&);


#endif  // ANGLE_HPP

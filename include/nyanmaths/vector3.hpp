#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <iostream>

#include <nyanmaths/core.hpp>
#include <nyanmaths/vector.hpp>


namespace nm
{
    class Vector3 : public nm::Vector
    {
        public:
            explicit Vector3();
            explicit Vector3(double x, double y, double z);

            virtual ~Vector3() override;


            double x() const;
            double y() const;
            double z() const;
            double length() const override;

            void setX(double newX);
            void setY(double newY);
            void setZ(double newY);
            virtual nm::Error setLength(double newLength) override;

            virtual bool isNull() const override;
            bool isCollinear(const nm::Vector3& mayBeCollinear) const;


            nm::Vector3& operator+=(const nm::Vector3&);
            nm::Vector3& operator-=(const nm::Vector3&);
            nm::Vector3& operator*=(double);
            nm::Vector3& operator/=(double);


        private:
            double _x;
            double _y;
            double _z;
    };  /// Class Vector3
}  /// Namespace nm


nm::Vector3 operator+(nm::Vector3&, const nm::Vector3&);

nm::Vector3 operator-(nm::Vector3&, const nm::Vector3&);

nm::Vector3 operator-(const nm::Vector3&);

nm::Vector3 operator*(nm::Vector3, double);
nm::Vector3 operator*(double, nm::Vector3);

double operator*(const nm::Vector3&, const nm::Vector3&);

nm::Vector3 operator/(const nm::Vector3&, double);


bool operator==(const nm::Vector3&, const nm::Vector3&);
bool operator!=(const nm::Vector3&, const nm::Vector3&);


std::ostream& operator<<(std::ostream&, const nm::Vector3&);


#endif  // VECTOR3_HPP

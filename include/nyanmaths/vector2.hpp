#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <iostream>

#include <nyanmaths/core.hpp>


namespace nm
{
    class Vector2
    {
        public:
            explicit Vector2();
            explicit Vector2(double x, double y);

            virtual ~Vector2();


            double x() const;
            double y() const;
            double length() const;

            void setX(double newX);
            void setY(double newY);
            nm::Error setLength(double newLength);

            bool isNull() const;
            bool isCollinear(const nm::Vector2& mayBeCollinear) const;


            nm::Vector2& operator+=(const nm::Vector2&);
            nm::Vector2& operator-=(const nm::Vector2&);
            nm::Vector2& operator*=(double);
            nm::Vector2& operator/=(double);


        private:
            double _x;
            double _y;
    };  /// Class Vector2
}  /// Namespace nm


nm::Vector2 operator+(nm::Vector2, const nm::Vector2&);

nm::Vector2 operator-(nm::Vector2, const nm::Vector2&);

nm::Vector2 operator-(const nm::Vector2&);

nm::Vector2 operator*(nm::Vector2, double);
nm::Vector2 operator*(double, nm::Vector2);

double operator*(const nm::Vector2&, const nm::Vector2&);

nm::Vector2 operator/(nm::Vector2, double);


bool operator==(const nm::Vector2&, const nm::Vector2&);
bool operator!=(const nm::Vector2&, const nm::Vector2&);


std::ostream& operator<<(std::ostream&, const nm::Vector2&);


#endif  // VECTOR2_HPP

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/shape2d.hpp>


namespace nm
{
    class Disk;
    class Square;

    class Rectangle : public nm::Shape2D
    {
        public:
            explicit Rectangle();
            explicit Rectangle(double length, double width, nm::MeasurementUnit unit = defaultMeasurementUnit());
            explicit Rectangle(double side, nm::MeasurementUnit unit = defaultMeasurementUnit());
            explicit Rectangle(const nm::Square& square);

            virtual ~Rectangle() override;

            virtual std::string whatIsThis() const override;


            double length(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double width(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double diagonal(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            virtual double perimeter(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            virtual double surface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            nm::Disk circumcircle() const;

            virtual nm::Error setLength(double newLength, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setWidth(double newWidth, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setDiagonal(double newDiagonal, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setPerimeter(double newPerimeter, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setSurface(double newSurface, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setCircumcircle(const nm::Disk& newCircumcircle);

            bool isGolden() const;
            bool isSquare() const;


            virtual nm::Rectangle& operator*=(double) override;
            virtual nm::Rectangle& operator/=(double) override;

        protected:
            double _length;
            double _width;
    };  /// Class Rectangle
}  /// Namespace nm


nm::Rectangle operator*(nm::Rectangle, double);
nm::Rectangle operator*(double, nm::Rectangle);
nm::Rectangle operator/(nm::Rectangle, double);

bool operator==(const nm::Rectangle&, const nm::Rectangle&);
bool operator!=(const nm::Rectangle&, const nm::Rectangle&);


#endif  // RECTANGLE_HPP

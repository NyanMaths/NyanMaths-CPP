#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/rectangle.hpp>


namespace nm
{
    class Disk;
    class Rectangle;

    class Square : public nm::Rectangle
    {
        public:
            explicit Square();
            explicit Square(double side, nm::MeasurementUnit unit = defaultMeasurementUnit());
            explicit Square(const nm::Rectangle& rectangle);

            virtual ~Square() override;

            virtual std::string whatIsThis() const override;


            double side(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double apothem(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double diagonal(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            virtual double perimeter(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            virtual double surface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            nm::Disk incircle() const;

            virtual nm::Error setLength(double newLength, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setWidth(double newWidth, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            nm::Error setSide(double newSide, nm::MeasurementUnit unit = defaultMeasurementUnit());
            nm::Error setApothem(double newApothem, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setDiagonal(double newDiagonal, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setPerimeter(double newPerimeter, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setSurface(double newSurface, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            void setIncircle(const nm::Disk& newIncircle);


            virtual nm::Square& operator*=(double) override;
            virtual nm::Square& operator/=(double) override;
    };  /// Class Square
}  /// Namespace nm


nm::Square operator* (nm::Square, double);
nm::Square operator* (double, nm::Square);
nm::Square operator/ (nm::Square, double);

bool operator== (const nm::Square&, const nm::Square&);
bool operator!= (const nm::Square&, const nm::Square&);


#endif  // SQUARE_HPP

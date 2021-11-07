#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/shape2d.hpp>


namespace nm
{
    class Disk;

    class Ellipse : public nm::Shape2D
    {
        public:
            explicit Ellipse();
            explicit Ellipse(double a, double b, nm::MeasurementUnit unit = defaultMeasurementUnit());
            explicit Ellipse(double radius, nm::MeasurementUnit unit = defaultMeasurementUnit());
            explicit Ellipse(const nm::Disk& disk);

            virtual ~Ellipse() override;

            virtual std::string whatIsThis() const override;


            double a(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double b(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            virtual double perimeter(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            virtual double surface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;

            virtual nm::Error setA(double newA, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setB(double newB, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setPerimeter(double newPerimeter, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setSurface(double newSurface, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;

            double linearEccentricity() const;
            double eccentricity() const;
            bool isDisk() const;


            virtual nm::Ellipse& operator*=(double) override;
            virtual nm::Ellipse& operator/=(double) override;


        protected:
            double _a;
            double _b;
    };  /// Class Ellipse
}  /// Namespace nm


nm::Ellipse operator*(nm::Ellipse, double);
nm::Ellipse operator*(double, nm::Ellipse);
nm::Ellipse operator/(nm::Ellipse, double);

bool operator==(const nm::Ellipse&, const nm::Ellipse&);
bool operator!=(const nm::Ellipse&, const nm::Ellipse&);


#endif  // ELLIPSE_HPP

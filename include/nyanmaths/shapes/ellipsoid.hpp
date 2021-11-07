#ifndef ELLIPSOID_HPP
#define ELLIPSOID_HPP

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/shape3d.hpp>


namespace nm
{
    class Ball;

    class Ellipsoid : public nm::Shape3D
    {
        public:
            explicit Ellipsoid();
            explicit Ellipsoid(double a, double b, double c, nm::MeasurementUnit unit = defaultMeasurementUnit());
            explicit Ellipsoid(double radius, nm::MeasurementUnit unit = defaultMeasurementUnit());
            explicit Ellipsoid(const nm::Ball& ball);

            virtual ~Ellipsoid() override;

            virtual std::string whatIsThis() const override;


            double a(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double b(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double c(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            virtual double surface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            virtual double volume(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;

            virtual nm::Error setA(double newA, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setB(double newB, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setC(double newC, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setSurface(double newSurface, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setVolume(double newVolume, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;

            bool isBall() const;


            virtual nm::Ellipsoid& operator*=(double) override;
            virtual nm::Ellipsoid& operator/=(double) override;


        protected:
            double _a;
            double _b;
            double _c;
    };  /// Class Ellipsoid
}  /// Namespace nm


nm::Ellipsoid operator*(nm::Ellipsoid, double);
nm::Ellipsoid operator*(double, nm::Ellipsoid);
nm::Ellipsoid operator/(nm::Ellipsoid, double);

bool operator==(const nm::Ellipsoid&, const nm::Ellipsoid&);
bool operator!=(const nm::Ellipsoid&, const nm::Ellipsoid&);


#endif  // ELLIPSOID_HPP

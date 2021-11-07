#ifndef BALL_HPP
#define BALL_HPP

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/ellipsoid.hpp>


namespace nm
{
    class Ball : public nm::Ellipsoid
    {
        public:
            explicit Ball();
            explicit Ball(double radius, nm::MeasurementUnit unit = defaultMeasurementUnit());
            explicit Ball(const nm::Ellipsoid& ellipsoid);

            virtual ~Ball() override;

            virtual std::string whatIsThis() const override;


            double radius(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double diameter(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            virtual double surface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            virtual double volume(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;

            virtual nm::Error setA(double newA, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setB(double newB, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setC(double newC, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            nm::Error setRadius(double newRadius, nm::MeasurementUnit unit = defaultMeasurementUnit());
            nm::Error setDiameter(double newDiameter, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setSurface(double newSurface, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setVolume(double newVolume, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;


            virtual nm::Ball& operator*=(double) override;
            virtual nm::Ball& operator/=(double) override;
    };  /// Class Ball
}  /// Namespace nm


nm::Ball operator*(nm::Ball, double);
nm::Ball operator*(double, nm::Ball);
nm::Ball operator/(nm::Ball, double);

bool operator==(const nm::Ball&, const nm::Ball&);
bool operator!=(const nm::Ball&, const nm::Ball&);


#endif  // BALL_HPP

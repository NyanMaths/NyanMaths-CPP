#ifndef CAPSULE_HPP
#define CAPSULE_HPP

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/shape3d.hpp>


namespace nm
{
    class Ball;
    class Cylinder;

    class Capsule : public nm::Shape3D
    {
        public:
            explicit Capsule();
            explicit Capsule(double radius, double length, nm::MeasurementUnit unit = defaultMeasurementUnit());
            explicit Capsule(const nm::Cylinder& trunk);
            explicit Capsule(const nm::Ball& ball);

            virtual ~Capsule() override;

            virtual std::string whatIsThis() const override;


            double radius(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double diameter(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double length(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            nm::Cylinder trunk() const;
            double tipSurface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            virtual double surface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            double tipVolume(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            virtual double volume(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;

            nm::Error setRadius(double newRadius, nm::MeasurementUnit unit = defaultMeasurementUnit());
            nm::Error setDiameter(double newDiameter, nm::MeasurementUnit unit = defaultMeasurementUnit());
            nm::Error setLength(double newLength, nm::MeasurementUnit unit = defaultMeasurementUnit());
            void setTrunk(const nm::Cylinder& newTrunk);
            nm::Error setTipSurface(double newTipSurface, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setSurface(double newSurface, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            nm::Error setTipVolume(double newTipVolume, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setVolume(double newVolume, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;

            bool isBall() const;


            virtual Capsule& operator*=(double) override;
            virtual Capsule& operator/=(double) override;


        protected:
            double _radius;
            double _length;
    };  /// Class Capsule
}  /// Namespace nm


nm::Capsule operator*(nm::Capsule, double);
nm::Capsule operator*(double, nm::Capsule);
nm::Capsule operator/(nm::Capsule, double);

bool operator==(const nm::Capsule&, const nm::Capsule&);
bool operator!=(const nm::Capsule&, const nm::Capsule&);


#endif  // CAPSULE_HPP

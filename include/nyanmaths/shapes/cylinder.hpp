#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/shape3d.hpp>


namespace nm
{
    class Disk;

    class Cylinder : public nm::Shape3D
    {
        public:
            explicit Cylinder();
            explicit Cylinder(double radius, double height = defaultMeasurement(), nm::MeasurementUnit unit = defaultMeasurementUnit());

            virtual ~Cylinder() override;

            virtual std::string whatIsThis() const override;


            double radius(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            nm::Disk base() const;
            double height(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double lateralSurface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            virtual double surface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            virtual double volume(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;

            nm::Error setRadius(double newRadius, nm::MeasurementUnit unit = defaultMeasurementUnit());
            void setBase(const nm::Disk& newBase);
            nm::Error setHeight(double newHeight, nm::MeasurementUnit unit = defaultMeasurementUnit());
            nm::Error setLateralSurface(double newLateralSurface, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setSurface(double newSurface, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setVolume(double newVolume, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;


            virtual Cylinder& operator*=(double) override;
            virtual Cylinder& operator/=(double) override;


        protected:
            double _radius;
            double _height;
    };  /// Class Cylinder
}  /// Namespace nm


nm::Cylinder operator*(nm::Cylinder, double);
nm::Cylinder operator*(double, nm::Cylinder);
nm::Cylinder operator/(nm::Cylinder, double);

bool operator==(const nm::Cylinder&, const nm::Cylinder&);
bool operator!=(const nm::Cylinder&, const nm::Cylinder&);


#endif  // CYLINDER_HPP

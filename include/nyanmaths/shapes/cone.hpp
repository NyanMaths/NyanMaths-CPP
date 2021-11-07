#ifndef CONE_HPP
#define CONE_HPP

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/shape3d.hpp>


namespace nm
{
    class Disk;

    class Cone : nm::Shape3D
    {
        public:
            explicit Cone();
            explicit Cone(double radius, double height, nm::MeasurementUnit unit = defaultMeasurementUnit());
            explicit Cone(const nm::Disk& base, double height, nm::MeasurementUnit unit = defaultMeasurementUnit());

            virtual ~Cone() override;

            virtual std::string whatIsThis() const override;


            double radius(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double diameter(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            nm::Disk base() const;
            double height(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double slantHeight(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double lateralSurface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            virtual double surface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            virtual double volume(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;

            nm::Error setRadius(double newRadius, nm::MeasurementUnit unit = defaultMeasurementUnit());
            nm::Error setDiameter(double newDiameter, nm::MeasurementUnit unit = defaultMeasurementUnit());
            void setBase(const nm::Disk& newBase);
            nm::Error setHeight(double newHeight, nm::MeasurementUnit unit = defaultMeasurementUnit());
            nm::Error setSlantHeight(double newSlantHeight, nm::MeasurementUnit unit = defaultMeasurementUnit());
            nm::Error setLateralSurface(double newLateralSurface, nm::MeasurementUnit unit = defaultMeasurementUnit());
            nm::Error setSurface(double newSurface, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            nm::Error setVolume(double newVolume, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;


            virtual Cone& operator*=(double) override;
            virtual Cone& operator/=(double) override;


        protected:
            double _radius;
            double _height;
    };  /// Class Cone
}  /// Namespace nm


nm::Cone operator*(nm::Cone, double);
nm::Cone operator*(double, nm::Cone);
nm::Cone operator/(nm::Cone, double);

bool operator==(const nm::Cone&, const nm::Cone&);
bool operator!=(const nm::Cone&, const nm::Cone&);


#endif  // CONE_HPP

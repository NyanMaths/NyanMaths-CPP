#ifndef DISK_HPP
#define DISK_HPP

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/ellipse.hpp>


namespace nm
{
    class Disk : public nm::Ellipse
    {
        public:
            explicit Disk();
            explicit Disk(double radius, nm::MeasurementUnit unit = defaultMeasurementUnit());
            explicit Disk(const nm::Ellipse& ellipse);

            virtual ~Disk() override;

            virtual std::string whatIsThis() const override;


            double radius(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double diameter(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            virtual double perimeter(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            virtual double surface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;

            virtual nm::Error setA(double newA, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setB(double newB, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            nm::Error setRadius(double newRadius, nm::MeasurementUnit unit = defaultMeasurementUnit());
            nm::Error setDiameter(double newDiameter, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setPerimeter(double newPerimeter, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setSurface(double newSurface, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;


            virtual nm::Disk& operator*=(double) override;
            virtual nm::Disk& operator/=(double) override;
    };  /// Class Disk
}  /// Namespace nm


nm::Disk operator*(nm::Disk, double);
nm::Disk operator*(double, nm::Disk);
nm::Disk operator/(nm::Disk, double);

bool operator==(const nm::Disk&, const nm::Disk&);
bool operator!=(const nm::Disk&, const nm::Disk&);


#endif  // DISK_HPP

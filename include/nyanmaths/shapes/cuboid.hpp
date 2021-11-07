#ifndef CUBOID_HPP
#define CUBOID_HPP

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/shape3d.hpp>


namespace nm
{
    class Cube;
    class Ellipsoid;
    class Ball;

    class Cuboid : public nm::Shape3D
    {
        public:
            explicit Cuboid();
            explicit Cuboid(double length, double width, double height, nm::MeasurementUnit unit = defaultMeasurementUnit());
            explicit Cuboid(double edge, nm::MeasurementUnit unit = defaultMeasurementUnit());
            explicit Cuboid(const nm::Cube& cube);

            virtual ~Cuboid() override;

            virtual std::string whatIsThis() const override;


            double length(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double width(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double height(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            virtual double diagonal(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            virtual double surface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            virtual double volume(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            nm::Ellipsoid inscribedEllipsoid() const;
            nm::Ball circumsphere() const;

            virtual nm::Error setLength(double newLength, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setWidth(double newWidth, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setHeight(double newHeight, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setDiagonal(double newDiagonal, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setSurface(double newSurface, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setVolume(double newVolume, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual void setInscribedEllipsoid(const nm::Ellipsoid& newInscribedEllipsoid);
            virtual nm::Error setCircumsphere(const nm::Ball& newCircumsphere);

            bool isCube() const;


            virtual nm::Cuboid& operator*=(double) override;
            virtual nm::Cuboid& operator/=(double) override;


        protected:
            double _length;
            double _width;
            double _height;
    };  /// Class Cuboid
}  /// Namespace nm


nm::Cuboid operator*(nm::Cuboid, double);
nm::Cuboid operator*(double, nm::Cuboid);
nm::Cuboid operator/(nm::Cuboid, double);

bool operator==(const nm::Cuboid&, const nm::Cuboid&);
bool operator!=(const nm::Cuboid&, const nm::Cuboid&);


#endif  // CUBOID_HPP

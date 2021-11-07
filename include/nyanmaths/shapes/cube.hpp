#ifndef CUBE_HPP
#define CUBE_HPP

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/cuboid.hpp>


namespace nm
{
    class Square;
    class Ball;

    class Cube : public nm::Cuboid
    {
        public:
            explicit Cube();
            explicit Cube(double edge, nm::MeasurementUnit unit = defaultMeasurementUnit());
            explicit Cube(const nm::Cuboid& cuboid);

            virtual ~Cube() override;

            virtual std::string whatIsThis() const override;


            double edge(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            virtual double diagonal(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            virtual double surface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            nm::Ball insphere() const;
            nm::Square face() const;

            virtual nm::Error setLength(double newLength, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setWidth(double newWidth, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setHeight(double newHeight, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            nm::Error setEdge(double newEdge, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setDiagonal(double newDiagonal, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setSurface(double newSurface, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setVolume(double newVolume, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            void setInsphere(const nm::Ball& newInsphere);
            void setFace(const nm::Square& newFace);


            virtual nm::Cube& operator*=(double) override;
            virtual nm::Cube& operator/=(double) override;
    };  /// Class Cube
}  /// Namespace nm


nm::Cube operator*(nm::Cube, double);
nm::Cube operator*(double, nm::Cube);
nm::Cube operator/(nm::Cube, double);

bool operator==(const nm::Cube&, const nm::Cube&);
bool operator!=(const nm::Cube&, const nm::Cube&);


#endif  // CUBE_HPP

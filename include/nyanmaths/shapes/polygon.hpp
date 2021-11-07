#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/shape2d.hpp>


namespace nm
{
    class Disk;
    class Square;

    class Polygon : public nm::Shape2D
    {
        public:
            explicit Polygon();
            explicit Polygon(uint64_t numberOfSides, double side, nm::MeasurementUnit unit = defaultMeasurementUnit());
            explicit Polygon(const nm::Square&);

            virtual ~Polygon() override;

            virtual std::string whatIsThis() const override;


            uint64_t numberOfSides() const;
            uint64_t numberOfDiagonals() const;
            double side(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double apothem(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            virtual double perimeter(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            virtual double surface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            nm::Disk incircle() const;
            nm::Disk circumcircle() const;

            nm::Error setNumberOfSides(uint64_t newNumberOfSides);
            nm::Error setNumberOfDiagonals(uint64_t newNumberOfDiagonals);
            nm::Error setSide(double newSide, nm::MeasurementUnit unit = defaultMeasurementUnit());
            nm::Error setApothem(double newApothem, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setPerimeter(double newPerimeter, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setSurface(double newSurface, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            void setIncircle(const nm::Disk& newIncircle);
            void setCircumcircle(const nm::Disk& newCircumcircle);


            virtual nm::Polygon& operator*=(double) override;
            virtual nm::Polygon& operator/=(double) override;


        protected:
            uint64_t _numberOfSides;
            double _side;

        private:
            static const std::map<uint64_t, std::string> names;
    };  /// Class Polygon
}  /// Namespace nm


nm::Polygon operator*(nm::Polygon, double);
nm::Polygon operator*(double, nm::Polygon);
nm::Polygon operator/(nm::Polygon, double);

bool operator==(const nm::Polygon&, const nm::Polygon&);
bool operator!=(const nm::Polygon&, const nm::Polygon&);


#endif  // POLYGON_HPP

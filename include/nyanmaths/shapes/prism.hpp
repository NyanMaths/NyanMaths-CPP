#ifndef PRISM_HPP
#define PRISM_HPP

#include <nyanmaths/core.hpp>
#include <nyanmaths/shapes/shape3d.hpp>


namespace nm
{
    class Shape2D;

    class Prism : public nm::Shape3D
    {
        public:
            explicit Prism(nm::Shape2D*, double height = defaultMeasurement(metre), nm::MeasurementUnit unit = defaultMeasurementUnit());

            virtual ~Prism() override;

            virtual std::string whatIsThis() const override;


            virtual nm::Shape2D* base() const;
            double height(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            double lateralSurface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const;
            virtual double surface(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;
            virtual double volume(nm::MeasurementUnit unit = defaultMeasurementUnit()) const override;

            virtual void setBase(nm::Shape2D*);
            nm::Error setHeight(double, nm::MeasurementUnit unit = defaultMeasurementUnit());
            nm::Error setLateralSurface(double, nm::MeasurementUnit unit = defaultMeasurementUnit());
            virtual nm::Error setSurface(double, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;
            virtual nm::Error setVolume(double, nm::MeasurementUnit unit = defaultMeasurementUnit()) override;


            virtual Prism& operator*=(double) override;
            virtual Prism& operator/=(double) override;


        protected:
            nm::Shape2D* _base;
            double _height;
    };  /// Class Prism
}  /// Namespace nm


nm::Prism operator*(nm::Prism, double);
nm::Prism operator*(double, nm::Prism);
nm::Prism operator/(nm::Prism, double);


#endif  // PRISM_HPP

#ifndef LINEARFUNCTION_HPP
#define LINEARFUNCTION_HPP

#include <iostream>
#include <string>
#include <complex>

#include <nyanmaths/core.hpp>
#include <nyanmaths/functions/function.hpp>
;

namespace nm
{
    class Quadratic;

    class LinearFunction : public nm::Function
    {
        public:
            enum class Form : uint8_t
            {
                SLOPE_INTERCEPT,
                POINT_SLOPE,
                FACTORED
            };

            explicit LinearFunction();
            explicit LinearFunction(double a, double b);

            virtual ~LinearFunction() override;


            double a() const;
            double b() const;

            nm::Error setA(double newA);
            void setB(double newB);


            virtual std::string asString() const override;
            std::string asString(nm::LinearFunction::Form form, double point = 0.0) const;
            virtual double exec(double x) const override;
            virtual std::complex<double> exec(const std::complex<double>& x) const override;

            virtual std::string derivativeAsString() const override;
            double derivative() const;
            virtual double execDerivative(double x) const override;
            virtual std::complex<double> execDerivative(const std::complex<double>& x) const override;

            virtual std::string secondDerivativeAsString() const override;
            double secondDerivative() const;
            virtual double execSecondDerivative(double x) const override;
            virtual std::complex<double> execSecondDerivative(const std::complex<double>& x) const override;

            virtual std::string antiderivativeAsString(double constant = 0.0) const override;
            nm::Quadratic antiderivative(double constant = 0.0) const;
            virtual double execAntiderivative(double x, double constant = 0.0) const override;
            virtual std::complex<double> execAntiderivative(const std::complex<double>& x, double constant = 0.0) const override;


            double root() const;
            virtual std::vector<double> roots() const override;
            virtual std::vector<std::complex<double>> complexRoots() const override;

            virtual double integral(double from, double to) const override;

            virtual nm::LinearFunction tangent(double x) const override;  // I was just worried about performances


            nm::LinearFunction& operator+=(const nm::LinearFunction&);
            nm::LinearFunction& operator+=(double);

            nm::LinearFunction& operator-=(const nm::LinearFunction&);
            nm::LinearFunction& operator-=(double);

            nm::LinearFunction& operator*=(double);

            nm::LinearFunction& operator/=(double);


            static nm::LinearFunction::Form preferredForm();
            static void setPreferredForm(nm::LinearFunction::Form newPreferredForm);


        protected:
            double _a;
            double _b;

            static nm::LinearFunction::Form _preferredForm;
    };  /// Class LinearFunction
}  /// Namespace nm



nm::LinearFunction operator+(nm::LinearFunction, const nm::LinearFunction&);
nm::LinearFunction operator+(nm::LinearFunction, double);
nm::LinearFunction operator+(double, nm::LinearFunction);
nm::Quadratic operator+(const nm::LinearFunction&, nm::Quadratic);

nm::LinearFunction operator-(nm::LinearFunction, const nm::LinearFunction&);
nm::LinearFunction operator-(nm::LinearFunction, double);
nm::LinearFunction operator-(double, nm::LinearFunction);
nm::Quadratic operator-(const nm::LinearFunction&, const nm::Quadratic&);

nm::LinearFunction operator-(const nm::LinearFunction&);

nm::Quadratic operator*(const nm::LinearFunction&, const nm::LinearFunction&);
nm::LinearFunction operator*(nm::LinearFunction, double);
nm::LinearFunction operator*(double, nm::LinearFunction);

nm::LinearFunction operator/(nm::LinearFunction, double);


bool operator<(const nm::LinearFunction&, const nm::LinearFunction&);
bool operator<(const nm::LinearFunction&, const nm::Quadratic&);

bool operator<=(const nm::LinearFunction&, const nm::LinearFunction&);
bool operator<=(const nm::LinearFunction&, const nm::Quadratic&);

bool operator==(const nm::LinearFunction&, const nm::LinearFunction&);
bool operator!=(const nm::LinearFunction&, const nm::LinearFunction&);

bool operator>=(const nm::LinearFunction&, const nm::LinearFunction&);
bool operator>=(const nm::LinearFunction&, const nm::Quadratic&);

bool operator>(const nm::LinearFunction&, const nm::LinearFunction&);
bool operator>(const nm::LinearFunction&, const nm::Quadratic&);


std::ostream& operator<< (std::ostream&, const nm::LinearFunction&);


#endif  // LINEARFUNCTION_HPP

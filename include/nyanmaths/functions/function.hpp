#ifndef FUNCTION_HPP
#define FUNCTION_HPP


#include <vector>
#include <complex>
#include <string>


namespace nm
{
    class LinearFunction;

    class Function
    {
        public:
            virtual ~Function();

            virtual std::vector<double> roots() const = 0;
            virtual std::vector<std::complex<double>> complexRoots() const = 0;


            virtual std::string asString() const = 0;
            virtual double exec(double x) const = 0;
            double operator()(double x) const;
            virtual std::complex<double> exec(const std::complex<double>& x) const = 0;
            std::complex<double> operator()(const std::complex<double>& x) const;

            virtual std::string derivativeAsString() const = 0;
            virtual double execDerivative(double x) const = 0;
            virtual std::complex<double> execDerivative(const std::complex<double>& x) const = 0;

            virtual std::string secondDerivativeAsString() const = 0;
            virtual double execSecondDerivative(double x) const = 0;
            virtual std::complex<double> execSecondDerivative(const std::complex<double>& x) const = 0;

            virtual std::string antiderivativeAsString(double constant = 0.0) const = 0;
            virtual double execAntiderivative(double x, double constant = 0.0) const = 0;
            virtual std::complex<double> execAntiderivative(const std::complex<double>& x, double constant = 0.0) const = 0;

            virtual double integral(double from, double to) const = 0;

            virtual nm::LinearFunction tangent(double x) const;
    };
}


#endif  // FUNCTION_HPP

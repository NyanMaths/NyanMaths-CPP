#ifndef QUADRATIC_HPP
#define QUADRATIC_HPP

#include <iostream>
#include <string>
#include <complex>

#include <nyanmaths/core.hpp>
#include <nyanmaths/functions/function.hpp>
#include <nyanmaths/functions/linearfunction.hpp>


namespace nm
{
    class Quadratic : public nm::Function
    {
        public:
            enum class Form : uint8_t
            {
                EXPANDED,
                VERTEX,
                FACTORED
            };

            explicit Quadratic();
            explicit Quadratic(double a, double b, double c);

            virtual ~Quadratic() override;


            double a() const;
            double b() const;
            double c() const;

            nm::Error setA(double newA);
            void setB(double newB);
            void setC(double newC);

            nm::Error setExpandedForm(double newA, double newB, double newC);
            nm::Error setVertexForm(double newA, double newAlpha, double newBeta);
            nm::Error setFactoredForm(double newA, double newRoot1, double newRoot2);
            nm::Error setFactoredForm(double newA, const std::complex<double>& newRoot1, const std::complex<double>& newRoot2);


            virtual std::string asString() const override;
            std::string asString(nm::Quadratic::Form form) const;
            virtual double exec(double x) const override;
            virtual std::complex<double> exec(const std::complex<double>& x) const override;

            virtual std::string derivativeAsString() const override;
            std::string derivativeAsString(LinearFunction::Form form) const;
            nm::LinearFunction derivative() const;
            virtual double execDerivative(double x) const override;
            virtual std::complex<double> execDerivative(const std::complex<double>& x) const override;
            void setDerivative(const LinearFunction& newDerivative);

            virtual std::string secondDerivativeAsString() const override;
            double secondDerivative() const;
            virtual double execSecondDerivative(double x) const override;
            virtual std::complex<double> execSecondDerivative(const std::complex<double>& x) const override;
            void setSecondDerivative(double newSecondDerivative);

            virtual std::string antiderivativeAsString(double constant = 0.0) const override;
            virtual double execAntiderivative(double x, double constant = 0.0) const override;
            virtual std::complex<double> execAntiderivative(const std::complex<double>& x, double constant = 0.0) const override;
            nm::Error setAntiderivative(double newAntiderivativeA, double newAntiderivativeB, double newAntiderivativeC);


            uint8_t numberOfRealRoots() const;
            virtual std::vector<double> roots() const override;
            virtual std::vector<std::complex<double>> complexRoots() const override;
            double rootsSummation() const;
            double rootsProduct() const;

            double alpha() const;
            double beta() const;
            double delta() const;
            double reducedDelta() const;

            virtual double integral(double from, double to) const override;


            nm::Quadratic& operator+=(const nm::Quadratic&);
            nm::Quadratic& operator+=(const nm::LinearFunction&);
            nm::Quadratic& operator+=(double);

            nm::Quadratic& operator-=(const nm::Quadratic&);
            nm::Quadratic& operator-=(const nm::LinearFunction&);
            nm::Quadratic& operator-=(double);

            nm::Quadratic& operator*=(double);

            nm::Quadratic& operator/=(double);


            static nm::Quadratic::Form preferredForm();
            static void setPreferredForm(nm::Quadratic::Form newPreferredForm);


        protected:
            double _a;
            double _b;
            double _c;

            // These three just exist in order to split asString()
            std::string expandedForm() const;
            std::string vertexForm() const;
            std::string factoredForm() const;

            static nm::Quadratic::Form _preferredForm;
    };  /// Class Quadratic
}  /// Namespace nm


nm::Quadratic operator+(nm::Quadratic, const nm::Quadratic&);
nm::Quadratic operator+(nm::Quadratic, const nm::LinearFunction&);
nm::Quadratic operator+(nm::Quadratic, double);
nm::Quadratic operator+(double, nm::Quadratic);

nm::Quadratic operator-(nm::Quadratic, const nm::Quadratic&);
nm::Quadratic operator-(nm::Quadratic, const nm::LinearFunction&);
nm::Quadratic operator-(nm::Quadratic, double);
nm::Quadratic operator-(double, const nm::Quadratic&);

nm::Quadratic operator*(nm::Quadratic, double);
nm::Quadratic operator*(double, nm::Quadratic);

nm::Quadratic operator/(nm::Quadratic, double);

nm::Quadratic operator-(const nm::Quadratic&);


bool operator<(const nm::Quadratic&, const nm::Quadratic&);
bool operator<(const nm::Quadratic&, const nm::LinearFunction&);
bool operator<(const nm::Quadratic&, double);
bool operator<(double, const nm::Quadratic&);

bool operator<=(const nm::Quadratic&, const nm::Quadratic&);
bool operator<=(const nm::Quadratic&, const nm::LinearFunction&);
bool operator<=(const nm::Quadratic&, double);
bool operator<=(double, const nm::Quadratic&);

bool operator==(const nm::Quadratic&, const nm::Quadratic&);
bool operator!=(const nm::Quadratic&, const nm::Quadratic&);

bool operator>=(const nm::Quadratic&, const nm::Quadratic&);
bool operator>=(const nm::Quadratic&, const nm::LinearFunction&);
bool operator>=(const nm::Quadratic&, double);
bool operator>=(double, const nm::Quadratic&);

bool operator>(const nm::Quadratic&, const nm::Quadratic&);
bool operator>(const nm::Quadratic&, const nm::LinearFunction&);
bool operator>(const nm::Quadratic&, double);
bool operator>(double, const nm::Quadratic&);


std::ostream& operator<<(std::ostream&, const nm::Quadratic&);


#endif  // QUADRATIC_HPP

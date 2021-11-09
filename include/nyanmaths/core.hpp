#ifndef NYANMATHS_CORE_HPP
#define NYANMATHS_CORE_HPP

/*

Here is the core module of the library where near all constants are defined.
There are also some basic mathematical functions like fast power or factorial.

*/

#include <vector>
#include <complex>


namespace nm
{
    // Error codes sometimes returned by functions, but mostly shapes
    enum class Error : uint8_t
    {
        NoError,
        InvalidMeasurement,
        ImpossibleScaling,
        InvalidValue,
        LogicError
    };


    nm::Error pythagore(double& a, double& b, double& greatest);

    std::vector<uint64_t>* divisors(uint64_t);

    bool prime(uint64_t);

    uint64_t collatz(uint64_t x, uint64_t index);
    std::vector<uint64_t>* collatz(uint64_t);

    uint64_t fibonacci(uint64_t);


    uint64_t factorial(uint16_t);

    double power(double x, int64_t exposant);

    double inverse(double);
    std::complex<double> inverse(const std::complex<double>&);

    double root(double x, double n);
    std::complex<double> root(const std::complex<double>& x, const std::complex<double>& n);

    double square(double);
    uint64_t square(int64_t);
    uint64_t square(uint64_t);
    std::complex<double> square(const std::complex<double>&);

    double cube(double);
    int64_t cube(int64_t);
    uint64_t cube(uint64_t);
    std::complex<double> cube(const std::complex<double>&);


    namespace consts  // Everything is in international system units
    {
        const long double pi(3.14159265358979323846l);
        const long double tau(6.28318530717958647693l);
        const long double e(2.71828182845904523536l);
        const long double phi(1.6180339887498948482l);

        const double h(6.62607015e-34);
        const double hBar(1.054571817e-34);
        const double G(6.6743015e-11);
        const double E(1.602176634e-19);
        const double K(8.9875517923e+19);

        const float sunAcceleration(273.95f);
        const float mercuryAcceleration(3.701f);
        const float venusAcceleration(8.87f);
        const float earthAcceleration(9.80665f);
        const float moonAcceleration(1.622f);
        const float marsAcceleration(3.711f);
        const float jupiterAcceleration(24.796f);
        const float saturnAcceleration(10.44f);
        const float uranusAcceleration(8.87f);
        const float neptuneAcceleration(11.15f);
        const float plutoAcceleration(0.62f);


        const double electronWeight(9.10938356e-31);
        const double protonWeight(1.672649e-27);
        const double neutronWeight(1.674927471e-27);

        const float moonWeight(7.342e+22f);
        const float earthWeight(5.97237e+24f);
        const float sunWeight(1.9885e+30f);

        const uint32_t lightSpeed(299792458u);
        const uint16_t soundSpeed(347u);
    }  /// Namespace consts
}  /// Namespace nm


#endif  // NYANMATHS_CORE_HPP

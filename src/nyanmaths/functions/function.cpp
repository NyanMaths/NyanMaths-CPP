#include <nyanmaths/functions/linearfunction.hpp>
#include <nyanmaths/functions/function.hpp>


nm::Function::~Function()
{
    // Nothing to be done here
}


double nm::Function::operator()(const double x) const
{
    return exec(x);
}
std::complex<double> nm::Function::operator()(const std::complex<double>& x) const
{
    return exec(x);
}


nm::LinearFunction nm::Function::tangent(const double x) const
{
    const double derivativeAtX(execDerivative(x));

    return nm::LinearFunction(derivativeAtX, exec(x) - derivativeAtX * x);
}

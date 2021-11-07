#include <cmath>
#include <stdexcept>
#include <sstream>

#include <nyanmaths/functions/quadratic.hpp>
#include <nyanmaths/functions/linearfunction.hpp>


////////////////////////// Define static const members //////////////////////////


nm::LinearFunction::Form nm::LinearFunction::_preferredForm(nm::LinearFunction::Form::SLOPE_INTERCEPT);


////////////////////////// nm::LinearFunction members //////////////////////////


nm::LinearFunction::LinearFunction () :
    _a(1.0),
    _b(0.0)
{
    // Nothing to be done here
}

nm::LinearFunction::LinearFunction (const double a, const double b) :
    _a(a),
    _b(b)
{
    if (a == 0.0)
        throw std::invalid_argument("Exception in nm::LinearFunction::nm::LinearFunction : null slope");
}

nm::LinearFunction::~LinearFunction ()
{
    // Nothing to be done here
}


double nm::LinearFunction::a () const
{
    return _a;
}

double nm::LinearFunction::b () const
{
    return _b;
}


nm::Error nm::LinearFunction::setA (const double newA)
{
    if (newA == 0.0)
        return nm::Error::InvalidValue;

    _a = newA;
    return nm::Error::NoError;
}

void nm::LinearFunction::setB (const double newB)
{
    _b = newB;
}


std::string nm::LinearFunction::asString (nm::LinearFunction::Form form, const double point) const
{
    std::string functionAsString;

    if (form == nm::LinearFunction::Form::POINT_SLOPE)
    {
        if (_a == -1.0)
            functionAsString = "-x";

        else if (_a == 1.0)
            functionAsString = "x";

        else
            functionAsString = std::to_string(_a) + "x";


        if (_b < 0.0)
            functionAsString += " - " + std::to_string(std::abs(_b));

        if (_b > 0.0)
            functionAsString += " + " + std::to_string(_b);
    }
    else if (form == nm::LinearFunction::Form::POINT_SLOPE)
    {
        if (_a == -1.0)
            functionAsString = "-(";

        else if (_a == 1.0)
            functionAsString = "(";

        else
            functionAsString = std::to_string(_a) + "(x";


        if (point < 0.0)
            functionAsString += " + " + std::to_string(std::abs(point));

        else
            functionAsString += " - " + std::to_string(point);

        if (exec(point) < 0.0)
            functionAsString += ") - " + std::to_string(std::abs(point));

        if (exec(point) > 0.0)
            functionAsString += ") + " + std::to_string(point);
    }
    else
    {
        if (_a == -1.0)
            functionAsString = "-(x";

        else
            functionAsString = ((_a == 1.0) ? "" : std::to_string(_a)) + "(x";


        if (root() < 0.0)
            functionAsString += " + " + std::to_string(std::abs(root())) + ")";

        else
            functionAsString += " - " + std::to_string(std::abs(root())) + ")";
    }

    return functionAsString;
}
std::string nm::LinearFunction::asString () const
{
    return asString(_preferredForm);
}

double nm::LinearFunction::exec (const double x) const
{
    return _a * x + _b;
}
std::complex<double> nm::LinearFunction::exec (const std::complex<double>& x) const
{
    return _a * x + _b;
}


std::string nm::LinearFunction::derivativeAsString () const
{
    return std::to_string(_a);
}

double nm::LinearFunction::derivative () const
{
    return _a;
}

double nm::LinearFunction::execDerivative (const double) const
{
    return _a;
}
std::complex<double> nm::LinearFunction::execDerivative (const std::complex<double>&) const
{
    return std::complex<double>(_a, 0.0);
}


std::string nm::LinearFunction::secondDerivativeAsString () const
{
    return std::to_string(_a);
}

double nm::LinearFunction::secondDerivative () const
{
    return 0.0;
}

double nm::LinearFunction::execSecondDerivative (const double) const
{
    return 0.0;
}
std::complex<double> nm::LinearFunction::execSecondDerivative (const std::complex<double>&) const
{
    return std::complex<double>(0.0, 0.0);
}


std::string nm::LinearFunction::antiderivativeAsString (const double constant) const
{
    return nm::Quadratic(_a * 0.5, _b, constant).asString();
}

nm::Quadratic nm::LinearFunction::antiderivative (const double constant) const
{
    return nm::Quadratic(_a * 0.5, _b, constant);
}
double nm::LinearFunction::execAntiderivative (const double x, const double constant) const
{
    return _a * x * x * 0.5 + _b * x + constant;
}
std::complex<double> nm::LinearFunction::execAntiderivative (const std::complex<double>& x, const double constant) const
{
    return _a * x * x * 0.5 + _b * x + constant;
}


double nm::LinearFunction::root () const
{
    return -_b / _a;
}
std::vector<double> nm::LinearFunction::roots () const
{
    return std::vector<double>{ -_b / _a };
}
std::vector<std::complex<double>> nm::LinearFunction::complexRoots () const
{
    return std::vector<std::complex<double>>{ std::complex<double>(-_b / _a, 0.0) };
}

double nm::LinearFunction::integral (double from, double to) const
{
    if (from == to)
        return 0.0;

    if (to < from)
    {
        const double tmp(from);
        from = to;
        to = tmp;
    }


    double root(roots().at(0u));

    if ((from < root && to <= root) || from >= root)
        return std::abs(execAntiderivative(to) - execAntiderivative(from));

    else
        return std::abs(execAntiderivative(root) - execAntiderivative(from)) +
               std::abs(execAntiderivative(to) - execAntiderivative(root));
}

nm::LinearFunction nm::LinearFunction::tangent (const double) const
{
    return nm::LinearFunction(_a, _b);
}


nm::LinearFunction::Form nm::LinearFunction::preferredForm ()
{
    return _preferredForm;
}

void nm::LinearFunction::setPreferredForm (nm::LinearFunction::Form newPreferredForm)
{
    _preferredForm = newPreferredForm;
}


////////////////////////// Operators //////////////////////////


nm::LinearFunction& nm::LinearFunction::operator+= (const nm::LinearFunction& n)
{
    if (_a + n.a() == 0.0)
        throw std::invalid_argument("Exception in nm::LinearFunction::operator+= : null slope");

    _a += n.a();
    _b += n.b();

    return *this;
}
nm::LinearFunction& nm::LinearFunction::operator+= (const double n)
{
    _b += n;

    return *this;
}

nm::LinearFunction& nm::LinearFunction::operator-= (const nm::LinearFunction& n)
{
    if (_a == n.a())
        throw std::invalid_argument("Exception in nm::LinearFunction::operator-= : null slope");

    _a -= n.a();
    _b -= n.b();

    return *this;
}
nm::LinearFunction& nm::LinearFunction::operator-= (const double n)
{
    _b -= n;

    return *this;
}

nm::LinearFunction& nm::LinearFunction::operator*= (const double n)
{
    if (n == 0.0)
        throw std::invalid_argument("Exception in nm::LinearFunction::operator*= : null slope");

    _a *= n;
    _b *= n;

    return *this;
}

nm::LinearFunction& nm::LinearFunction::operator/= (const double n)
{
    if (n == 0.0)
        throw std::invalid_argument("Exception in nm::LinearFunction::operator/= : division by zero");

    _a /= n;
    _b /= n;

    return *this;
}


nm::LinearFunction operator+ (nm::LinearFunction a, const nm::LinearFunction& b)
{
    a += b;
    return a;
}
nm::LinearFunction operator+ (nm::LinearFunction a, const double b)
{
    a += b;
    return a;
}
nm::LinearFunction operator+ (const double a, nm::LinearFunction b)
{
    b += a;
    return b;
}
nm::Quadratic operator+ (const nm::LinearFunction& a, nm::Quadratic b)
{
    b += a;
    return b;
}

nm::LinearFunction operator- (nm::LinearFunction a, const nm::LinearFunction& b)
{
    a -= b;
    return a;
}
nm::LinearFunction operator- (nm::LinearFunction a, const double b)
{
    a -= b;
    return a;
}
nm::LinearFunction operator- (const double a, const nm::LinearFunction& b)
{
    return -b + a;
}
nm::Quadratic operator- (const nm::LinearFunction& a, const nm::Quadratic& b)
{
    return -b + a;
}

nm::LinearFunction operator- (const nm::LinearFunction& n)
{
    return nm::LinearFunction(-n.a(), -n.b());
}

nm::Quadratic operator* (const nm::LinearFunction& a, const nm::LinearFunction& b)
{
    return nm::Quadratic(a.a() * b.a(), a.a() * b.b() + a.b() + b.a(), a.b() * b.b());
}
nm::LinearFunction operator* (nm::LinearFunction a, const double b)
{
    a *= b;
    return a;
}
nm::LinearFunction operator* (const double a, nm::LinearFunction b)
{
    b *= a;
    return b;
}

nm::LinearFunction operator/ (nm::LinearFunction a, const double b)
{
    a /= b;
    return a;
}


///////////// Comparsion operators


bool operator< (const nm::LinearFunction& a, const nm::LinearFunction& b)
{
    return a.a() == b.a() && a.b() < b.b();
}
bool operator< (const nm::LinearFunction& a, const nm::Quadratic& b)
{
    return a - b < 0.0;
}

bool operator<= (const nm::LinearFunction& a, const nm::LinearFunction& b)
{
    return a.a() == b.a() && a.b() <= b.b();
}
bool operator<= (const nm::LinearFunction& a, const nm::Quadratic& b)
{
    return a - b <= 0.0;
}

bool operator== (const nm::LinearFunction& a, const nm::LinearFunction& b)
{
    return a.a() == b.a() && a.b() == b.b();
}

bool operator!= (const nm::LinearFunction& a, const nm::LinearFunction& b)
{
    return !(a == b);
}

bool operator>= (const nm::LinearFunction& a, const nm::LinearFunction& b)
{
    return a.a() == b.a() && a.b() >= b.b();
}
bool operator>= (const nm::LinearFunction& a, const nm::Quadratic& b)
{
    return a - b >= 0.0;
}

bool operator> (const nm::LinearFunction& a, const nm::LinearFunction& b)
{
    return a.a() == b.a() && a.b() > b.b();
}
bool operator> (const nm::LinearFunction& a, const nm::Quadratic& b)
{
    return operator-(a, b) > 0.0;
}


///////////// Stream operator


std::ostream& operator<< (std::ostream& stream, const nm::LinearFunction& n)
{
    stream<<n.asString(nm::LinearFunction::preferredForm(), 0.0);

    return stream;
}

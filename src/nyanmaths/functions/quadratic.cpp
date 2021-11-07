#include <cmath>
#include <bits/stdc++.h>
#include <stdexcept>
#include <sstream>

#include <nyanmaths/functions/quadratic.hpp>


////////////////////////// Define static const members //////////////////////////


nm::Quadratic::Form nm::Quadratic::_preferredForm(nm::Quadratic::Form::EXPANDED);


////////////////////////// Some useful stuff //////////////////////////


namespace
{
    std::string toString (const double x)
    {
        std::stringstream tempStream;

        tempStream<<x;
        return tempStream.str();
    }

    std::string toString (const std::complex<double>& x)
    {
        std::string xStr("(");

        xStr += x.real() < 0.0 ? toString(x.real()) : toString(x.real()) +
                (x.imag() < 0.0 ? " - " + toString(-x.imag()) : " + " + toString(x.imag())) + "i)";

        return xStr;
    }
}


////////////////////////// nm::Quadratic members //////////////////////////


nm::Quadratic::Quadratic () : _a(1.0), _b(0.0), _c(0.0)
{
    // Nothing to be done here
}

nm::Quadratic::Quadratic (const double a, const double b, const double c) :
    _a(a),
    _b(b),
    _c(c)
{
    if (a == 0.0)
        throw std::invalid_argument("Exception in nm::Quadratic::Quadratic : null coefficient a");
}

nm::Quadratic::~Quadratic ()
{
    // Nothing to be done here
}


double nm::Quadratic::a () const
{
    return _a;
}

double nm::Quadratic::b () const
{
    return _b;
}

double nm::Quadratic::c () const
{
    return _c;
}


nm::Error nm::Quadratic::setA (const double newA)
{
    if (newA == 0.0)
        return nm::Error::InvalidValue;

    _a = newA;
    return nm::Error::NoError;
}

void nm::Quadratic::setB (const double newB)
{
    _b = newB;
}

void nm::Quadratic::setC (const double newC)
{
    _c = newC;
}


nm::Error nm::Quadratic::setExpandedForm (const double newA, const double newB, const double newC)
{
    if (newA == 0.0)
        return nm::Error::InvalidValue;

    _a = newA;
    _b = newB;
    _c = newC;
    return nm::Error::NoError;
}

nm::Error nm::Quadratic::setVertexForm (const double newA, const double newAlpha, const double newBeta)
{
    if (newA == 0.0)
        return nm::Error::InvalidValue;

    _a = newA;
    _b = -2.0 * newA * newAlpha;
    _c = newA * newAlpha * newAlpha + newBeta;
    return nm::Error::NoError;
}

nm::Error nm::Quadratic::setFactoredForm (const double newA, const double newRoot1, const double newRoot2)
{
    if (newA == 0.0)
        return nm::Error::InvalidValue;

    _a = newA;
    _b = -newA * (newRoot1 + newRoot2);
    _c = newA * newRoot1 * newRoot2;
    return nm::Error::NoError;
}

nm::Error nm::Quadratic::setFactoredForm (const double newA, const std::complex<double>& newRoot1, const std::complex<double>& newRoot2)
{
    if (newA == 0.0 || newRoot1 != std::conj(newRoot2))
        return nm::Error::InvalidValue;

    _a = newA;
    _b = -2.0 * newA * newRoot1.real();
    _c = newA * (newRoot1.real() * newRoot1.real() + newRoot1.imag() * newRoot1.imag());
    return nm::Error::NoError;
}


std::string nm::Quadratic::asString (nm::Quadratic::Form form) const
{
    if (form == nm::Quadratic::Form::EXPANDED)
        return expandedForm();

    else if (form == nm::Quadratic::Form::VERTEX)
        return vertexForm();

    else
        return factoredForm();
}
std::string nm::Quadratic::asString () const
{
    return asString(preferredForm());
}
std::string nm::Quadratic::expandedForm () const
{
    std::string func;

    if (_a == -1.0)
        func = "-x^2";

    else if (_a == 1.0)
        func = "x^2";

    else
        func = toString(_a) + "x^2";

    if (_b < 0.0)
    {
        if (_b == -1.0)
            func += " - x";

        else
            func += " - " + toString(-_b) + "x";
    }
    if (_b > 0.0)
    {
        if (_b == 1.0)
            func += " + x";

        else
            func += " + " + toString(_b) + "x";
    }

    if (_c < 0.0)
        func += " - " + toString(-_c);

    if (_c > 0.0)
        func += " + " + toString(_c);


    return func;
}
std::string nm::Quadratic::vertexForm () const
{
    std::string func;

    if (_a == -1.0)
        func = "-(x";

    else if (_a == 1.0)
        func = "(x";

    else
        func = toString(_a) + "(x";


    if (alpha() < 0.0)
        func += " + " + toString(-alpha()) + ")";

    else
        func += " - " + toString(alpha()) + ")";

    if (beta() < 0.0)
        func += " - " + toString(-beta());

    else
        func += " + " + toString(beta());

    return func;
}
std::string nm::Quadratic::factoredForm () const
{
    std::string func;

    if (_a == -1.0)
        func = "-(x";

    else if (_a == 1.0)
        func = "(x";

    else
        func = toString(_a) + "(x";


    if (std::abs(delta()) == 0.0)
    {
        const double tmpRoot(roots().at(0u));

        if (tmpRoot < 0.0)
            func += " + " + toString(-tmpRoot) + ")^2";

        else
            func += " - " + toString(tmpRoot) + ")^2";
    }
    else if (delta() < 0.0)
        func += " - " + toString(complexRoots().at(0u)) + ")(x - " + toString(complexRoots().at(1u)) + ")";

    else
    {
        const std::vector<double> tmpRoots(roots());

        if (tmpRoots.at(0u) < 0.0)
            func += " + " + toString(-tmpRoots.at(0u)) + ")(x";

        else
            func += " - " + toString(tmpRoots.at(0u)) + ")(x";

        if (tmpRoots.at(1u) < 0.0)
            func += " + " + toString(-tmpRoots.at(1u)) + ")";

        else
            func += " - " + toString(tmpRoots.at(1u)) + ")";
    }

    return func;
}

double nm::Quadratic::exec (const double x) const
{
    return _a * x * x + _b * x + _c;
}

std::complex<double> nm::Quadratic::exec (const std::complex<double>& x) const
{
    return _a * x * x + _b * x + _c;
}


std::string nm::Quadratic::derivativeAsString (nm::LinearFunction::Form form) const
{
    return derivative().asString(form);
}
std::string nm::Quadratic::derivativeAsString () const
{
    return derivativeAsString(nm::LinearFunction::preferredForm());
}

nm::LinearFunction nm::Quadratic::derivative() const
{
    return nm::LinearFunction(2.0 * _a, _b);
}

double nm::Quadratic::execDerivative (const double x) const
{
    return 2.0 * _a * x + _b;
}
std::complex<double> nm::Quadratic::execDerivative (const std::complex<double>& x) const
{
    return 2.0 * _a * x + _b;
}

void nm::Quadratic::setDerivative (const nm::LinearFunction& newDerivative)
{
    _a = newDerivative.a() * 0.5;
    _b = newDerivative.b();
}


std::string nm::Quadratic::secondDerivativeAsString () const
{
    return toString(2.0 * _a);
}

double nm::Quadratic::secondDerivative() const
{
    return 2.0 * _a;
}

double nm::Quadratic::execSecondDerivative (const double) const
{
    return 2.0 * _a;
}
std::complex<double> nm::Quadratic::execSecondDerivative (const std::complex<double>&) const
{
    return std::complex<double>(2.0 * _a, 0.0);
}

void nm::Quadratic::setSecondDerivative (const double newSecondDerivative)
{
    _a = newSecondDerivative * 0.5;
}


std::string nm::Quadratic::antiderivativeAsString (const double constant) const
{
    std::string func;

    if (_a / 3.0 == -1.0)
        func = "-x^3";

    else if (_a / 3.0 == 1.0)
        func = "x^3";

    else
        func = toString(_a / 3.0) + "x^3";

    if (_b < 0.0)
    {
        if (_b * 0.5 == -1.0)
            func += " - x^2";

        else
            func += " - " + toString(std::abs(_b) / 2) + "x^2";
    }
    if (_b > 0.0)
    {
        if (_b * 0.5 == 1.0)
            func += " + x^2";

        else
            func += " + " + toString(_b * 0.5) + "x^2";
    }

    if (_c < 0.0)
        func += " - " + toString(std::abs(_c)) + "x";

    if (_c > 0.0)
        func += " + " + toString(_c) + "x";


    if (constant < 0.0)
        func += " - " + toString(-constant);

    if (constant > 0.0)
        func += " + " + toString(constant);

    return func;
}

double nm::Quadratic::execAntiderivative (const double x, const double constant) const
{
    return _a * x * x * x / 3.0 + _b * x * x * 0.5 + _c * x + constant;
}
std::complex<double> nm::Quadratic::execAntiderivative (const std::complex<double>& x, const double constant) const
{
    return _a * x * x * x / 3.0 + _b * x * x * 0.5 + _c * x + constant;
}

nm::Error nm::Quadratic::setAntiderivative (const double newAntiderivativeA, const double newAntiderivativeB, const double newAntiderivativeC)
{
    if (newAntiderivativeA == 0.0)
        return nm::Error::InvalidValue;

    _a = newAntiderivativeA * 3.0;
    _b = newAntiderivativeB * 2.0;
    _c = newAntiderivativeC;
    return nm::Error::NoError;
}


uint8_t nm::Quadratic::numberOfRealRoots () const
{
    const double tempDelta(delta());

    if (tempDelta < 0.0)
        return 0u;

    else if (tempDelta == 0.0)
        return 1u;

    else
        return 2u;
}

std::vector<double> nm::Quadratic::roots () const
{
    if (delta() < 0.0)
        return std::vector<double>{};


    const double tempDelta(delta());
    return std::vector<double>
    {
        (-_b - sqrt(tempDelta)) * 0.5 / _a,
        (-_b + sqrt(tempDelta)) * 0.5 / _a
    };
}
std::vector<std::complex<double>> nm::Quadratic::complexRoots () const
{
    const double tempDelta(delta());

    if (tempDelta < 0.0)
        return std::vector<std::complex<double>>
        {
            std::complex<double>(-_b * 0.5 / _a, -sqrt(-tempDelta) * 0.5 / _a),
            std::complex<double>(-_b * 0.5 / _a, sqrt(-tempDelta) * 0.5 / _a)
        };

    return std::vector<std::complex<double>>
    {
        std::complex<double>((-_b - sqrt(tempDelta)) * 0.5 / _a, 0.0),
        std::complex<double>((-_b + sqrt(tempDelta)) * 0.5 / _a, 0.0)
    };
}

double nm::Quadratic::rootsSummation () const
{
    return -_b / _a;
}
double nm::Quadratic::rootsProduct () const
{
    return _c / _a;
}


double nm::Quadratic::alpha () const
{
    return -_b * 0.5 / _a;
}

double nm::Quadratic::beta () const
{
    return exec(alpha());
}

double nm::Quadratic::delta () const
{
    return _b * _b - 4.0 * _a * _c;
}
double nm::Quadratic::reducedDelta () const
{
    return _b * _b * 0.25 - _a * _c;
}


double nm::Quadratic::integral (double from, double to) const
{
    if (from == to)
        return 0.0;

    if (to < from)
    {
        const double swap(from);
        from = to;
        to = swap;
    }


    if (numberOfRealRoots() < 2u)
        return std::abs(execAntiderivative(to) - execAntiderivative(from));


    std::vector<double> realRoots(roots());
    if (realRoots.at(0u) > realRoots.at(1u))
        std::swap(realRoots[0u], realRoots[1u]);

    if (to <= realRoots.at(0u) || (from >= realRoots.at(0u) && to <= realRoots.at(1u)) || from >= realRoots.at(1u))
        return std::abs(execAntiderivative(to) - execAntiderivative(from));

    else if (from < realRoots.at(0u) && to <= realRoots.at(1u))
        return std::abs(execAntiderivative(realRoots.at(0u)) - execAntiderivative(from)) +
               std::abs(execAntiderivative(to) - execAntiderivative(realRoots.at(0u)));

    else if (from >= realRoots.at(0u) && to > realRoots.at(1u))
        return std::abs(execAntiderivative(realRoots.at(1u)) - execAntiderivative(from)) +
               std::abs(execAntiderivative(to) - execAntiderivative(realRoots.at(1u)));

    else
        return std::abs(execAntiderivative(realRoots.at(0u)) - execAntiderivative(from)) +
               std::abs(execAntiderivative(realRoots.at(1u)) - execAntiderivative(realRoots.at(0u))) +
               std::abs(execAntiderivative(to) - execAntiderivative(realRoots.at(1u)));
}


nm::Quadratic::Form nm::Quadratic::preferredForm ()
{
    return _preferredForm;
}

void nm::Quadratic::setPreferredForm (nm::Quadratic::Form newPreferredForm)
{
    _preferredForm = newPreferredForm;
}


////////////////////////// Operators //////////////////////////


nm::Quadratic& nm::Quadratic::operator+= (const nm::Quadratic& n)
{
    if (_a + n.a() == 0.0)
        throw std::invalid_argument("Exception in nm::Quadratic::operator+= : null coefficient a");

    _a += n.a();
    _b += n.b();
    _c += n.c();

    return *this;
}
nm::Quadratic& nm::Quadratic::operator+= (const nm::LinearFunction& n)
{
    _b += n.a();
    _c += n.b();

    return *this;
}
nm::Quadratic& nm::Quadratic::operator+= (const double n)
{
    _c += n;

    return *this;
}

nm::Quadratic& nm::Quadratic::operator-= (const nm::Quadratic& n)
{
    if (_a - n.a() == 0.0)
        throw std::invalid_argument("Exception in nm::Quadratic::operator-= : null coefficient a");

    _a -= n.a();
    _b -= n.b();
    _c -= n.c();

    return *this;
}
nm::Quadratic& nm::Quadratic::operator-= (const nm::LinearFunction& n)
{
    _b -= n.a();
    _c -= n.b();

    return *this;
}
nm::Quadratic& nm::Quadratic::operator-= (const double n)
{
    _c -= n;

    return *this;
}

nm::Quadratic& nm::Quadratic::operator*= (const double n)
{
    if (n == 0.0)
        throw std::invalid_argument("Exception in nm::Quadratic::operator*= : null coefficient a");

    _a *= n;
    _b *= n;
    _c *= n;

    return *this;
}

nm::Quadratic& nm::Quadratic::operator/= (const double n)
{
    if (n == 0.0)
        throw std::invalid_argument("Exception in nm::Quadratic::operator/= : division by 0");

    _a /= n;
    _b /= n;
    _c /= n;

    return *this;
}


nm::Quadratic operator+ (nm::Quadratic a, const nm::Quadratic& b)
{
    a += b;
    return a;
}
nm::Quadratic operator+ (nm::Quadratic a, const nm::LinearFunction& b)
{
    a += b;
    return a;
}
nm::Quadratic operator+ (nm::Quadratic a, const double b)
{
    a += b;
    return a;
}
nm::Quadratic operator+ (const double a, nm::Quadratic b)
{
    b += a;
    return b;
}

nm::Quadratic operator- (nm::Quadratic a, const nm::Quadratic& b)
{
    a -= b;
    return a;
}
nm::Quadratic operator- (nm::Quadratic a, const nm::LinearFunction& b)
{
    a -= b;
    return a;
}
nm::Quadratic operator- (nm::Quadratic a, const double b)
{
    a -= b;
    return a;
}
nm::Quadratic operator- (const double a, const nm::Quadratic& b)
{
    return -b + a;
}

nm::Quadratic operator- (const nm::Quadratic& n)
{
    return nm::Quadratic(-n.a(), -n.b(), -n.c());
}

nm::Quadratic operator* (nm::Quadratic a, const double b)
{
    a *= b;
    return a;
}
nm::Quadratic operator* (const double a, nm::Quadratic b)
{
    b *= a;
    return b;
}


nm::Quadratic operator/ (nm::Quadratic a, const double b)
{
    a /= b;
    return a;
}


///////////// Comparsion operators


bool operator< (const nm::Quadratic& a, const nm::Quadratic& b)
{
    if (a.a() == b.a())
    {
        if (a.b() == b.b())
            return a.c() - b.c() < 0.0;

        return false;
    }

    return a - b < 0.0;
}
bool operator< (const nm::Quadratic& a, const nm::LinearFunction& b)
{
    return a - b < 0.0;
}
bool operator< (const nm::Quadratic& a, const double b)
{
    return a.a() < 0.0 && a.beta() < b;
}
bool operator< (const double a, const nm::Quadratic& b)
{
    return b.a() > 0.0 && b.beta() > a;
}

bool operator<= (const nm::Quadratic& a, const nm::Quadratic& b)
{
    if (a.a() == b.a())
    {
        if (a.b() == b.b())
            return a.c() <= b.c();

        return false;
    }

    return a - b <= 0.0;
}
bool operator<= (const nm::Quadratic& a, const nm::LinearFunction& b)
{
    return a - b <= 0.0;
}
bool operator<= (const nm::Quadratic& a, const double b)
{
    return a.a() < 0.0 && a.beta() <= b;
}
bool operator<= (const double a, const nm::Quadratic& b)
{
    return b.a() > 0.0 && b.beta() >= a;
}

bool operator== (const nm::Quadratic& a, const nm::Quadratic& b)
{
    return a.a() == b.a() && a.b() == b.b() && a.c() == b.c();
}

bool operator!= (const nm::Quadratic& a, const nm::Quadratic& b)
{
    return !(a == b);
}

bool operator>= (const nm::Quadratic& a, const nm::Quadratic& b)
{
    if (a.a() == b.a())
    {
        if (a.b() == b.b())
            return a.c() >= b.c();

        return false;
    }

    return a - b >= 0.0;
}
bool operator>= (const nm::Quadratic& a, const nm::LinearFunction& b)
{
    return a - b >= 0.0;
}
bool operator>= (const nm::Quadratic& a, const double b)
{
    return a.a() > 0.0 && a.beta() >= b;
}
bool operator>= (const double a, const nm::Quadratic& b)
{
    return b.a() < 0.0 && b.beta() <= a;
}

bool operator> (const nm::Quadratic& a, const nm::Quadratic& b)
{
    if (a.a() == b.a())
    {
        if (a.b() == b.b())
            return a.c() > b.c();

        return false;
    }

    return a - b > 0.0;
}
bool operator> (const nm::Quadratic& a, const nm::LinearFunction& b)
{
    return a - b > 0.0;
}
bool operator> (const nm::Quadratic& a, const double b)
{
    return a.a() > 0.0 && a.beta() > b;
}
bool operator> (const double a, const nm::Quadratic& b)
{
    return b.a() < 0.0 && b.beta() < a;
}


///////////// Stream operator


std::ostream& operator<< (std::ostream& stream, const nm::Quadratic& n)
{
    stream<<n.asString(nm::Quadratic::preferredForm());

    return stream;
}

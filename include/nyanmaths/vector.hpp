#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <vector>

#include <nyanmaths/core.hpp>


namespace nm
{
    class Vector
    {
        public:
            virtual ~Vector();


            virtual double length() const = 0;
            virtual nm::Error setLength(double) = 0;

            virtual bool isNull() const = 0;
    };  /// Class Vector
}  /// Namespace nm


#endif  // VECTOR_HPP

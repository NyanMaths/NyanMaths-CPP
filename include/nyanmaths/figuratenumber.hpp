#ifndef FIGURATENUMBER_HPP
#define FIGURATENUMBER_HPP

#include <iostream>

#include <nyanmaths/core.hpp>


namespace nm
{
    class FigurateNumber
    {
        public:
            explicit FigurateNumber(uint64_t type, uint64_t index);

            virtual ~FigurateNumber();


            uint64_t type() const;
            uint64_t index() const;
            uint64_t value() const;


            nm::Error setType(uint64_t newType);
            void setIndex(uint64_t newIndex);
            nm::Error setValue(uint64_t newValue);


        private:
            uint64_t _type;
            uint64_t _index;
    };  /// Class FigurateNumber
}  /// Namespace nm


bool operator==(const nm::FigurateNumber&, const nm::FigurateNumber&);
bool operator!=(const nm::FigurateNumber&, const nm::FigurateNumber&);

std::ostream& operator<<(std::ostream&, const nm::FigurateNumber&);


#endif  // FIGURATENUMBER_HPP

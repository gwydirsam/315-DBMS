// CSCE 315-503
// sqltypes.h

#ifndef SQLTYPES_H_
#define SQLTYPES_H_

#include <array>

// Here we define all the sql data types
// Everything is in namespace SQL, so VARCHAR can be referenced as
// SQL::VARCHAR(n)
namespace SQL {

// Fixed length n
// example of use: CHARACTER<5> gives a fixed length 5 character string
template <typename N>
using CHARACTER = std::array<char, N>;

// Variable Length. Max length n.
template <typename N>
using VARCHAR = std::array<char, N>;

template <typename N>
using CHARACTER_VARYING = std::array<char, N>;

// Boolean
typedef bool BOOLEAN;

// Integer
typedef long int INTEGER;
typedef short int SMALLINT;
typedef long long int BIGINT;

// Decimal
typedef float DECIMAL;
typedef double NUMERIC;
typedef double DOUBLE;
typedef double DOUBLEPRECISION;

// Float
typedef float FLOAT;

// Real
typedef double REAL;

// Array
typedef std::array ARRAY;

// MultiSet
typedef std::multiset MULTISET;

// Date
struct DATE {
  INTEGER YEAR;
  INTEGER MONTH;
  INTEGER DAY;
};

// Time
struct TIME {
  INTEGER HOUR;
  INTEGER MINUTE;
  INTEGER SECOND;
};

// Timestamp
struct TIMESTAMP {
  DATE DATE;
  TIME TIME;
};

// Interval
struct INTERVAL {
  INTEGER TIME_INTERVAL;
};
}

#endif  // SQLTYPES_H_

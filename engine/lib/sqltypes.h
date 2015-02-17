// CSCE 315-503
// sqltypes.h

#ifndef SQLTYPES_H_
#define SQLTYPES_H_

#include <vector>
#include <array>
#include <string>

// Here we define all the sql data types
// Everything is in namespace SQL, so VARCHAR can be referenced as
// sql::VARCHAR(n)
namespace sql {
// TODO: FIX THESE
//// Fixed length n
//// example of use: CHARACTER<5> gives a fixed length 5 character string
// template <typename N>
// using CHARACTER = std::array<char, N>;
//
//// Variable Length. Max length n.
// template <typename N>
// using VARCHAR = std::array<char, N>;
//
// template <typename N>
// using CHARACTER_VARYING = std::array<char, N>;

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
// TODO array needs <size>
// typedef std::array ARRAY;

// MultiSet
// doesn't work
// typedef std::multiset MULTISET;

// Date
struct DATE {
  INTEGER YEAR;
  INTEGER MONTH;
  INTEGER DAY;
  bool operator<(const DATE& rhs) const {
    if (this->YEAR == rhs.YEAR) {
      if (this->MONTH == rhs.MONTH) {
        return this->DAY < rhs.DAY;
      } else
        return this->MONTH < rhs.MONTH;
    } else
      return this->YEAR < rhs.YEAR;
  }

  bool operator>(const DATE& rhs) const { return rhs < *this; }

  bool operator==(const DATE& rhs) const {
    if (this->YEAR == rhs.YEAR) {
      if (this->MONTH == rhs.MONTH) {
        if (this->DAY == rhs.DAY)
          return true;
        else
          return false;
      } else
        return false;
    }

    return false;
  }

  bool operator<=(const DATE& rhs) const {
    return (*this == rhs || *this < rhs);
  }

  bool operator>=(const DATE& rhs) const {
    return (*this == rhs || *this > rhs);
  }
};

// Time
struct TIME {
  INTEGER HOUR;
  INTEGER MINUTE;
  INTEGER SECOND;
  bool operator<(const TIME& rhs) const {
    if (this->HOUR == rhs.HOUR) {
      if (this->MINUTE == rhs.MINUTE) {
        return this->SECOND < rhs.SECOND;
      } else
        return this->MINUTE < rhs.MINUTE;
    } else
      return this->HOUR < rhs.HOUR;
  }

  bool operator>(const TIME& rhs) const { return rhs < *this; }

  bool operator==(const TIME& rhs) const {
    if (this->HOUR == rhs.HOUR) {
      if (this->MINUTE == rhs.MINUTE) {
        if (this->SECOND == rhs.SECOND)
          return true;
        else
          return false;
      } else
        return false;
    }

    return false;
  }

  bool operator<=(const TIME& rhs) const {
    return (*this == rhs || *this < rhs);
  }

  bool operator>=(const TIME& rhs) const {
    return (*this == rhs || *this > rhs);
  }
};

// Timestamp
struct TIMESTAMP {
  DATE date;
  TIME time;
  bool operator<(const TIMESTAMP& rhs) const {
    if (this->date < rhs.date) return true;
    return this->time < rhs.time;
  }
  bool operator>(const TIMESTAMP& rhs) const { return rhs < *this; }
  bool operator==(const TIMESTAMP& rhs) const {
    return (this->date == rhs.date) && (this->time == rhs.time);
  }
  bool operator<=(const TIMESTAMP& rhs) const {
    return (*this == rhs || *this < rhs);
  }
  bool operator>=(const TIMESTAMP& rhs) const {
    return (*this == rhs || *this > rhs);
  }
};

// Interval
struct INTERVAL {
  INTEGER TIME_INTERVAL;
};

// Invalid Type
typedef int INVALIDTYPE;
}  // end namespace SQL

class SQLType {
 public:
  SQLType(std::string type, std::string value) : type_(type), value_(value){};
  // Default Constructor creates an invalid type
  SQLType() : type_("INVALIDTYPE"), value_("INVALID"){};

 private:
  std::string type_;
  std::string value_;
};

// Define a tuple
typedef std::vector<std::string> Tuple;

#endif  // SQLTYPES_H_

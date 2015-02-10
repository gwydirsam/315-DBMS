// CSCE 315-503
// attribute.h

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include <utility>  // std::pair
#include <string>   // std::string

// An attribute is a std::pair<std::string type, std::string title>
class Attribute {
 public:
  // Constructors
  Attribute(std::string type, std::string title) : attribute_(type, title){};
  // Default Constructor
  Attribute() : attribute_("INVALID", "INVALID"){};

  // Destructors
  // Default Destructor
  ~Attribute(){};

  // Getters
  std::string type() { return std::get<0>(attribute_); }
  std::string title() { return std::get<1>(attribute_); }

  // Setters

 private:
  // Data Structures
  std::pair<std::string, std::string> attribute_;
};

#endif  // ATTRIBUTE_H_

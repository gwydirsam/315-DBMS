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
  std::string type() { return attribute_.first; }
  std::string title() { return attribute_.second; }

  // Setters
  void type(std::string type) { attribute_.first = type; }
  void title(std::string title) { attribute_.second = title; }

 private:
  // Data Structures
  std::pair<std::string, std::string> attribute_;
};

#endif  // ATTRIBUTE_H_
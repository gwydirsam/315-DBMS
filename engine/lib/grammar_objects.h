#ifndef GRAMMAR_OBJECTS_H_
#define GRAMMAR_OBJECTS_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <boost/variant.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/include/boost_tuple.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/include/at_c.hpp>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_as.hpp>

#include <boost/foreach.hpp>

#include "grammar_objects/condition.h"
#include "grammar_objects/expression.h"
#include "grammar_objects/command.h"
#include "grammar_objects/query.h"
#include "grammar_objects/program.h"

#include "relation.h"
#include "engine.h"
#include "utility.h"

#endif /* GRAMMAR_OBJECTS_H_ */

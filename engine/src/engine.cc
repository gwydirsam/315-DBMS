#include "engine.h"
#include "relation.h"

int engine::createTable(std::string TableName, std::vector<Attributes> attributes, std::vector<Attributes> primarykey) {
	
	Relation table(TableName, attributes, primarykey);
	openTable(table);
}

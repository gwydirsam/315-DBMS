// Rabia Gunonu, Sam Gwydir, Nicolas Juarez, Daniel Koon
// CSCE 315-503
// test_main.cc

#include <iostream>
#include <memory>

#include "../lib/engine.h"
#include "../lib/column.h"
#include "../lib/relation.h"
#include "../lib/utility.h"
#include "../lib/grammar.h"

#include "../include/gtest/include/gtest/gtest.h"

namespace {
// The fixture for testing class Project1. From google test primer.
class EngineTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    Column<std::string> first_col("Scrooge");
    first_col.primary_key(true);
    first_col.insert_entry("bah");
    first_col.insert_entry("hum");
    first_col.insert_entry("bug");
    first_col.insert_entry("foo");
    first_col.insert_entry("bar");

    Column<std::string> second_col("Money");
    second_col.insert_entry("$10");
    second_col.insert_entry("$100");
    second_col.insert_entry("$1000");
    second_col.insert_entry("$10000");
    second_col.insert_entry("$100000");

    Column<std::string> third_col("Scrooge");
    third_col.primary_key(true);
    third_col.insert_entry("1");
    third_col.insert_entry("2");
    third_col.insert_entry("3");
    third_col.insert_entry("4");
    third_col.insert_entry("5");

    Column<std::string> fourth_col("Money");
    fourth_col.insert_entry("Money1");
    fourth_col.insert_entry("Money2");
    fourth_col.insert_entry("Money3");
    fourth_col.insert_entry("Money4");
    fourth_col.insert_entry("Money5");

    Column<std::string> fifth_col("Scrooge");
    fifth_col.primary_key(true);
    fifth_col.insert_entry("1");
    fifth_col.insert_entry("4");
    fifth_col.insert_entry("5");

    Column<std::string> sixth_col("Money");
    sixth_col.insert_entry("Money1");
    sixth_col.insert_entry("Money2");
    sixth_col.insert_entry("Money5");

    Column<std::string> seventh_col("id");
    seventh_col.primary_key(true);
    seventh_col.insert_entry("1");
    seventh_col.insert_entry("2");
    seventh_col.insert_entry("3");
    seventh_col.insert_entry("4");
    seventh_col.insert_entry("5");

    Column<std::string> eighth_col("Name");
    eighth_col.insert_entry("sam");
    eighth_col.insert_entry("rabia");
    eighth_col.insert_entry("nick");
    eighth_col.insert_entry("kade");
    eighth_col.insert_entry("leonardo");

    std::vector<Column<std::string>> columns0;
    std::vector<Column<std::string>> columns1;
    std::vector<Column<std::string>> columns2;
    std::vector<Column<std::string>> columns3;
    std::vector<Column<std::string>> columns4;

    columns0.push_back(first_col);
    columns0.push_back(second_col);

    columns1.push_back(third_col);
    columns1.push_back(fourth_col);

    columns2.push_back(first_col);
    columns2.push_back(fourth_col);

    columns3.push_back(fifth_col);
    columns3.push_back(sixth_col);

    columns4.push_back(seventh_col);
    columns4.push_back(eighth_col);

    db1.createNewTable("Test0", columns0);
    db1.createNewTable("Test1", columns1);
    db1.createNewTable("Test2", columns2);
    db1.createNewTable("Test3", columns3);
    db1.createNewTable("Test4", columns4);
  }

  Engine db0;  // Tested for empty
  Engine db1;  // Has all the tables
};

TEST_F(EngineTest, NoOpenTablesOnInit) { EXPECT_EQ(0, db0.num_open_tables()); }

TEST_F(EngineTest, EmptyListOpenTablesOnInit) {
  EXPECT_EQ(0, db0.list_open_tables().size());
}

TEST_F(EngineTest, NumOpenTables) { EXPECT_EQ(5, db1.num_open_tables()); }

TEST_F(EngineTest, ListOpenTables) {
  EXPECT_EQ(5, db1.list_open_tables().size());
}

TEST_F(EngineTest, FindUnkownTable) {
  EXPECT_EQ(-1, db1.find_table_index("Unkown"));
}

TEST_F(EngineTest, FindTables) {
  EXPECT_EQ(0, db1.find_table_index("Test0"));
  EXPECT_EQ(1, db1.find_table_index("Test1"));
  EXPECT_EQ(2, db1.find_table_index("Test2"));
  EXPECT_EQ(3, db1.find_table_index("Test3"));
  EXPECT_EQ(4, db1.find_table_index("Test4"));
}

TEST_F(EngineTest, SelectTests) {
  EXPECT_EQ(db1.find_relation("Test0"), db1.select({}, "Test0"));

  std::vector<Column<std::string>> testselectcolumns;
  Column<std::string> testselectcolumn("Money");
  testselectcolumn.insert_entry("Money2");
  testselectcolumns.push_back(testselectcolumn);

  Relation testselectwhere("Test1", testselectcolumns);
  EXPECT_EQ(testselectwhere, db1.select({"Money"}, "Test1", "Money", "Money2"));

  std::vector<Column<std::string>> testselectcolumns2;
  Column<std::string> testselectcolumn2("Money");
  testselectcolumn2.insert_entry("Money5");
  testselectcolumns2.push_back(testselectcolumn2);

  Relation testselectwhere2("Test2", testselectcolumns2);
  EXPECT_EQ(testselectwhere2, db1.select({"Money"}, "Test2", "Scrooge", "bar"));
}

TEST_F(EngineTest, ProjectTests) {
  std::vector<Column<std::string>> testprojectcolumns;
  Column<std::string> col("Scrooge");
  col.primary_key(true);
  col.insert_entry("bah");
  col.insert_entry("hum");
  col.insert_entry("bug");
  col.insert_entry("foo");
  col.insert_entry("bar");
  testprojectcolumns.push_back(col);

  Relation testproject("Test0", testprojectcolumns);

  EXPECT_EQ(testproject, db1.project({"Scrooge"}, "Test0"));
}

TEST_F(EngineTest, UnionTests) {
  std::vector<Column<std::string>> testunioncolumns;
  Column<std::string> col1("Scrooge");
  col1.primary_key(true);
  col1.insert_entry("bah");
  col1.insert_entry("hum");
  col1.insert_entry("bug");
  col1.insert_entry("foo");
  col1.insert_entry("bar");
  col1.insert_entry("1");
  col1.insert_entry("2");
  col1.insert_entry("3");
  col1.insert_entry("4");
  col1.insert_entry("5");
  testunioncolumns.push_back(col1);

  Column<std::string> col2("Money");
  col2.insert_entry("$10");
  col2.insert_entry("$100");
  col2.insert_entry("$1000");
  col2.insert_entry("$10000");
  col2.insert_entry("$100000");
  col2.insert_entry("Money1");
  col2.insert_entry("Money2");
  col2.insert_entry("Money3");
  col2.insert_entry("Money4");
  col2.insert_entry("Money5");
  testunioncolumns.push_back(col2);

  Relation testunion("UnionTable", testunioncolumns);

  EXPECT_EQ(testunion, db1.setunion("Test0", "Test1"));

  Relation testunion2("INVALID");
  EXPECT_EQ(testunion2, db1.setunion("Test0", db1.select({"Money"}, "Test2")));
}

TEST_F(EngineTest, DifferenceTests) {
  Relation difftest1 = db1.find_relation("Test0");
  difftest1.title("DifferenceTable");
  EXPECT_EQ(difftest1, db1.setdifference("Test0", "Test2"));

  std::vector<Column<std::string>> testdiffcolumns;
  Column<std::string> col2("Money");
  col2.insert_entry("Money3");
  col2.insert_entry("Money4");
  testdiffcolumns.push_back(col2);

  Relation testdiff("DifferenceTable", testdiffcolumns);

  EXPECT_EQ(testdiff, db1.setdifference(db1.select({"Money"}, "Test1"),
                                        db1.select({"Money"}, "Test3")));
}

TEST_F(EngineTest, CrossProductTests) {
  std::vector<Column<std::string>> testcrosscolumns;
  Column<std::string> col1("Money");
  col1.insert_entry("$100");
  col1.insert_entry("$100");
  col1.insert_entry("$100");
  col1.insert_entry("$100");
  col1.insert_entry("$100");
  testcrosscolumns.push_back(col1);

  Column<std::string> col2("Name");
  col2.insert_entry("sam");
  col2.insert_entry("rabia");
  col2.insert_entry("nick");
  col2.insert_entry("kade");
  col2.insert_entry("leonardo");
  testcrosscolumns.push_back(col2);

  Relation testcross("CrossProductTable", testcrosscolumns);

  EXPECT_EQ(testcross, db1.setcrossproduct(
                           db1.select({"Money"}, "Test0", "Scrooge", "hum"),
                           db1.select({"Name"}, "Test4")));
}

class ParserTest : public ::testing::Test {
 protected:
  virtual void SetUp() { Engine db; }
};

  // TEST_F(ParserTests, SQLInsertTest) {
  //   EXPECT_
  // }

}  // Namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

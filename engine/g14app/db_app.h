#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <limits.h>

#include "../lib/engine.h"

using namespace std;

struct post {
  // string exe_cmd;//Execution Command for SQL side??
  int post_id = INT_MAX;  // Unique post ID for every post
  string author, title, content, month, day, year, full_date, tags;
  int commenting;
  vector<string> no_comma_tags;  // commas removed, tags put here

} p;

/*struct database{
  //TODO: make this for server interaction!

}db;*/

Engine dbengine;
// Database_manager dbengine;

void initialize_db();
void main_menu_operations();

void make_post();
void send_post();

void find_post();
void find_post_operations();

void find_author();
void find_title();
void find_tags();
void find_date();

void post_options(string);
void post_options_operations(string);

void view_post(string);

void edit_post(string);

void delete_post(string);
void comment_post(string);

void tag_scrubber();
void post_id_processing();
void post_id_deletion();

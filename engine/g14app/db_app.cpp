#include "db_app.h"

// initialize database engine
void initialize_db() {
  // create the table if necessary

  if (dbengine.execSQL("OPEN Poststable;") == 0) {
    // create table
    // Title, author, date, content, comments, commentingAllowed
    dbengine.execSQL(
        string("") +
        "CREATE TABLE Poststable (PostId INT, Title VARCHAR(64), " +
        "Author VARCHAR(32), Date VARCHAR(32), Content VARCHAR(256), " +
        "Comments VARCHAR(256), CommentingAllowed INT);");
  } else
    dbengine.execSQL("OPEN Poststable;");

  // check if Tagstable exists
  if (dbengine.execSQL("OPEN Tagstable;") == 0) {
    // if not create the table
    dbengine.execSQL(
        "CREATE TABLE Tagstable (post_id INT, tags VARCHAR(256));");
  } else
    dbengine.execSQL("OPEN Tagstable;");

  /* if(dbengine.execute("OPEN Poststable;") == -1){
          //create table
          //Title, author, date, content, comments, commentingAllowed
          dbengine.execute(string ("")
          + "CREATE TABLE Poststable (PostId INT, Title VARCHAR(64), "
          +  "Author VARCHAR(32), Date VARCHAR(32), Content VARCHAR(256), "
          +  "Comments VARCHAR(256), CommentingAllowed BOOLEAN)PRIMARY KEY
  (PostId, Title);");
  }
  else
          dbengine.execute("OPEN Poststable;");

  //check if Tagstable exists
  if(dbengine.execute("OPEN Tagstable;") == -1){
          //if not create the table
          dbengine.execute("CREATE TABLE Tagstable (post_id INT, tags
  VARCHAR(256));");
  }
  else
          dbengine.execute("OPEN Tagstable;");	 */
}

void main_menu() {
  cout << "<Hello, User! Welcome to the Web Log!> \n";
  cout << "<Choose a command by entering the corresponding number!>\n";
  cout << "[1] Make a Post\n";
  cout << "[2] Find a Post\n";
  cout << "[3] Exit Application\n";

  main_menu_operations();
}

void main_menu_operations() {
  char command;
  bool stuck_in_while = true;

  while (stuck_in_while) {
    cin >> command;

    switch (command) {
      case ('1'):
        make_post();
        stuck_in_while = false;
        break;
      case ('2'):
        find_post();
        stuck_in_while = false;
        break;
      case ('3'):
        cout << "<Have a nice day!>\n";
        dbengine.exitEngine();
        exit(1);
      default:
        cout << "<Sorry, but I'm looking for 1 2 or 3!>\n";
        cout << "<Try again, and then press enter!>\n";
        break;
    }
  }
}

void find_post() {
  cout << "\n<What would you like to search with?>\n";
  cout << "[1] Author\n";
  cout << "[2] Title\n";
  cout << "[3] Tag\n";
  cout << "[4] Date\n";
  cout << "[5] Return to menu\n";
  cout << "[6] Exit Application\n";

  find_post_operations();
}

void find_post_operations() {
  char command;
  bool stuck_in_while = true;  // Used to leave while-loop

  while (stuck_in_while) {
    cin >> command;

    switch (command) {
      case ('1'):
        find_author();
        stuck_in_while = false;
        break;
      case ('2'):
        find_title();
        stuck_in_while = false;
        break;
      case ('3'):
        find_tags();
        stuck_in_while = false;
        break;
      case ('4'):
        find_date();
        stuck_in_while = false;
        break;
      case ('5'):
        main_menu();
        stuck_in_while = false;
        break;
      case ('6'):
        cout << "<Have a nice day!>\n";
        exit(1);
      default:
        cout << "<Sorry, but I'm looking for 1 2 3 4 5 or 6!>\n";
        cout << "<Try again, and then press enter!>\n";
        break;
    }
  }
}

void find_author() {
  cin.ignore();
  // Flushes newline out of the buffer inbetween cin-getline call

  string author;
  cout << "Please type the name to search: ";
  getline(cin, author);

  // Create command
  /*    string query = string("") +
                    "select * from 'tablename?' where author = '" + author +
     "';"; */
  string query =
      string("") + "auth <- select (author == \"" + author + "\") Poststable;";

  // works on query
  dbengine.execSQL(query);
  // dbengine.execute(query);
  // Extracting posts from parsed query. If they exist.
  // using the relation, create vector of titles with given author

  /* const Relation& rel = dbms.get_relation("auth");
  //const vector<string>& row = rel.get_row(vector<string>{"Marty", "dog"});
  const vector<string>& row = rel.print_rows());  */

  int column_index = dbengine.find_relation("auth").find_column_index("Title");
  vector<std::string> titles =
      dbengine.find_relation("auth").get_column(column_index).entries();
  // dbengine.execSQL("SHOW auth;");
  // display the posts with selected author
  cout << "[Posts from " << author << "] \n";
  int num_posts = 0;
  int post_input;
  // display the all options
  for (int i = 0; i < titles.size(); ++i) {
    cout << "" << (i + 1) << ". " << titles[i] << "\n";
    num_posts = i + 1;
  }
  int main_option = num_posts + 1;
  // option to return to main menu
  cout << "" << main_option << ". Return to Main Menu\n";
  cout << "Enter the Post ID: ";
  cin >> post_input;
  // checking for valid input
  while (post_input < 1 || post_input > (main_option)) {
    cout << "Enter a proper Post ID: ";
    cin >> post_input;
  }
  if (post_input == (main_option)) main_menu();
  // send the selected post title to the options function
  string post_title =
      titles[post_input - 1];  // TODO: Actually pass title from DB
  post_options(post_title);
}

void find_title() {
  cin.ignore();
  // Flushes newline out of the buffer inbetween cin-getline call

  string title;
  cout << "Please type the title to search:";
  getline(cin, title);

  // Create command
  // string query = string("") +
  // "select * from 'tablename?' where title = '" + title + "';";

  string query =
      string("") + "ttl <- select (Title == \"" + Title + "\") Poststable; ";

  // works on query
  dbengine.execSQL(query);
  // dbengine.execute(query);
  /* const Relation& rel = dbms.get_relation("ttl");
  //const vector<string>& row = rel.get_row(vector<string>{"Marty", "dog"});
  const vector<string>& row = rel.print_rows());  */

  int column_index = dbengine.find_relation("ttl").find_column_index("Title");
  vector<std::string> titles =
      dbengine.find_relation("ttl").get_column(column_index).entries();
  // Extracting posts from parsed query. If they exist.
  // dbengine.execSQL("SHOW ttl;");

  // should only be one post when searching for title
  string post_title = "";  // TODO: Actually pass title from DB
  post_options(titles[0]);
}

void find_tags() {  // TODO: Use JOIN table w/ SQL!
  cin.ignore();
  // Flushes newline out of the buffer inbetween cin-getline call

  string tags;
  cout << "Please type the tags to search: ";
  getline(cin, tags);
  cout << "[Posts with tag " << tags << "] \n";
  string query =
      string("") + "tag <- select (tags == \"" + tags + "\") Tagstable; ";
  // Create command
  string query = string("") +  // TODO: Get from tags table!
                 "SELECT Poststable.PostId, Poststable.Title, tag.tags " +
                 "FROM Poststable " + "INNER JOIN Tagstable " +
                 "ON Poststable.PostId=Tagstable.post_id;";

  // db.execute(query);
  dbengine.execSQL(query);
  // works on query, not yet done. TODO: Parsing segment here

  // db.post something

  cout << "Enter the Post ID or 0 for main menu: ";
  cin >> post_input;
  // checking for valid input

  if (post_input == 0) main_menu();
  // send the selected post title to the options function
  string post_title =
      titles[post_input - 1];  // TODO: Actually pass title from DB
  post_options(post_title);
}

void find_date() {
  cin.ignore();
  // Flushes newline out of the buffer inbetween cin-getline call

  string date;
  cout << "Please type the date(EX: 05/31/1995) to search:";
  getline(cin, date);

  // Create command
  // TODO: concatenate month,day,year to make complete date for searching
  string query = string("") + "Date <- select (full_date == \"" + date +
                 "\") Poststable; ";

  dbengine.execSQL(query);
  // dbengine.execute(query);
  /* const Relation& rel = dbms.get_relation("ttl");
  //const vector<string>& row = rel.get_row(vector<string>{"Marty", "dog"});
  const vector<string>& row = rel.print());  */

  // db.post something
  // TODO: Work on extracting posts. If they exist.
  int column_index = dbengine.find_relation("Date").find_column_index("Title");
  vector<std::string> titles =
      dbengine.find_relation("Date").get_column(column_index).entries();

  cout << "[Posts on Date: " + date + "] \n";
  int num_posts = 0;
  int post_input;
  // display the all options
  for (int i = 0; i < titles.size(); i++) {
    cout << "" << (i + 1) << ". " << titles[i] << "\n";
    num_posts = i + 1;
  }
  int main_option = num_posts + 1;
  // option to return to main menu
  cout << "" << main_option << ". Return to Main Menu\n";
  cout << "Enter the Post ID: ";
  cin >> post_input;
  // checking for valid input
  while (post_input < 1 || post_input > (main_option)) {
    cout << "Enter a proper Post ID: ";
    cin >> post_input;
  }
  if (post_input == (main_option)) main_menu();
  // send the selected post title to the options function
  string post_title = titles[post_input - 1];  // Actually pass title from DB
  post_options(post_title);
}

void post_options(string post_title) {
  cout << "[" << post_title << "]\n";
  cout << "<What would you like to do?>\n";
  cout << "[1] View the post\n";
  cout << "[2] Edit the post\n";
  cout << "[3] Delete the post\n";
  cout << "[4] Comment on the post\n";
  cout << "[5] Return to the menu\n";
  cout << "[6] Exit the Application\n";

  post_options_operations(post_title);
}

void post_options_operations(string post_title) {
  char command;
  bool stuck_in_while = true;  // Used to leave while-loop

  while (stuck_in_while) {
    cin >> command;

    switch (command) {
      case ('1'):
        view_post(post_title);
        stuck_in_while = false;
        break;
      case ('2'):
        edit_post(post_title);
        stuck_in_while = false;
        break;
      case ('3'):
        delete_post(post_title);
        stuck_in_while = false;
        break;
      case ('4'):
        comment_post(post_title);
        stuck_in_while = false;
        break;
      case ('5'):
        main_menu();
        stuck_in_while = false;
        break;
      case ('6'):
        cout << "<Have a nice day!>\n";
        exit(1);
      default:
        cout << "<Sorry, but I'm looking for 1 2 3 4 5 or 6!>\n";
        cout << "<Try again, and then press enter!>\n";
        break;
    }
  }
}

void view_post(string post_title) {
  // Create command
  /* string query = string("") +
                 "MODIFY MEMO from Poststable where title = \""
                 + post_title + "\" [NO EDIT];"; */
  string query =
      string("") + "ttl <- select (Title == \"" + p.title + "\") Poststable;";
  dbengine.execSQL(query);
  dbengine.execSQL("SHOW ttl");
  // works on query, not yet done. TODO: Parsing segment here

  // cout<< string("") + post_title + "\n";

  post_options(string post_title);
}

void edit_post(string post_title) {
  // Create command. TODO: Double check all SQL
  string query = string("") + "MODIFY MEMO from Poststable where Title = \"" +
                 post_title + "\";";

  dbengine.execSQL(query);
  post_options(string post_title);
}

// TODO: Rework SQL and delete post ids appropriately
// Deleting post ids will involve removing from SQL
// And from the text file?
void delete_post(string post_title) {
  // create the query to remove the post from the DB

  string query = string("") + "ttl <- select (Title == \"" + post_title +
                 "\") Poststable; ";

  // works on query
  dbengine.execSQL(query);
  // Extract post_id from row that matches the post_name
  int column_index = dbengine.find_relation("ttl").find_column_index("PostId");
  vector<std::string> post_id =
      dbengine.find_relation("ttl").get_column(column_index).entries();

  query = string("") + "DELETE FROM Poststable WHERE Title = \"" + post_title +
          "\";";
  dbengine.execSQL(query);

  query = string("") + "DELETE FROM Tagstable WHERE post_id = \"" + post_id[0] +
          "\";";

  dbengine.execSQL(query);

  // TODO: Extract post_id from row that matches the post_name
  // dbengine.execSQL(query)
  // p.post_id = blah blah extracted post_id!

  /* p.post_id = 4;//Just to test!

  query = string("") +
              "DELETE FROM 'Tagstable' WHERE post_id = \"" +
              to_string(p.post_id) + "\";"; */

  post_id_deletion();

  post_options(post_title);
}

void comment_post(string post_title) {
  // implement
  string post_date;
  string name;
  string comment;
  string formatComment;

  // check to see if commenting is allowed
  string query = string("") + "comm <- select (Title == \"" + post_title +
                 "\") Poststable; ";
  dbengine.execSQL(query);
  int column_index =
      dbengine.find_relation("comm").find_column_index("CommentsAllowed");
  vector<std::string> comAllowed =
      dbengine.find_relation("comm").get_column(column_index).entries();
  if (comAllowed[0]) {
    cout << "Sorry comments are not allowed on this post.\n" post_options(
        post_title);
  }

  // need to take input for id, name, comment
  cout << "[Commenting on " << post_title << "]\n";
  cout << "Enter name: ";
  cin >> name;
  cout << "Enter Date: ";
  cin >> post_date;
  cout << "Enter comment: ";
  cin >> comment;
  cout << "Comment added";

  query = string("") + "ttl <- select (Title == \"" + post_title +
          "\") Poststable; ";
  dbengine.execSQL(query);
  column_index = dbengine.find_relation("ttl").find_column_index("Comments");
  vector<std::string> comments =
      dbengine.find_relation("ttl").get_column(column_index).entries();

  formatComment =
      string("") + "On " + post_date + ", " + name + " said: \n" + comment;
  // build query for adding comment
  query = string("") + "UPDATE Poststable SET Comments=\"" + comments[0] +
          "\n\n" + formatComment + "\" WHERE Title=\"" + post_title + ";";

  dbengine.execSQL(query);
  post_options(post_title);
}

void make_post() {
  cin.ignore();

  cout << "Please type your name: ";
  getline(cin, p.author);

  cout << "What's the title of your publication?: ";
  getline(cin, p.title);

  cout << "Please provide the body of the post, then press Enter: \n ";
  getline(cin, p.content);

  cout << "Please enter the month(EX: 5 for May): ";
  cin >> p.month;

  cout << "Please enter the day(EX: 21): ";
  cin >> p.day;

  cout << "Please enter the year(EX: 2017): ";
  cin >> p.year;
  p.full_date = "" + p.month + "/" + p.day + "/" + p.year;

  char commenting;
  cout << "Allow comments on this post? (y/n): ";
  cin >> commenting;
  if (commenting == 'y')
    p.commenting = 1;
  else
    p.commenting = 0;

  cout << "(Tag EX: funny,cute,silly,odd)\n";
  cout << "Please enter a few tags, separated by commas: ";
  getline(cin, p.tags);

  tag_scrubber();

  post_id_processing();

  // TODO: Tags semantics, USE SQL JOIN STUFF
  // General table and tag table will coordinate via ids
  // Can merge using INNER JOINs and such!

  // dbengine.execSQL(query);
  send_post();
}

void send_post() {
  // this will create a post in the db

  string query;

  if (p.commenting) {
    query = string("") + "INSERT INTO Poststable VALUES (" + "\"" +
            to_string(p.post_id) + "\", " + "\"" + p.title +
            "\", " +  // TODO: Fix this SQL ordering
            "\"" + p.author + "\", " + "\"" + p.full_date + "\", " + "\"" +
            p.content + "\", " + string("") + "\"1\", " + ");";

    dbengine.execSQL(query);
  } else {
    query = string("") + "INSERT INTO Poststable VALUES (" + "\"" +
            to_string(p.post_id) + "\", " + "\"" + p.title +
            "\", " +  // TODO: Fix this SQL ordering
            "\"" + p.author + "\", " + "\"" + p.full_date + "\", " + "\"" +
            p.content + "\", " + string("") + "\"0\", " + ");";

    dbengine.execSQL(query);
  }

  for (int i = 0; i < p.no_comma_tags.size(); ++i) {
    query = string("") + "(INSERT INTO Tagstable VALUES (" + "\"" +
            to_string(p.post_id) + "\"" + ", " + "\"" + p.no_comma_tags[i] +
            "\"" + "));";

    dbengine.execSQL(query);
    // cmd to exe query. TODO: Parse the segment?
    // TODO: work with DB team to execute query
  }
  main_menu();
}

// Removes commas and puts tags into vector no_comma_tags
void tag_scrubber() {
  cout << p.tags << endl;  // Testing
  int lc = 0;  // Location of last comma

  for (int i = 0; i < p.tags.length(); ++i) {
    if (p.tags.at(i) == ',') {
      if (i != 0) {  // Avoid pesky ',' as 1st char in str
        p.no_comma_tags.push_back(p.tags.substr(lc, i - lc));
        lc = i + 1;
      }
    }
  }

  // Takes care of last tag (for loop will miss)
  p.no_comma_tags.push_back(p.tags.substr(lc, p.tags.length() - lc));

  for (int i = 0; i < p.no_comma_tags.size(); ++i) {
    cout << p.no_comma_tags[i] << endl;  // Testing
  }
}

void post_id_processing() {
  string line;  // Holds input from file
  vector<int> post_ids;  // Holds int versions of all post ids

  fstream myfile("post_id_list.txt");
  if (myfile.is_open()) {  // Loads 'used' post ids into vect
    while (myfile >> line) {
      post_ids.push_back(stoi(line));  // stoi converts str to int
    }
    myfile.close();
  }

  // For testing. Shows results of above code
  for (int i = 0; i < post_ids.size(); ++i) {
    cout << "Postids: " << to_string(post_ids[i]) << endl;
  }

  // Finds unused post_id for use
  for (int i = 0; i < 1300; ++i) {  // Uses 1300 for simple testing
    for (int j = 0; j < post_ids.size(); ++j) {
      if (i == post_ids[j]) {
        break;  // End when 'i' is an id already in use
      }
      if (j == (post_ids.size() - 1)) {
        p.post_id = i;  // If all ids are checked, 'i' is unique
      }
    }

    // ENDFOR when post_id has been found
    if (p.post_id == i) {
      post_ids.push_back(p.post_id);
      break;
    }
  }

  myfile.open("post_id_list.txt");
  for (int i = 0; i < post_ids.size(); ++i) {
    myfile << post_ids[i] << endl;  // Writes ids to textfile
  }
  myfile.close();
}

void post_id_deletion() {
  string line;  // Holds input from file
  vector<int> post_ids;  // Holds int versions of all post ids

  fstream myfile("post_id_list.txt");
  if (myfile.is_open()) {  // Loads 'used' post ids into vect
    while (myfile >> line) {
      post_ids.push_back(stoi(line));  // stoi converts str to int
    }
    myfile.close();
  }

  // For testing. Shows results of above code
  for (int i = 0; i < post_ids.size(); ++i) {
    cout << "Before Postids: " << to_string(post_ids[i]) << endl;
  }

  for (int j = 0; j < post_ids.size(); ++j) {
    if (p.post_id == post_ids[j]) {
      post_ids.erase(post_ids.begin() + j);
      break;  // End when 'i' is an id already in use
    }
  }

  myfile.open("post_id_list.txt");
  for (int i = 0; i < (post_ids.size() - 1); ++i) {
    myfile << post_ids[i] << endl;  // Writes ids to textfile
  }
  myfile.close();

  // For testing. Shows results of above code
  for (int i = 0; i < post_ids.size(); ++i) {
    cout << "After Postids: " << to_string(post_ids[i]) << endl;
  }
}

int main() {
  initialize_db();  // open db or create tables if necessary

  main_menu();  // Starts up the app

  // close_db(); //write and close database
  dbengine.exitEngine();
  // execute("command blah blah");
  // Execute is currently on hold
}

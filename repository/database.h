//
// Created by horique on 3/20/24.
//

#ifndef OOP_A4_5_916_SILEA_HORIA_DATABASE_H
#define OOP_A4_5_916_SILEA_HORIA_DATABASE_H

#include <vector>
#include <map>
#include "../domain/tutorial.h"

using namespace std;

/*
 * Class that stores the tutorials.
 */
class Database {
private:
    vector<Tutorial> data;
    map<string, int> names;
    int exists(const string& title, const string& link);
    void validate_position(int position);

    /*
     * Function that saves the database to a pre-set text file.
     */
    void save_database();

    /*
     * Function that loads the database from a pre-set text file.
     */
    void load_database();
public:
    Database();
    ~Database();
    int get_size();
    vector<Tutorial>& get_data();
    map<string, int>& get_names();
    /*
     * Function that adds a tutorial to the database.
     * Throws an exception if a tutorial with the same name exists already.
     */
    void add_tutorial(Tutorial tutorial);
    /*
     * Function that removes a tutorial from the database, at the specified position.
     * Throws an exception if the position is invalid.
     */
    void remove_tutorial(int position);
    /*
     * Function that updates the title of a tutorial identified by position.
     * Throws an exception if the position is invalid or if the new title is taken.
     */
    void update_title(int position, const string& new_title);
    /*
     * Function that updates the presenter name of a tutorial identified by position.
     * Throws an exception if the specified position is invalid.
     */
    void update_presenter(int position, string new_presenter);
    /*
     * Function that updates the duration(minutes and seconds) of a tutorial identified by position.
     * Throws an exception if the specified position is invalid.
     */
    void update_duration(int position, int new_minutes, int new_seconds);
    /*
     * Function that updates the likes of a tutorial identified by position.
     * Throws an exception if the specified position is invalid.
     */
    void update_likes(int position, int new_likes);
    /*
    * Function that updates the link of a tutorial identified by position.
    * Throws an exception if the specified position is invalid.
    */
    void update_link(int position, string new_link);

    /*
     * Function that returns the position of a tutorial based on its title.
     */
    int get_position(const string& title);
};


#endif //OOP_A4_5_916_SILEA_HORIA_DATABASE_H

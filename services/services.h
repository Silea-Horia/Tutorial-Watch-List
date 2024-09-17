//
// Created by horique on 3/21/24.
//

#ifndef OOP_A4_5_916_SILEA_HORIA_SERVICES_H
#define OOP_A4_5_916_SILEA_HORIA_SERVICES_H

#include "../repository/database.h"

/*
 * Business side of the app, for the admin user.
 */
class Services {
private:
    Database* repository;
    static bool is_numeric(const string& str);
    static void validate_duration(const string& minutes, const string& seconds);
    static void validate_likes(const string& likes);
public:
    static void validate_position(const string& position);
    explicit Services(Database* database);
    /*
     * Function that returns the iterator for the database.
     */
    vector<Tutorial> get_iterator();
    map<string, int>& get_names();
    /*
     * Function that validates the parameters of a tutorial and adds it to the database.
     * Throws an exception if the minutes or seconds aren't numerical, if the likes aren't numerical or if the tutorial doesn't exist.
     */
    void add_tutorial(string title, string presenter, const string& minutes, const string& seconds, const string& likes, string link);
    /*
     * Function that removes a tutorial from the database.
     * Throws an exception if the specified position isn't a positive integer.
     */
    void remove_tutorial(const string& position);
    /*
     * Function that updates the title of a tutorial identified by position.
     * Throws an exception if the tutorial doesn't exist or if the new title is taken.
     */
    void update_title(const string& position, const string& new_title);
    /*
     * Function that updates the presenter name of a tutorial identified by position.
     * Throws an exception if the tutorial doesn't exist.
     */
    void update_presenter(const string& position, const string& new_presenter);
    /*
     * Function that updates the duration(minutes and seconds) of a tutorial identified by position.
     * Throws an exception if the minutes or seconds aren't positive integers or if the tutorial doesn't exist.
     */
    void update_duration(const string& position, const string& new_minutes, const string& new_seconds);
    /*
     * Function that updates the likes of a tutorial identified by position.
     * Throws an exception if the likes aren't a positive integer or if the tutorial doesn't exist.
     */
    void update_likes(const string& position, const string& new_likes);
    /*
    * Function that updates the link of a tutorial identified by position.
    * Throws an exception if the tutorial doesn't exist.
    */
    void update_link(const string& position, string new_link);
    /*
     * Function that adds 10 entries.
     */
    void add_entries();
};


#endif //OOP_A4_5_916_SILEA_HORIA_SERVICES_H

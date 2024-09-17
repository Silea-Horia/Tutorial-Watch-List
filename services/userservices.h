//
// Created by horique on 3/27/24.
//

#ifndef OOP_A4_5_916_SILEA_HORIA_USERSERVICES_H
#define OOP_A4_5_916_SILEA_HORIA_USERSERVICES_H

#include "../repository/database.h"
#include "services.h"
#include <vector>
#include "writer.h"

using namespace std;

/*
 * Business side of app, for non-admin user.
 */
class UserServices {
    friend Services;
private:
    vector<Tutorial> watchList;
    Database* database;
    vector<Tutorial> temporary_search;
    CSVWriter* csvWriter;
    HTMLWriter* htmlWriter;
public:
    explicit UserServices(Database* database, CSVWriter* _csvWriter, HTMLWriter* _htmlWriter);
    ~UserServices();
    /*
     * Function that returns an iterator over the database.
     */
    vector<Tutorial> get_database();

    /*
     * Function that returns an iterator over the watchlist.
     */
    vector<Tutorial> get_watchlist();
    vector<Tutorial> get_search();

    /*
     * Function that returns an iterator over the temporary search.
     * The search is performed by filling the temporary_search dynamic array with copies of the tutorials whose presenter names
     * correspond to the given one.
     * If no presenter name is given, then add all the elements.
     */
    vector<Tutorial>& search(const string& presenter_name);
    
    /* 
     * Function that removes a tutorial at a given position from the temporary search list.
     */
    void remove_from_search(int position);

    /*
     * Function that adds a tutorial to the watch list.
     */
    void add_to_watchlist(Tutorial tutorial);

    /*
     * Function that returns the length of the search vector.
     */
    int search_length();

    /*
     * Function that returns true if the specified tutorial is in the watchlist, false otherwise.
     */
    bool is_in_watchlist(Tutorial tutorial);

    /*
     * Function that validates that the position specified is correct and removes the tutorial.
     */
    void remove_from_watchlist(const string& position, bool like);

    void open_csv_watch_list();

    void open_html_watch_list();
};


#endif //OOP_A4_5_916_SILEA_HORIA_USERSERVICES_H

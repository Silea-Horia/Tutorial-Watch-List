//
// Created by horique on 3/27/24.
//

#include <algorithm>
#include "userservices.h"
#include "CustomException.h"

UserServices::UserServices(Database* database, CSVWriter* _csvWriter, HTMLWriter* _htmlWriter) {
    this->database = database;
    this->csvWriter = _csvWriter;
    this->htmlWriter = _htmlWriter;
}

UserServices::~UserServices() {
    delete(this->csvWriter);
    delete(this->htmlWriter);
}

vector<Tutorial> UserServices::get_database() {
    return this->database->get_data();
}

vector<Tutorial> UserServices::get_watchlist() {
    return this->watchList;
}

vector<Tutorial> UserServices::get_search() {
    return this->temporary_search;
}

vector<Tutorial>& UserServices::search(const string& presenter_name) {
    temporary_search.clear();

    if (presenter_name.empty()) {
        //copy(temporary_search.begin(), this->database->get_data().begin(), this->database->get_data().end());
        temporary_search = this->database->get_data();
    }
    else {
        for (Tutorial tutorial1 : this->database->get_data())
            if (tutorial1.get_presenter() == presenter_name)
                temporary_search.push_back(tutorial1);
    }

    return temporary_search;
}

void UserServices::remove_from_search(int position) {
	this->temporary_search.erase(temporary_search.begin() + position);
}

void UserServices::add_to_watchlist(Tutorial tutorial) {
    if (is_in_watchlist(tutorial)) throw ValidateException("Tutorial already in watchlist!");
    watchList.push_back(tutorial);
    this->csvWriter->write(this->watchList);
    this->htmlWriter->write(this->watchList);
}

int UserServices::search_length() {
    return (int)this->temporary_search.size();
}

bool UserServices::is_in_watchlist(Tutorial tutorial) {
    for (Tutorial tut : this->watchList) {
        if (tut.get_title() == tutorial.get_title()) return true;
    }
    return false;
}

void UserServices::remove_from_watchlist(const string& position, bool like) {

    int i_position = stoi(position);

    if (i_position < 0 || i_position >= this->watchList.size()) throw ValidateException("Invalid position!");

    string title = this->watchList[i_position].get_title();

    if (like) this->database->update_likes(this->database->get_position(title), this->watchList[i_position].get_likes() + 1);

    this->watchList.erase(this->watchList.begin() + i_position);

    this->csvWriter->write(this->watchList);
    this->htmlWriter->write(this->watchList);

}

void UserServices::open_csv_watch_list() {
    this->csvWriter->open();
}

void UserServices::open_html_watch_list() {
    this->htmlWriter->open();
}
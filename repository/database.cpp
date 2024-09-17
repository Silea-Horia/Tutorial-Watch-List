//
// Created by horique on 3/20/24.
//

#include "database.h"
#include <utility>
#include <fstream>
#include <iostream>
#include "../services/CustomException.h"

Database::Database() {
    this->load_database();
}

Database::~Database() {
    this->save_database();
}

void Database::load_database() {
    ifstream file;
    file.open("../repository/database.txt");
    Tutorial tut{};
    this->data.clear();
    this->names.clear();
    while (file >> tut) {
        this->data.push_back(tut);
        if (this->names.contains(tut.get_presenter())) this->names[tut.get_presenter()]++;
        else this->names.insert(make_pair(tut.get_presenter(), 1));
    }
    file.close();
}

void Database::save_database() {
    ofstream file;
    file.open("../repository/database.txt");
    for (Tutorial tutorial : this->data)
        file << tutorial;
    file.close();
}

vector<Tutorial>& Database::get_data() {
    this->load_database();
    return this->data;
}

int Database::exists(const string& title, const string& link="") {
    int i = 0;
    for (Tutorial tut : this->data) {
        if (tut.get_title() == title) {
            return i;
        }
        i++;
    }
    return -1;
}

void Database::validate_position(int position) {
    if (position < 0 || position >= this->get_size()) throw RepoException("Invalid position!");
}

int Database::get_size() {
    return (int)this->data.size() + 1;
}

void Database::add_tutorial(Tutorial tutorial) {
    if(exists(tutorial.get_title(), tutorial.get_link()) != -1)
        throw RepoException("Tutorial already exists!");
    this->data.push_back(tutorial);
    this->save_database();
    if (this->names.contains(tutorial.get_presenter())) this->names[tutorial.get_presenter()]++;
    else this->names.insert(make_pair(tutorial.get_presenter(), 1));
}

void Database::remove_tutorial(int position) {
    validate_position(position);

    if (--this->names[(data.begin() + position)->get_presenter()] == 0) {
        this->names.erase((data.begin() + position)->get_presenter());
    }

    this->data.erase(data.begin() + position);
    this->save_database();
}

void Database::update_title(int position, const string& new_title) {
    validate_position(position);
    if(exists(new_title) != -1)
        throw RepoException("New title is already in use!");
    this->data[position].set_title(new_title);
    this->save_database();
}

void Database::update_presenter(int position, string new_presenter) {
    validate_position(position);

    //cout << (data.begin() + position)->get_presenter() << " " << this->names[(data.begin() + position)->get_presenter()];
    this->names[(data.begin() + position)->get_presenter()]--;
    if (this->names[(data.begin() + position)->get_presenter()] == 0) {
        this->names.erase((data.begin() + position)->get_presenter());
    }
    if (this->names.contains(new_presenter)) this->names[new_presenter]++;
    else this->names.insert(make_pair(new_presenter, 1));

    this->data[position].set_presenter(std::move(new_presenter));
    this->save_database();
}

void Database::update_duration(int position, int new_minutes, int new_seconds) {
    validate_position(position);
    this->data[position].set_duration(new_minutes, new_seconds);
    this->save_database();
}

void Database::update_likes(int position, int new_likes) {
    validate_position(position);
    this->data[position].set_likes(new_likes);
    this->save_database();
}

void Database::update_link(int position, string new_link) {
    validate_position(position);
    this->data[position].set_link(std::move(new_link));
    this->save_database();
}

int Database::get_position(const string& title) {
    int i = 0;
    for (Tutorial tut : this->data)
        if (tut.get_title() == title) return i;
        else i++;

    return -1;
}

map<string, int> &Database::get_names() {
    return this->names;
}



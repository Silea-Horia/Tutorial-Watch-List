//
// Created by horique on 3/20/24.
//

#include "tutorial.h"
#include <utility>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

Tutorial::Tutorial(string title, string presenter, int minutes, int seconds, int likes, string link) {
    this->title = std::move(title);

    this->presenter = std::move(presenter);

    this->minutes = minutes;

    this->seconds = seconds;

    this->likes = likes;

    this->link = std::move(link);
}

string Tutorial::get_title() {
    return this->title;
}

void Tutorial::set_title(string new_title){
    this->title = std::move(new_title);
}

string Tutorial::get_presenter() {
    return this->presenter;
}

void Tutorial::set_presenter(string new_presenter){
    this->presenter = std::move(new_presenter);
}

int Tutorial::get_minutes() const {
    return this->minutes;
}

int Tutorial::get_seconds() const {
    return this->seconds;
}

void Tutorial::set_duration(int new_minutes, int new_seconds){
    this->minutes = new_minutes;
    this->seconds = new_seconds;
}

int Tutorial::get_likes() const {
    return this->likes;
}

void Tutorial::set_likes(int new_likes){
    this->likes = new_likes;
}

string Tutorial::get_link() {
    return this->link;
}

void Tutorial::set_link(string new_link){
    this->link = std::move(new_link);
}

string Tutorial::string_format() {
    string format = this->title + " by " + this->presenter + " | " + to_string(this->minutes) + ":" +
            to_string(this->seconds) + " | " + to_string(this->likes) + " likes | " + this->link;
    return format;
}

string Tutorial::string_format_db() {
    string format = this->title + "," + this->presenter + "," + to_string(this->minutes) + "," +
                    to_string(this->seconds) + "," + to_string(this->likes) + "," + this->link;
    return format;
}

bool Tutorial::operator==(Tutorial& other) {
    return this->title == other.title;
}

istream & operator>>(istream & stream, Tutorial & t)
{
    string input;
    getline(stream, input);
    stringstream ss(input);

    string token;
    vector<string> tokens;

    char delimiter = ',';

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    if (tokens.empty()) return stream;

    t.title = tokens[0];
    t.presenter = tokens[1];
    t.minutes = stoi(tokens[2]);
    t.seconds = stoi(tokens[3]);
    t.likes = stoi(tokens[4]);
    t.link = tokens[5];

    return stream;
}

ostream &operator<<(ostream &stream, Tutorial &t) {
    stream << t.string_format_db();
    stream << "\n";
    return stream;
}


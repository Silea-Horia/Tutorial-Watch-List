//
// Created by horique on 3/21/24.
//

#include <utility>
#include "services.h"
#include <iostream>
#include <algorithm>
#include "CustomException.h"

Services::Services(Database* database) {
    this->repository = database;
}

bool Services::is_numeric(const string& str) {
    return std::all_of(str.begin(), str.end(), [](char ch){return isdigit(ch);});
}

void Services::validate_duration(const std::string& minutes, const std::string& seconds) {
    if(!(is_numeric(minutes) && is_numeric(seconds))) throw ValidateException("Duration must be specified by positive integers!");
}

void Services::validate_position(const std::string& position) {
    if (!is_numeric(position)) throw ValidateException("Position must be a positive integer!");
}

void Services::validate_likes(const std::string& likes) {
    if (!is_numeric(likes)) throw ValidateException("Likes count must be a positive integer!");
}

vector<Tutorial> Services::get_iterator() {
    return this->repository->get_data();
}

void Services::add_tutorial(string title, string presenter, const string& minutes, const string& seconds, const string& likes, string link) {
    validate_duration(minutes, seconds);
    validate_likes(likes);

    int i_minutes = stoi(minutes), i_seconds = stoi(seconds), i_likes = stoi(likes);
    Tutorial new_tutorial(std::move(title), std::move(presenter), i_minutes, i_seconds, i_likes, std::move(link));

    this->repository->add_tutorial(new_tutorial);
}

void Services::remove_tutorial(const std::string& position) {
    validate_position(position);
    this->repository->remove_tutorial(stoi(position));
}

void Services::update_title(const std::string& position, const std::string& new_title) {
    validate_position(position);
    this->repository->update_title(stoi(position), new_title);
}

void Services::update_presenter(const std::string& position, const std::string& new_presenter) {
    validate_position(position);
    this->repository->update_presenter(stoi(position), new_presenter);
}

void Services::update_duration(const std::string& position, const std::string& new_minutes, const std::string& new_seconds) {
    validate_duration(new_minutes, new_seconds);
    validate_position(position);
    int i_minutes = stoi(new_minutes), i_seconds = stoi(new_seconds), i_position = stoi(position);
    this->repository->update_duration(i_position, i_minutes, i_seconds);
}

void Services::update_likes(const std::string& position, const std::string& new_likes) {
    validate_position(position);
    validate_likes(new_likes);
    int i_likes = stoi(new_likes), i_position = stoi(position);
    this->repository->update_likes(i_position, i_likes);
}

void Services::update_link(const std::string& position, std::string new_link) {
    this->repository->update_link(stoi(position), std::move(new_link));
}

void Services::add_entries() {
    this->add_tutorial("How to open CLion", "Harry", "10", "20", "123444", "https://www.youtube.com/watch?v=7qMk79sIv5U");
    this->add_tutorial("How to close CLion", "Harry", "00", "40", "10", "https://www.youtube.com/watch?v=rfdqzfsCmx0");
    this->add_tutorial("How to create a project", "Harry", "50", "21", "2137", "https://www.youtube.com/watch?v=8qG_BK11nLg");
    this->add_tutorial("How to save a project", "Harry", "03", "00", "477", "https://www.youtube.com/watch?v=x8oca0LB6Fc");
    this->add_tutorial("How to push to GitHub", "Harry", "45", "56", "875", "https://www.youtube.com/watch?v=ZzaPdXTrSb8");
    this->add_tutorial("How to deal with memory leaks", "Harry", "59", "59", "6549039", "https://www.youtube.com/watch?v=7DCO-IISBnc");
    this->add_tutorial("How to copy/paste code", "Harry", "28", "50", "7690", "https://www.youtube.com/watch?v=wN0x9eZLix4");
    this->add_tutorial("How to think about C++ at night", "Michael", "54", "05", "955", "https://www.youtube.com/watch?v=ZzaPdXTrSb8");
    this->add_tutorial("How not to go insane doing your homework", "Alex", "33", "56", "8563078", "https://www.youtube.com/watch?v=MNeX4EGtR5Y");
    this->add_tutorial("How to sleep well after doing your homework", "Alex", "00", "59", "145444", "https://www.youtube.com/watch?v=i_wDa2AS_8w");
}

map<string, int> &Services::get_names() {
    return this->repository->get_names();
}

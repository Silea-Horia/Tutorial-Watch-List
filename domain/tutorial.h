//
// Created by horique on 3/20/24.
//

#ifndef OOP_A4_5_916_SILEA_HORIA_TUTORIAL_H
#define OOP_A4_5_916_SILEA_HORIA_TUTORIAL_H

#include <string>
using namespace std;

/*
 * Class that stores a Tutorial entity, with a title, presenter, duration, likes count and a link.
 */
class Tutorial {
private:
    string title;
    string presenter;
    int minutes, seconds;
    int likes;
    string link;

public:
    explicit Tutorial(string title = "", string presenter = "", int minutes = -1, int seconds = -1, int likes = -1, string link = "");
    string get_title();
    void set_title(string new_title);
    string get_presenter();
    void set_presenter(string new_presenter);
    int get_minutes() const;
    int get_seconds() const;
    void set_duration(int new_minutes, int new_seconds);
    int get_likes() const;
    void set_likes(int new_likes);
    string get_link();
    void set_link(string new_link);
    /*
     * Function that returns the string format of a Tutorial
     */
    string string_format();
    bool operator==(Tutorial& other);
    friend istream & operator>>(istream & stream, Tutorial & t);
    friend ostream & operator<<(ostream & stream, Tutorial & t);

    string string_format_db();
};


#endif //OOP_A4_5_916_SILEA_HORIA_TUTORIAL_H

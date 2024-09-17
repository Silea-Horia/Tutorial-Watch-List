//
// Created by horique on 4/17/24.
//

#include "writer.h"
#include <fstream>

void CSVWriter::write(vector<Tutorial> watchList) {
    ofstream file;
    file.open("../repository/watch_list.csv");

    for (Tutorial tutorial : watchList) {
        file << tutorial;
    }

    file.close();
}

void CSVWriter::open() {
    string command = "open ../repository/watch_list.csv";
    system(command.c_str());
}

void HTMLWriter::write(vector<Tutorial> watchList) {
    ofstream file;
    file.open("../repository/watch_list.html");

    file << "<!DOCTYPE html>\n"
            "<html>\n"
            "<head>\n"
            "    <title>Watch List</title>\n"
            "</head>\n"
            "<body>\n"
            "<table border=\"1\">\n"
            "    <tr>\n"
            "        <td>Title</td>\n"
            "        <td>Presenter</td>\n"
            "        <td>Duration</td>\n"
            "        <td>Likes</td>\n"
            "        <td>YouTube link</td>\n"
            "    </tr>\n";

    for (Tutorial tutorial : watchList) {
        file << "    <tr>\n"
                "        <td>" + tutorial.get_title() + "</td>\n" +
                "        <td>" + tutorial.get_presenter() + "</td>\n" +
                "        <td>" + to_string(tutorial.get_minutes()) + ":" + to_string(tutorial.get_seconds()) + "</td>\n" +
                "        <td>" + to_string(tutorial.get_likes()) + "</td>\n" +
                "        <td><a href=\"" + tutorial.get_link() + "\">Link</a></td>\n"
                "    </tr>\n";
    }

    file << "</table>\n"
            "</body>\n"
            "</html>";

    file.close();
}

void HTMLWriter::open() {
    string command = "open ../repository/watch_list.html";
    system(command.c_str());
}

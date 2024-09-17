//
// Created by horique on 5/27/24.
//

#include "Operation.h"

void AddOperation::execute() {
    repo.add_tutorial(tutorial);
}

void AddOperation::undo() {
    repo.remove_tutorial(repo.get_position(tutorial.get_title()));
}

void AddOperation::redo() {
    execute();
}

void RemoveOperation::execute() {
    repo.remove_tutorial(repo.get_position(tutorial.get_title()));
}

void RemoveOperation::undo() {
    repo.add_tutorial(tutorial);
}

void RemoveOperation::redo() {
    execute();
}

void EditOperation::execute() {
    int position = repo.get_position(oldTutorial.get_title());
    if (!newTutorial.get_presenter().empty()) repo.update_presenter(position, newTutorial.get_presenter());
    if (!newTutorial.get_link().empty()) repo.update_link(position, newTutorial.get_link());
    if (newTutorial.get_likes() != -1) repo.update_likes(position, newTutorial.get_likes());
    if (newTutorial.get_minutes() != -1) repo.update_duration(position, newTutorial.get_minutes(), newTutorial.get_seconds());
    if (!newTutorial.get_title().empty()) repo.update_title(position, newTutorial.get_title());
}

void EditOperation::undo() {
    int position = newTutorial.get_title().empty() ? repo.get_position(oldTutorial.get_title()) : repo.get_position(newTutorial.get_title());
    repo.update_presenter(position, oldTutorial.get_presenter());
    repo.update_link(position, oldTutorial.get_link());
    repo.update_likes(position, oldTutorial.get_likes());
    repo.update_duration(position, oldTutorial.get_minutes(), oldTutorial.get_seconds());
    if (!newTutorial.get_title().empty()) repo.update_title(position, oldTutorial.get_title());
}

void EditOperation::redo() {
    execute();
}

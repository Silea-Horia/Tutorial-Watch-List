//
// Created by horique on 5/27/24.
//

#include "CommandController.h"

void CommandController::addCommand(AbstractOperation *command) {
    command->execute();
    undoStack.push_back(command);
    redoStack.clear();
}

void CommandController::undo() {
    if (undoStack.empty())
        throw ValidateException("No more undoes!");
    AbstractOperation* command = undoStack.back();
    undoStack.pop_back();
    command->undo();
    redoStack.push_back(command);
}

void CommandController::redo() {
    if (redoStack.empty())
        throw ValidateException("No more redoes!");
    AbstractOperation* command = redoStack.back();
    redoStack.pop_back();
    command->redo();
    undoStack.push_back(command);
}

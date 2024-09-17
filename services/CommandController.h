//
// Created by horique on 5/27/24.
//

#ifndef OOP_A10_916_SILEA_HORIA_COMMANDCONTROLLER_H
#define OOP_A10_916_SILEA_HORIA_COMMANDCONTROLLER_H

#include "../domain/tutorial.h"
#include "Operation.h"
#include "CustomException.h"
#include <vector>

/*
 * Class that stores the commands in a stack for undo and redo purposes.
 */
class CommandController {
private:
    std::vector<AbstractOperation*> undoStack;
    std::vector<AbstractOperation*> redoStack;
public:
    void addCommand(AbstractOperation* command);
    void undo();
    void redo();
};


#endif //OOP_A10_916_SILEA_HORIA_COMMANDCONTROLLER_H

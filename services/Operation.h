//
// Created by horique on 5/27/24.
//

#ifndef OOP_A10_916_SILEA_HORIA_OPERATION_H
#define OOP_A10_916_SILEA_HORIA_OPERATION_H

#include <utility>

#include "services.h"
#include "../repository/database.h"

/*
 * Abstract class that is the base for explicit commands that are held in the undo/redo stack.
 */
class AbstractOperation {
public:
    virtual void execute()=0;
    virtual void undo()=0;
    virtual void redo()=0;
};

class AddOperation : public AbstractOperation {
private:
    Database &repo;
    Tutorial tutorial;
public:
    AddOperation(Database &repo, Tutorial tutorial) : repo(repo), tutorial(std::move(tutorial)) {};
    void execute() override;
    void undo() override;
    void redo() override;

};

class RemoveOperation : public AbstractOperation {
private:
    Database &repo;
    Tutorial tutorial;
public:
    RemoveOperation(Database &repo, Tutorial tutorial) : repo(repo), tutorial(std::move(tutorial)) {};
    void execute() override;
    void undo() override;
    void redo() override;
};

class EditOperation : public AbstractOperation {
private:
    Database &repo;
    Tutorial oldTutorial, newTutorial;
public:
    EditOperation(Database &repo, Tutorial oldTutorial, Tutorial newTutorial) : repo(repo), oldTutorial(std::move(oldTutorial)),
                                                                                newTutorial(std::move(newTutorial)) {};
    void execute() override;
    void undo() override;
    void redo() override;
};

#endif //OOP_A10_916_SILEA_HORIA_OPERATION_H

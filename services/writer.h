//
// Created by horique on 4/17/24.
//

#ifndef OOP_A6_7_916_SILEA_HORIA_WRITER_H
#define OOP_A6_7_916_SILEA_HORIA_WRITER_H

#include <vector>
#include "../domain/tutorial.h"

/*
 * Abstract class to provide a model for the concrete classes that write to specific file formats.
 */
class AbstractWriter {
public:
    virtual void write(vector<Tutorial> watchList)=0;
    virtual void open()=0;
};

class CSVWriter : public AbstractWriter {
public:
    void write(vector<Tutorial> watchList) override;
    void open() override;
};

class HTMLWriter : public AbstractWriter {
public:
    void write(vector<Tutorial> watchList) override;
    void open() override;
};


#endif //OOP_A6_7_916_SILEA_HORIA_WRITER_H

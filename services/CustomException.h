//
// Created by horique on 4/16/24.
//

#ifndef OOP_A6_7_916_SILEA_HORIA_CUSTOMEXCEPTION_H
#define OOP_A6_7_916_SILEA_HORIA_CUSTOMEXCEPTION_H

#include <exception>
#include <string>
#include <utility>

using namespace std;

class CustomException : public exception {
protected:
    string message;
public:
    explicit CustomException(string _message) { this->message = std::move(_message); };
    const char* what() const noexcept override {
        return message.c_str();
    };
};

class RepoException : public CustomException {
public:
    explicit RepoException(string _message) : CustomException(std::move(_message)) {};
};

class ValidateException : public CustomException {
public:
    explicit ValidateException(string _message) : CustomException(std::move(_message)) {};
};

#endif //OOP_A6_7_916_SILEA_HORIA_CUSTOMEXCEPTION_H

#ifndef MENDELEEV_FUNCTIONS_H
#define MENDELEEV_FUNCTIONS_H
#include <iostream>

class Exception {
public:
    const std::string message;
    const std::string name;
    Exception (std::string m = "", std::string n = "Exception") : message(m), name(n) {}
    std::string getMessage() {
        return this->message;
    }
    std::string getName() {
        return this->name;
    }
    friend std::ostream& operator<<(std::ostream& out, Exception exception) {
        out << exception.getName() << ": " << exception.getMessage();
        return out;
    }
};

class ElementNotFoundException : public Exception {
public:
    ElementNotFoundException(std::string m = "") : Exception(m, "ElementNotFound") {}
};

class IncorrectOrbitalNameException : public Exception {
public:
    IncorrectOrbitalNameException(std::string m = "") : Exception(m, "IncorrectOrbitalNameException") {}
};


#endif //MENDELEEV_FUNCTIONS_H

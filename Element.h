#ifndef MENDELEEV_ELEMENT_H
#define MENDELEEV_ELEMENT_H


#include <vector>
#include <string>


enum class Metal {
    METAL,
    NONMETAL,
    UNKNOWN
};

void initElement(int numIn, int& periodOut, int& groupOut, bool& subGroupOut, Metal& metalOut);

class Element {
private:
    int number;
    std::string symbol;
    std::string rusName;
    double relMass;
    int period;
    int group;
    bool subGroup;
    Metal metal;
    int Z = 0;
public:

    Element(int num = 1, std::string symb = "H", std::string name = "Водород", double mass = 1.0) :
            number(num),
            symbol(symb),
            rusName(name),
            relMass(mass)
    {
        initElement(number, period, group, subGroup, metal);
    }

    //Position in MendeleevTable
    int getNumber() const {
        return this->number;
    }

    int getPeriod() const {
        return this->period;
    }
    int getGroup() const {
        return this->group;
    }
    bool getSubGroup() const {
        return this->subGroup;
    }
    // ************
    std::string getSymbol() const {
        return this->symbol;
    }
    std::string getName() const {
        return this->rusName;
    }


    //Element's parameters

    double getRelMass() const {
        return this->relMass;
    }
    int getZ() const {
        return this->Z;
    }
    Metal getMetal() const {
        return this->metal;
    }
    void setZ(int newZ) {
        this->Z = newZ;
    }
    //Maths functions
    int getProtons() const;
    int getNeutrons() const;
    int getElectrons() const;
    int getValency() const;
    int getMaxOxid() const;
    int getMinOxid() const;
    bool operator==(Element& other) const;
    std::vector<std::vector<int>> getElectronVector() const;
    //out functions
    std::string getNumberOfPNE() const; // Protons, Neutrons, Electrons
    std::string getElectronGroupPosition() const;
    std::string getElectronSubGroupPosition() const;
};

#endif //MENDELEEV_ELEMENT_H

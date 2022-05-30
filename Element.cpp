#include "Element.h"
#include "exceptions.h"


void initElement(int numIn, int& periodOut, int& groupOut, bool& subGroupOut, Metal& metalOut) {
    switch (numIn) {
        case 1 ... 2:
            periodOut = 1;
            break;
        case 3 ... 10:
            periodOut = 2;
            break;
        case 11 ... 18:
            periodOut = 3;
            break;
        case 19 ... 36:
            periodOut = 4;
            break;
        case 37 ... 54:
            periodOut = 5;
            break;
        case 55 ... 86:
            periodOut = 6;
            break;
        case 87 ... 118:
            periodOut = 7;
            break;
        default:
            periodOut = -1;
    } // periodOut
    switch (numIn) {
        case 1:
        case 3:
        case 11:
        case 19:
        case 29:
        case 37:
        case 47:
        case 55:
        case 79:
        case 87:
        case 111:
            groupOut = 1;
            break;
        case 4:
        case 12:
        case 20:
        case 30:
        case 38:
        case 48:
        case 56:
        case 80:
        case 88:
        case 112:
            groupOut = 2;
            break;
        case 5:
        case 13:
        case 21:
        case 31:
        case 39:
        case 49:
        case 57 ... 71:
        case 81:
        case 89 ... 103:
        case 113:
            groupOut = 3;
            break;
        case 6:
        case 14:
        case 22:
        case 32:
        case 40:
        case 50:
        case 72:
        case 82:
        case 104:
        case 114:
            groupOut = 4;
            break;
        case 7:
        case 15:
        case 23:
        case 33:
        case 41:
        case 51:
        case 73:
        case 83:
        case 105:
        case 115:
            groupOut = 5;
            break;
        case 8:
        case 16:
        case 24:
        case 34:
        case 42:
        case 52:
        case 74:
        case 84:
        case 106:
        case 116:
            groupOut = 6;
            break;
        case 9:
        case 17:
        case 25:
        case 35:
        case 43:
        case 53:
        case 75:
        case 85:
        case 107:
        case 117:
            groupOut = 7;
            break;
        case 2:
        case 10:
        case 18:
        case 26 ... 28:
        case 36:
        case 44 ... 46:
        case 54:
        case 76 ... 78:
        case 86:
        case 108 ... 110:
        case 118:
            groupOut = 8;
            break;
        default:
            groupOut = -1;
    } // groupOut
    switch (numIn) {
        case 1 ... 20:
        case 31 ... 38:
        case 49 ... 56:
        case 81 ... 88:
        case 113 ... 118:
            subGroupOut = true;
            break;
        case 21 ... 30:
        case 39 ... 48:
        case 57 ... 80:
        case 89 ... 112:
            subGroupOut = false;
    } // subGroupOut
    switch (numIn) {
        case 3 ... 4:
        case 11 ... 13:
        case 19 ... 32:
        case 37 ... 51:
        case 55 ... 84:
        case 87 ... 108:
        case 112:
            metalOut = Metal::METAL;
            break;
        case 109 ... 111:
        case 113 ... 118:
            metalOut = Metal::UNKNOWN;
        default:
            metalOut = Metal::NONMETAL;
    } // metalOut
}

// Maths in Element
int Element::getProtons() const {
    return this->getNumber();
}
int Element::getNeutrons() const {
    return (int)this->getRelMass() - this->getProtons();
}
int Element::getElectrons() const {
    return this->getProtons() - this->getZ();
}
int Element::getValency() const {
    switch (this->number) {
        case 7:
            return 3;
        case 8:
            return 2;
        case 9:
            return 1;
        default:
            return this->getGroup();
    }
}
int Element::getMaxOxid() const {
    if (this->number == 9 || (this->getSubGroup() && this->getGroup() == 8)) {
        return 0;
    }else if (this->number == 8) {
        return 2;
    } else {
        return this->getGroup();
    }
}
int Element::getMinOxid() const {
    if (this->getMetal() == Metal::METAL || (this->getSubGroup() && this->getGroup() == 8)) {
        return 0;
    } else if (this->number == 1) {
        return -1;
    } else {
        return this->getGroup() - 8;
    }
}

int _getElectronsOnOrbital(std::string orbitalName, int numOfElectrons) {
    int numberFromWhichStartsOrbital =
                    (
                        orbitalName == "1s" ? 1 :
                        orbitalName == "2s" ? 3 :
                        orbitalName == "2p" ? 5 :
                        orbitalName == "3s" ? 11 :
                        orbitalName == "3p" ? 13 :
                        orbitalName == "4s" ? 19 :
                        orbitalName == "3d" ? 21 :
                        orbitalName == "4p" ? 31 :
                        orbitalName == "5s" ? 37 :
                        orbitalName == "4d" ? 39 :
                        orbitalName == "5p" ? 49 :
                        orbitalName == "6s" ? 55 :
                        orbitalName == "4f" ? 58 :
                        orbitalName == "5d" ? 72 :
                        orbitalName == "6p" ? 81 :
                        orbitalName == "7s" ? 87 :
                        orbitalName == "5f" ? 90 :
                        orbitalName == "6d" ? 104 :
                     /* orbitalName == "7p"*/ 113
                    );

    int maxOnOrbital = -1;
    switch (orbitalName[1]) {
        case 's':
            maxOnOrbital = 2;
            break;
        case 'p':
            maxOnOrbital = 6;
            break;
        case 'd':
            maxOnOrbital = 10;
            break;
        case 'f':
            maxOnOrbital = 14;
            break;
        default:
            throw IncorrectOrbitalNameException(std::string() + orbitalName[1]);
    }
    int result = numOfElectrons - (numberFromWhichStartsOrbital - 1);
    if (result > maxOnOrbital)
        result = maxOnOrbital;
    else if (result < 0)
        result = 0;
    return result;
}

std::vector<std::vector<int>> Element::getElectronVector() const {

    std::vector<std::vector<int>> res(7, std::vector<int>(0));
    int electrons = this->getElectrons();
    res[0].push_back(_getElectronsOnOrbital("1s", electrons));

    res[1].push_back(_getElectronsOnOrbital("2s", electrons));
    res[1].push_back(_getElectronsOnOrbital("2p", electrons));

    res[2].push_back(_getElectronsOnOrbital("3s", electrons));
    res[2].push_back(_getElectronsOnOrbital("3p", electrons));

    res[3].push_back(_getElectronsOnOrbital("4s", electrons));
    res[2].push_back(_getElectronsOnOrbital("3d", electrons));
    res[3].push_back(_getElectronsOnOrbital("4p", electrons));

    res[4].push_back(_getElectronsOnOrbital("5s", electrons)); //5s
    res[3].push_back(_getElectronsOnOrbital("4d", electrons));//4d
    res[4].push_back(_getElectronsOnOrbital("5p", electrons)); //5p

    res[5].push_back(_getElectronsOnOrbital("6s", electrons)); //6s
    res[3].push_back(_getElectronsOnOrbital("4f", electrons));//4f
    res[4].push_back(_getElectronsOnOrbital("5d", electrons));//5d
    res[5].push_back(_getElectronsOnOrbital("6p", electrons)); //6p

    res[6].push_back(_getElectronsOnOrbital("7s", electrons)); //7s
    res[4].push_back(_getElectronsOnOrbital("5f", electrons));//5f
    res[5].push_back(_getElectronsOnOrbital("6d", electrons));//6d
    res[6].push_back(_getElectronsOnOrbital("7p", electrons));//7p
    if (this->getNumber() >= (57 - 1)) res[4][2]++;
    if (this->getNumber() >= (89 - 1)) res[5][2]++;
    if (this->getNumber() == 24) {
        res[2][2] = 5;
        res[3][0] = 1;
    } else if (this->number == 29) {
        res[2][2] = 10;
        res[4][0] = 1;
    } else if (this->number == 42) {
        res[3][2] = 5;
        res[4][0] = 1;
    } else if (this->number == 44) {
        res[3][2] = 7;
        res[4][0] = 1;
    } else if (this->number == 45) {
        res[3][2] = 8;
        res[4][0] = 1;
    } else if (this->number == 46) {
        res[3][2] = 10;
        res[4][0] = 0;
    } else if (this->number == 47) {
        res[3][2] = 10;
        res[4][0] = 1;
    } else if (this->number == 78) {
        res[4][2] = 9;
        res[5][0] = 1;
    } else if (this->number == 79) {
        res[4][2] = 10;
        res[5][0] = 1;
    } else if (this->number == 110) {
        res[5][2] = 9;
        res[6][0] = 1;
    } else if (this->number == 111) {
        res[5][2] = 10;
        res[6][0] = 1;
    }
    std::vector<std::vector<int>> result;
    for (int i = 0; i < res.size(); ++i) {
        result.emplace_back(std::vector<int>());
        for (int j = 0; j < res[i].size(); ++j) {
            if (res[i][j] > 0)
                result[i].push_back(res[i][j]);
        }
    }

    return result;
}   
// out
std::string Element::getElectronSubGroupPosition() const {
    std::string s;
    std::vector<std::vector<int>> gr = this->getElectronVector();
    std::vector<std::string> typesOfOrbitals = {"s", "p", "d", "f"};
    for (int i = 0; i < gr.size(); ++i)
        for (int j = 0; j < gr[i].size(); ++j)
            s += std::to_string(i + 1) + typesOfOrbitals[j] + "<sup>" + std::to_string(gr[i][j]) + "</sup>";

    return s;
}
std::string Element::getElectronGroupPosition() const {
    std::string s;
    if (this->getZ() != 0)
        s += "<big>[</big>";
    s += this->getSymbol();
    s += "{+" + std::to_string(this->getNumber()) + "} ";
    std::vector<std::vector<int>> gr = this->getElectronVector();
    for (auto & i : gr) {
        int a = 0;
        for (int j : i) {
            a += j;
        }
        if (a != 0)
            s += ")" + std::to_string(a) + " ";

    }
    if (this->getZ() != 0)
        s += std::string("<big>]</big><sup>") + (this->getZ() > 0 ? "+" : "") + std::to_string(this->getZ()) + "</sup>";
    return s;
}
std::string Element::getNumberOfPNE() const {
    std::string s;
    s += std::to_string(this->getProtons()) + "p<sup>+</sup>, ";
    s += std::to_string(this->getNeutrons()) + "n<sup>0</sup>, ";
    s += std::to_string(this->getElectrons()) + "e<sup>-</sup>";
    return s;
}


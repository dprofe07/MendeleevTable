#include "MendeleevTable.h"
#include "exceptions.h"

Element& MendeleevTable::fromNumber(int num) {
    if (num < 1 || num > 118)
        throw ElementNotFoundException(std::to_string(num));
    return lst[num - 1];
}
Element& MendeleevTable::fromName(std::string name) {
    for (auto& i : lst)
        if (i.getName() == name)
            return i;
    throw ElementNotFoundException(name);
}
Element& MendeleevTable::fromSymbol(std::string symbol) {
    for (auto& i : lst)
        if (i.getSymbol() == symbol)
            return i;
    throw ElementNotFoundException(symbol);
}
Element& MendeleevTable::fromPosition(int period, int group, bool subgroup) {
    std::vector<int> vec;
    for (auto& i : lst) {
        if (i.getPeriod() == period && i.getSubGroup() == subgroup && i.getGroup() == group)
            vec.push_back(i.getNumber());
    }
    if (vec.size() == 1)
        return MendeleevTable::fromNumber(vec[0]);
    else if (vec.size() == 0)
        throw ElementNotFoundException(std::string() + "period=" + std::to_string(period) + "; group=" + std::to_string(group) + "; subgroup=" + (subgroup ? "A" : "B"));
    else 
        throw vec;
}
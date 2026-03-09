#include "Component.h"

void Variables::addInt(std::string name, int value) {
    integers[name] = value;
}

void Variables::addFloat(std::string name, float value) {
    floats[name] = value;
}

void Variables::addDouble(std::string name, double value) {
    doubles[name] = value;
}

void Variables::addString(std::string name, std::string value) {
    strings[name] = value;
}


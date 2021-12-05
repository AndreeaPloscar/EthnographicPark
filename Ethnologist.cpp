//
// Created by Andreea Ploscar on 22.06.2021.
//

#include "Ethnologist.h"

Ethnologist::Ethnologist(const string &name, const string &area) : name(name), area(area) {}

const string &Ethnologist::getName() const {
    return name;
}

void Ethnologist::setName(const string &name) {
    Ethnologist::name = name;
}

const string &Ethnologist::getArea() const {
    return area;
}

void Ethnologist::setArea(const string &area) {
    Ethnologist::area = area;
}

bool Ethnologist::operator==(const Ethnologist &rhs) const {
    return name == rhs.name;
}

bool Ethnologist::operator!=(const Ethnologist &rhs) const {
    return !(rhs == *this);
}

static vector<string> tokenize(string stringLine, char delimiter)
{
    vector <string> result;
    stringstream stringStream(stringLine);
    string token;
    while (getline(stringStream, token, delimiter))
        result.push_back(token);

    return result;
}

std::istream& operator>>(std::istream& inputStream, Ethnologist * elem){
    string line;
    getline(inputStream, line);
///TODO CHANGE DELIMITER
    vector<string> tokens = tokenize(line, ';');
///TODO CHANGE NR ARGS
    if (tokens.size() != 2)
        return inputStream;
    elem->name = tokens[0];
    elem->area = tokens[1];

    return inputStream;
}

ostream &operator<<(ostream &os, const Ethnologist &ethnologist) {
    os << "name: " << ethnologist.name << " area: " << ethnologist.area;
    return os;
}

string to_string(){
    return "";
}
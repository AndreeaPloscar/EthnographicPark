//
// Created by Andreea Ploscar on 22.06.2021.
//

#include "Building.h"
#include "sstream"
Building::Building(int id, const string &description, const string &thematic, const string &location) : id(id),
                                                                                                        description(
                                                                                                                description),
                                                                                                        thematic(
                                                                                                                thematic),
                                                                                                        location(
                                                                                                                location) {}

int Building::getId() const {
    return id;
}

void Building::setId(int id) {
    Building::id = id;
}

const string &Building::getDescription() const {
    return description;
}

void Building::setDescription(const string &description) {
    Building::description = description;
}

const string &Building::getThematic() const {
    return thematic;
}

void Building::setThematic(const string &thematic) {
    Building::thematic = thematic;
}

const string &Building::getLocation() const {
    return location;
}

void Building::setLocation(const string &location) {
    Building::location = location;
}

bool Building::operator==(const Building &rhs) const {
    return id == rhs.id;
}

bool Building::operator!=(const Building &rhs) const {
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

std::istream& operator>>(std::istream& inputStream, Building * elem){
    string line;
    getline(inputStream, line);
///TODO CHANGE DELIMITER
    vector<string> tokens = tokenize(line, ';');
///TODO CHANGE NR ARGS
    if (tokens.size() !=4 )
        return inputStream;
    elem->id = stoi(tokens[0]); /// erase spaces
    elem->description = tokens[1];
    elem->thematic = tokens[2];
    elem->location = tokens[3];
    return inputStream;

}

ostream &operator<<(ostream &os, const Building &building) {
    os << "id: " << building.id << " description: " << building.description << " thematic: " << building.thematic
       << " location: " << building.location;
    return os;
}

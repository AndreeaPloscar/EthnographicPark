//
// Created by Andreea Ploscar on 22.06.2021.
//

#ifndef E2_915_PLOSCAR_ANDREEA_BUILDING_H
#define E2_915_PLOSCAR_ANDREEA_BUILDING_H

#include <ostream>
#include "string"
#include "vector"
using namespace std;
class Building {
int id;
string description;
string thematic;
string location;
public:
    Building(int id = 0, const string &description = "", const string &thematic = "", const string &location="");
    Building(const Building & b){
        this->id = b.id;
        this->location = b.location;
        this->description = b.description;
        this->thematic = b.thematic;
    }

    int getId() const;

    void setId(int id);

    const string &getDescription() const;

    void setDescription(const string &description);

    const string &getThematic() const;

    void setThematic(const string &thematic);

    const string &getLocation() const;

    void setLocation(const string &location);

    bool operator==(const Building &rhs) const;

    bool operator!=(const Building &rhs) const;

    friend std::istream& operator>>(std::istream& inputStream, Building * elem);

    friend ostream &operator<<(ostream &os, const Building &building);

    Building & operator = (const Building& b){
        this->id = b.id;
        this->location = b.location;
        this->description = b.description;
        this->thematic = b.thematic;
        return * this;
    }
};


#endif //E2_915_PLOSCAR_ANDREEA_BUILDING_H

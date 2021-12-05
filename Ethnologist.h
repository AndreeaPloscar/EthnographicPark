//
// Created by Andreea Ploscar on 22.06.2021.
//

#ifndef E2_915_PLOSCAR_ANDREEA_ETHNOLOGIST_H
#define E2_915_PLOSCAR_ANDREEA_ETHNOLOGIST_H

#include <ostream>
#include "string"
#include "sstream"
#include "vector"

using namespace std;

class Ethnologist {
string name;
string area;
public:
    Ethnologist(const string &name = "", const string &area = "");
    Ethnologist(const Ethnologist & e){
        this->name = e.name;
        this->area = e.area;
    }

    const string &getName() const;

    void setName(const string &name);

    const string &getArea() const;

    void setArea(const string &area);

    bool operator==(const Ethnologist &rhs) const;

    bool operator!=(const Ethnologist &rhs) const;

    friend std::istream& operator>>(std::istream& inputStream, Ethnologist * elem);

    friend ostream &operator<<(ostream &os, const Ethnologist &ethnologist);
};


#endif //E2_915_PLOSCAR_ANDREEA_ETHNOLOGIST_H

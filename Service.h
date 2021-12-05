//
// Created by Andreea Ploscar on 22.06.2021.
//

#ifndef E2_915_PLOSCAR_ANDREEA_SERVICE_H
#define E2_915_PLOSCAR_ANDREEA_SERVICE_H

#include "Repository.h"
#include "Ethnologist.h"
#include "Building.h"
#include "iostream"
using namespace std;

class Service {
private:
FileRepository<Building> & buildings_repo;
FileRepository<Ethnologist> & ethno_repo;

public:
    Service(FileRepository<Building> &buildingsRepo, FileRepository<Ethnologist> &ethnoRepo);

    FileRepository<Building> &getBuildingsRepo() const;

    FileRepository<Ethnologist> &getEthnoRepo() const;

    string get_area(string name){
        int i;
        auto objects = ethno_repo.getElements();
        for(i = 0; i < objects.size(); i++)
            if(objects[i].getName() == name)
                return objects[i].getArea();
            return "";
    }
    vector<Building> get_buildings_sorted(string name);
    static vector<string> tokenize(string stringLine, char delimiter)
    {
        vector <string> result;
        stringstream stringStream(stringLine);
        string token;
        while (getline(stringStream, token, delimiter))
            result.push_back(token);

        return result;
    }

    vector<Building> sort_by_area(vector<Building> buildings){
        int i,j;
        Building aux;
        for(i=0; i < buildings.size()-1; i++)
        {
            for(j=i+1;j<buildings.size();j++){
                if(buildings[i].getThematic() > buildings[j].getThematic())
                {
                    aux = buildings[i];
                    buildings[i] = buildings[j];
                    buildings[j]= aux;
                }
            }
        }
        return buildings;
    }

    bool is_contiguous(string location){
        vector<string> tokens = tokenize(location, ',');
        if(tokens.size() == 1)
            return true;
        for(int i =0; i < tokens.size(); i++)
        {   string coordinates = tokens[i];
            int ok = 0;
            for(int j = 0; j < tokens.size(); j++)
                if(j != i and (tokens[j][0] == coordinates[0] or tokens[j][1] == coordinates[1]))
                    ok =1;
            if(not ok)
                return false;
        }
        return true;
    }

    int get_columns();

    int get_rows();

    bool have_common_elem(vector<string> v1, vector<string> v2){
        for(int i = 0; i < v1.size(); i++)
        {
            for( int j =0; j < v2.size(); j++)
                if(v1[i] == v2[j])
                    return true;
        }
        return false;
    }

    bool overlaps(string location, int id){
        vector<string> new_locations = tokenize(location, ',');
        int i;
        auto objects = buildings_repo.getElements();
        for(i = 0; i < objects.size(); i++)
        {
            string loc = objects[i].getLocation();
            vector<string> locations = tokenize(loc, ',');
            if(have_common_elem(new_locations, locations) and id != objects[i].getId())
                return true;
        }
        return false;
    }

    void add_building(int id, string description, string area, string location);

    void update(int id, string desc, string loc);

    string get_area(int row, int column){
        string location ="00";
        location[0] = char(row + 'A');
        location[1] = char(column + '1');
        auto objects = buildings_repo.getElements();
        for(int i = 0; i < objects.size(); i++){
            vector<string> tokens = tokenize(objects[i].getLocation(), ',');
            for(auto & elem: tokens){
                if(elem == location)
                    return objects[i].getThematic();
            }
        }
        return "";
    }
};


#endif //E2_915_PLOSCAR_ANDREEA_SERVICE_H

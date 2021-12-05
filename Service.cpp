//
// Created by Andreea Ploscar on 22.06.2021.
//

#include "Service.h"

Service::Service(FileRepository<Building> &buildingsRepo, FileRepository<Ethnologist> &ethnoRepo) : buildings_repo(
        buildingsRepo), ethno_repo(ethnoRepo) {}

FileRepository<Building> &Service::getBuildingsRepo() const {
    return buildings_repo;
}

FileRepository<Ethnologist> &Service::getEthnoRepo() const {
    return ethno_repo;
}

vector<Building> Service::get_buildings_sorted(string name) {
    int i;
    vector<Building> result;
    vector<Building> intermediate;
    string area = get_area(name);
    auto objects = buildings_repo.getElements();
    for(i = 0; i < objects.size(); i++)
        if(objects[i].getThematic() == area)
            result.push_back(objects[i]);
    for(i = 0; i < objects.size(); i++)
        if(objects[i].getThematic() != area and objects[i].getThematic() != "office")
            intermediate.push_back(objects[i]);
    auto result2 = sort_by_area(intermediate);
    for(auto & elem: result2)
        result.push_back(elem);
    for(i = 0; i < objects.size(); i++)
        if(objects[i].getThematic() == "office")
            result.push_back(objects[i]);
    return result;
}

int Service::get_columns() {
    int max =0;
    int i;
    auto objects = buildings_repo.getElements();
    for(i = 0; i < objects.size(); i++){
        vector<string> tokens = tokenize(objects[i].getLocation(), ',');
        for(auto & elem: tokens)
            if(elem[1]-'0' > max)
                max = elem[1]-'0';
    }
    return max;
}

int Service::get_rows() {
    int max =0;
    int i;
    auto objects = buildings_repo.getElements();
    for(i = 0; i < objects.size(); i++){
        vector<string> tokens = tokenize(objects[i].getLocation(), ',');
        for(auto & elem: tokens)
            if(elem[0]-'A' > max)
                max = elem[0]-'A';
    }
    return max + 1;
}

void Service::add_building(int id, string description, string area, string location) {
    Building building(id, description, area, location);
    int i;
    auto objects = buildings_repo.getElements();
    for(i = 0; i < objects.size(); i++)
        if(objects[i].getId() == id)
            throw exception();
    if(not is_contiguous(location))
        throw exception();
    if(overlaps(location, id))
        throw exception();
    this->buildings_repo.add(building);
}

void Service::update(int id, string desc, string loc) {
    if(not is_contiguous(loc))
        throw exception();
    if(overlaps(loc, id))
        throw exception();
    int i;
    Building old_building;
    auto objects = buildings_repo.getElements();
    for(i = 0; i < objects.size(); i++)
        if(objects[i].getId() == id) {
            old_building.setId(id);
            old_building.setDescription(objects[i].getDescription());
            old_building.setLocation(objects[i].getLocation());
            old_building.setThematic(objects[i].getThematic());
        }
    Building new_building(id, desc, old_building.getThematic(),loc);
    this->buildings_repo.update(old_building, new_building);
}

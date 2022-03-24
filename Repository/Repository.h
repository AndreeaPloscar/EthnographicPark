//
// Created by Andreea Ploscar on 19.06.2021.
//

#ifndef TEMPLATE_PRACTIC_REPOSITORY_H
#define TEMPLATE_PRACTIC_REPOSITORY_H

#include <fstream>
#include <vector>
#include "string"


using namespace std;
template <typename TElem>
class Repository {
protected:
    std::vector<TElem> elements;
public:
    Repository() {}

    virtual void add(TElem& elem) {
//        if(this->find(elem))
//            throw exception();
        this->elements.push_back(elem);
    }

    const vector<TElem> &getElements() const {
        return elements;
    }

    virtual void remove(TElem elem) {
        if(not this->find(elem))
            throw exception();
        int i = 0;
        bool found = false;
        while (i < this->elements.size() && not found){
            if(this->elements[i] != elem){
                i++;
            }
            else
            {found = true;
            }
        }
        this->elements.erase(this->elements.begin() + i);
    }

    virtual bool find(TElem & elem){
        for(int i =0;i < elements.size(); i++){
            if(elements[i] == elem)
                return true;
        }
        return false;
//       if ( std::find(elements.begin(), elements.end(), elem) != elements.end())
//           return true;
//        return false;
    }

    virtual void update(TElem elem, TElem new_elem){
        if(not this->find(elem))
            throw exception();
        int i = 0;
        bool found = false;
        while (i < this->elements.size() && not found){
            if(this->elements[i] != new_elem){
                i++;
            }
            else
            {found = true;
            }
        }
        this->elements[i] = new_elem;
    }

    virtual void save_to_file() = 0;
};

template<typename TElem>
class FileRepository: public Repository<TElem>{
private:
    string path;
    char * file_name;
public:

    FileRepository(char * fileName, string path) : Repository<TElem>(), file_name(fileName), path(path){
        this->load_from_file();}

    void save_to_file() {
//        char file_name[100];
//        strcpy(file_name, path.c_str());
//        std::strcat(file_name, this->file_name);
//        std::ofstream out_file;
//        out_file.open (file_name);
//        std::string line;
//        for (auto &elem: this->getElements()){
//            out_file << elem << endl;
//        }
//        out_file.close();
    }

    void add(TElem elem) {
        Repository<TElem>::add(elem);
        this->save_to_file();
    }

    void remove(TElem elem) {
        Repository<TElem>::remove(elem);
        this->save_to_file();
    }

    void update(TElem elem, TElem new_elem) {
        Repository<TElem>::update(elem, new_elem);
        this->save_to_file();
    }

    bool find(TElem elem) {
        return Repository<TElem>::find(elem);
    }

    void load_from_file() {
        std::ifstream infile;
        char file_name_aux[100];
        strcpy(file_name_aux, path.c_str());
        std::strcat(file_name_aux, this->file_name);
        infile.open(file_name_aux);
        std::string line;
        TElem elem;
        while(infile >> &elem){
            this->add(elem);
        }
    }


};



#endif //TEMPLATE_PRACTIC_REPOSITORY_H

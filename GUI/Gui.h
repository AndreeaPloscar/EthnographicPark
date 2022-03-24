//
// Created by Andreea Ploscar on 22.06.2021.
//

#ifndef E2_915_PLOSCAR_ANDREEA_GUI_H
#define E2_915_PLOSCAR_ANDREEA_GUI_H
#include "QWidget"
#include "Service.h"
#include "QTableWidget"
#include "QVBoxLayout"
#include "QLineEdit"
#include "QPushButton"
#include "iostream"
#include "QMessageBox"

using namespace std;

class Gui : public QWidget{
    Q_OBJECT
private:
Service & service;
    QWidget * windows[15];
    vector<string> colors = { "red", "green", "grey", "purple", "cyan", "darkCyan", "darkMagenta"};
    vector<pair<string, string>> colors_map;
    QTableWidget * tables[15];
    QVBoxLayout * tables_layouts[15];
    QPushButton * add_buttons[15];
    QPushButton * update_buttons[15];
    QLineEdit * id_lines[15];
    QLineEdit * description_lines[15];
    QLineEdit * location_lines[15];
    QWidget * map;
    QTableWidget * map_table;
    QVBoxLayout * map_layout;
    vector<int> chosen;


public:
    Gui(Service & serv): service{serv}{start();}
    void start(){
        for(int i = 0; i < 15; i ++){
            windows[i] = nullptr;
        }
        for(int i = 0; i < 15; i ++){
            tables[i] = nullptr;
        }
        map = nullptr;
        map_table = nullptr;
        create_windows();
        create_map();
    }

    void create_map();

    void populate_map();

    void create_windows();

    void populate_table(QTableWidget *table, int index);

    void notify_all(){
        for(int i =0; i < 15; i++)
            if(tables[i] != nullptr)
                populate_table(tables[i], i);
    }

private slots:
    void add_clicked();

    void update_clicked();
};


#endif //E2_915_PLOSCAR_ANDREEA_GUI_H

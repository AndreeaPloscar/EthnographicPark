//
// Created by Andreea Ploscar on 22.06.2021.
//

#include "Gui.h"

void Gui::create_map() {
    map = new QWidget();
    map->setFixedSize(400,400);
    // map->setStyleSheet(QString::fromStdString("background-color: white;"));
    map_layout = new QVBoxLayout(map);
    map_table = new QTableWidget();

    populate_map();
    map_layout->addWidget(map_table);
    map->show();
}

void Gui::populate_map() {
    map_table->clear();
    int rows = service.get_rows();
    int columns = service.get_columns();
    map_table->setColumnCount(columns);
    map_table->setRowCount(rows);
    for(int j = 0; j < columns ; j++) {
        map_table->setColumnWidth(j, 50);}
    for(int i = 0; i < rows; i++){
        map_table->setRowHeight(i, 50);
        for(int j = 0; j < columns ; j++) {
            //map_table->setColumnWidth(j, 50);
            QTableWidgetItem *item1 = new QTableWidgetItem("");
            item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
            map_table->setItem(i, j, item1);

            if(i == rows - 1 and j == columns -1)
                item1->setBackground(Qt::black);
            string area = service.get_area(i,j);
            if( area != "")
            {string color = "";
                for(auto & pair: colors_map)
                    if(pair.first == area)
                        color = pair.second;
                string style = "background-color: " + color + ";";
                item1->setBackground(QColor(QString::fromStdString(color)));
            }
            string row = "0";
            row[0] = char('A' + i);
//                string column;
//                column[0] = char('1' + j);
            map_table->setVerticalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(row)));
            //map_table->setHorizontalHeaderItem(j, new QTableWidgetItem(QString::fromStdString(column)));
        }
    }
    //map_table->resizeColumnsToContents();
    map_table->show();
}

void Gui::create_windows() {
    int index = 0;
    srand(time(NULL));
    for(auto & ethno : this->service.getEthnoRepo().getElements()){
        windows[index] = new QWidget();
        windows[index]->setWindowTitle(QString::fromStdString(ethno.getName()));
        windows[index]->setFixedSize(420,500);
        int random_int = rand() % 7;
        while(std::find(chosen.begin(), chosen.end(), random_int) != chosen.end())
            random_int = rand() % 7;
        chosen.push_back(random_int);
        string color = colors[random_int];
        colors_map.push_back(make_pair(ethno.getArea(), color));
        string style = "background-color: " + color + ";";
        windows[index]->setStyleSheet(QString::fromStdString(style));
        tables_layouts[index] = new QVBoxLayout(windows[index]);
        tables[index] = new QTableWidget();
        tables[index]->setColumnCount(4);
        populate_table(tables[index], index);
        tables[index]->setHorizontalHeaderLabels(QStringList{"Id","Description", "Sector","Location"});
        tables_layouts[index]->addWidget(tables[index]);
        id_lines[index] =  new QLineEdit("Id");
        description_lines[index] =  new QLineEdit("Description");
        location_lines[index] = new QLineEdit("Location");
        add_buttons[index] = new QPushButton("Add");
        QObject::connect(add_buttons[index], SIGNAL(clicked(bool)), this, SLOT(add_clicked()));
        update_buttons[index] = new QPushButton("Update");
        QObject::connect(update_buttons[index], SIGNAL(clicked(bool)), this, SLOT(update_clicked()));
        tables_layouts[index]->addWidget(id_lines[index]);
        tables_layouts[index]->addWidget(description_lines[index]);
        tables_layouts[index]->addWidget(location_lines[index]);
        tables_layouts[index]->addWidget(add_buttons[index]);
        tables_layouts[index]->addWidget(update_buttons[index]);
        windows[index]->show();
        index++;
    }
}

void Gui::populate_table(QTableWidget *table, int index) {
    string name = windows[index]->windowTitle().toStdString();
    string area = service.get_area(name);
    table->clear();
    vector<Building> objects = this->service.get_buildings_sorted(name);
    table->setRowCount(objects.size());
    int count = 0;
    for(auto & item: objects){
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(item.getId()));
        item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
        table->setItem(count, 0, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem(QString::fromStdString(item.getDescription()));
        item2->setFlags(item2->flags() ^ Qt::ItemIsEditable);
        table->setItem(count, 1, item2);

        QTableWidgetItem *item3 = new QTableWidgetItem(QString::fromStdString(item.getThematic()));
        item3->setFlags(item3->flags() ^ Qt::ItemIsEditable);
        table->setItem(count, 2, item3);

        QTableWidgetItem *item4 = new QTableWidgetItem(QString::fromStdString(item.getLocation()));
        item4->setFlags(item4->flags() ^ Qt::ItemIsEditable);
        table->setItem(count, 3, item4);
        count ++;

        if(area == item.getThematic()){
            item1->setBackground(Qt::blue);
            item2->setBackground(Qt::blue);
            item3->setBackground(Qt::blue);
            item4->setBackground(Qt::blue);
        }
    }
    table->resizeColumnsToContents();
    table->show();
}

void Gui::add_clicked() {
    int index = 0;
    while(add_buttons[index] != sender())
        index++;
    string name = windows[index]->windowTitle().toStdString();
    string area = service.get_area(name);
    string description = description_lines[index]->text().toStdString();
    string location = location_lines[index]->text().toStdString();
    string id_string = id_lines[index]->text().toStdString();
    int id;
    try {
        id = stoi(id_string);
    }
    catch (...){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Id should be an integer");
        messageBox.setFixedSize(300,200);
        return;
    }
    if(description == "")
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Description should not be empty");
        messageBox.setFixedSize(300,200);
        return;
    }
    try{
        service.add_building(id, description, area, location);
        notify_all();
        populate_map();

    }catch (...){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Building could not be added!");
        messageBox.setFixedSize(300,200);
    }
}

void Gui::update_clicked() {

        int index = 0;
        while(update_buttons[index] != sender())
            index++;

        string description = description_lines[index]->text().toStdString();
        string location = location_lines[index]->text().toStdString();
        string correct_area = service.get_area(windows[index]->windowTitle().toStdString());
        string area = tables[index]->item(tables[index]->currentRow(), 2)->text().toStdString();
        string id = tables[index]->item(tables[index]->currentRow(), 0)->text().toStdString();
        int id_int = stoi(id);
        if(correct_area != area){
            QMessageBox messageBox;
            messageBox.critical(0,"Error","You can only modify your area!");
            messageBox.setFixedSize(300,200);
            return;
        }
        if(description == ""){
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Description should not be empty!");
            messageBox.setFixedSize(300,200);
            return;
        }
        try{
            service.update(id_int, description, location);
            notify_all();
            populate_map();
        }
        catch (...){
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Could not update!");
            messageBox.setFixedSize(300,200);
        }


}

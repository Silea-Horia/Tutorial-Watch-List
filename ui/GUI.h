//
// Created by horique on 4/25/24.
//

#ifndef TESTQT_GUI_H
#define TESTQT_GUI_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <qlineedit.h>
#include <QGroupBox>
#include <QMainWindow>
#include <QCheckBox>
#include <QLabel>
#include <QtCharts/QPieSeries>
#include <QTableView>
#include "../services/services.h"
#include "../services/userservices.h"
#include "../services/CommandController.h"

class MyModel : public QAbstractTableModel {
private:
    Database& database;
public:
    explicit MyModel(Database& database) : database(database) {};
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

class GUI : public QMainWindow {
private:
    int n;
    MyModel* model;
    QWidget* window;
    QTableView* view;
    Database& database;
    Services& services;
    UserServices& userServices;
    CommandController commandController;
    QListWidget* tutorialListWidget;
    QLineEdit* titleEdit;
    QLineEdit* presenterEdit;
    QLineEdit* linkEdit;
    QLineEdit* minutesEdit;
    QLineEdit* secondsEdit;
    QLineEdit* likesEdit;

    QLabel* errorLabel;

    QPushButton* backButton;

    QGroupBox* mainMenu;
    QPushButton* userButton;
    QPushButton* adminButton;
    QPushButton* exitButton;

    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* editButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QPushButton* viewButton;

    QChart* chart;
    QPieSeries* series;

    QListWidget* searchListWidget;
    QListWidget* watchListWidget;
    QLineEdit* searchLabel;
    QPushButton* searchButton;
    QPushButton* saveButton;
    QPushButton* removeButton;
    QCheckBox* checkBox;
    QPushButton* csvButton;
    QPushButton* htmlButton;
    QPushButton* yesButton;
    QPushButton* noButton;


public:
    GUI(Database& database, Services& services, UserServices& userServices, QScreen* screen);
private:
    void keyPressEvent(QKeyEvent* event) override;
    void buildLoginGUI();
    void buildAdminGUI();
    void buildUserGUI();

    void populateList();
    void buildChart();

    void backButtonHandler();

    static void exitButtonHandler();
    void adminButtonHandler();
    void userButtonHandler();

    void addButtonHandler();
    void deleteButtonHandler();
    void editButtonHandler();
    void undoButtonHandler();
    void redoButtonHandler();

    void populateWatchList();

public slots:
    void searchButtonHandler();
    void saveButtonHandler();
    void removeButtonHandler();
    void csvButtonHandler();
    void htmlButtonHandler();
    void yesButtonHandler();
    void noButtonHandler();

    void buildView();
};


#endif //TESTQT_GUI_H

//
// Created by horique on 4/25/24.
//

#include "GUI.h"
#include <qlayout.h>
#include <QLabel>
#include <QGroupBox>
#include <QDialog>
#include <QCoreApplication>
#include <QScreen>
#include <sstream>
#include <QtCharts/QPieSeries>
#include <QChart>
#include <QChartView>
#include <QShortcut>

GUI::GUI(Database& database, Services &services, UserServices& userServices, QScreen* screen): database{database}, services{services}, userServices{userServices} {
    this->buildLoginGUI();
    //this->showMaximized();
    int width = this->frameGeometry().width();
    int height = this->frameGeometry().height();

    int screenWidth = screen->geometry().width();
    int screenHeight = screen->geometry().height();

    this->setGeometry((screenWidth/2)-(width/2), (screenHeight/2)-(height/2), width, height);
    this->model = new MyModel(database);
}

void GUI::backButtonHandler() {
    this->buildLoginGUI();
}

void GUI::buildLoginGUI() {
    mainMenu = new QGroupBox(tr("Main menu"), this);
    mainMenu->setAlignment(Qt::AlignCenter);

    this->userButton = new QPushButton{ "User mode" };
    this->adminButton = new QPushButton{ "Admin mode" };
    this->exitButton = new QPushButton{ "Exit" };

    QObject::connect(this->exitButton, &QPushButton::clicked, this, &GUI::exitButtonHandler);
    QObject::connect(this->adminButton, &QPushButton::clicked, this, &GUI::adminButtonHandler);
    QObject::connect(this->userButton, &QPushButton::clicked, this, &GUI::userButtonHandler);

    auto *vbox = new QVBoxLayout(this->mainMenu);
    vbox->addWidget(this->userButton);
    vbox->addWidget(this->adminButton);
    vbox->addWidget(this->exitButton);
    vbox->setAlignment(Qt::AlignAbsolute);
    mainMenu->setLayout(vbox);

    this->setCentralWidget(mainMenu);
}

void GUI::exitButtonHandler() {
    QCoreApplication::quit();
}

void GUI::adminButtonHandler() {
    this->buildAdminGUI();
    this->populateList();

    QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addButtonHandler);
    QObject::connect(this->backButton, &QPushButton::clicked, this, &GUI::backButtonHandler);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &GUI::deleteButtonHandler);
    QObject::connect(this->editButton, &QPushButton::clicked, this, &GUI::editButtonHandler);
    QObject::connect(this->undoButton, &QPushButton::clicked, this, &GUI::undoButtonHandler);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &GUI::redoButtonHandler);
    QObject::connect(this->viewButton, &QPushButton::clicked, this, &GUI::buildView);

}


void GUI::buildChart() {
    this->chart->removeAllSeries();
    // add series from the database
    this->series = new QPieSeries();
    for (pair<string, int> p : this->services.get_names()) {
        series->append(QString::fromStdString(p.first + " " + to_string(p.second)), p.second);
    }
    series->setLabelsVisible();
    series->setLabelsPosition(QPieSlice::LabelOutside);


    // add to chart
    this->chart->addSeries(series);
    this->chart->setAnimationOptions(QChart::AllAnimations);

}


void GUI::buildAdminGUI() {
    auto* mainWidget = new QWidget(this->centralWidget());
    auto* mainLayout = new QHBoxLayout{ mainWidget };
    tutorialListWidget = new QListWidget{};
    mainLayout->addWidget(tutorialListWidget);

    auto* rightLayout = new QVBoxLayout{};
    auto* formLayout = new QGridLayout{};
    auto* titleLabel = new QLabel{"Title"};
    titleEdit = new QLineEdit{};
    auto* presenterLabel = new QLabel{"Presenter"};
    presenterEdit = new QLineEdit{};
    auto* minutesLabel = new QLabel{ "Minutes" };
    minutesEdit = new QLineEdit{};
    auto* secondsLabel = new QLabel{ "Seconds" };
    secondsEdit = new QLineEdit{};
    auto* likesLabel = new QLabel{ "Likes" };
    likesEdit = new QLineEdit{};
    auto* linkLabel = new QLabel{"Link"};
    linkEdit = new QLineEdit{};

    formLayout->addWidget(titleLabel, 0, 0);
    formLayout->addWidget(titleEdit, 0, 1);
    formLayout->addWidget(presenterLabel, 1, 0);
    formLayout->addWidget(presenterEdit, 1, 1);
    formLayout->addWidget(minutesLabel, 2, 0);
    formLayout->addWidget(minutesEdit, 2, 1);
    formLayout->addWidget(secondsLabel, 3, 0);
    formLayout->addWidget(secondsEdit, 3, 1);
    formLayout->addWidget(likesLabel, 4, 0);
    formLayout->addWidget(likesEdit, 4, 1);
    formLayout->addWidget(linkLabel, 5, 0);
    formLayout->addWidget(linkEdit, 5, 1);

    rightLayout->addLayout(formLayout);

    this->addButton = new QPushButton{ "Add" };
    this->deleteButton = new QPushButton{"Delete"};
    this->editButton = new QPushButton{"Edit"};
    this->backButton = new QPushButton{ "Back" };
    this->undoButton = new QPushButton{"Undo"};
    this->redoButton = new QPushButton{"Redo"};
    this->viewButton = new QPushButton{"View"};

    rightLayout->addWidget(addButton);

    auto* twoButtonsLayout = new QGridLayout{};
    rightLayout->addLayout(twoButtonsLayout);

    twoButtonsLayout->addWidget(deleteButton, 1, 0);
    twoButtonsLayout->addWidget(editButton, 1, 1);
    twoButtonsLayout->addWidget(undoButton, 2, 0);
    twoButtonsLayout->addWidget(redoButton, 2, 1);

    errorLabel = new QLabel{};
    rightLayout->addWidget(errorLabel);

    rightLayout->addWidget(backButton);
    rightLayout->addWidget(viewButton);

    // create chart
    this->chart = new QChart();
    this->buildChart();
    // display chart
    auto* chartView = new QChartView(chart);
    rightLayout->addWidget(chartView);

    mainLayout->addLayout(rightLayout);

    this->setCentralWidget(mainWidget);
}

void GUI::populateList() {
    this->tutorialListWidget->clear();

    for (auto tutorial : this->services.get_iterator()) {
        auto* item = new QListWidgetItem{QString::fromStdString(tutorial.string_format())};
        QFont font{"Verdana", 14, 5};
        item->setFont(font);
        this->tutorialListWidget->addItem(item);
    }
    emit model->dataChanged(model->index(0,0), model->index(database.get_size()-2, 1));
}

void GUI::addButtonHandler() {
    errorLabel->clear();
    QString title = this->titleEdit->text();
    QString presenter = this->presenterEdit->text();
    QString minutes = this->minutesEdit->text();
    QString seconds = this->secondsEdit->text();
    QString likes = this->likesEdit->text();
    QString link = this->linkEdit->text();
    try {
        Tutorial tut(title.toStdString(), presenter.toStdString(), stoi(minutes.toStdString()), stoi(seconds.toStdString()), stoi(likes.toStdString()), link.toStdString());
        this->commandController.addCommand(new AddOperation(database, tut));
    }
    catch (RepoException& re){
        string s = re.what();
        errorLabel->setText(QString::fromStdString("<font color='red'>" + s + "</font>"));
    }
    catch (ValidateException& se) {
        string s = se.what();
        errorLabel->setText(QString::fromStdString("<font color='red'>" + s + "</font>"));
    }

    this->populateList();
    this->buildChart();
    this->titleEdit->clear();
    this->presenterEdit->clear();
    this->minutesEdit->clear();
    this->secondsEdit->clear();
    this->likesEdit->clear();
    this->linkEdit->clear();
}

void GUI::deleteButtonHandler() {
    errorLabel->clear();
    try {
        Tutorial tut = this->database.get_data()[this->tutorialListWidget->currentRow()];
        this->commandController.addCommand(new RemoveOperation(database, tut));
        // this->services.remove_tutorial(to_string(this->tutorialListWidget->currentRow()));
    }
    catch (RepoException& re){
        string s = re.what();
        errorLabel->setText(QString::fromStdString("<font color='red'>" + s + "</font>"));
    }
    catch (ValidateException& se) {
        string s = se.what();
        errorLabel->setText(QString::fromStdString("<font color='red'>" + s + "</font>"));
    }
    this->populateList();
    this->buildChart();
}

void GUI::editButtonHandler() {
    errorLabel->clear();
    int pos = this->tutorialListWidget->currentRow();
    string position = to_string(pos);
    Tutorial oldTut = database.get_data()[pos];
    Tutorial newTut = Tutorial();
    try {
        if (!this->titleEdit->text().toStdString().empty()) {
            newTut.set_title(this->titleEdit->text().toStdString());
        }
        if (!this->presenterEdit->text().toStdString().empty()) {
            newTut.set_presenter(this->presenterEdit->text().toStdString());
        }
        if (!this->minutesEdit->text().toStdString().empty() && !this->secondsEdit->text().toStdString().empty()) {
            newTut.set_duration(this->minutesEdit->text().toInt(), this->secondsEdit->text().toInt());
        }
        if (!this->likesEdit->text().toStdString().empty()) {
            newTut.set_likes(this->likesEdit->text().toInt());
        }
        if (!this->linkEdit->text().toStdString().empty()) {
            newTut.set_link(this->linkEdit->text().toStdString());
        }
        commandController.addCommand(new EditOperation(database, oldTut, newTut));
        this->buildChart();
        this->populateList();
    }
    catch (RepoException& re){
        string s = re.what();
        errorLabel->setText(QString::fromStdString("<font color='red'>" + s + "</font>"));
    }
    catch (ValidateException& se) {
        string s = se.what();
        errorLabel->setText(QString::fromStdString("<font color='red'>" + s + "</font>"));
    }
    this->titleEdit->clear();
    this->presenterEdit->clear();
    this->minutesEdit->clear();
    this->secondsEdit->clear();
    this->likesEdit->clear();
    this->linkEdit->clear();
}

void GUI::userButtonHandler() {
    this->buildUserGUI();
    this->populateWatchList();
    QObject::connect(this->backButton, &QPushButton::clicked, this, &GUI::backButtonHandler);
    QObject::connect(this->searchButton, &QPushButton::clicked, this, &GUI::searchButtonHandler);
    //QObject::connect(this->saveButton, &QPushButton::clicked, this, &GUI::saveButtonHandler);
    QObject::connect(this->removeButton, &QPushButton::clicked, this, &GUI::removeButtonHandler);
    QObject::connect(this->csvButton, &QPushButton::clicked, this, &GUI::csvButtonHandler);
    QObject::connect(this->htmlButton, &QPushButton::clicked, this, &GUI::htmlButtonHandler);
    QObject::connect(this->yesButton, &QPushButton::clicked, this, &GUI::yesButtonHandler);
    QObject::connect(this->noButton, &QPushButton::clicked, this, &GUI::noButtonHandler);
}

void GUI::buildUserGUI() {
    auto* mainWidget = new QWidget(this->centralWidget());
    auto* mainLayout = new QVBoxLayout{ mainWidget };

    auto* searchLayout = new QGridLayout{};
    searchLabel = new QLineEdit{};
    searchButton = new QPushButton{ "Search" };
    searchLayout->addWidget(searchLabel, 0, 0);
    searchLayout->addWidget(searchButton, 0, 1);

    auto* resultsLayout = new QHBoxLayout();
    searchListWidget = new QListWidget{};
    watchListWidget = new QListWidget{};
    resultsLayout->addWidget(searchListWidget);
    resultsLayout->addWidget(watchListWidget);

    yesButton = new QPushButton{ "Yes" };
    noButton = new QPushButton{ "No" };

    //saveButton = new QPushButton{ "Save" };

    errorLabel = new QLabel{};

    auto* removeLayout = new QGridLayout{};
    removeButton = new QPushButton{ "Remove" };
    checkBox = new QCheckBox{"Like?"};
    removeLayout->addWidget(removeButton, 0, 0);
    removeLayout->addWidget(checkBox, 0, 1);

    backButton = new QPushButton{ "Back" };
    csvButton = new QPushButton{ "CSV" };
    htmlButton = new QPushButton{ "HTML" };

    mainLayout->addLayout(searchLayout);
    mainLayout->addLayout(resultsLayout);
    mainLayout->addWidget(yesButton);
    mainLayout->addWidget(noButton);
    //mainLayout->addWidget(saveButton);
    mainLayout->addWidget(errorLabel);
    mainLayout->addLayout(removeLayout);
    mainLayout->addWidget(csvButton);
    mainLayout->addWidget(htmlButton);
    mainLayout->addWidget(backButton);

    setCentralWidget(mainWidget);
}
void GUI::searchButtonHandler() {
    n = 0;
    errorLabel->clear();
    searchListWidget->clear();
    this->userServices.search(searchLabel->text().toStdString());
    Tutorial tutorial = this->userServices.get_search()[0];
    auto* item = new QListWidgetItem{QString::fromStdString(tutorial.string_format_db())};
    QFont font{"Verdana", 14, 5};
    item->setFont(font);
    searchListWidget->addItem(item);
    n++;
    if (n == this->userServices.get_search().size()) n = 0;
}

void GUI::noButtonHandler() {
    errorLabel->clear();
    if (searchListWidget->count() > 0)
    {
        searchListWidget->clear();
        this->userServices.search(searchLabel->text().toStdString());
        Tutorial tutorial = this->userServices.get_search()[n];
        auto* item = new QListWidgetItem{QString::fromStdString(tutorial.string_format_db())};
        QFont font{"Verdana", 14, 5};
        item->setFont(font);
        searchListWidget->addItem(item);
        n++;
        if (n == this->userServices.get_search().size()) n = 0;
    }
}

void GUI::yesButtonHandler() {
    errorLabel->clear();
    if (searchListWidget->count() > 0)
    {
        std::string text = searchListWidget->item(0)->text().toStdString();
        vector<string> tokens;
        stringstream check1(text);
        string intermediate;
        while(getline(check1, intermediate, ','))
        {
            tokens.push_back(intermediate);
        }
        try {
            this->userServices.add_to_watchlist(
                    Tutorial(tokens[0], tokens[1], stoi(tokens[2]), stoi(tokens[3]), stoi(tokens[4]), tokens[5]));
            searchListWidget->clear();
            this->userServices.search(searchLabel->text().toStdString());
            Tutorial tutorial = this->userServices.get_search()[n];
            auto* item = new QListWidgetItem{QString::fromStdString(tutorial.string_format_db())};
            QFont font{"Verdana", 14, 5};
            item->setFont(font);
            searchListWidget->addItem(item);
            n++;
            if (n == this->userServices.get_search().size()) n = 0;
            this->populateWatchList();
        }
        catch (RepoException& re){
            string s = re.what();
            errorLabel->setText(QString::fromStdString("<font color='red'>" + s + "</font>"));
        }
        catch (ValidateException& se) {
            string s = se.what();
            errorLabel->setText(QString::fromStdString("<font color='red'>" + s + "</font>"));
        }
    }

}

void GUI::populateWatchList() {
    watchListWidget->clear();
    for (auto tutorial : this->userServices.get_watchlist()) {
        auto* item = new QListWidgetItem{QString::fromStdString(tutorial.string_format_db())};
        QFont font{"Verdana", 14, 5};
        item->setFont(font);
        watchListWidget->addItem(item);
    }
}

void GUI::saveButtonHandler() {
    errorLabel->clear();
    std::string text = searchListWidget->currentItem()->text().toStdString();
    vector<string> tokens;
    stringstream check1(text);
    string intermediate;
    while(getline(check1, intermediate, ','))
    {
        tokens.push_back(intermediate);
    }
    try {
        this->userServices.add_to_watchlist(
                Tutorial(tokens[0], tokens[1], stoi(tokens[2]), stoi(tokens[3]), stoi(tokens[4]), tokens[5]));

        this->populateWatchList();
    }
    catch (RepoException& re){
        string s = re.what();
        errorLabel->setText(QString::fromStdString("<font color='red'>" + s + "</font>"));
    }
    catch (ValidateException& se) {
        string s = se.what();
        errorLabel->setText(QString::fromStdString("<font color='red'>" + s + "</font>"));
    }
}

void GUI::removeButtonHandler() {
    errorLabel->clear();
    bool like = checkBox->isChecked();
    try {
        this->userServices.remove_from_watchlist(to_string(this->watchListWidget->currentRow()), like);
        this->populateWatchList();
        this->searchButtonHandler();
    }
    catch (RepoException& re){
        string s = re.what();
        errorLabel->setText(QString::fromStdString("<font color='red'>" + s + "</font>"));
    }
    catch (ValidateException& se) {
        string s = se.what();
        errorLabel->setText(QString::fromStdString("<font color='red'>" + s + "</font>"));
    }
}

void GUI::csvButtonHandler() {
    errorLabel->clear();
    this->userServices.open_csv_watch_list();
}

void GUI::htmlButtonHandler() {
    errorLabel->clear();
    this->userServices.open_html_watch_list();
}

void GUI::undoButtonHandler() {
    try {
        this->errorLabel->clear();
        commandController.undo();
        this->populateList();
        this->buildChart();
        this->titleEdit->clear();
        this->presenterEdit->clear();
        this->minutesEdit->clear();
        this->secondsEdit->clear();
        this->likesEdit->clear();
        this->linkEdit->clear();
    }
    catch (ValidateException &ve) {
        string s = ve.what();
        errorLabel->setText(QString::fromStdString("<font color='red'>" + s + "</font>"));
    }
}

void GUI::redoButtonHandler() {
    try {
        this->errorLabel->clear();
        commandController.redo();
        this->populateList();
        this->buildChart();
        this->titleEdit->clear();
        this->presenterEdit->clear();
        this->minutesEdit->clear();
        this->secondsEdit->clear();
        this->likesEdit->clear();
        this->linkEdit->clear();
    }
    catch (ValidateException &ve) {
        string s = ve.what();
        errorLabel->setText(QString::fromStdString("<font color='red'>" + s + "</font>"));
    }
}

void GUI::keyPressEvent(QKeyEvent *event) {
    if (event->matches(QKeySequence::StandardKey::Undo)) undoButtonHandler();
    else if (event->modifiers() == Qt::ControlModifier && event->key()==Qt::Key_Y) redoButtonHandler();
}

void GUI::buildView() {
    window = new QWidget();
    auto* mainLayout = new QHBoxLayout{ window };
    view = new QTableView(window);
    view->setModel(model);
    mainLayout->addWidget(view);
    int width = this->frameGeometry().width();
    int height = this->frameGeometry().height();

    int screenWidth = window->geometry().width();
    int screenHeight = window->geometry().height();
    window->setGeometry((screenWidth/2)-(width/2), (screenHeight/2)-(height/2), width, height);
    window->show();
}

int MyModel::rowCount(const QModelIndex &parent) const {
    return database.get_size();
}

int MyModel::columnCount(const QModelIndex &parent) const {
    return 2;
}

QVariant MyModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int col = index.column();
    if (row > database.get_size() - 2) return {};
    Tutorial tutorial = database.get_data()[row];

    if (role == Qt::DisplayRole) {
        switch (col)
        {
            case 0:
                return QString::fromStdString(tutorial.get_title());
            case 1:
                return QString::fromStdString(tutorial.get_presenter());
            default:
                break;
        }
    }

    return {};
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return "Title";
            case 1:
                return "Presenter";
            default:
                break;
        }
    }
    return {};
}

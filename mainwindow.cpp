#include "mainwindow.h"

//ui setup
MainWindow::MainWindow(QApplication *app, QWidget *parent) : QMainWindow(parent)
{
    this->app = app;    //quit slot needed

    db = new DB(":/xml/cell_items.xml", ":/xml/gui_config.xml");

    this->setWindowTitle(db->gui_config->value("propmainwindowtitle")->at(0));
    this->setWindowIcon(QIcon(QPixmap(db->gui_config->value("propmainwindowtitle")->at(0))));

    QWidget *central = new QWidget();
    QGridLayout *grid = new QGridLayout(this);
    grid->setSpacing(20);
    int grow=0, gcolumn=1;

    //load and scale house pixmap
     for(int i=0; i<6; i++) {
        pmap[i].load(this->db->gui_config->value("prophouseimg")->at(i));
        pmap[i] = pmap[i].scaled(80, 80);
    }

    //init 5 houses
    for(int i=0; i<5; i++) {
        houses[i] = new QLabel(this);
        grid->addWidget(houses[i], grow, gcolumn++);
    }
    grow=1;
    gcolumn=0;

    //labels font
    QFont f;
    f.setPointSize(10);
    f.setBold(true);

    //create and setup labels
    for(int i=0; i<5; i++) {
        labels[i] = new QLabel(this);
        labels[i]->setFont(f);
        labels[i]->setText(db->gui_config->value("proplabels")->at(i));
        labels[i]->setAlignment(Qt::AlignRight);
        grid->addWidget(labels[i], grow++, gcolumn);
    }

    //create and setup cells
    for(int i=0, grow=1; i<5; i++, grow++) {
        for(int j=0, gcolumn=1; j<5; j++, gcolumn++) {
            cells[i][j] = new Cell(j, this);
            cells[i][j]->addItems(*db->cell_items->value(db->cell_items->value("props")->at(i)));
            grid->addWidget(cells[i][j], grow, gcolumn);
        }
        //conect top row cells (color related ones)
        QObject::connect(cells[0][i], SIGNAL(color_index_changed(int,int)), this, SLOT(change_house_pixmap(int,int)));
    }

    //set blank house image and reset cells indexes
    this->clear();

    //buttons
    grow=6, gcolumn=1;

    for(int i=0; i<5; i++) {
        buttons[i] = new QPushButton(this);
        buttons[i]->setIcon(QIcon(QPixmap(this->db->gui_config->value("propbuttonimg")->at(i))));
        buttons[i]->setIconSize(QSize(buttons_iconsize, buttons_iconsize));
        buttons[i]->setText(this->db->gui_config->value("propbuttonlabels")->at(i));
        grid->addWidget(buttons[i], grow, gcolumn++);
    }

    QObject::connect(buttons[RELOAD], SIGNAL(clicked()), this, SLOT(clear()));
    QObject::connect(buttons[INDICATIONS], SIGNAL(clicked()), this, SLOT(spawn_clues_window()));
    QObject::connect(buttons[QUIT], SIGNAL(clicked()), app, SLOT(quit()));

    clues_window_lock = false;

    central->setLayout(grid);
    this->setCentralWidget(central);


    //only for DEBUG purposes, table class is only being tested...
    Table t(this->db);
}

MainWindow::~MainWindow()
{
}


//SLOTS

void MainWindow::clear() {
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) cells[i][j]->setCurrentIndex(-1);
        QPixmap p = QPixmap(db->gui_config->value("propblankhouseimg")->at(0));
        p = p.scaled(80, 80);
        houses[i]->setPixmap(p);  //blank one
    }

    if(this->clues_window) this->clues_window->clear();
}

void MainWindow::change_house_pixmap(int house_index, int pixmap_index) {
    houses[house_index]->setPixmap(pmap[pixmap_index]);
}

void MainWindow::spawn_clues_window() {
    if(!this->clues_window_lock) {
        this->clues_window = new CluesWindow(this);
        this->clues_window->show();
        this->clues_window_lock = true;

        QObject::connect(this->clues_window, SIGNAL(clues_window_closed()), this, SLOT(unlock_clues_window()));
    }
}

void MainWindow::unlock_clues_window() {
    this->clues_window_lock = false;
}

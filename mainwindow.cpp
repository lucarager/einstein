#include "mainwindow.h"

/*  4 Fed
 *  Need DB.h, DB.c with all QStringLists needed
 *  Need Styles.h, Styles.c with fonts and sizes
*/

//ui setup
MainWindow::MainWindow(QApplication *app, QWidget *parent) : QMainWindow(parent)
{
    this->app = app;    //quit slot needed

    QWidget *central = new QWidget();
    QGridLayout *grid = new QGridLayout(this);
    grid->setSpacing(20);
    int grow=0, gcolumn=1;

    //load and scale house pixmap
    QStringList img_files;
    img_files << "C:/qtres/house_white.png" << "C:/qtres/house_red.png" << "C:/qtres/house_blue.png"
              << "C:/qtres/house_green.png" << "C:/qtres/house_violet.png" << "C:/qtres/house_blank.png";
    for(int i=0; i<6; i++) {
        pmap[i].load(img_files[i]);
        pmap[i] = pmap[i].scaled(80, 80);
    }

    //init 5 houses
    for(int i=0; i<5; i++) {
        houses[i] = new QLabel(this);
        grid->addWidget(houses[i], grow, gcolumn++);
    }
    grow=1;
    gcolumn=0;

    //labels text and font
    QStringList label_text;
    label_text << "Colore" << "Nazionalità" << "Bevanda" << "Sigarette" << "Animale";
    QFont f;
    f.setPointSize(10);
    f.setBold(true);

    //create and setup labels
    for(int i=0; i<5; i++) {
        labels[i] = new QLabel(this);
        labels[i]->setFont(f);
        labels[i]->setText(label_text[i]);
        labels[i]->setAlignment(Qt::AlignRight);
        grid->addWidget(labels[i], grow++, gcolumn);
    }

    //cells data
    enum {COLOR=0, NATIONALITY, DRINK, CIGARETTES, ANIMAL};
    QStringList cells_text[5];
    cells_text[COLOR]       << "Bianco" << "Rosso" << "Blu" << "Verde" << "Viola";
    cells_text[NATIONALITY] << "Russo" << "Tedesco" << "Maya" << "Italiano" << "Americano";
    cells_text[DRINK]       << "Vodka" << "Birra" << "Chamapane" << "Tequila" << "Rum";
    cells_text[CIGARETTES]  << "Virginia" << "Chesterfield" << "Davidoff" << "Diva" << "Camel";
    cells_text[ANIMAL]      << "Cavallo" << "Maialino" << "Gallina" << "Criceto" << "Serpente";

    //create and setup cells
    for(int i=0, grow=1; i<5; i++, grow++) {
        for(int j=0, gcolumn=1; j<5; j++, gcolumn++) {
            cells[i][j] = new Cell(j, this);
            cells[i][j]->addItems(cells_text[i]);
            grid->addWidget(cells[i][j], grow, gcolumn);
        }
        //conect top row cells (color related ones)
        QObject::connect(cells[0][i], SIGNAL(color_index_changed(int,int)), this, SLOT(change_house_pixmap(int,int)));
    }

    //set blank house image and reset cells indexes
    this->clear();

    //buttons
    QStringList button_labels, button_icon_files;
    button_labels << "Clear" << "Indications" << "Check" << "Solve" << "Quit";
    button_icon_files << "C:/qtres/reload.png" << "C:/qtres/info.png" << "C:/qtres/check.png"
                      << "C:/qtres/solve.png" << "C:/qtres/exit.png";

    grow=6, gcolumn=1;

    for(int i=0; i<5; i++) {
        buttons[i] = new QPushButton(this);
        buttons[i]->setIcon(QIcon(QPixmap(button_icon_files[i])));
        buttons[i]->setIconSize(QSize(buttons_iconsize, buttons_iconsize));
        buttons[i]->setText(button_labels[i]);
        grid->addWidget(buttons[i], grow, gcolumn++);
    }

    QObject::connect(buttons[RELOAD], SIGNAL(clicked()), this, SLOT(clear()));
    QObject::connect(buttons[QUIT], SIGNAL(clicked()), app, SLOT(quit()));

    central->setLayout(grid);
    this->setCentralWidget(central);
}

MainWindow::~MainWindow()
{
}


//SLOTS

void MainWindow::clear() {
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) cells[i][j]->setCurrentIndex(-1);
        houses[i]->setPixmap(pmap[5]);  //blank one
    }
}

void MainWindow::change_house_pixmap(int house_index, int pixmap_index) {
    houses[house_index]->setPixmap(pmap[pixmap_index]);
}

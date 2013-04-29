#include "mainwindow.h"

//ui setup
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setGeometry(100, 100, 650, 350);

    //load and scale house pixmap
    enum { WHITE, RED, BLUE, GREEN, VIOLET };

    //load images
    QStringList img_files;
    img_files << "C:/qtres/house_white.png" << "C:/qtres/house_red.png" << "C:/qtres/house_blue.png"
              << "C:/qtres/house_green.png" << "C:/qtres/house_violet.png" << "C:/qtres/house_blank.png";
    for(int i=0; i<6; i++) {
        pmap[i].load(img_files[i]);
        pmap[i] = pmap[i].scaled(80, 80);
    }

    //draw 5 houses
    for(int i=0, x=houses_init_x, y=houses_init_y;
        i<5;
        i++, x+=houses_inc_x) {
        houses[i] = new QLabel(this);
        houses[i]->setGeometry(x, y, houses_dim_x, houses_dim_y);
    }

    //labels text and font
    QStringList label_text;
    label_text << "Colore" << "Nazionalità" << "Bevanda" << "Sigarette" << "Animale";
    QFont f;
    f.setPointSize(10);
    f.setBold(true);

    //create and setup labels
    for(int i=0, x=labels_init_x, y=labels_init_y;
        i<5;
        i++, y+=labels_inc_y) {
        labels[i] = new QLabel(this);
        labels[i]->setGeometry(x, y, labels_dim_x, labels_dim_y);
        labels[i]->setFont(f);
        labels[i]->setText(label_text[i]);
        labels[i]->setAlignment(Qt::AlignRight);
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
    for(int i=0, y=cells_init_y;
        i<5;
        i++, y+=cells_inc_y) {
        for(int j=0, x=cells_init_x;
            j<5;
            j++, x+=cells_inc_x) {
            cells[i][j] = new Cell(j, this);
            cells[i][j]->setGeometry(x, y, cells_dim_x, cells_dim_y);
            cells[i][j]->addItems(cells_text[i]);
        }
    }

    //set blank house image and reset cells indexes
    this->clear();

    //set up signals&slots for house color change
    for(int i=0; i<5; i++)
        QObject::connect(cells[0][i], SIGNAL(color_index_changed(int,int)), this, SLOT(change_house_pixmap(int,int)));

    //buttons
    reload = new QPushButton(this);
    reload->setGeometry(120, 280, 80, 40);
    reload->setIcon(QIcon(QPixmap("C:/qtres/reload.png")));
    reload->setIconSize(QSize(30, 30));
    reload->setText("Clear");
    QObject::connect(reload, SIGNAL(released()), this, SLOT(clear()));

    indications = new QPushButton(this);
    indications->setGeometry(220, 280, 100, 40);
    indications->setIcon(QIcon(QPixmap("C:/qtres/info.png")));
    indications->setIconSize(QSize(30, 30));
    indications->setText("Indications");

    check = new QPushButton(this);
    check->setGeometry(340, 280, 80, 40);
    check->setIcon(QIcon(QPixmap("C:/qtres/check.png")));
    check->setIconSize(QSize(30,30));
    check->setText("Check");

    solve = new QPushButton(this);
    solve->setGeometry(440, 280, 80, 40);
    solve->setIcon(QIcon(QPixmap("C:/qtres/solve.png")));
    solve->setIconSize(QSize(30, 30));
    solve->setText("Solve");


}

MainWindow::~MainWindow()
{
}

//SLOTS

void MainWindow::clear() {
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) cells[i][j]->setCurrentIndex(-1);
        houses[i]->setPixmap(pmap[5]);//blank one
    }
}

void MainWindow::change_house_pixmap(int house_index, int pixmap_index) {
    houses[house_index]->setPixmap(pmap[pixmap_index]);
}

#include "mainwindow.h"

//ui setup
MainWindow::MainWindow(QApplication *app, QWidget *parent) : QMainWindow(parent)
{
    this->app = app;    //quit slot needed

    db = new DB(":/xml/cell_items.xml", ":/xml/gui_config.xml");
    t = new Table(this->db);

    QString tmp;
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            tmp += this->t->table[i][j].answer + " ";
        }
        tmp += "\n";
    }
    qDebug(tmp.toLatin1().data());

    this->setWindowTitle(db->gui_config->value("mainwindowtitle")->at(0).answer);
    this->setWindowIcon(QIcon(QPixmap(db->gui_config->value("mainwindowicon")->at(0).answer)));

    //labels font
    QFont f;
    f.setPointSize(10);
    f.setBold(true);

    QVBoxLayout *main_mw_layout;


    //create and visualize clues in the top part of window
    QCheckBox *tmp_clue_cbox;
    QLabel *tmp_clue_label;

    QHBoxLayout *tmph = new QHBoxLayout(this);
    QVBoxLayout *tmpv = new QVBoxLayout(this);
    QHBoxLayout *tmp_clue_row;

    //DUMMY CULES INSERT
    this->t->clues->clear();
    for(int i=0; i<25; i++) this->t->clues->append(QString::number(i+1) + "). TEST CLUE");
    //

    int clues_displayed=0;
    while(clues_displayed != this->t->clues->size()) {
        if(clues_displayed == 15) {
            tmph->addLayout(tmpv);
            tmpv = new QVBoxLayout;
        }

        tmp_clue_cbox = new QCheckBox(this);
        this->clues_checkbox << tmp_clue_cbox;
        tmp_clue_label = new QLabel(this);
        this->clues_labels << tmp_clue_label;

        tmp_clue_label->setText(this->t->clues->at(clues_displayed));
        tmp_clue_label->setAlignment(Qt::AlignLeft);
        QObject::connect(tmp_clue_cbox, SIGNAL(clicked(bool)), tmp_clue_label, SLOT(setDisabled(bool)));

        tmp_clue_row = new QHBoxLayout(this);
        tmp_clue_row->addWidget(tmp_clue_cbox);
        tmp_clue_row->addSpacing(20);
        tmp_clue_row->addWidget(tmp_clue_label);

        tmpv->addLayout(tmp_clue_row);

        clues_displayed++;
    }

    if(clues_displayed > 15) tmph->addLayout(tmpv);

    int row=0, col=0;

    QWidget *central = new QWidget();
    QGridLayout *grid = new QGridLayout(this);
    grid->setSpacing(20);

    //create and setup labels
    for(int i=0; i<5; i++, row++) {
        labels[i] = new QLabel(this);
        labels[i]->setFont(f);
        labels[i]->setText(t->table[i][0].answertype);
        labels[i]->setAlignment(Qt::AlignRight);
        grid->addWidget(labels[i], row, 0);
    }

    //create and setup cells
    for(int i=0, row=0; i<5; i++, row++) {
        for(int j=0, col=1; j<5; j++, col++) {
            cells[i][j] = new QComboBox(this);
            cells[i][j]->addItems(t->rowstext[i]);
            grid->addWidget(cells[i][j], row, col);
        }
    }

    for(int i=0, col=1; i<5; i++, col++) {
        buttons[i] = new QPushButton(this);
        buttons[i]->setIcon(QIcon(QPixmap(this->db->gui_config->value("buttonimg")->at(i).answer)));
        buttons[i]->setIconSize(QSize(buttons_iconsize, buttons_iconsize));
        buttons[i]->setText(this->db->gui_config->value("buttonlabels")->at(i).answer);
        grid->addWidget(buttons[i], row, col);
    }

    QObject::connect(buttons[RELOAD], SIGNAL(clicked()), this, SLOT(clear()));
    QObject::connect(buttons[QUIT], SIGNAL(clicked()), app, SLOT(quit()));
    QObject::connect(buttons[CHECK], SIGNAL(clicked()), this, SLOT(send_to_check()));
    QObject::connect(buttons[SOLVE], SIGNAL(clicked()), this, SLOT(solve()));

    main_mw_layout = new QVBoxLayout(this);
    main_mw_layout->addLayout(tmph);
    main_mw_layout->addSpacing(20);
    main_mw_layout->addLayout(grid);

    central->setLayout(main_mw_layout);
    this->setCentralWidget(central);

    //set blank house image and reset cells indexes
    this->clear();
}

MainWindow::~MainWindow()
{
}

//SLOTS

void MainWindow::clear() {
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            this->cells[i][j]->setCurrentIndex(-1);

    for(int i=0; i<this->clues_checkbox.size(); i++) {
        this->clues_checkbox[i]->setChecked(false);
        this->clues_labels[i]->setEnabled(true);
    }
}

void MainWindow::send_to_check() {
    QString answers[5][5];
    QMessageBox box;

    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            answers[i][j] = this->cells[i][j]->itemText(this->cells[i][j]->currentIndex());
        }
    }

    if(t->check(answers)) {
        box.setText("Hai risolto l'indovinello, complimenti!");
        box.setIcon(QMessageBox::Warning);
    }
    else {
        box.setText("Non è esatto. Riprova!");
        box.setIcon(QMessageBox::Critical);
    }

    box.setWindowTitle("Risultato");
    box.setWindowIcon(QIcon(db->gui_config->value("mainwindowicon")->at(0).answer));
    box.exec();
}

void MainWindow::solve() {
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            cells[i][j]->setCurrentText(t->table[i][j].answer);
}

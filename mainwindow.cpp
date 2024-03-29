#include "mainwindow.h"

//ui setup
MainWindow::MainWindow(QApplication *app, QWidget *parent) : QMainWindow(parent)
{
    this->app = app;    //quit slot needed

    db = new DB(":/xml/cell_items.xml", ":/xml/gui_config.xml");
    t = new Table(this->db);

    this->setWindowTitle(db->gui_config->value("mainwindowtitle")->at(0).answer);
    this->setWindowIcon(QIcon(QPixmap(db->gui_config->value("mainwindowicon")->at(0).answer)));
    this->setStyleSheet(
                "QMainWindow {"\
                "background-image: url(\"://images/mwbackground.jpg\");"\
                "}");

    //labels font
    QFont f;
    f.setPointSize(10);
    f.setBold(true);

    //Layouts & Widgets for GUI
    QWidget *mw_widget = new QWidget(this);
    mw_widget->setContentsMargins(20,0,20,0);
    QVBoxLayout *mw_layout = new QVBoxLayout(this);

    QLabel *einstein_logo = new QLabel(this);

    QWidget *answers_and_clues_widget = new QWidget(this);
    QVBoxLayout *answers_and_clues_vl = new QVBoxLayout(this);

    QWidget *grid_widget = new QWidget(this);
    QGridLayout *grid = new QGridLayout(this);

    QWidget *clues_widget = new QWidget(this);
    clues_widget->setObjectName("clues_widget");
    QHBoxLayout *clues_hl = new QHBoxLayout(this);
    QVBoxLayout *tmpv = new QVBoxLayout(this);
    QHBoxLayout *tmp_clue_row;

    QWidget *buttons_widget = new QWidget(this);
    QHBoxLayout *buttons_layout = new QHBoxLayout(this);

    //create and visualize clues in the top part of window
    QCheckBox *tmp_clue_cbox;
    QLabel *tmp_clue_label;
    QLabel *label;

    QHBoxLayout *tmphl = new QHBoxLayout(this);
    //developed by
    label=new QLabel(this);
    label->setText("Alexei '4mp3R' Liulin\nLuca 'Antariano' Rager\nFederica 'Feddie' Baiocchi\nFrancesco 'Acala' Iubatti");
    label->setStyleSheet(
                "color: white;"\
                "font-size: 10px;");
    tmphl->addWidget(label);

    //Einstein logo
    einstein_logo->setPixmap(QPixmap("://images/logoeinstein.png"));
    einstein_logo->setPixmap(einstein_logo->pixmap()->scaled(160, 80, Qt::KeepAspectRatio));
    einstein_logo->setAlignment(Qt::AlignCenter);
    tmphl->addWidget(einstein_logo);

    label=new QLabel(this);
    tmphl->addWidget(label);

    //clues combobox grid generetion
    int clues_displayed=0;
    while(clues_displayed != this->t->clues->size()) {
        if(clues_displayed == this->t->clues->size() / 2 + this->t->clues->size() % 2) {
            clues_hl->addLayout(tmpv);
            tmpv = new QVBoxLayout;
        }

        tmp_clue_cbox = new QCheckBox(this);
        this->clues_checkbox.append(tmp_clue_cbox);
        tmp_clue_label = new QLabel(this);
        this->clues_labels.append(tmp_clue_label);
        tmp_clue_label->setAlignment(Qt::AlignLeft);

        tmp_clue_label->setText(this->t->clues->at(clues_displayed));
        QObject::connect(tmp_clue_cbox, SIGNAL(clicked(bool)), tmp_clue_label, SLOT(setDisabled(bool)));

        tmp_clue_row = new QHBoxLayout(this);
        tmp_clue_row->addWidget(tmp_clue_cbox);
        tmp_clue_row->addSpacing(10);
        tmp_clue_row->addWidget(tmp_clue_label, 1, Qt::AlignLeft);

        tmpv->addLayout(tmp_clue_row);

        clues_displayed++;
    }

    if(this->t->clues->size() % 2 == 1) {
        tmp_clue_label = new QLabel(this);
        tmpv->addWidget(tmp_clue_label);
    }
/*
    for(int i=clues_displayed; i<30; i++) {
        tmp_clue_label = new QLabel(this);
        tmpv->addWidget(tmp_clue_label);
    }
    */

    if(clues_displayed > 15) clues_hl->addLayout(tmpv);
    clues_widget->setLayout(clues_hl);
    clues_widget->setStyleSheet(
                "#clues_widget {"\
                "background-color: #c5c5c5;"\
                "border: 1px solid #aaa;"\
                "}");

    int row=0;

    //create and setup labels
    QLabel *tmplabel;
    for(int i=0; i<5; i++, row++) {
        tmplabel = new QLabel(this);
        tmplabel->setFont(f);
        tmplabel->setText(t->table[i][0].answertype);
        tmplabel->setAlignment(Qt::AlignRight);
        grid->addWidget(tmplabel, row, 0);
    }

    grid_widget->setLayout(grid);
    grid_widget->setStyleSheet(
                "QLabel {"\
                "color: #225588;"\
                "font-weight: bold;"\
                "}"\
                "QComboBox {"\
                "font-weight: bold;"\
                "}");


    //create and setup cells
    for(int i=0, row=0; i<5; i++, row++) {
        for(int j=0, col=1; j<5; j++, col++) {
            cells[i][j] = new QComboBox(this);
            cells[i][j]->addItem("");
            cells[i][j]->addItems(t->rowstext[i]);
            grid->addWidget(cells[i][j], row, col);
        }
    }

    answers_and_clues_widget->setObjectName("acw");
    answers_and_clues_widget->setStyleSheet(
                "#acw {"\
                "background-color: white;"\
                "}");

    //Buttons
    for(int i=0, col=1; i<4; i++, col++) {
        buttons[i] = new QPushButton(this);
        buttons[i]->setIcon(QIcon(QPixmap(this->db->gui_config->value("buttonimg")->at(i).answer)));
        buttons[i]->setIconSize(QSize(buttons_iconsize, buttons_iconsize));
        buttons[i]->setText(this->db->gui_config->value("buttonlabels")->at(i).answer);
        buttons_layout->addWidget(buttons[i]);
    }

    buttons_widget->setLayout(buttons_layout);
    buttons_widget->setStyleSheet(
                "QPushButton {"\
                "color: #fff;"\
                "font-weight: bold;"\
                "background-color: transparent;"\
                "padding: 5px 5px;"\
                "}"\
                "QPushButton:hover {"\
                "border: 1px solid rgba(255,255,255,.8);"\
                "}");

    //buttons connection
    QObject::connect(buttons[RELOAD], SIGNAL(clicked()), this, SLOT(clear()));
    QObject::connect(buttons[QUIT], SIGNAL(clicked()), app, SLOT(quit()));
    QObject::connect(buttons[CHECK], SIGNAL(clicked()), this, SLOT(send_to_check()));
    QObject::connect(buttons[SOLVE], SIGNAL(clicked()), this, SLOT(solve()));

    //put all together
    //mw_layout->addWidget(einstein_logo);
    mw_layout->addLayout(tmphl);
    answers_and_clues_vl->addWidget(grid_widget);
    answers_and_clues_vl->addWidget(clues_widget);
    answers_and_clues_widget->setLayout(answers_and_clues_vl);
    mw_layout->addWidget(answers_and_clues_widget);
    mw_layout->addSpacing(20);
    mw_layout->addWidget(buttons_widget);

    mw_widget->setLayout(mw_layout);

    this->setCentralWidget(mw_widget);

    //set blank house image and reset cells indexes
    this->clear();

    //info label
    label=new QLabel(this);
    label->setText("Per avere informazioni premi F1");
    label->setStyleSheet("color: white;");
    label->setAlignment(Qt::AlignCenter);
    mw_layout->addWidget(label);

    //rules notification at startup
    this->show_notification(this->db->gui_config->value("rules")->at(0).answer);
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

    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            answers[i][j] = this->cells[i][j]->itemText(this->cells[i][j]->currentIndex());

    if(t->check(answers))
        this->show_notification(this->db->gui_config->value("solved_ok")->at(0).answer);
    else
        this->show_notification(this->db->gui_config->value("solved_ko")->at(0).answer);

}

void MainWindow::solve() {
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            cells[i][j]->setCurrentText(t->table[i][j].answer);
}

void MainWindow::show_notification(QString msg) {
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            this->cells[i][j]->setEnabled(false);

    for(int i=0; i<this->clues_checkbox.size(); i++)
        this->clues_checkbox.at(i)->setEnabled(false);

    for(int i=0; i<4; i++) this->buttons[i]->setEnabled(false);

    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect(this);
    blur->setBlurRadius(3);
    this->setGraphicsEffect(blur);

    this->notification = new NotificationWidget(msg, this);
    QObject::connect(notification, SIGNAL(closed()), this, SLOT(notification_closed()));
    this->notification->show();

    this->has_active_notification = true;
}

void MainWindow::notification_closed() {
    delete this->notification;

    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            this->cells[i][j]->setEnabled(true);

    for(int i=0; i<this->clues_checkbox.size(); i++)
        this->clues_checkbox.at(i)->setEnabled(true);

    for(int i=0; i<4; i++) this->buttons[i]->setEnabled(true);

    this->setGraphicsEffect(0);

    this->has_active_notification = false;
}

void MainWindow::keyPressEvent(QKeyEvent *ke) {
    if(ke->key() == Qt::Key_F1 && !has_active_notification)
        this->show_notification(this->db->gui_config->value("rules")->at(0).answer);
}

void MainWindow::moveEvent(QMoveEvent *me) {    //used to translate child as parent translates
    static int canmove_counter = 0;

    if(this->has_active_notification && canmove_counter >= 2) { //need to filter 2 init events
        this->notification->move(this->notification->pos() + me->pos() - me->oldPos());
    } else if(canmove_counter < 2) canmove_counter++;
}

void MainWindow::paintEvent(QPaintEvent *) {    //used for init allign
    if(this->has_active_notification)
    this->notification->move(
                this->geometry().x() + (this->geometry().width() - this->notification->geometry().width()) / 2,
                this->geometry().y() + (this->geometry().height() - this->notification->geometry().height()) / 2
                );
}

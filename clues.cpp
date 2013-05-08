#include "clues.h"

CluesWindow::CluesWindow(QWidget *parent) : QMainWindow(parent) {
    this->setWindowTitle("Clues");

    QWidget *central = new QWidget(this);
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    QHBoxLayout *hlayouts[15];

    for(int i=0; i<15; i++) {
        checks[i] = new CheckBox(i, this);
        clues[i] = new QLabel(this);
        clues[i]->setText(QString::number(i+1) + "). Il tizio che beve vodka ha un orso addomesticato............");

        hlayouts[i] = new QHBoxLayout(this);
        hlayouts[i]->addWidget(checks[i]);
        hlayouts[i]->addWidget(clues[i]);
        vlayout->addLayout(hlayouts[i]);

        QObject::connect(checks[i], SIGNAL(strikeout_emitter(int,bool)), this, SLOT(strike_out(int,bool)));
    }

    central->setLayout(vlayout);
    this->setCentralWidget(central);
}

CluesWindow::~CluesWindow() {

}

void CluesWindow::closeEvent(QCloseEvent *event) {
    event->accept();
    emit clues_window_closed();
}


void CluesWindow::strike_out(int index, bool strikeout) {
    QFont f;

    f.setStrikeOut(strikeout);

    this->clues[index]->setFont(f);
}

void CluesWindow::clear() {
    for(int i=0; i<15; i++)
        this->checks[i]->setChecked(false);
}

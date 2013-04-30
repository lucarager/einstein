#include "indications.h"

Indications::Indications(QWidget *parent) : QMainWindow(parent) {
    this->setWindowTitle("Indications");

    QWidget *central = new QWidget(this);
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    QHBoxLayout *hlayouts[15];

    for(int i=0; i<15; i++) {
        checks[i] = new CheckBox(i, this);
        indications[i] = new QLabel(this);
        indications[i]->setText(QString::number(i+1) + "). Il tizio che beve vodka ha un orso addomesticato............");

        hlayouts[i] = new QHBoxLayout(this);
        hlayouts[i]->addWidget(checks[i]);
        hlayouts[i]->addWidget(indications[i]);
        vlayout->addLayout(hlayouts[i]);

        QObject::connect(checks[i], SIGNAL(strikeout_emitter(int,bool)), this, SLOT(strike_out(int,bool)));
    }

    central->setLayout(vlayout);
    this->setCentralWidget(central);
}

Indications::~Indications() {

}

void Indications::closeEvent(QCloseEvent *event) {
    event->accept();
    emit indications_window_closed();
}


void Indications::strike_out(int index, bool strikeout) {
    QFont f;

    f.setStrikeOut(strikeout);

    this->indications[index]->setFont(f);
}

void Indications::clear() {
    for(int i=0; i<15; i++) {
        this->checks[i]->setChecked(false);
    }
}

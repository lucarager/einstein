#include "indications.h"

Indications::Indications(QWidget *parent) : QMainWindow(parent) {
    this->setWindowTitle("Indications");
}

Indications::~Indications() {

}

void Indications::closeEvent(QCloseEvent *event) {
    event->accept();
    emit indications_window_closed();
}

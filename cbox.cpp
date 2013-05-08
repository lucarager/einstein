#include "cbox.h"

CBox::CBox(int cell_index, QWidget *parent) : QComboBox(parent) {
    this->cell_index = cell_index;

    //when currentIndex changes emit a signal containing cell position and pixmap index
    QObject::connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(signal_caller(int)));
}

CBox::~CBox() {

}

void CBox::signal_caller(int cur_index) {
    emit color_index_changed(this->cell_index, cur_index);
}
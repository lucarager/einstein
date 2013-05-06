#include "clue_checkbox.h"

CheckBox::CheckBox(int index, QWidget *parent) : QCheckBox(parent) {
    this->index = index;

    QObject::connect(this, SIGNAL(stateChanged(int)), SLOT(read_state_change(int)));
}

CheckBox::~CheckBox() {

}

void CheckBox::read_state_change(int state) {
    bool strikeout = (state == Qt::Checked) ? true : false;

    emit strikeout_emitter(this->index, strikeout);
}

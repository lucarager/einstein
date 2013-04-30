#ifndef IND_CHECKBOX_H
#define IND_CHECKBOX_H

#include <QCheckBox>

class CheckBox : public QCheckBox {
    Q_OBJECT

public:
    CheckBox(int index, QWidget *parent=0);
    ~CheckBox();

private slots:
    void read_state_change(int state);

signals:
    void strikeout_emitter(int index, bool strikeout);

private:
    int index;
};

#endif // IND_CHECKBOX_H

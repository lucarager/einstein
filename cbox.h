#ifndef CELL_H
#define CELL_H

#include <QComboBox>

class CBox : public QComboBox {
    Q_OBJECT

public:
    CBox(int cell_index, QWidget *parent=0);
    ~CBox();

private slots:
    void signal_caller(int cur_index);

signals:
    void color_index_changed(int cell_index, int color_index);

private:
    int cell_index;
};

#endif // CELL_H

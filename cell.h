#ifndef CELL_H
#define CELL_H

#include <QComboBox>

class Cell : public QComboBox {
    Q_OBJECT

public:
    Cell(int cell_index, QWidget *parent=0);
    ~Cell();

private slots:
    void signal_caller(int cur_index);

signals:
    void color_index_changed(int cell_index, int color_index);

private:
    int cell_index;
};

#endif // CELL_H

#ifndef INDICATIONS_H
#define INDICATIONS_H

#include <QMainWindow>
#include <QWidget>
#include <QCloseEvent>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "ind_checkbox.h"

class CluesWindow : public QMainWindow {
    Q_OBJECT

public:
    CluesWindow(QWidget *parent=0);
    ~CluesWindow();

    void clear();

private slots:
    void strike_out(int index, bool strikeout);

signals:
    void clues_window_closed();
    void checked(int index, int state);

private:
    void closeEvent(QCloseEvent *event);

    CheckBox *checks[15];
    QLabel *clues[15];
};

#endif // INDICATIONS_H

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

class Indications : public QMainWindow {
    Q_OBJECT

public:
    Indications(QWidget *parent=0);
    ~Indications();

    void clear();

private slots:
    void strike_out(int index, bool strikeout);

signals:
    void indications_window_closed();
    void checked(int index, int state);

private:
    void closeEvent(QCloseEvent *event);

    CheckBox *checks[15];
    QLabel *indications[15];
};

#endif // INDICATIONS_H

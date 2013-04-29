#ifndef INDICATIONS_H
#define INDICATIONS_H

#include <QMainWindow>
#include <QWidget>
#include <QCloseEvent>
#include <QLabel>

class Indications : public QMainWindow {
    Q_OBJECT

public:
    Indications(QWidget *parent=0);
    ~Indications();

signals:
    void indications_window_closed();

private:
    void closeEvent(QCloseEvent *event);

    QLabel *indications[15];
};

#endif // INDICATIONS_H

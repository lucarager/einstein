#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QStringList>
#include <QLabel>
#include <QPixmap>
#include <QComboBox>
#include <QPushButton>
#include <QIcon>
#include <QPixmap>
#include <QGridLayout>
#include "cell.h"

//pixmaps enum
enum { WHITE, RED, BLUE, GREEN, VIOLET };
//button array index enum
enum { RELOAD, INDICATIONS, CHECK, SOLVE, QUIT };

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QApplication *app, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void clear(void);
    void change_house_pixmap(int house_index, int pixmap_index);

private:
    QApplication *app;

    QLabel *houses[5];
    QPixmap pmap[6];

    QLabel *labels[5];

    Cell *cells[5][5];

    static const int buttons_iconsize=30;
    QPushButton *buttons[5];
};

#endif // MAINWINDOW_H

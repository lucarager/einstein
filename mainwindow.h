#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QLabel>
#include <QPixmap>
#include <QComboBox>
#include <QPushButton>
#include <QIcon>
#include <QPixmap>
#include "cell.h"

enum { WHITE, RED, BLUE, GREEN, VIOLET };

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void clear(void);
    void change_house_pixmap(int house_index, int pixmap_index);

signals:    //signals DO NOT HAVE imlementations in .c file !

private:
    static const int houses_init_x=120, houses_init_y=20, houses_dim_x=80, houses_dim_y=80, houses_inc_x=100;
    QLabel *houses[5];
    QPixmap pmap[6];

    static const int labels_init_x=10, labels_init_y=120, labels_dim_x=90, labels_dim_y=20, labels_inc_y=30;
    QLabel *labels[5];

    static const int cells_init_x=120, cells_init_y=120, cells_dim_x=80, cells_dim_y=20, cells_inc_x=100, cells_inc_y=30;
    Cell *cells[5][5];

    QPushButton *reload, *indications, *check, *solve;
};

#endif // MAINWINDOW_H

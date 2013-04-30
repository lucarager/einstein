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
#include <QXmlStreamReader>
#include <QMessageBox>
#include "cell.h"
#include "indications.h"
#include "db.h"

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
    void spawn_indications_window();
    void unlock_indications_window();

private:
    QApplication *app;

    DB *db;

    QLabel *houses[5];
    QPixmap pmap[6];

    QLabel *labels[5];

    Cell *cells[5][5];

    static const int buttons_iconsize=30;
    QPushButton *buttons[5];

    Indications *indications_window;
    bool indications_window_lock;
};

#endif // MAINWINDOW_H

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
#include <QTimer>
#include <QCheckBox>
#include "db.h"
#include "table.h"

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
    void send_to_check();
    void solve();

private:
    QApplication *app;

    DB *db;
    Table *t;

    QList<QCheckBox*> clues_checkbox;
    QList<QLabel*> clues_labels;

    QLabel *labels[5];

    QComboBox *cells[5][5];

    static const int buttons_iconsize=30;
    QPushButton *buttons[5];
};

#endif // MAINWINDOW_H

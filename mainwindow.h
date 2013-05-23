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
#include <QGraphicsBlurEffect>
#include <QKeyEvent>
#include "db.h"
#include "table.h"
#include "notificationwidget.h"

//pixmaps enum
enum { WHITE, RED, BLUE, GREEN, VIOLET };
//button array index enum
enum { RELOAD, CHECK, SOLVE, QUIT };

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
    void notification_closed();

private:
    QApplication *app;

    DB *db;
    Table *t;

    QList<QCheckBox*> clues_checkbox;
    QList<QLabel*> clues_labels;

    QComboBox *cells[5][5];
    QPushButton *buttons[4];

    NotificationWidget *notification;

    static const int buttons_iconsize=30;

    bool has_active_notification;

    void show_notification(QString msg);
    void keyPressEvent(QKeyEvent *);
};

#endif // MAINWINDOW_H

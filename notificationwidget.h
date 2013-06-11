#ifndef NOTIFICATION_WIDGET_H
#define NOTIFICATION_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>
#include <QKeyEvent>

class NotificationWidget : public QWidget
{
    Q_OBJECT

public:
    NotificationWidget(QString msg, QWidget *parent = 0);

signals:
    void closed();

private:
    QPushButton *close_button;
    QLabel *message;

    virtual void closeEvent(QCloseEvent *);
    virtual void keyPressEvent(QKeyEvent *);
};

#endif // NOTIFICATION_WIDGET_H

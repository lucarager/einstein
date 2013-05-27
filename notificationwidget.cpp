#include "notificationwidget.h"


NotificationWidget::NotificationWidget(QString msg, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *vl = new QVBoxLayout(this);

    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    this->setStyleSheet("background: white;");

    this->close_button = new QPushButton(this);
    this->close_button->setObjectName("close_button");
    this->close_button->setStyleSheet(
                "#close_button {"
                "font-size: 16px;"\
                "text-align: right;"\
                "background: transparent;"\
                "}"\
                "#close_button:hover {"\
                "font-size: 20px;"\
                "font-weight: bold;"\
                "color: #225588;"\
                "}");
    this->close_button->setText("X");
    vl->addWidget(this->close_button);

    QObject::connect(close_button, SIGNAL(clicked()), this, SLOT(close()));

    this->message = new QLabel(this);
    this->message->setStyleSheet(
                "font-family: Comic Sans MS;"\
                "font-size: 14px;"\
                "margin: 30px 30px");
    msg.replace("\\n", "\n");
    this->message->setText(msg);
    vl->addWidget(this->message);

}

void NotificationWidget::closeEvent(QCloseEvent *ce) {
    emit closed();
}

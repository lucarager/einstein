#ifndef DB_H
#define DB_H

#include <QStringList>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QMessageBox>

class DB : public QObject {
    Q_OBJECT

public:
    DB(QString dbfile, QObject *parent=0);
    ~DB();

    //TODO: use hashtable or map to avoid manual indexing in mainwindow
    QList<QStringList> properties;
};

#endif // DB_H

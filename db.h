#ifndef DB_H
#define DB_H

#include <QStringList>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QMessageBox>

class DB {
public:
    DB(QString itemsxml, QString guixml);
    ~DB();

    void parseXML(QString xmlfile, QHash<QString, QStringList*>* &h);

    QHash<QString, QStringList*> *cell_items;
    QHash<QString, QStringList*> *gui_config;
};

#endif // DB_H

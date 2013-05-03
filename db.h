#ifndef DB_H
#define DB_H

#include <QStringList>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QList>
#include "tablecell.h"

class DB {
public:
    DB(QString itemsxml, QString guixml);
    ~DB();

    void parseXML(QString xmlfile, QHash<QString, QList<TableCell>*>* &h);

    QHash<QString, QList<TableCell>*> *cell_items;
    QHash<QString, QList<TableCell>*> *gui_config;
};

#endif // DB_H

#ifndef TABLE_H
#define TABLE_H

#include <QString>
#include <QTime>
#include <QDate>
#include <QStringList>
#include "db.h"

struct TableCell {
    bool referenced;
    bool deducable;
    int col;
    QString answer;
    QString aswertype;
    QString verb;
};

class Table {
public:
    Table(DB *db);
    ~Table();

private:
    DB *db;
    TableCell table[5][5];          //used to generate clues and check for the right answers
    QStringList finalproperties[5]; //used to fill comboboxes

    void generateRandomTableFromDB();
    void generateClues();

    TableCell *getRandomUnreferencedCellInRow(int row);
    TableCell *getRandomReferencedCellInRow(int row);

    QStringList getCellStringList(int row);

    bool check(QString **answers);
    QString **solve();
};

#endif // TABLE_H

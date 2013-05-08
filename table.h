#ifndef TABLE_H
#define TABLE_H

#include <QString>
#include <QTime>
#include <QDate>
#include <QStringList>
#include "db.h"
#include "tablecell.h"

class Table {
public:
    Table(DB *db);
    ~Table();

    QStringList rowstext[5];        //used to fill comboboxes
    TableCell table[5][5];          //used to generate clues and check for the right answers

    bool check(QString answers[5][5]);
    QString **solve();

    TableCell *getRandomUnreferencedCellInRow(int row);
    TableCell *getRandomReferencedCellInRow(int row);

private:
    DB *db;

    void generateRandomTableFromDB();
    void generateClues();
};

#endif // TABLE_H

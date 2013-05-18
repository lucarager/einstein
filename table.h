#ifndef TABLE_H
#define TABLE_H

#include <QString>
#include <QTime>
#include <QDate>
#include <QDebug>
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
    bool solvable;
    QStringList *clues;
    QString **solve();

    int unreferencedCellsCount;
    int referencedCellsCount;

    TableCell *getCell(int row, int column, bool referenced);

private:
    DB *db;

    void generateRandomTableFromDB();
    void generateClues();
    void generateRandomClue(TableCell *cell);
    void generateVerticalClue(TableCell *cell);
    void generateBetweenClue(TableCell *cell);
    void generateDirectionalClue(TableCell *cell);
    void generateNearClue(TableCell *cell);
    void reference(TableCell *cell);
};

#endif // TABLE_H

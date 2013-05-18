#ifndef TABLECELL_H
#define TABLECELL_H

#include <QString>

struct TableCell {
    bool referenced;
    bool deducable;
    int col;
    int row;
    QString answer;
    QString answertype;
    QString prefix;
};

#endif // TABLECELL_H

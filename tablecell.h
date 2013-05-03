#ifndef TABLECELL_H
#define TABLECELL_H

#include <QString>

struct TableCell {
    bool referenced;
    bool deducable;
    int col;
    QString answer;
    QString answertype;
    QString verb;
};

#endif // TABLECELL_H

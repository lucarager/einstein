#include "table.h"


Table::Table(DB *db) {
    this->db = db;
    this->solvable = false;
    this->unreferencedCellsCount = 25;
    this->referencedCellsCount = 0;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    this->generateRandomTableFromDB();
}

Table::~Table() {

}

void Table::generateRandomTableFromDB() {
    //FOR DEBUGGING INFO
    QMessageBox m;

    //random seed
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    qsrand(date.year() + date.month() + date.day() + time.hour() + time.minute() + time.second());

    //random selection of 5 properties from DB
    QList<TableCell> *rows[5];
    QList<int> used;
    int rndindex;
/*
 *  Nationalita' + colore hardcoded
 *  + 3 random properties
 *
 *  Select 5 properties from db
 */
    for(int i=0; i<5; i++) {
        while(used.contains(rndindex = qrand() % db->cell_items->size()));
        used << rndindex;
        rows[i] = db->cell_items->value(db->cell_items->keys().at(rndindex));
    }

    //random selection of 5 items for each of 5 selected properties
    //and random table construction
    for(int i=0; i<5; i++) {
        used.clear();
        for(int j=0; j<5; j++) {
            while(used.contains(rndindex = qrand() % rows[i]->size())) ;
            used << rndindex;

            table[i][j].answer = rows[i]->at(rndindex).answer;
            table[i][j].answertype = rows[i]->at(rndindex).answertype;
            table[i][j].prefix = rows[i]->at(rndindex).prefix;
            table[i][j].referenced = false;
            table[i][j].deducable = true;
            table[i][j].row = i;
            table[i][j].col = j;

            rowstext[i] << rows[i]->at(j).answer;
        }
    }

    //DEBUG purposes: visualize generated matrix, it's NOT yet used in the UI construction
    QMessageBox box;
    QString msg = "\t-=[ Right Answers]=-\n\n";
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) msg += table[i][j].answer + " ";
        msg += "\n";
    }
    box.setText(msg);
    box.exec();
    generateClues();
}

void Table::generateClues() {

    int i = 20;

    while(i--) {

        if(this->unreferencedCellsCount > 0) {
            if(this->unreferencedCellsCount == 25) {
                generateRandomClue(getCell(-1, -1, false));
            } else {
                generateRandomClue(getCell(-1, -1, true));
            }
        } else {
            this->solvable = true;
        }

    }
    for (int i = 0; i < clues->size(); i++)
    {
        qDebug() << this->clues->at(i);
    }


    //while !solvable
        //if unreferencedCells > 0
            //if unreferencedCells == CellCount
                //generateRandomClue(randomUnreferencedTile());
            //else
                //generateRandomClue(randomReferencedTile);
        //else
            //solvable = true
            //cleanup

}

TableCell* Table::getCell(int row, int column, bool referenced) {
    int rand1, rand2;
    while(true) {
        rand1 = qrand()%5;
        if(row > -1) {
            if(column > -1) {
                if(table[row][column].referenced == referenced) {
                    return &table[row][column];
                }  else {
                    return NULL;
                }
            } else {
                if(table[row][rand1].referenced == referenced) return &table[row][rand1];
            }
        } else {
            if(column > -1) {
                if(table[rand1][column].referenced == referenced) return &table[rand1][column];
            } else {
                rand2 = qrand()%5;
                if(table[rand1][rand2].referenced == referenced) return &table[rand1][rand2];
            }
        }
    }
}

void Table::generateRandomClue(TableCell *cell) {
    switch(qrand()%4) {
        case 0:
            generateVerticalClue(cell);
        break;
        case 1:
            generateBetweenClue(cell);
        break;
        case 2:
            generateDirectionalClue(cell);
        break;
        case 3:
            generateNearClue(cell);
        break;
    }
}
void Table::generateVerticalClue(TableCell *cell) {

    //data la tile di partenza, seleziona un'altra della stessa colonna
    //che non sia referenced
    TableCell *other;

    if(cell->row == 0) {
        other = getCell(1, cell->col, false);
        if(!other) return;
    } else if(cell->row == 4) {
        other = getCell(3, cell->col, false);
        if(!other) return;
    } else {
        if(qrand()%2) {
            other = getCell(cell->row + 1, cell->col, false);
            if(!other) other = getCell(cell->row - 1, cell->col, false);
            if(!other) return;
        } else {
            other = getCell(cell->row - 1, cell->col, false);
            if(!other) other = getCell(cell->row + 1, cell->col, false);
            if(!other) return;
        }
    }

    //fa sì che siano referenced
    this->reference(cell);
    this->reference(other);

    //genera la risposta
    this->clues->append(cell->answer + " è" + (other->row > cell->row ? " sopra " : " sotto ") + other->answer);
}
void Table::generateDirectionalClue(TableCell *cell) {
    TableCell *other;

    if(cell->row == 0) {
        other = getCell(cell->row, 1, false);
        if(!other) return;
    } else if(cell->row == 4) {
        other = getCell(cell->col, 3, false);
        if(!other) return;
    } else {
        if(qrand()%2) {
            other = getCell(cell->row, cell->col + 1, false);
            if(!other) other = getCell(cell->row, cell->col - 1, false);
            if(!other) return;
        } else {
            other = getCell(cell->row, cell->col - 1, false);
            if(!other) other = getCell(cell->row, cell->col + 1, false);
            if(!other) return;
        }
    }

    //fa sì che siano referenced
    this->reference(cell);
    this->reference(other);
    //genera la risposta
    this->clues->append(cell->answer + " è" + (other->col > cell->col ? " a sinistra di " : " a destra di ") + other->answer);
}
void Table::generateBetweenClue(TableCell *cell) {
    this->clues->append("generateBetweenClue");
}
void Table::generateNearClue(TableCell *cell) {
    this->clues->append("generateNearClue");
}
void Table::reference(TableCell *cell) {
    if(!cell->referenced) {
        cell->referenced = true;
        this->referencedCellsCount++;
        this->referencedCellsCount--;
    }
}
bool Table::check(QString answers[5][5]) {  //compares user's answers to the right ones
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            if(answers[i][j] != this->table[i][j].answer) return false;
        }
    }
    return true;
}

QString** Table::solve() {  //returns array of correct answers (strings)
    return NULL;
}

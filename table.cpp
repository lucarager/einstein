#include "table.h"


Table::Table(DB *db) {
    this->db = db;

    this->clues = new QStringList;
    this->solvable = false;
    this->unreferencedCellsCount = 25;
    this->referencedCellsCount = 0;

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    this->generateRandomTableFromDB();
    this->generateClues();    // CRASHES HERE //maby because of the infinite loop that should be already solved
}

Table::~Table() {

}

void Table::generateRandomTableFromDB() {
    //FOR DEBUGGING INFO
    QMessageBox m;

    //random selection of 5 properties from DB
    QList<TableCell> *rows[5];
    QList<TableCell> five_items[5];
    QList<int> used;
    int rndindex;

//  Select 5 properties from db
    qDebug("5 PROPS SELECTION");
    qDebug(QString::number(db->cell_items->size()).toLatin1().data());
    for(int i=0; i<5; i++) {
        while(used.contains(rndindex = qrand() % db->cell_items->size()));
        used << rndindex;
        rows[i] = db->cell_items->value(db->cell_items->keys().at(rndindex));   //QList<TableCell>
    }
    qDebug("5 ITEMS SELECTION");
    //random selection of 5 items for each of 5 selected properties
    //and random table construction
    for(int i=0; i<5; i++) {
        used.clear();
        for(int j=0; j<5; j++) {
            while(used.contains(rndindex = qrand() % rows[i]->size())) ;
            used.append(rndindex);
            five_items[i].append(rows[i]->at(rndindex));
            rowstext[i].append(rows[i]->at(rndindex).answer);
        }
    }

    qDebug("TABLE FILLING");
    for(int i=0; i<5; i++) {
        used.clear();

        for(int j=0; j<5; j++) {
            while(used.contains(rndindex = qrand() % 5));
            used.append(rndindex);

            table[i][j].answer = five_items[i].at(rndindex).answer;
            table[i][j].answertype = five_items[i].at(rndindex).answertype;
            table[i][j].prefix = five_items[i].at(rndindex).prefix;
            table[i][j].referenced = false;
            table[i][j].deducable = true;
            table[i][j].row = i;
            table[i][j].col = j;
        }
    }
    qDebug("FILLED");

    //DEBUG purposes: visualize generated matrix, it's NOT yet used in the UI construction
    QMessageBox box;
    QString msg = "\t-=[ Right Answers]=-\n\n";
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) msg += table[i][j].answer + " ";
        msg += "\n";
    }
    box.setText(msg);
    box.exec();
}

void Table::generateClues() {

    int i = 20;

    while(i--) {

        if(this->unreferencedCellsCount > 0) {
            if(this->unreferencedCellsCount == 25) {
                generateRandomClue(getCell(-1, -1, false, -1, -1));
            } else {
                generateRandomClue(getCell(-1, -1, true, -1, -1));
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

TableCell* Table::getCell(int row, int column, bool referenced, int exceptrow, int exceptcol) {
    int rand1, rand2;
    while(true) {
        rand1 = qrand()%5;
        if(row > -1) {
            if(column > -1) {
                if(table[row][column].referenced == referenced && table[row][column].row != exceptrow && table[row][column].col != exceptcol) {
                    return &table[row][column];
                }  else {
                    return NULL;
                }
            } else {
                if(table[row][rand1].referenced == referenced && table[row][rand2].row != exceptrow && table[row][rand2].col != exceptcol) return &table[row][rand1];
            }
        } else {
            if(column > -1) {
                if(table[rand1][column].referenced == referenced && table[rand1][column].row != exceptrow && table[rand1][column].col != exceptcol) return &table[rand1][column];
            } else {
                rand2 = qrand()%5;
                if(table[rand1][rand2].referenced == referenced && table[rand1][rand2].row != exceptrow && table[rand1][rand2].col != exceptcol) return &table[rand1][rand2];
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
        other = getCell(1, cell->col, false, -1, -1);
        if(!other) return;
    } else if(cell->row == 4) {
        other = getCell(3, cell->col, false, -1, -1);
        if(!other) return;
    } else {
        if(qrand()%2) {
            other = getCell(cell->row + 1, cell->col, false, -1, -1);
            if(!other) other = getCell(cell->row - 1, cell->col, false, -1, -1);
            if(!other) return;
        } else {
            other = getCell(cell->row - 1, cell->col, false, -1, -1);
            if(!other) other = getCell(cell->row + 1, cell->col, false, -1, -1);
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

    if(cell->col == 0) {
        other = getCell(-1, 1, false, cell->row, -1);
        if(!other) return;
    } else if(cell->col == 4) {
        other = getCell(-1, 3, false, cell->row, -1);
        if(!other) return;
    } else {
        if(qrand()%2) {
            other = getCell(-1, cell->col + 1, false, cell->row, -1);
            if(!other) other = getCell(-1, cell->col - 1, false, cell->row, -1);
            if(!other) return;
        } else {
            other = getCell(-1, cell->col - 1, false, cell->row, -1);
            if(!other) other = getCell(-1, cell->col + 1, false, cell->row, -1);
            if(!other) return;
        }
    }

    //fa sì che siano referenced
    this->reference(cell);
    this->reference(other);
    //genera la risposta
    this->clues->append(cell->answer + " è" + (other->col > cell->col ? " a sinistra di " : " a destra di ") + other->answer);
}
void Table::generateNearClue(TableCell *cell) {
    TableCell *other;

    if(cell->row == 0) {
        other = getCell(1, cell->col, false, -1, -1);
        if(!other) return;
    } else if(cell->row == 4) {
        other = getCell(3, cell->col, false, -1, -1);
        if(!other) return;
    } else {
        if(qrand()%2) {
            other = getCell(cell->row + 1, cell->col, false, -1, -1);
            if(!other) other = getCell(cell->row - 1, cell->col, false, -1, -1);
            if(!other) return;
        } else {
            other = getCell(cell->row - 1, cell->col, false, -1, -1);
            if(!other) other = getCell(cell->row + 1, cell->col, false, -1, -1);
            if(!other) return;
        }
    }

    this->clues->append("generateBetweenClue");
}
void Table::generateBetweenClue(TableCell *cell) {
    TableCell *other1, *other2;

    if(cell->col == 0 || cell->col == 4) return;
    other1 = getCell(-1, cell->col-1, false, cell->row, -1);
    other2 = getCell(-1, cell->col+1, false, cell->row, -1);

    //fa sì che siano referenced
    this->reference(cell);
    this->reference(other1);
    this->reference(other2);
    //genera la risposta
    this->clues->append(cell->answer + " è tra " + other1->answer + " e " + other2->answer);
}

void Table::reference(TableCell *cell) {
    if(!cell->referenced) {
        cell->referenced = true;
        this->referencedCellsCount++;
        this->unreferencedCellsCount--;
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

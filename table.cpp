#include "table.h"


Table::Table(DB *db) {
    this->db = db;

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
    rows[0] = db->cell_items->value("Nazionalita'");
    rows[1] = db->cell_items->value("Colore");
    used << db->cell_items->keys().indexOf("Nazionalita'")
         << db->cell_items->keys().indexOf("Colore");
    for(int i=2; i<5; i++) {
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
            table[i][j].verb = rows[i]->at(rndindex).verb;
            table[i][j].col = j;
            table[i][j].referenced = false;
            table[i][j].deducable = true;

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
}

void Table::generateClues() {

}

TableCell* Table::getRandomUnreferencedCellInRow(int row) {
    row;
    return NULL;
}

TableCell* Table::getRandomReferencedCellInRow(int row) {
    row;
    return NULL;
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

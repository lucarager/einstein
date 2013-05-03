#include "table.h"


Table::Table(DB *db) {
    this->db = db;

qDebug("Generating random table");
    this->generateRandomTableFromDB();
}

Table::~Table() {

}

void Table::generateRandomTableFromDB() {
    //FOR DEBUGGIN INFO
    QMessageBox m;

    //random seed
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    qsrand(date.year() + date.month() + date.day() + time.hour() + time.minute() + time.second());

    //random selection of 5 properties from DB
    QList<TableCell> *rows[5];
    QList<TableCell> finalrows[5];
    QList<int> used;
    int rndindex;

qDebug("selecting 5 properties from DB");
    for(int i=0; i<5; i++) {
        while(used.contains(rndindex = qrand() % db->cell_items->size()));
        used << rndindex;
        rows[i] = db->cell_items->value(db->cell_items->keys().at(rndindex));
    }

qDebug("selecting 5 item for each property");
    //random selection of 5 items for each of 5 selected properties
    for(int i=0; i<5; i++) {
        used.clear();
        for(int j=0; j<5; j++) {
            while(used.contains(rndindex = qrand() % rows[i]->size())) ;
            used << rndindex;
            finalrows[i] << rows[i]->at(rndindex);
            rowstext[i] << rows[i]->at(j).answer;
        }
    }

    //random table construction
    for(int i=0; i<5; i++) {
        used.clear();
        for(int j=0; j<5; j++) {
            while(used.contains(rndindex = qrand() % 5));
            used << rndindex;
            table[i][j].answer = finalrows[i].at(rndindex).answer;
            table[i][j].answertype = finalrows[i].at(rndindex).answertype;
            table[i][j].verb = finalrows[i].at(rndindex).verb;
            table[i][j].col = j;
            table[i][j].referenced = false;
            table[i][j].deducable = true;
            //TODO: in order to init aother cell properties as cell.answertype and cell.verb
            //need to modify parser class and XML structure
        }
    }

    //
    m.setText("visualizing generated matrix");
    m.exec();
    //DEBUG purposes: visualize generated matrix, it's NOT yet used in the UI construction
    QMessageBox box;
    QString msg;
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

bool Table::check(QString **answers) {  //compares user's answers to the right ones
    answers;
    return false;
}

QString** Table::solve() {  //returns array of correct answers (strings)
    return NULL;
}

#include "table.h"


Table::Table(DB *db) {
    this->db = db;

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
    QStringList *fiveprops[5];
    QList<int> used;
    int rndindex;

    for(int i=0; i<5; i++) {
        while(used.contains(rndindex = qrand()%5)) ;
        used << rndindex;
        fiveprops[i] = db->cell_items->value(db->cell_items->keys().at(rndindex));
    }

    for(int i=0; i<5; i++) {
        used.clear();
        for(int j=0; j<5; j++) {
            while(used.contains(rndindex = qrand()%5)) ;
            used << rndindex;
            finalproperties[i] << fiveprops[i]->at(rndindex);
        }
    }


    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            this->table[i][j].answer = finalproperties[i].at(j);
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

QStringList Table::getCellStringList(int row) { //returns strings in order to be able to fill comboboxes
    QStringList dummy;
    return dummy;
}

bool Table::check(QString **answers) {  //compares user's answers to the right ones
    answers;
    return false;
}

QString** Table::solve() {  //returns array of correct answers (strings)
    return NULL;
}

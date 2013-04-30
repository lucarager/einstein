#include "db.h"

DB::DB(QString dbfile, QObject *parent) : QObject(parent) {
    QFile file(dbfile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray buf = file.readAll();
    file.close();

    QXmlStreamReader xml(buf);
    QXmlStreamReader::TokenType token;
    QStringList list;

    while(!xml.atEnd() && !xml.hasError()) {
        token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;
        else if(token == QXmlStreamReader::EndElement && xml.name().toString().contains("prop")) {
            this->properties << list;
            list.clear();
        }
        else if(token == QXmlStreamReader::Characters) {
            if(xml.isCharacters() && !xml.isWhitespace()) list << xml.text().toString();
        }
    }
}

DB::~DB() {

}

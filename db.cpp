#include "db.h"

DB::DB(QString itemsxml, QString guixml) {
    this->parseXML(itemsxml, cell_items);
    this->parseXML(guixml, gui_config);
    qDebug(QString::number(gui_config->size()).toLatin1().data());
}

DB::~DB() {

}

void DB::parseXML(QString xmlfile, QHash<QString, QStringList *>* &h) {
    QFile file(xmlfile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray buf = file.readAll();
    file.close();

    QXmlStreamReader xml(buf);
    QXmlStreamReader::TokenType token;
    QString propname;

    h = new QHash<QString, QStringList*>;

    while(!xml.atEnd() && !xml.hasError()) {
        token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name().toString().contains("prop")) {
            propname = xml.name().toString();
            if(!h->contains(propname)) h->insert(propname, new QStringList);
        }
        else if(token == QXmlStreamReader::Characters && !xml.isWhitespace()) {
            h->value(propname)->append(xml.text().toString());
        }
    }
}

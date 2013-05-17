#include "db.h"

DB::DB(QString itemsxml, QString guixml) {
    this->parseXML(itemsxml, cell_items);
    this->parseXML(guixml, gui_config);
}

DB::~DB() {

}

void DB::parseXML(QString xmlfile, QHash<QString, QList<TableCell> *> *&h) {
    QFile file(xmlfile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray buf = file.readAll();
    file.close();

    QXmlStreamReader xml(buf);
    QXmlStreamReader::TokenType token;
    QString propname, propprefix, propval;
    QXmlStreamAttributes attr;
    TableCell tmp;

    h = new QHash<QString, QList<TableCell>*>;

    while(!xml.atEnd() && !xml.hasError()) {
        token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name().toString().contains("prop")) {
            attr = xml.attributes();
            propname = attr.value("name").toString();
            propprefix = attr.hasAttribute("prefix") ? attr.value("prefix").toString() : "";
            if(!h->contains(propname)) h->insert(propname, new QList<TableCell>);
        }
        else if(token == QXmlStreamReader::Characters && !xml.isWhitespace()) {
            propval = xml.text().toString();
            tmp.answertype = propname;
            tmp.prefix = propprefix;
            tmp.answer = propval;
            h->value(propname)->append(tmp);
        }
    }
}

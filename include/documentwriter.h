/* Chishiki
Copyright (C) 2020 Lianhua Studio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef DOCUMENTWRITER_H
#define DOCUMENTWRITER_H

#include <QPdfWriter>
#include <QPainter>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include "include/character.h"

#define CSK_PPI 300.0
#define CSK_PPM CSK_PPI/25.4

class DocumentWriter
{
    Q_DECLARE_TR_FUNCTIONS(DocumentWriter)

    public:
        DocumentWriter(const QString &filename);
        ~DocumentWriter(void);
        void setCharList(QList<Character>* _charList);
        void setReading(bool param);
        void setWriting(bool param);
        void loadTemplate(const QString _template);
        void generate(void);
        void open(void);
        void close(void);

    private:
        QPdfWriter* pdf;
        QPainter* painter;
        QList<Character>* charList;
        QList<QLine>* outlines;
        QFile* file;
        bool reading;
        bool writing;
        void setTemplate(const QJsonObject &tmpl);
        void setOutlines(const QJsonArray &lines);
        void drawBack(void);
};

#endif // DOCUMENTWRITER_H

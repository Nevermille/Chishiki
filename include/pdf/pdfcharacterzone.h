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

#ifndef PDFCHARACTERZONE_H
#define PDFCHARACTERZONE_H

#include <QRect>
#include <QJsonObject>
#include <QCoreApplication>

class PdfCharacterZone
{
    Q_DECLARE_TR_FUNCTIONS(PdfCharacterZone)

    public:
        PdfCharacterZone();
        void load(const QJsonObject &zone);
        void setRectangle(const QJsonObject &coordinates, QRect &rect);
        QRect getCharZone(void);
        QRect getOnZone(void);
        QRect getKunZone(void);
        QRect getMeaningZone(void);

    private:
        QRect charZone;
        QRect onZone;
        QRect kunZone;
        QRect meaningZone;
};

#endif // PDFCHARACTERZONE_H

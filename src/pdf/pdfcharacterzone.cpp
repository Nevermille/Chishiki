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

#include "include/pdf/pdfcharacterzone.h"
#include "include/pdf/pdfsettings.h"

PdfCharacterZone::PdfCharacterZone(): charZone(), onZone(), kunZone(), meaningZone()
{

}

void PdfCharacterZone::load(const QJsonObject &zone)
{
    if (!zone.contains("char") || !zone.value("char").isObject()
            || !zone.contains("on") || !zone.value("on").isObject()
            || !zone.contains("kun") || !zone.value("kun").isObject()
            || !zone.contains("meaning") || !zone.value("meaning").isObject())
    {
        throw "Char zone corrupted";
    }

    setRectangle(zone.value("char").toObject(), charZone);
    setRectangle(zone.value("on").toObject(), onZone);
    setRectangle(zone.value("kun").toObject(), kunZone);
    setRectangle(zone.value("meaning").toObject(), meaningZone);
}

void PdfCharacterZone::setRectangle(const QJsonObject &coordinates, QRect &rect)
{
    if (!coordinates.contains("x1") || !coordinates.value("x1").isDouble()
            || !coordinates.contains("y1") || !coordinates.value("y1").isDouble()
            || !coordinates.contains("x2") || !coordinates.value("x2").isDouble()
            || !coordinates.contains("y2") || !coordinates.value("y2").isDouble())
    {
        throw "Coordinates corrupted";
    }

    rect.setCoords(coordinates.value("x1").toDouble() * CSK_PPM,
                   coordinates.value("y1").toDouble() * CSK_PPM,
                   coordinates.value("x2").toDouble() * CSK_PPM,
                   coordinates.value("y2").toDouble() * CSK_PPM);
}

QRect PdfCharacterZone::getCharZone()
{
    return charZone;
}

QRect PdfCharacterZone::getOnZone()
{
    return onZone;
}

QRect PdfCharacterZone::getKunZone()
{
    return kunZone;
}

QRect PdfCharacterZone::getMeaningZone()
{
    return meaningZone;
}


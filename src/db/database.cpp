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

#include <QFile>
#include <QJsonDocument>
#include "include/db/database.h"
#include "include/db/path.h"

PdfLayout* Database::getPdfLayout(const QString &name)
{
    PdfLayout* res = new PdfLayout();

    qDebug() << "Load template" << name;
    QFile dbFile(Path::getDbPath("templates"));
    qDebug() << "Opening database file";

    if (!dbFile.open(QIODevice::ReadOnly))
    {
        throw tr("Error opening template database!");
    }

    QJsonDocument rawDb = QJsonDocument::fromJson(dbFile.readAll());

    if (!rawDb.isObject())
    {
        throw tr("Database corrupted!");
    }

    QJsonObject db = rawDb.object();
    qDebug() << "Searching template";

    if (!db.contains(name)) {
        throw tr("Template not found!");
    }

    if (!db.value(name).isObject())
    {
        throw tr("Database corrupted!");
    }

    res->load(db.value(name).toObject());

    qDebug() << "Returning template";
    return res;
}

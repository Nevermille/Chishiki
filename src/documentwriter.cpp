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

#include <QJsonDocument>
#include <QFile>
#include "include/documentwriter.h"
#include "include/path.h"

/**
 * @brief DocumentWriter::DocumentWriter Constructor
 * @param filename Path of the PDF file to write
 */
DocumentWriter::DocumentWriter(const QString &filename)
{
    file = new QFile(filename);
    outlines = new QList<QLine>();
}

/**
 * @brief DocumentWriter::~DocumentWriter Destructor
 */
DocumentWriter::~DocumentWriter(void)
{
    close();
    delete file;
    delete outlines;
}

void DocumentWriter::open(void)
{
    if (!file->open(QIODevice::WriteOnly))
    {
        throw tr("Couldn't open destination file");
    }

    pdf = new QPdfWriter(file);
}

void DocumentWriter::close(void)
{
    delete pdf;
    file->close();
}

/**
 * @brief DocumentWriter::setOutlines Sets the loaded outlines
 * @param lines The loaded outlines
 */
void DocumentWriter::setOutlines(const QJsonArray &lines)
{
    for (const QJsonValue &line : lines)
    {
        if (!line.isObject())
        {
            qDebug() << "Ignored corrupted line";
            continue;
        }

        QJsonObject lineCoordonates = line.toObject();

        if (!(lineCoordonates.contains("x1") && lineCoordonates.value("x1").isDouble())
                || !(lineCoordonates.contains("y1") && lineCoordonates.value("x1").isDouble())
                || !(lineCoordonates.contains("x2") && lineCoordonates.value("x1").isDouble())
                || !(lineCoordonates.contains("y2") && lineCoordonates.value("x1").isDouble()))
        {
            qDebug() << "Ignored corrupted line";
            continue;
        }

        QLine lineObject(lineCoordonates.value("x1").toDouble() * CSK_PPM,
                         lineCoordonates.value("y1").toDouble() * CSK_PPM,
                         lineCoordonates.value("x2").toDouble() * CSK_PPM,
                         lineCoordonates.value("y2").toDouble() * CSK_PPM);

        outlines->append(lineObject);
    }
}

/**
 * @brief DocumentWriter::setTemplate Sets the loaded template
 * @param tmpl The loaded template
 */
void DocumentWriter::setTemplate(const QJsonObject &tmpl)
{
    qDebug() << "Searching outlines";
    if (tmpl.contains("outlines") && tmpl.value("outlines").isArray())
    {
        qDebug() << "Setting outlines";
        setOutlines(tmpl.value("outlines").toArray());
        qDebug() << "Outlines loaded";
    }
}

/**
 * @brief DocumentWriter::loadTemplate Load the selected template
 * @param _template The template name
 */
void DocumentWriter::loadTemplate(const QString _template)
{
    qDebug() << "Load template" << _template;
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

    if (!db.contains(_template)) {
        throw tr("Template not found!");
    }

    if (!db.value(_template).isObject())
    {
        throw tr("Database corrupted!");
    }

    QJsonObject tmpl = db.value(_template).toObject();
    qDebug() << "Setting template";
    setTemplate(tmpl);
    qDebug() << "Template loaded";
}

/**
 * @brief DocumentWriter::generate Generates the PDF file
 */
void DocumentWriter::generate(void)
{
    qDebug() << "Generating PDF";

    pdf->setPageSize(QPageSize(QPageSize::A4));
    pdf->setPageOrientation(QPageLayout::Portrait);
    pdf->setResolution(CSK_PPI);
    pdf->setPageMargins(QMarginsF(0, 0, 0, 0));

    painter = new QPainter(pdf);

    drawBack();

    delete painter;
}

void DocumentWriter::drawBack(void)
{
    qDebug() << "Drawing Background";
    qDebug() << "Drawing Outlines";

    QPen outlinePen;
    outlinePen.setColor(QColor(0,0,0));
    outlinePen.setWidth(0.353 * CSK_PPM);
    outlinePen.setStyle(Qt::PenStyle::SolidLine);
    painter->setPen(outlinePen);

    for (const QLine line : *outlines)
    {
        painter->drawLine(line);
    }
}

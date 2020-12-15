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
#include "include/pdf/documentwriter.h"
#include "include/db/path.h"
#include "include/pdf/pdfsettings.h"
#include "include/db/database.h"

/**
 * @brief DocumentWriter::DocumentWriter Constructor
 * @param filename Path of the PDF file to write
 */
DocumentWriter::DocumentWriter(const QString &filename)
{
    file = new QFile(filename);
}

/**
 * @brief DocumentWriter::~DocumentWriter Destructor
 */
DocumentWriter::~DocumentWriter(void)
{
    close();
    delete file;
    delete layout;
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
 * @brief DocumentWriter::loadTemplate Load the selected template
 * @param _template The template name
 */
void DocumentWriter::loadTemplate(const QString _template)
{
    layout = Database::getPdfLayout(_template);
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

    for (const QLine &line : *layout->getOutlines())
    {
        painter->drawLine(line);
    }
}

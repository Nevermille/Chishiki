#include "include/pdf/pdflayout.h"
#include "include/pdf/pdfsettings.h"
#include <QJsonArray>

PdfLayout::PdfLayout()
{
    outlines = new QList<QLine>;
    charZones = new QList<PdfCharacterZone>;
    staticZones = new QList<QRect>;
}

PdfLayout::~PdfLayout()
{
    delete outlines;
    delete charZones;
    delete staticZones;
}

void PdfLayout::load(const QJsonObject &layout)
{
    qDebug() << "Searching outlines";
    if (layout.contains("outlines") && layout.value("outlines").isArray())
    {
        qDebug() << "Setting outlines";
        setOutlines(layout.value("outlines").toArray());
        qDebug() << "Outlines loaded";
    }
}

QList<QLine> *PdfLayout::getOutlines()
{
    return outlines;
}

/**
 * @brief DocumentWriter::setOutlines Sets the loaded outlines
 * @param lines The loaded outlines
 */
void PdfLayout::setOutlines(const QJsonArray &lines)
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

#ifndef PDFLAYOUT_H
#define PDFLAYOUT_H

#include <QLine>
#include <QRect>
#include <QList>
#include "include/pdf/pdfcharacterzone.h"

class PdfLayout
{
    public:
        PdfLayout();
        ~PdfLayout();
        void load(const QJsonObject &layout);
        QList<QLine>* getOutlines(void);
        QList<PdfCharacterZone>* getCharZones(void);
        int getCharQuantity(void);

    private:
        int charQuantity;
        QList<QLine>* outlines;
        QList<PdfCharacterZone>* charZones;
        QList<QRect>* staticZones;
        void setOutlines(const QJsonArray &lines);
};

#endif // PDFLAYOUT_H

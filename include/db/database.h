#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include "include/pdf/pdflayout.h"

class Database
{
    Q_DECLARE_TR_FUNCTIONS(Database)

    public:
        static PdfLayout* getPdfLayout(const QString &name);
};

#endif // DATABASE_H

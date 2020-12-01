#ifndef CHARACTERTESTRESULT_H
#define CHARACTERTESTRESULT_H

#include <QDateTime>

class CharacterTestResult
{
    public:
        CharacterTestResult();

    private:
        QDateTime date;
        int result;
        int testId;
};

#endif // CHARACTERTESTRESULT_H

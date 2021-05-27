#ifndef CHARSET_H
#define CHARSET_H

#include <QString>

class Charset
{
    private:
        int id;
        QString name;

    public:
        bool operator==(const Charset &other) const;
        bool operator!=(const Charset &other) const;
        bool isNull(void) const;

        Charset(void);

        int getId(void) const;
        void setId(int _id);

        QString getName(void) const;
        void setName(QString _name);
};

#endif // CHARSET_H

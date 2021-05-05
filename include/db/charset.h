#ifndef CHARSET_H
#define CHARSET_H

#include <QString>

class Charset
{
    private:
        int id;
        QString name;

    public:
        bool operator==(const Charset &other);
        bool operator!=(const Charset &other);
        bool isNull(void);

        Charset(void);

        int getId(void);
        void setId(int _id);
        QString getName(void);
        void setName(QString _name);
};

#endif // CHARSET_H

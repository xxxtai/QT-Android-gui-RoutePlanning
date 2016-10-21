#ifndef CONTENT_H
#define CONTENT_H
#include <QString>

class Content
{
public:
    Content();
    ~Content();
    void setContent(QString& ads, QString& num);
private:
public:
    QString m_address;
    QString m_phoneNum;
};
#endif // CONTENT_H

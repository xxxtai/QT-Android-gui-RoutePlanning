#ifndef CLICKHANDLER_H
#define CLICKHANDLER_H

#include <QUrl>
#include <QObject>
class ClickHandler : public QObject
{
    Q_OBJECT;
public:
    ClickHandler(QObject* parent);
private slots:
    void on_linkOpen();
    void on_messageBox();
};

#endif // CLICKHANDLER_H

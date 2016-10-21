#ifndef SETGUI_H
#define SETGUI_H

#include <QWidget>
#include <QStackedLayout>
#include "logingui.h"
#include "usergui.h"

class SetGui : public QWidget
{
    Q_OBJECT
public:
    explicit SetGui(QWidget *parent = 0);

signals:

public slots:

private:
    LoginGui* loginGui;
    UserGui* userGui;
    QStackedLayout* stackLayout;
    QVBoxLayout *mainLayout;

};

#endif // SETGUI_H

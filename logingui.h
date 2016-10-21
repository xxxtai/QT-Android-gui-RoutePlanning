#ifndef LOGINGUI_H
#define LOGINGUI_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>

class LoginGui : public QWidget
{
    Q_OBJECT
public:
    explicit LoginGui(QWidget *parent = 0);

signals:
    void display(int number);

public slots:
    void on_loginButton();

};

#endif // LOGINGUI_H

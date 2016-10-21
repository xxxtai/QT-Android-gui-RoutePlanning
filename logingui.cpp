#include "logingui.h"
#include <QPushButton>
#include <QVBoxLayout>


LoginGui::LoginGui(QWidget *parent) :
    QWidget(parent)
{
    QPushButton* loginButton = new QPushButton("Login", this);
    connect(loginButton, SIGNAL(clicked()), this, SLOT(on_loginButton()));
/**********************
    QTableWidget* table = new QTableWidget(2,1);

    table->setItem(0,0, new QTableWidgetItem("huananligong"));
    table->setItem(1, 0, new QTableWidgetItem("tianhe"));


        QVBoxLayout * mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(table);
        setLayout(mainLayout);
        ********************/
}

void LoginGui::on_loginButton()
{
    emit display(1);
}

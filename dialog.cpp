#include "dialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextCodec>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    adsEdit = new QLineEdit;
    numEdit = new QLineEdit;
    QLabel* adsLabel = new QLabel(tr("地址："));
    QLabel* numLabel = new QLabel(tr("电话："));

    QGridLayout* gridLayout = new QGridLayout;
    gridLayout->addWidget(numLabel, 0, 0, 1, 1);
    gridLayout->addWidget(adsLabel, 1, 0, 1, 1);
    gridLayout->addWidget(numEdit, 0, 1, 1, 3);
    gridLayout->addWidget(adsEdit, 1, 1, 1, 3);

    QPushButton* okBtn = new QPushButton(tr("确定"));
    QPushButton* celBtn = new QPushButton(tr("取消"));

    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->setSpacing(60);
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(celBtn);
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setMargin(40);
    mainLayout->addLayout(gridLayout);
    mainLayout->stretch(40);
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);

    connect(okBtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(celBtn, SIGNAL(clicked()), this, SLOT(reject()));
    resize(150,100);
}

Dialog::~Dialog()
{

}

QString Dialog::redAds()
{
    return adsEdit->text();

}

QString Dialog::redNum()
{
    return numEdit->text();
}

#include "setgui.h"


SetGui::SetGui(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(400, 300);
    loginGui = new LoginGui;
    userGui = new UserGui;
    //three = new Three;
    stackLayout = new QStackedLayout;
    stackLayout->addWidget(loginGui);
    stackLayout->addWidget(userGui);
    //stackLayout->addWidget(three);
    connect(loginGui, &LoginGui::display, stackLayout, &QStackedLayout::setCurrentIndex);             // 0
    connect(userGui, &UserGui::display, stackLayout, &QStackedLayout::setCurrentIndex);             // 1
    //connect(three, &Three::display, stackLayout, &QStackedLayout::setCurrentIndex);       // 2

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(stackLayout);
    setLayout(mainLayout);
}

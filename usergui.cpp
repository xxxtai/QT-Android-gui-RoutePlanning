#include "usergui.h"
#include "dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QDialog>
#include <iostream>
#include "qDebug2Logcat.h"
#include <QDebug>
#include <QLineEdit>
#include <QPointer>
#include <QScrollArea>
#include <QSizeGrip>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QTableWidget>
#include <QTableWidgetItem>

using namespace std;

UserGui::UserGui(QWidget *parent)
    : QWidget(parent),countGap(this),m_dis(1),m_i(0),m_j(0)
{
    setupGui();
    connect(&countGap, SIGNAL(deliver_dis(double)), this,SLOT(onDeliver_dis(double)));
    connect(&m_timer,SIGNAL(timeout()), this, SLOT(on_timeOUt()));
    connect(this, SIGNAL(routePlanning_signal()), this, SLOT(on_routePlanning()));

    m_planningSocket = new QTcpSocket(this);
    connect(m_planningSocket, SIGNAL(readyRead()), this, SLOT(on_readPlanning()));
    m_planningSocket->abort();
    m_planningSocket->connectToHost(QHostAddress("119.29.200.140"),8888);

    m_verifySocket = new QTcpSocket(this);
    connect(m_verifySocket, SIGNAL(readyRead()), this, SLOT(on_readVerify()));
    m_verifySocket->abort();
    m_verifySocket->connectToHost(QHostAddress("119.29.243.158"), 8889);


    QString ads, num;
    Content* content_tmp_1 = new Content;
    ads = "广州市天河区五山路381华南理工大学自动化科学与工程学院";
    num = "15918790317";
    content_tmp_1->setContent(ads, num);
    updateContents(content_tmp_1);

    Content* content_tmp_2 = new Content;
    ads = "广东省广州市天河区燕岭路633号";
    num = "15918790317";
    content_tmp_2->setContent(ads, num);
    updateContents(content_tmp_2);

    Content* content_tmp_3 = new Content;
    ads = "广州市天河区珠江东路4号";
    num = "15918790317";
    content_tmp_3->setContent(ads, num);
    updateContents(content_tmp_3);

}

UserGui::~UserGui()
{

}

void UserGui::on_addButton()
{
    QString ads, num, tmp;

    Dialog* inputDialog = new Dialog;

    if(inputDialog->exec() == QDialog::Accepted){
        Content* content_tmp = new Content;
        ads = inputDialog->redAds();
        num = inputDialog->redNum();
        content_tmp->setContent(ads, num);
        updateContents(content_tmp);
    }
    if(inputDialog->exec() == QDialog::Rejected){
        return;
    }
    QListWidgetItem* itemTmp = new QListWidgetItem(m_lists);
    savePlist(itemTmp);
    tmp = num + "\n" + ads;
    itemTmp->setText(tmp);
    qDebug() << "addButton be pressed" << ads;

}

void UserGui::setupGui()
{
    /**************************************************
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    QHBoxLayout * bottomLine = new QHBoxLayout(this);
    m_addButton = new QPushButton("添加", this);
    m_addButton->setGeometry(10,10,200,200);
    m_addButton->setFlat(true);
    m_addButton->resize(200,80);
    m_addButton->setStyleSheet("QPushButton{background-color:white;\
                               color:black; border-radius:300px; border:2px groove black;\
                               border-style:outset}"
                             //  "QPushButton:pressed{background-color:rgb(85,170,255);\
                               border-style:inset}"
                            //   "QPushButton{font-family:'Microsoft YaHei',font-size:21px;color:#666666}");

    bottomLine->addWidget(m_addButton, 0 , Qt::AlignLeft | Qt::AlignBottom);
    m_startButton = new QPushButton("开始", this);
    m_startButton->resize(300,100);

    bottomLine->addWidget(m_startButton, 0, Qt::AlignRight | Qt::AlignBottom);
    mainLayout->addLayout(bottomLine);
    ************************************************/
    m_addButton = new ImageButton(QPixmap(":/new/prefix1/image/button.png"),
                                  QPixmap(":/new/prefix1/image/button.png"),this);
    int w = this->width() / 4;
    m_addButton->setFixedSize(w,55);
    m_startButton = new ImageButton(QPixmap(":/new/prefix1/image/button.png"),
                                    QPixmap(":/new/prefix1/image/button.png"),this);
    m_startButton->setFixedSize(w, 55);
    connect(m_startButton, SIGNAL(clicked()), this, SLOT(on_startButton()));
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    QHBoxLayout * bottomLine = new QHBoxLayout(this);
    bottomLine->setMargin(0);
    mainLayout->setMargin(0);

    bottomLine->addWidget(m_addButton, 0, Qt::AlignBottom | Qt::AlignLeft);
    bottomLine->addWidget(m_startButton, 0, Qt::AlignBottom | Qt::AlignRight);


    //QLabel* addLabel = new QLabel("添加",this);
    //addLabel->setGeometry(w/2-20, this->height()-80, w, 55);
    QFont ft;
    ft.setPointSize(22);
    //addLabel->setFont(ft);
    //addLabel->setStyleSheet("QLabel{font-family:'Microsoft YaHei',font-size:21px;color:#666666}");
    //QLabel* startLabel = new QLabel("开始",this);
    //startLabel->setGeometry(w+57, this->height()-80, w, 55);
    //startLabel->setFont(ft);

    connect(m_addButton, SIGNAL(clicked()), this, SLOT(on_addButton()));

    m_lists=new QListWidget;
    m_lists->setSpacing(10);
    QHBoxLayout* lay=new QHBoxLayout;
    QScrollArea* scr=new QScrollArea;
    scr->setWidget(m_lists);
    scr->setAlignment(Qt::AlignLeft);
    scr->setBackgroundRole(QPalette::Dark);// 设置滚动区域的背景

    lay->addWidget(m_lists);
    mainLayout->addLayout(lay);
    mainLayout->addLayout(bottomLine);
    setLayout(mainLayout);
    showMaximized();
}

void UserGui::on_startButton()
{
    m_timer.start(50);
}

void UserGui::on_timeOUt()
{
    if(m_dis != 0 ){
        m_timer.stop();

        if(m_dis != 1){
            QListWidgetItem* itemTmp = new QListWidgetItem(m_lists);
            QString tmp = QString::number(m_dis);
            itemTmp->setText(tmp);
        }

        m_dis =0;

        if(m_i < m_contents.size()-1){
            m_j++;
            if(m_j >= m_contents.size()){
                m_i++;
                m_j = m_i + 1;
            }
        }

        if(m_i < m_contents.size()-1){
            m_timer.start(50);
            countGap.countDistance(m_contents[m_i]->m_address, m_contents[m_j]->m_address);
        }else{
            emit routePlanning_signal();
        }
    }
}


void UserGui::on_routePlanning()
{
    QJsonObject jsonObj;
    QJsonArray disArry;
    disArry.insert(0, 80);
    disArry.insert(1, 31);
    disArry.insert(2, 83);
    disArry.insert(3, 82);
    disArry.insert(4, 54);
    disArry.insert(5, 100);
    disArry.insert(6, 53);
    disArry.insert(7, 58);
    disArry.insert(8, 82);
    disArry.insert(9, 26);
    disArry.insert(10, 35);
    disArry.insert(11, 10);
    disArry.insert(12, 20);
    disArry.insert(13, 52);
    disArry.insert(14, 82);
    disArry.insert(15, 86);
    disArry.insert(16, 90);
    disArry.insert(17, 75);
    disArry.insert(18, 14);
    disArry.insert(19, 29);
    disArry.insert(20, 41);
    disArry.insert(21, 34);
    disArry.insert(22, 60);
    disArry.insert(23, 28);
    disArry.insert(24, 51);
    disArry.insert(25, 44);
    disArry.insert(26, 66);
    disArry.insert(27, 8);
    jsonObj.insert("distance", disArry);

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);
    m_planningSocket->write(json_str.toStdString().c_str(),strlen(json_str.toStdString().c_str()));

    QJsonObject phpJson;
    QJsonArray dataArray;
    QJsonObject dataObj;
    dataObj.insert("phoneNumber", 15918790317);
    dataObj.insert("address", "华南理工大学3号楼");
    QJsonObject dataObj1;
    dataObj1.insert("phoneNumber", 15918790317);
    dataObj1.insert("address", "华南理工大学3号楼204");
    QJsonObject dataObj2;
    dataObj2.insert("phoneNumber", 15918790317);
    dataObj2.insert("address", "华南理工大学3号楼302");
    dataArray.insert(0,dataObj);
    dataArray.insert(1, dataObj1);
    dataArray.insert(2, dataObj2);
    phpJson.insert("data", dataArray);
    phpJson.insert("passWord", "2121212");
    phpJson.insert("userName", "abc");
    phpJson.insert("id", 12345678);
    phpJson.insert("flag", 0);

    QJsonDocument phpDocument;
    phpDocument.setObject(phpJson);
    QByteArray byte = phpDocument.toJson(QJsonDocument::Compact);

    QString json_strs(byte);
    m_verifySocket->write(json_strs.toStdString().c_str(),strlen(json_strs.toStdString().c_str()));
}

void UserGui::on_readPlanning()
{
    QByteArray bety_array = m_planningSocket->readAll();
    int point_array[14];
    QString tmp;
    QString total = "";
    QJsonParseError err;
    QJsonDocument json = QJsonDocument::fromJson(bety_array, &err);
    if(err.error == QJsonParseError::NoError)
    {
        QJsonObject json_obj = json.object();
        QJsonValue order = json_obj.take("order");
        QJsonArray order_array = order.toArray();
        int size = order_array.size();
        for(int i = 0; i < size; ++i){
            point_array[i] = order_array.at(i).toInt();
            tmp = QString::number(point_array[i]);
            total += tmp;
        }
    }

    QListWidgetItem* itemTmp = new QListWidgetItem(m_lists);
    itemTmp->setText(total);
    //QString ss=QVariant(qba).toString();
    qDebug()<< "total:" << total << endl;
}

void UserGui::on_readVerify()
{
    QByteArray bety_array = m_verifySocket->readAll();
    QString str(bety_array);
    qDebug()<<"phphhphhphhp:" << str;
}

//void UserGui::paintEvent(QPaintEvent *e)
//{

//}



void UserGui::updateContents(Content* ct)
{
    m_contents.push_back(ct);

}

void UserGui::savePlist(QListWidgetItem* ql)
{
    m_plist.push_back(ql);
}

void UserGui::onDeliver_dis(double dis)
{
    m_dis = dis;
}

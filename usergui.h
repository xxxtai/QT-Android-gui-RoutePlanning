#ifndef USERGUI_H
#define USERGUI_H

#include <QWidget>
#include <QPaintEvent>
#include "imageButton.h"
#include <QPushButton>
#include <QList>
#include <QScopedPointer>
#include "content.h"
#include <QListWidget>
#include <QTimer>
#include <QtNetwork>
#include "countlnglat.h"

class UserGui : public QWidget
{
    Q_OBJECT

public:
    UserGui(QWidget *parent = 0);
    ~UserGui();
    void updateContents(Content* ct);
    void savePlist(QListWidgetItem* ql);
signals:
    void routePlanning_signal();
    void display(int number);
protected:
    //void paintEvent(QPaintEvent *e);
protected slots:
    void on_startButton();
    void on_addButton();
    void onDeliver_dis(double dis);
    void on_timeOUt();
    void on_routePlanning();
    void on_readPlanning();
    void on_readVerify();
private:
    void setupGui();
private:
    QList<Content*> m_contents;
    QList<QListWidgetItem*> m_plist;
    ImageButton* m_addButton;
    ImageButton* m_startButton;
    QListWidget* m_lists;
    QTcpSocket* m_planningSocket;
    QTcpSocket* m_verifySocket;
    CountLngLat countGap;
    double m_dis;
    QTimer m_timer;
    int m_i;
    int m_j;
};

#endif

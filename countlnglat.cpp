#include "countlnglat.h"
#include "qDebug2Logcat.h"
#include <QDebug>

CountLngLat::CountLngLat(QWidget *parent)
    : QWidget(parent),m_ipQuery_1(this),m_ipQuery_2(this)
    ,m_ipQuery_dis(this),m_lng_1(0),m_lat_1(0),m_lng_2(0),m_lat_2(0)
{
    connect(&m_ipQuery_1, SIGNAL(finished(bool,bool,double,double))
            ,this, SLOT(onQueryFinished(bool,bool,double,double)));
    connect(&m_ipQuery_2, SIGNAL(finished(bool,bool,double,double))
            ,this, SLOT(onQueryFinished(bool,bool,double,double)));
    connect(&m_ipQuery_dis, SIGNAL(finished_dis(double))
            ,this, SLOT(onQueryFinished_dis(double)));

    connect(&timer,SIGNAL(timeout()),this, SLOT(onTimeout()));
}

CountLngLat::~CountLngLat()
{
}

void CountLngLat::onQueryFinished(bool bOK, bool sec, double lng_dou, double lat_dou)
{
       if(bOK && sec == false)
       {
           m_lng_1 = lng_dou;
           m_lat_1 = lat_dou;
       }
       else if(bOK && sec == true)
       {
           m_lng_2 = lng_dou;
           m_lat_2 = lat_dou;
       }
}

void CountLngLat::onQueryFinished_dis( double distance)
{
    emit deliver_dis(distance);
}

void CountLngLat::onTimeout()
{
    if(m_lng_1 != 0 && m_lat_1 != 0 && m_lng_2 != 0 && m_lat_1 != 0 )
    {
        m_ipQuery_dis.query_dis(m_lng_1, m_lat_1, m_lng_2, m_lat_2);
        timer.stop();
        m_lng_1 = 0;
        m_lat_1 = 0;
        m_lng_2 = 0;
        m_lat_2 = 0;
    }
}

void CountLngLat::countDistance(QString ads_1, QString ads_2)
{
    m_ipQuery_1.query(false, ads_1);
    m_ipQuery_2.query(true, ads_2);
    timer.start(40);
}

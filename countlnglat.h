#ifndef COUNTLNGLAT_H
#define COUNTLNGLAT_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include "ipQuery.h"


class CountLngLat : public QWidget
{
    Q_OBJECT

public:
    CountLngLat(QWidget *parent = 0);
    ~CountLngLat();
    void countDistance(QString ads_1, QString ads_2);

signals:
    void deliver_dis(double dis);

protected slots:
    void onQueryFinished(bool bOK, bool sec, double lng_str, double lat_str);
    void onQueryFinished_dis( double distance);
    void onTimeout();

protected:
    IpQuery m_ipQuery_1;
    IpQuery m_ipQuery_2;
    IpQuery m_ipQuery_dis;
    QTimer timer;

private:
    double m_lng_1;
    double m_lat_1;
    double m_lng_2;
    double m_lat_2;

};

#endif // WIDGET_H

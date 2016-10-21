#ifndef IPQUERY_H
#define IPQUERY_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class IpQuery : public QObject
{
    Q_OBJECT
public:
    IpQuery(QObject *parent = 0);
    ~IpQuery();

    void query(bool sec, QString ads);
    void query_dis(double lng_1, double lat_1, double lng_2, double lat_2);

signals:
    void finished(bool bOK, bool sec, double ip, double area);
    void finished_dis(double distance);

protected slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager m_nam;
    double m1_lng;
    double m1_lat;
    double m2_lng;
    double m2_lat;
    double m_emptyString;
    bool m_sec;
    QString flag;
};

#endif // IPQUERY_H

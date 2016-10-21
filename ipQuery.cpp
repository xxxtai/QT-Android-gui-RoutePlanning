#include "ipQuery.h"
#include <QJsonDocument>
#include <QByteArray>
#include <QJsonArray>
#include <QHostAddress>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QTextCodec>
#include <QDebug>

IpQuery::IpQuery(QObject *parent)
    : QObject(parent), m_nam(this)
{
    connect(&m_nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(onReplyFinished(QNetworkReply*)));
}

IpQuery::~IpQuery()
{

}

void IpQuery::query(bool sec, QString ads)
{
    QString strUrl = QString("http://apis.map.qq.com/ws/geocoder/v1/?address=%1%2")
            .arg(ads).arg("&key=2WCBZ-ZOPHG-PF3Q7-IJSVA-Q72UO-HCBBN");
    QUrl url(strUrl);
    QNetworkRequest req(url);
    req.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
    req.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.114 Safari/537.36");
    m_nam.get(req);
    m_sec = sec;
    flag = "lng_lat";
}

void IpQuery::query_dis(double lng_1, double lat_1, double lng_2, double lat_2)
{
    QString strUrl = QString("http://apis.map.qq.com/ws/distance/v1/?mode=walking&from=%1,%2&to=%3,%4&key=%5")
            .arg(lat_1).arg(lng_1).arg(lat_2).arg(lng_2).arg("2WCBZ-ZOPHG-PF3Q7-IJSVA-Q72UO-HCBBN");
    QUrl url(strUrl);
    QNetworkRequest req(url);
    req.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
    req.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.114 Safari/537.36");
    m_nam.get(req);
    flag = "distance";

}

void IpQuery::onReplyFinished(QNetworkReply *reply)
{
    reply->deleteLater();
    double strIp = 0.0;
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "IpQuery, error - " << reply->errorString();
        emit finished(false, m_sec, strIp, m_emptyString);
        return;
    }

    int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if(status != 200)
    {
        emit finished(false, m_sec, strIp, m_emptyString);
        return;
    }

    QByteArray data = reply->readAll();
    QString contentType = reply->header(QNetworkRequest::ContentTypeHeader).toString();

    int charsetIndex = contentType.indexOf("charset=");
    if(charsetIndex > 0)
    {
        charsetIndex += 8;
        QString charset = contentType.mid(charsetIndex).trimmed().toLower();
        if(charset.startsWith("gbk") || charset.startsWith("gb2312"))
        {
            QTextCodec *codec = QTextCodec::codecForName("GBK");
            if(codec)
            {
                data = codec->toUnicode(data).toUtf8();
            }
        }
    }

    int parenthesisLeft = data.indexOf('(');
    int parenthesisRight = data.lastIndexOf(')');
    if(parenthesisLeft >=0 && parenthesisRight >=0)
    {
        parenthesisLeft++;
        data = data.mid(parenthesisLeft, parenthesisRight - parenthesisLeft);
    }
    QJsonParseError err;
    QJsonDocument json = QJsonDocument::fromJson(data, &err);
    if(err.error != QJsonParseError::NoError)
    {
        qDebug() << "IpQuery, json error - " << err.errorString();
        emit finished(false, m_sec, strIp, m_emptyString);
        return;
    }

    if(flag == "lng_lat")
    {
        QJsonObject obj = json.object();
        QJsonValue res_val = obj.take("result");
        QJsonObject res_obj = res_val.toObject();
        QJsonValue loc_val = res_obj.take("location");
        QJsonObject loc_obj = loc_val.toObject();
        QJsonValue lat_val = loc_obj.take("lat");
        long double lat_dou = lat_val.toDouble(100);
        QJsonValue lng_val = loc_obj.take("lng");
        long double lng_dou = lng_val.toDouble(100);
        emit finished(true, m_sec, lng_dou, lat_dou);
    }
    if(flag == "distance")
    {
        QJsonObject obj_dis = json.object();
        QJsonValue res_val_dis = obj_dis.take("result");
        QJsonObject res_obj_dis = res_val_dis.toObject();
        QJsonObject::const_iterator it = res_obj_dis.find("elements");
        if(it != res_obj_dis.constEnd())
        {
            QJsonArray ele_arr = it.value().toArray();
            QJsonObject ele_obj = ele_arr.first().toObject();
            double distance = ele_obj.find("distance").value().toDouble();
            emit finished_dis(distance);
            //qDebug()<< "realy distance!!!!!!!!!!!!!" << distance;
        }
    }
}

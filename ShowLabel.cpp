
#include <QDesktopServices>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "showlabel.h"
#include "cscrollscreenview.h"
#include "qDebug2Logcat.h"
#include <QDebug>
//#include "clickhandler.h"
ShowLabel::ShowLabel(const QString &string)
: m_isPressed(false), m_isUnderLine(false)
{
    m_text = string;
    //setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    //setAcceptHoverEvents(true);
}
void ShowLabel::setText(const QString &string)
{
    if ( m_text != string)
    {
        m_text = string;
        update();
    }

}
void ShowLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    //setUnderline(m_isUnderLine);
    painter->setFont(m_font);
    painter->setPen(m_penstyle);
    //QRect textRect = boundingRect().toRect();
    //painter->fillRect(0,0,303,50, (, 255, 255));
    //painter->fillRect();


    QRect textRect(0, 0, 320, 50);
    painter->drawText(textRect, Qt::AlignLeft, m_text);
    QPen pen;
    pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->drawLine(textRect.bottomLeft(), textRect.bottomRight());
}
void ShowLabel::setFont(const QFont& ft)
{
    m_font = ft;
}
void ShowLabel::setColor(const QColor& color)
{
    m_penstyle = color;
}
void ShowLabel::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_isPressed = true;
        setCursor(Qt::ArrowCursor);
    }

    qDebug() << "showlabel mouse be press" << endl;
}
void ShowLabel::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    if (e->button() == Qt::LeftButton && m_isPressed )
    {
        emit clicked();
        setCursor(Qt::PointingHandCursor);
        m_isPressed = false;
    }
    qDebug() << "showlabel mouse is release" << endl;
}
void ShowLabel::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    setCursor(Qt::PointingHandCursor);
}
void ShowLabel::hoverLeaveEvent()
{
    setCursor(Qt::ArrowCursor);
}
QRectF ShowLabel::boundingRect()
{
    QFontMetrics metrics(m_font);
    qreal width = metrics.width(m_text);
    qreal height = metrics.height();
    return QRectF(0,0,width,height);
}
void ShowLabel::setUnderline( bool isUnderLine )
{
    m_isUnderLine = isUnderLine;
    m_font.setUnderline(true);
}
QRect ShowLabel::getRect()
{
    return boundingRect().toRect();
}
QString ShowLabel::text()
{
    return m_text;
}


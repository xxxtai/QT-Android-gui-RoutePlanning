#pragma once
#ifndef SHOWLABEL_H
#define SHOWLABEL_H
#include <QGraphicsWidget>
class QGraphicsSceneMouseEvent;
class QGraphicsSceneHoverEvent;
class ShowLabel: public QGraphicsWidget
{
    Q_OBJECT
public:
    ShowLabel(const QString &string);
    void setText(const QString &string);
    QString text();
    void setFont(const QFont& font);
    void setColor(const QColor& color);
    void setUnderline(bool isUnderLine);
    QRect getRect();
signals:
    void clicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *e);
    void hoverLeaveEvent();
protected:
    virtual QRectF boundingRect();
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
private:
    QString m_text;
    bool m_isPressed;
    bool m_isUnderLine;
    bool m_isNotFilter;
    QFont m_font;
    QColor m_penstyle;
};
#endif //SHOWLABEL_Hsho

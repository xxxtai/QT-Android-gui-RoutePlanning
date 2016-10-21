#include "cscrollscreenview.h"
#include <QGraphicsWidget>
#include <QPropertyAnimation>
#include <QGraphicsLinearLayout>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include "qDebug2Logcat.h"
#include <QEvent>
#include <QTouchEvent>
#include <QDebug>

CScrollScreenView::CScrollScreenView(QGraphicsScene *pScene, QWidget *parent, QSize sc_size)
    :QGraphicsView(pScene, parent),m_screenSize()

{
    m_pScene = pScene;
    //m_pScene->setSceneRect(0,0,200,200);

    m_screenSize = sc_size;

    m_pForm = new QGraphicsWidget();
//m_pForm->setGeometry(0,0,m_screenSize.width(), m_screenSize.height());
    m_pParent = parent;
    QPointF item_init = m_pForm->pos();
    qDebug()<< "item_init = " << item_init.x() <<"|"<<item_init.y()<<endl;
    m_f_PressMouse = false;

    m_filterRelease = false;

    m_stopDownScroll = true;

    m_ScrollStartPos = QPoint(0, 0);

    m_AnimationDuration = 200;

    m_ScrollDist = 30;

    setBackgroundBrush(QBrush(QColor(255,255,255)));


    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAcceptDrops(true);
    m_pForm->setAcceptTouchEvents(true);

}

void CScrollScreenView::SetLayout(QGraphicsLinearLayout *pLayout)

{
    m_pForm->setLayout(pLayout);
    m_pScene->addItem(m_pForm);

    QPushButton* pushButton1 = new QPushButton("pushbutton1");
    QPushButton* pushButton2 = new QPushButton("pushbutton2");
    pushButton1->setFixedHeight(50);
    pushButton1->setFixedWidth(m_screenSize.width()/2);
    pushButton2->setFixedHeight(50);
    pushButton2->setFixedWidth(m_screenSize.width()/2);
    //pushButton1->setDefault(false);
    QWidget* widget = new QWidget;
    widget->setGeometry(0,m_screenSize.height()-60,m_screenSize.width()+20,50);
    widget->setWindowFlags(Qt::FramelessWindowHint);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(200,200,200));//0x00,0xff,0x00,0x00
    widget->setPalette(pal);
    //widget->setAttribute(Qt::WA_AcceptTouchEvents);
    QHBoxLayout* horiLayout = new QHBoxLayout;
    horiLayout->addWidget(pushButton1, 0, Qt::AlignLeft | Qt::AlignBottom);
    horiLayout->addWidget(pushButton2, 0, Qt::AlignRight | Qt::AlignBottom);
    widget->setLayout(horiLayout);
    m_pScene->addWidget(widget);


    pLayout->updateGeometry();

    qreal left = 0, top = 0, right = 0, bottom = 0;

    m_pForm->getContentsMargins(&left, &top, &right, &bottom );

    //printf("l=%f,t=%f,r=%f,b=%f/n", left,top,right,bottom);

    //printf("w=%f,h=%f/n", m_pForm->size().width(),m_pForm->size().height());

}

void CScrollScreenView::AnimationForm(bool UpScroll, int dist)
{

    if(!UpScroll && (!m_stopDownScroll))

    {

        QPropertyAnimation *animation = new QPropertyAnimation(m_pForm, "pos");

        animation->setDuration(m_AnimationDuration);

        animation->setStartValue(m_item_pos);

        m_item_pos.setY(m_item_pos.y() + dist);

        animation->setEndValue(m_item_pos);

        animation->setEasingCurve(QEasingCurve::Linear);
        if(m_item_pos.y() + dist < 0)
            animation->start();
        else{
            animation->setEndValue(m_ScrollStartPos);
            animation->start();
        }


    }

    else if(UpScroll)

    {

        QPropertyAnimation *animation = new QPropertyAnimation(m_pForm, "pos");

        animation->setDuration(m_AnimationDuration);

        animation->setStartValue(m_item_pos);

        m_item_pos.setY(m_item_pos.y() - dist);

        animation->setEndValue(m_item_pos);

        animation->setEasingCurve(QEasingCurve::Linear);

        animation->start();
        m_stopDownScroll = false;
    }


}

void CScrollScreenView::mousePressEvent(QMouseEvent *event)

{

    QGraphicsView::mousePressEvent(event);

    m_f_PressMouse = true;

    m_StartDragPos = event->pos();
    qDebug() << "mouse be pressed:" <<"x = " << m_StartDragPos.x() << ",y = " << m_StartDragPos.y() << endl;

}

void CScrollScreenView::mouseReleaseEvent(QMouseEvent *event)

{
    event->accept();
    QGraphicsView::mouseReleaseEvent(event);

    m_f_PressMouse = false;
    //qDebug()<< "mouse is released" << endl;

}

void CScrollScreenView::mouseMoveEvent(QMouseEvent *event)
{
    if(m_StartDragPos.y() != 0 &&m_StartDragPos.x() != 0){

    QPoint end_pos = event->pos();
    int deviator = qAbs(end_pos.y() - m_StartDragPos.y());

    QGraphicsView::mouseMoveEvent(event);
    qDebug()<< "deviator" << deviator << endl;
    if(m_f_PressMouse)

    {
        if(deviator > 3)

        {
            m_ScrollDist = deviator * 6;
            m_filterRelease = true;
            //qDebug()<< "m_filterRelease" << m_filterRelease << endl;
            if(end_pos.y() < m_StartDragPos.y())

            {

                AnimationForm(true, m_ScrollDist);

            }

            else if(end_pos.y() > m_StartDragPos.y())

            {

                AnimationForm(false, m_ScrollDist);

            }

        }
        m_StartDragPos = event->pos();

    }
  }
    //qDebug()<< "mouse moveeeeeeeeeeeeeee" << end_pos.y() << endl;

}


bool CScrollScreenView::eventFilter(QObject *obj, QEvent *event)
{
    QEvent::Type t = event->type();

    if(t == QEvent::GraphicsSceneMouseRelease && m_filterRelease == true){
        qDebug() << "release acceptttttttttt" << endl;
        event->accept();
        m_filterRelease = false;
        return true;
    }

    m_item_pos = m_pForm->pos();
    qDebug()<< "item_pos = " << m_item_pos.x() <<"|"<<m_item_pos.y()<<endl;
    if(m_item_pos.y() >= 0){
        m_ScrollStartPos = QPoint(0, 0);
        m_stopDownScroll = true;

    }


    return QWidget::eventFilter(obj, event);
}


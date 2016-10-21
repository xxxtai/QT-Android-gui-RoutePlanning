#ifndef CSCROLLSCREENVIEW_H
#define CSCROLLSCREENVIEW_H

#include <QGraphicsView>
#include <QGraphicsLinearLayout>

class CScrollScreenView : public QGraphicsView

{
    Q_OBJECT
public:
    CScrollScreenView(QGraphicsScene *pScene, QWidget *parent, QSize sc_size);
    //设置试图的布局
    virtual void SetLayout(QGraphicsLinearLayout *pLayout);

    //bool event(QEvent *);
    //设置滚动完成的时间，单位：ms
    void SetAnimationDuration(int msecs)
    {
        m_AnimationDuration = msecs;
    }
    //设置滚动的距离，单位：像素
    void SetScrollDist(int dist)
    {
        m_ScrollDist = dist;
    }
    //在父窗体上按场景位置显示试图
    virtual void ShowView()
    {
        this->show();
    }
private:
    int m_AnimationDuration;    //屏幕滚动动画控件
    int m_ScrollDist;           //屏幕滚动的距离
    //void dumpTouchEvent(QEvent *e);

signals:


protected:
    void resizeEvent(QResizeEvent *event)
    {
        QGraphicsView::resizeEvent(event);
        fitInView(sceneRect(), Qt::KeepAspectRatio);
    }
    //功能：滚动m_pForm指向的视图窗口
    //参数：LeftScroll为true则是向左滚动，否则是向右滚动；dist是滚动的距离
    virtual void AnimationForm(bool LeftScroll, int dist);
    bool eventFilter(QObject *obj, QEvent *event);
    //void paintEvent(QPaintEvent *e);
    QWidget *m_pParent;
    bool m_f_PressMouse;
    bool m_filterRelease;
    bool m_stopDownScroll;
    QPoint m_StartDragPos;
    QPoint m_ScrollStartPos;
    QGraphicsWidget *m_pForm;
    QGraphicsScene *m_pScene;
    QSize m_screenSize;
    QPointF m_item_pos;
protected slots:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
};

#endif // CSCROLLSCREENVIEW_H

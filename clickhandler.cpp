#include <QDesktopServices>
#include <QMessageBox>
#include "showlabel.h"
#include "clickhandler.h"
void ClickHandler::on_linkOpen()
{
    /********
    ShowLabel* label = qobject_cast<ShowLabel*>(sender());
    QString text = label->text();

    QDesktopServices::openUrl(text);
    **********/

    ShowLabel* label = qobject_cast<ShowLabel*>(sender());
    QString text = label->text();
    QMessageBox::about(NULL, "msg box", text);

}
void ClickHandler::on_messageBox()
{
    ShowLabel* label = qobject_cast<ShowLabel*>(sender());
    QString text = label->text();
    QMessageBox::about(NULL, "msg box", text);
}
ClickHandler::ClickHandler( QObject* parent )
: QObject(parent)
{
}

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QString redAds();
    QString redNum();
private:
    QLineEdit* adsEdit;
    QLineEdit* numEdit;
};

#endif // DIALOG_H

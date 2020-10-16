#ifndef PROJUSERITEMWDT_H
#define PROJUSERITEMWDT_H

#include <QWidget>
#include <QJsonObject>

namespace Ui {
class ProjUserItemWdt;
}

class ProjUserItemWdt : public QWidget
{
    Q_OBJECT

public:
    explicit ProjUserItemWdt(QJsonObject obj, QWidget *parent = nullptr);
    ~ProjUserItemWdt();

protected:
    void showEvent(QShowEvent *event);

private:
    Ui::ProjUserItemWdt *ui;
    QJsonObject itemObj;
};

#endif // PROJUSERITEMWDT_H

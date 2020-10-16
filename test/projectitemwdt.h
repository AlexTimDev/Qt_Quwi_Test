#ifndef PROJECTITEMWDT_H
#define PROJECTITEMWDT_H

#include <QWidget>
#include <QJsonObject>

namespace Ui {
class ProjectItemWdt;
}

class ProjectItemWdt : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectItemWdt(QJsonObject obj, QWidget *parent = nullptr);
    ~ProjectItemWdt();

signals:
    void onClick(int);

protected:
    void showEvent(QShowEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::ProjectItemWdt *ui;
    QJsonObject itemObj;
};

#endif // PROJECTITEMWDT_H

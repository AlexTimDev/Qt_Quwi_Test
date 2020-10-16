#ifndef PROJECTSWDT_H
#define PROJECTSWDT_H

#include <QWidget>

namespace Ui {
class ProjectsWdt;
}

class ProjectsWdt : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectsWdt(QWidget *parent = nullptr);
    ~ProjectsWdt();

private:
    Ui::ProjectsWdt *ui;
};

#endif // PROJECTSWDT_H

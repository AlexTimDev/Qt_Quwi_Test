#include "projectswdt.h"
#include "ui_projectswdt.h"

ProjectsWdt::ProjectsWdt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectsWdt)
{
    ui->setupUi(this);
}

ProjectsWdt::~ProjectsWdt()
{
    delete ui;
}

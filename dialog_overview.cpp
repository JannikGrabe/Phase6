#include "dialog_overview.h"
#include "ui_dialog_overview.h"
#include "phase6_gui.h"

Dialog_Overview::Dialog_Overview(Phase6_GUI *gui) :
    QDialog(gui),
    ui(new Ui::Dialog_Overview)
{
    ui->setupUi(this);
    this->gui = gui;
}

Dialog_Overview::~Dialog_Overview()
{
    delete ui;
}

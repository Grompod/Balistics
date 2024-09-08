#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Help)
{
  ui->setupUi(this);
  QIcon helpIcon(":/images/img_help.png");
  this->setWindowIcon(helpIcon);
  QPixmap helpPix(":/images/HELP.JPG");

  ui->label->setPixmap(helpPix.scaled(745, 742, Qt::KeepAspectRatio));
}

Help::~Help()
{
  delete ui;
}

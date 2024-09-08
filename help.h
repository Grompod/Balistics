#ifndef HELP_H
#define HELP_H

#include <QDialog>
#include <QPixmap>
#include <QIcon>

namespace Ui {
  class Help;
}

class Help : public QDialog
{
  Q_OBJECT

public:
  explicit Help(QWidget *parent = nullptr);
  ~Help();

private:
  Ui::Help *ui;
};

#endif // HELP_H

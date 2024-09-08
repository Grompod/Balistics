#include "mainwindow.h"
#include "rocket.h"
#include "ui_mainwindow.h"
#include "help.h"

#define UI_X 800
#define UI_Y 600
#define PI 3.14159265


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  QIcon mainIcon(":/images/img_main.png");
  this->setWindowIcon(mainIcon);
  scene = new QGraphicsScene(0, 0, UI_X, UI_Y, this);
  scene->setStickyFocus(true);
  scene->setBackgroundBrush(QBrush(Qt::black));
  ui->graphicsView->setScene(scene);

}

void MainWindow::on_pushButton_Start_clicked()
{
  if (model_flag == 0)
    {
      if ((ui->lineEdit_PlanetMass->text().toDouble() != 0) &&
          (ui->lineEdit_PlanetMass->text() != "") &&
          (ui->lineEdit_Radius->text().toFloat() != 0) &&
          (ui->lineEdit_Radius->text() != "") &&
          (ui->lineEdit_Trust->text().toFloat() != 0) &&
          (ui->lineEdit_Trust->text() != "") &&
          (ui->lineEdit_RocketMass->text().toFloat() != 0) &&
          (ui->lineEdit_RocketMass->text() != "") &&
          (ui->lineEdit_FuelPerSecond->text().toFloat() != 0) &&
          (ui->lineEdit_FuelPerSecond->text() != ""))
        {
          model_flag = 1;
          pic_flag = 2;

          if ((5.97e24 - 5.97e21) < (ui->lineEdit_PlanetMass->text().toDouble()) &&
              (ui->lineEdit_PlanetMass->text().toDouble()) <= (5.97e24 + 5.97e21) &&
              (6371000 - 6371) < (ui->lineEdit_Radius->text().toFloat()) &&
              (ui->lineEdit_Radius->text().toFloat()) <= (6371000 + 6371))
            {
              pic_flag = 0;
            }

          if ((7.35e22 - 7.35e19) < (ui->lineEdit_PlanetMass->text().toDouble()) &&
              (ui->lineEdit_PlanetMass->text().toDouble()) <= (7.35e22 + 7.35e19) &&
              (1737000 - 1737) < (ui->lineEdit_Radius->text().toFloat()) &&
              (ui->lineEdit_Radius->text().toFloat()) <= (1737000 + 1737))
            {
              pic_flag = 1;
            }

          r1 = new Rocket(UI_X/4, (ui->lineEdit_PlanetMass->text().toDouble()),
                          (ui->lineEdit_Radius->text().toFloat()),
                          (ui->lineEdit_Trust->text().toFloat()),
                          (ui->lineEdit_RocketMass->text().toFloat()),
                          (ui->lineEdit_FuelPerSecond->text().toFloat()));

          p1 = new Planet(UI_X/4, pic_flag);

          scene->addItem(p1);
          scene->addItem(r1);
          r1->setDirectInd();

          animationTimer = new QTimer(this);
          connect(animationTimer, SIGNAL(timeout()), scene, SLOT(advance()));
          connect(animationTimer, SIGNAL(timeout()), this, SLOT(status_out()));
          animationTimer->start(1000/60);
        }
      else{
          ui->statusbar->showMessage("Ошибка ввода!");
        }
    }
}

void MainWindow::on_pushButton_Stop_clicked()
{
  if (model_flag == 1)
    {
      scene->removeItem(r1);
      scene->removeItem(r1->ind);
      scene->removeItem(p1);
      while (r1->tracks.size() > 0)
        {
          for (int i = 0; i < r1->tracks.size(); i++)
            {
              scene->removeItem(r1->tracks[i]);
              r1->tracks.remove(i);
              scene->update();
            }
        }
      model_flag = 0;
    }
}

void MainWindow::status_out()
{
  QString out_str = QString("V = %1;   g = %2;   h = %3;   m = %4;  Топливо = %5%;   Ускор. модели: х%6")
      .arg(r1->SpeedOut, 0, 'g', 5)
      .arg(r1->GOut, 0, 'g', 3)
      .arg(r1->HOut)
      .arg(r1->mass)
      .arg((r1->mass - r1->zero_fuel_mass)/(r1->zero_fuel_mass/0.3 - r1->zero_fuel_mass)*100)
      .arg(r1->modelSpeed);
  ui->statusbar->showMessage(out_str);
}

MainWindow::~MainWindow()
{
  delete ui;
}


Planet::Planet(int RAD, int pf) : QGraphicsPixmapItem(0)
{
  if (pf == 0) {
      setPixmap(QPixmap(":/images/Earth_pic.png"));
    }
  if (pf == 1) {
      setPixmap(QPixmap(":/images/Moon_pic.png"));
    }
  if (pf == 2) {
      setPixmap(QPixmap(":/images/CustomPlanet_pic.png"));
    }
  setPos(UI_X/2-RAD, UI_Y/2-RAD);
}


void MainWindow::on_pushButton_Earth_clicked()
{
  ui->lineEdit_Radius->setText("6371000");
  ui->lineEdit_PlanetMass->setText("5.97e24");
}


void MainWindow::on_pushButton_Moon_clicked()
{
  ui->lineEdit_Radius->setText("1737000");
  ui->lineEdit_PlanetMass->setText("7.35e22");
}


void MainWindow::on_pushButton_CustomPlanet_clicked()
{
  ui->lineEdit_Radius->setText("");
  ui->lineEdit_PlanetMass->setText("");
}


void MainWindow::on_pushButton_RocketOne_clicked()
{
  ui->lineEdit_Trust->setText("4e5");
  ui->lineEdit_RocketMass->setText("30000");
  ui->lineEdit_FuelPerSecond->setText("60");
}


void MainWindow::on_pushButton_RocketTwo_clicked()
{
  ui->lineEdit_Trust->setText("4e6");
  ui->lineEdit_RocketMass->setText("280000");
  ui->lineEdit_FuelPerSecond->setText("400");
}


void MainWindow::on_pushButton_CustomRocket_clicked()
{
  ui->lineEdit_Trust->setText("");
  ui->lineEdit_RocketMass->setText("");
  ui->lineEdit_FuelPerSecond->setText("");
}


void MainWindow::on_pushButton_time1_clicked()
{
  r1->xSpeed = r1->xSpeed/r1->modelSpeed;
  r1->ySpeed = r1->ySpeed/r1->modelSpeed;
  r1->modelSpeed = 25;
  r1->xSpeed = r1->xSpeed*r1->modelSpeed;
  r1->ySpeed = r1->ySpeed*r1->modelSpeed;
}


void MainWindow::on_pushButton_time2_clicked()
{
  r1->xSpeed = r1->xSpeed/r1->modelSpeed;
  r1->ySpeed = r1->ySpeed/r1->modelSpeed;
  r1->modelSpeed = 50;
  r1->xSpeed = r1->xSpeed*r1->modelSpeed;
  r1->ySpeed = r1->ySpeed*r1->modelSpeed;
}


void MainWindow::on_pushButton_time3_clicked()
{
  r1->xSpeed = r1->xSpeed/r1->modelSpeed;
  r1->ySpeed = r1->ySpeed/r1->modelSpeed;
  r1->modelSpeed = 200;
  r1->xSpeed = r1->xSpeed*r1->modelSpeed;
  r1->ySpeed = r1->ySpeed*r1->modelSpeed;
}


void MainWindow::on_pushButton_time4_clicked()
{
  r1->xSpeed = r1->xSpeed/r1->modelSpeed;
  r1->ySpeed = r1->ySpeed/r1->modelSpeed;
  r1->modelSpeed = 500;
  r1->xSpeed = r1->xSpeed*r1->modelSpeed;
  r1->ySpeed = r1->ySpeed*r1->modelSpeed;
}



void MainWindow::on_ActionOpenHelp_triggered()
{
  Help HelpWindow;
  HelpWindow.setModal(true);
  HelpWindow.exec();
}


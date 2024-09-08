#include "mainwindow.h"
#include "rocket.h"

#define UI_X 800
#define UI_Y 600
#define PI 3.14159265



DirectInd::DirectInd(int X, int Y, double ind_fi) : QGraphicsPixmapItem(0)
{
  setPixmap(QPixmap(":/images/ind.png"));
  setZValue(2);
  setPos(X, Y);
  setTransformOriginPoint(7.5, 7.5);
  setRotation(ind_fi);
}

Rocket::Rocket(int startY, double PM, float PR, float TR, float M, float FP) : QGraphicsRectItem(0)
{
  QColor color = QColor(255, 0, 0);
  setBrush(color);
  setRect(UI_X/2, UI_Y/2, 0, 0);
  setPos(0, -startY); // Позиционирование старта
  setFlag(QGraphicsItem::ItemIsFocusable);
  setFocus();

  FPS = c_FPS/modelSpeed;
  M_to_pix = PR/startY;
  planetMass = PM;
  planetRadius = startY;
  Trust = TR;
  mass = M;
  zero_fuel_mass = 0.3*mass;
  fuel_per_sec = FP;
}

Track::Track(QPointF initPoint, QGraphicsItem *parent) : QGraphicsEllipseItem(parent)
{
  QColor color = QColor(255, 255, 100);
  setPen(color);
  setBrush(color);
  setRect(0, 0, 2, 2);
  setPos(initPoint);
}


//Расчет скорости и движения

void Rocket::advance(int phase)
{
  if (phase)
    {
      moveBy(xSpeed, ySpeed); //сдвиг ракеты по рсчитаной скорости

      ind->setPos(pos().x()+UI_X/2-7.5, pos().y()+UI_Y/2-7.5);
      ind->setRotation(fi);
    }

  else
    {
      FPS = c_FPS/modelSpeed;

      if (mass-fuel_per_sec/FPS >= zero_fuel_mass && engine == 1)
        {
          AccTrust = Trust/(mass*M_to_pix*pow(FPS, 2));
          mass -= fuel_per_sec/FPS;
        }
      else
        {
          if (mass-fuel_per_sec/FPS < zero_fuel_mass && engine == 1)
            {
              AccTrust = ((mass-zero_fuel_mass)/(mass-fuel_per_sec/FPS))*Trust/(mass*M_to_pix*pow(FPS, 2));
              mass = zero_fuel_mass;
            }
          if (engine == 0)
            {
              AccTrust = 0;
            }
        }
      xAccTrust =  sin(fi*PI/180)*AccTrust;
      yAccTrust = -cos(fi*PI/180)*AccTrust;


      xAccGravity = -(6.67 * 1e-11 * planetMass * (pos().x() - 0)) /
          (pow(distance(pos().x(), pos().y(), 0, 0), 3) * (pow(M_to_pix, 3) * pow(FPS, 2)));

      yAccGravity = -(6.67 * 1e-11 * planetMass * (pos().y() - 0)) /
          (pow(distance(pos().x(), pos().y(), 0, 0), 3) * (pow(M_to_pix, 3) * pow(FPS, 2)));


      //Коллизия планеты
      if (pow(pos().x(), 2)+pow(pos().y(), 2) < pow(planetRadius, 2))
        {

          if (pos().x() > 0)
            {
              if (pos().y() > 0)
                {
                  xSpeed = abs(xAccGravity + xAccTrust);
                  ySpeed = abs(yAccGravity + yAccTrust);
                }
              else
                {
                  xSpeed =  abs(xAccGravity + xAccTrust);
                  ySpeed = -abs(yAccGravity + yAccTrust);
                }
            }
          else
            {
              if (pos().y() > 0)
                {
                  xSpeed = -abs(xAccGravity + xAccTrust);
                  ySpeed =  abs(yAccGravity + yAccTrust);
                }
              else
                {
                  xSpeed = -abs(xAccGravity + xAccTrust);
                  ySpeed = -abs(yAccGravity + yAccTrust);
                }
            }
          HOut = 0;
        }
      else //Коллизия не активна
        {
          track_1 = new Track(mapToScene(QPointF(UI_X/2, UI_Y/2)), 0);
          tracks.push_back(track_1);
          scene()->addItem(track_1);

          xSpeed += (xAccGravity + xAccTrust);
          ySpeed += (yAccGravity + yAccTrust);

          HOut = (distance(pos().x(), pos().y(), 0, 0) - planetRadius)*M_to_pix/1000;
        }


      GOut = sqrt(pow((xAccGravity*M_to_pix*pow(FPS, 2)), 2)
                  + pow((yAccGravity*M_to_pix*pow(FPS, 2)), 2));

      SpeedOut = sqrt(pow((xSpeed*M_to_pix*FPS), 2)
                      + pow((ySpeed*M_to_pix*FPS), 2)) - GOut;
    }
}

//Управление
void Rocket::keyPressEvent(QKeyEvent *event)
{

  if (event->key() == Qt::Key_Left){
      fi -= 15;
    }
  if (event->key() == Qt::Key_Right){
      fi += 15;
    }

  if (event->key() == Qt::Key_Up){
      engine = 1;
    }
  if (event->key() == Qt::Key_Down){
      engine = 0;
    }

  if (event->key() == Qt::Key_1){
      xSpeed = xSpeed/modelSpeed;
      ySpeed = ySpeed/modelSpeed;
      modelSpeed = 25;
      xSpeed = xSpeed*modelSpeed;
      ySpeed = ySpeed*modelSpeed;
    }
  if (event->key() == Qt::Key_2){
      xSpeed = xSpeed/modelSpeed;
      ySpeed = ySpeed/modelSpeed;
      modelSpeed = 50;
      xSpeed = xSpeed*modelSpeed;
      ySpeed = ySpeed*modelSpeed;
    }

  if (event->key() == Qt::Key_3){
      xSpeed = xSpeed/modelSpeed;
      ySpeed = ySpeed/modelSpeed;
      modelSpeed = 200;
      xSpeed = xSpeed*modelSpeed;
      ySpeed = ySpeed*modelSpeed;
    }
  if (event->key() == Qt::Key_4){
      xSpeed = xSpeed/modelSpeed;
      ySpeed = ySpeed/modelSpeed;
      modelSpeed = 500;
      xSpeed = xSpeed*modelSpeed;
      ySpeed = ySpeed*modelSpeed;
    }
}

void Rocket::keyReleaseEvent(QKeyEvent *event)
{

  if (event->key() == Qt::Key_Left){
      fi += 0;
    }
  if (event->key() == Qt::Key_Right){
      fi += 0;
    }
}

void Rocket::setDirectInd()
{
  ind = new DirectInd(UI_X/2, UI_Y/2-planetRadius, fi);
  scene()->addItem(ind);
}



double distance(int x1, int y1, int x2, int y2)
{
  return sqrt(pow((x1-x2), 2) + pow((y1-y2), 2));
};

#ifndef ROCKET_H
#define ROCKET_H

#include <cmath>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>

#include <QKeyEvent>
#include <QPushButton>

#include <QTimer>



class Track : public QGraphicsEllipseItem
{
public:
  Track(QPointF initPoint, QGraphicsItem *parent);
};


class DirectInd : public QGraphicsPixmapItem
{
public:
  DirectInd(int, int, double);
};


class Rocket : public QGraphicsRectItem
{
public:
  Rocket(int, double, float, float, float, float);

public:

  int modelSpeed = 25;
  double xSpeed = 0;
  double ySpeed = 0;
  float HOut;
  double SpeedOut;
  double GOut;
  float mass;
  float zero_fuel_mass;

  virtual void advance(int phase);
  void setDirectInd();
  QList <QGraphicsItem*> tracks;
  Track *track_1;
  QGraphicsPixmapItem *ind;

private:
  double planetMass;
  float planetRadius;
  float c_FPS = 60;
  double FPS;
  double M_to_pix;


  double xAccGravity = 0;
  double yAccGravity = 0;
  double xAccTrust = 0;
  double yAccTrust = 0;
  double AccTrust = 0;
  double fi = 0; // Угол наклона ракеты
  bool engine = 0;

  float Trust;
  float fuel_per_sec;

protected:
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);
};



#endif // ROCKET_H

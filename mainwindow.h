#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <cmath>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QIcon>

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>

#include <QKeyEvent>
#include <QPushButton>

#include <QTimer>
#include "rocket.h"

QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

double distance(int x1, int y1, int x2, int y2);



class Planet : public QGraphicsPixmapItem
{
public:
  Planet(int, int);
};


class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void status_out();

    void on_pushButton_Start_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_Earth_clicked();

    void on_pushButton_Moon_clicked();

    void on_pushButton_CustomPlanet_clicked();

    void on_pushButton_RocketOne_clicked();

    void on_pushButton_RocketTwo_clicked();

    void on_pushButton_CustomRocket_clicked();

    void on_pushButton_time1_clicked();

    void on_pushButton_time2_clicked();

    void on_pushButton_time3_clicked();

    void on_pushButton_time4_clicked();

    void on_ActionOpenHelp_triggered();

private:
    Ui::MainWindow *ui;   
    QTimer *animationTimer;
    QGraphicsScene *scene;
    Rocket *r1;
    Planet *p1;
    bool model_flag = 0;
    int pic_flag = 2;


};

#endif // MAINWINDOW_H

#include <QApplication>
#include "mainwindow.h"
#include "movabledockwidget.h"
#include "main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ItemWidget* w1 = new ItemWidget();
    ItemWidget* w2 = new ItemWidget();

    QWidget* wdg = w1->takeCentralWidget();

    if (wdg) wdg->deleteLater();

    QWidget* wdg2 = w2->takeCentralWidget();

    if (wdg2) wdg2->deleteLater();

    MovableDockWidget* d1 = new MovableDockWidget("Dock A", w1);
    MovableDockWidget* d2 = new MovableDockWidget("Dock B", w1);
    MovableDockWidget* d3 = new MovableDockWidget("Dock С", w1);
    MovableDockWidget* d4 = new MovableDockWidget("Dock D", w1);
    MovableDockWidget* d5 = new MovableDockWidget("Dock E", w1);
    MovableDockWidget* d6 = new MovableDockWidget("Dock F", w1);
//    MovableDockWidget* d7 = new MovableDockWidget("Dock G", w1);
//    MovableDockWidget* d8 = new MovableDockWidget("Dock D", w1);


    w1->AddWidget("First", "First", d1, 0);
    w1->AddWidget("First", "First", d2, 0);
    w1->AddWidget("First", "First", d3, 0);
    w1->AddWidget("First", "First", d4, 0);
    w1->AddWidget("First", "First", d5, 0);
    w1->AddWidget("First", "First", d6, 0);

    QDockWidget* newdock = new QDockWidget("Second", w2);
    //newdock->setFeatures(QDockWidget::DockWidgetFeature::NoDockWidgetFeatures);
    w2->AddWidget("Second", "SECOND", newdock, 0);
    w2->AddWidget("First", "First", d1, 0);

//    w1->addDockWidget(Qt::LeftDockWidgetArea , d1);
//    w1->addDockWidget(Qt::RightDockWidgetArea, d2);
//    w1->addDockWidget(Qt::LeftDockWidgetArea , d3);
//    w1->addDockWidget(Qt::RightDockWidgetArea, d4);
//    w1->addDockWidget(Qt::LeftDockWidgetArea , d6);
//    w1->addDockWidget(Qt::RightDockWidgetArea, d7);
//    w1->addDockWidget(Qt::LeftDockWidgetArea , d8);
//    w1->addDockWidget(Qt::RightDockWidgetArea, d5);

    w1->show();
    w2->show();

//    MainWindow* w2 = new MainWindow();

//    QWidget* wdg2 = w2->takeCentralWidget();

//    if (wdg2){
//        wdg2->deleteLater();
//    }

//    w2->move(650, 100);
//    w2->show();

//    d1->setParent(w2);

    return a.exec();
}

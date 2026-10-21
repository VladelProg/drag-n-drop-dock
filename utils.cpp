#include "utils.h"
#include <QMainWindow>
#include <QDockWidget>
#include "movabledockwidget.h"
#include "mainwindow.h"
#include <QTimer>

void CheckAndCloseEmptyWindow(QWidget* widget) {
    if (!widget) return;
    QMainWindow* win = qobject_cast<QMainWindow*>(widget);
    if (!win) return;

    QList<QDockWidget*> docks = win->findChildren<QDockWidget*>();
    bool hasAttachedDock = false;

    if (MovableDockWidget::s_draggedDock && MovableDockWidget::s_draggedDock->window() == win and !MovableDockWidget::s_draggedDock->isFloating()) return;


        // Проверяем, осталось ли что-то
    for (QDockWidget* dock : docks) {
        if (!dock->isFloating() && dock->isVisible()) {
            hasAttachedDock = true;
            break;
        }
    }

    if (!hasAttachedDock) {
        for (QDockWidget* dock : docks) {
            if (dock->parentWidget() == win) {
                //dock->setFloating(true);
                dock->setParent(nullptr); // Если мы вытащили плавающие виджеты, они отвязываются и все
                //dock->setFloating(true);
                dock->show();
            }
        }

        win->hide();
        ItemWidget::deleteWidget(win);
        win->deleteLater(); // Закрываем
    }
//    if (docks.size() == 1 and hasAttachedDock)
//    {
//        for (QDockWidget* dock : docks) {
//            if (!dock->isFloating() && dock->isVisible()) {

//                dock->setParent(nullptr);
//                dock->show();
//            }
//        }
//        hasAttachedDock = false;

//        win->close();
//    }



//    if (docks.size() == 1 and hasAttachedDock)
//    {
//        MovableDockWidget* dock = MovableDockWidget::s_draggedDock;
//        dock->setParent(nullptr);
//        dock->show();
//        hasAttachedDock = false;
//    }
//
//    dock->setParent(nullptr);
//    dock->show();

    // Если внутри ничего нет, готовимся к закрытию

}


//void CheckAndCloseEmptyWindow(QWidget* widget) {
//    QMainWindow* win = qobject_cast<QMainWindow*>(widget);
//    if (!win) return;

//    QTimer::singleShot(0, [win](){
//        if(!win->isVisible()) return;
//        QList<QDockWidget*> docks = win->findChildren<QDockWidget*>(QString(), Qt::FindDirectChildrenOnly);
//        int attached = 0;

//        for (QDockWidget* dock : docks){
//            if (dock == MovableDockWidget::s_draggedDock) continue;
//            if (dock->isVisible() && !dock->isFloating()){
//                attached++;
//            }

//        }

//        if (attached == 0){
//            for (QDockWidget* dock :docks){
//                if (dock->isVisible() && dock->isFloating()){
//                    dock->setParent(nullptr);
//                }
//            }

//            win->hide();
//            win->deleteLater();
//        }
//    });



////    bool hasAttachedDock = false;

////    // Проверяем, осталось ли что-то внутри окна
////    for (QDockWidget* dock : docks) {
////        if (!dock->isFloating() && dock->isVisible()) {
////            hasAttachedDock = true;
////            break;
////        }
////    }

////    // Если внутри ничего нет, готовимся к закрытию
////    if (!hasAttachedDock) {
////        for (QDockWidget* dock : docks) { // Работаем с плавающими виджетами, которые принадлежат этому окну
////            if (dock->isFloating() and dock != MovableDockWidget::s_draggedDock ) {
////                dock->setParent(nullptr); // Отвязываем от родителя
////                dock->show();
////            }
////            else // если мы перетащили последний док, то при dock->setParent(nullptr); происходит удаление (он и так пропадает)
////            {
////                dock->setParent(nullptr);
////                dock->show();
////                //continue;
////                //qDebug() << "";
////            }
////        }
////        // 4. Закрываем окно
////        win->deleteLater();
////    }
//}

#include "docktitlebar.h"
#include "movabledockwidget.h" // dynamic_cast и s_draggedDock
#include "utils.h"

#include <QApplication>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QCursor>
#include <QTimer>

DockTitleBar::DockTitleBar(const QString& title, QWidget* parent)
    : QLabel(title, parent)
{

}

void DockTitleBar::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        m_dragStartPosition = event->pos();
    }
    QLabel::mousePressEvent(event);
}

void DockTitleBar::mouseMoveEvent(QMouseEvent* event) {
    if (!(event->buttons() & Qt::LeftButton)) return;
    //if ((event->pos() - m_dragStartPosition).manhattanLength() < QApplication::startDragDistance()) return;

    MovableDockWidget* dock = dynamic_cast<MovableDockWidget*>(parentWidget());

    if (!dock) return;

    MovableDockWidget::s_draggedDock = dock;
    QWidget* oldWindow = dock->window();

    //****
//    bool wasFloating = dock->isFloating();
//    if (!wasFloating){
//        dock->setFloating(true);
//        dock->move(QCursor::pos() - QPoint(50, 20));
//    }

    //dock->move(QCursor::pos() - QPoint(50, 20));

    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData();
    mimeData->setData("application/x-dockwidget", QByteArray());
    drag->setMimeData(mimeData);
    drag->setPixmap(this->grab());
    drag->setHotSpot(event->pos());

    Qt::DropAction result = drag->exec(Qt::MoveAction);

    //MovableDockWidget::s_draggedDock = nullptr;

//    if (oldWindow && oldWindow != dock->window()) { // успешно
//        CheckAndCloseEmptyWindow(oldWindow);
//    }

//    MovableDockWidget::s_draggedDock = nullptr;
//    if (oldWindow && oldWindow != dock->window()) { // успешно
//        CheckAndCloseEmptyWindow(oldWindow);
//    }

//    else if (result == Qt::IgnoreAction)
//    {
//        //dock->setParent(nullptr);
//        dock->setFloating(true);
//        //dock->setParent(nullptr);
//        dock->move(QCursor::pos() - QPoint(20, 10));
//        dock->show();
//        if (oldWindow)
//        {
//            CheckAndCloseEmptyWindow(oldWindow);
//        }
//    }

    if (result == Qt::IgnoreAction) { // Логика вытаскивания "в пустоту"
        //dock->hide();
        dock->setParent(nullptr);
        dock->setFloating(true);
        //dock->setParent(nullptr);
        dock->move(QCursor::pos());
        dock->show();
        if (oldWindow && oldWindow != dock)
        {
            QTimer::singleShot(0, oldWindow, [oldWindow](){
                CheckAndCloseEmptyWindow(oldWindow);
            });

        }
    } else {

        if (oldWindow && oldWindow != dock->window()) { // успешно
            QTimer::singleShot(0, oldWindow, [oldWindow](){
                CheckAndCloseEmptyWindow(oldWindow);
            });
        }
    }

    MovableDockWidget::s_draggedDock = nullptr;
}

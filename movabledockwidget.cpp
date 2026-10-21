#include "movabledockwidget.h"
#include "mainwindow.h"
#include "docktitlebar.h"
#include "utils.h"

#include <QLabel>
#include <QDragEnterEvent>
//#include <QRubberBand>
#include <QMainWindow>
#include <QMimeData>

// знаем что взяли
MovableDockWidget* MovableDockWidget::s_draggedDock = nullptr;

MovableDockWidget::MovableDockWidget(const QString& name, QWidget* parent)
    : QDockWidget(name, parent)
{
    DockTitleBar* titleBar = new DockTitleBar(name, this);
    setTitleBarWidget(titleBar);
    setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetClosable);
    setAcceptDrops(true);

    QLabel* content = new QLabel(name, this);
    content->setAlignment(Qt::AlignCenter);
    //content->setStyleSheet("background-color: #f0f0f0; border: 1px solid #ccc; font-size: 14px;");
    setWidget(content);

//    m_rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
//    QPalette pal;
//    pal.setBrush(QPalette::Highlight, QBrush(QColor(0, 255, 120, 100)));
//    m_rubberBand->setPalette(pal);
}

void MovableDockWidget::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasFormat("application/x-dockwidget") && s_draggedDock && s_draggedDock != this) {
        event->acceptProposedAction();
    }
}

void MovableDockWidget::dragMoveEvent(QDragMoveEvent* event) {
    if (s_draggedDock && s_draggedDock != this) {
//        m_rubberBand->setGeometry(rect());
//        m_rubberBand->show();
        event->acceptProposedAction();
    }
}

void MovableDockWidget::dragLeaveEvent(QDragLeaveEvent* event) {
    Q_UNUSED(event);
//    m_rubberBand->hide();
}

void MovableDockWidget::dropEvent(QDropEvent* event) {
//    m_rubberBand->hide();

    if (s_draggedDock && s_draggedDock != this) {
        QMainWindow* targetWin = qobject_cast<QMainWindow*>(this->window());

        // Присоединение к существующему окну (вкладки)
        if (targetWin && !this->isFloating())
        {
            s_draggedDock->hide();
            //if (s_draggedDock->isFloating())
            //s_draggedDock->setParent(nullptr); // Почему эту х//ня так работает
            s_draggedDock->setFloating(false);
            this->setFloating(false);

            targetWin->addDockWidget(Qt::AllDockWidgetAreas, s_draggedDock);
            targetWin->tabifyDockWidget(this, s_draggedDock);

            s_draggedDock->show();
            this->show();
        }

        // Слияние двух плавающих доков (новое окно)
        else {
            //QWidget* oldTargetWin = this->window();

            ItemWidget* newWin = new ItemWidget();
            newWin->setWindowTitle("Merged Window");


            QWidget* wdg = newWin->takeCentralWidget();
            if (wdg) wdg->deleteLater();

            newWin->move(QCursor::pos());

            //*****
            this->hide();
            s_draggedDock->hide();
            //***


            this->setFloating(false);
            s_draggedDock->setFloating(false);


//            if (this->parentWidget()) this->setParent(nullptr);
//            this->setFloating(false);

//            if (s_draggedDock->parentWidget()) s_draggedDock->setParent(nullptr);
//            s_draggedDock->setFloating(false);

            newWin->addDockWidget(Qt::LeftDockWidgetArea, this);
            newWin->addDockWidget(Qt::LeftDockWidgetArea, s_draggedDock);
            newWin->tabifyDockWidget(this, s_draggedDock);

            newWin->show();
            this->show();
            s_draggedDock->show();

            //if (oldTargetWin) CheckAndCloseEmptyWindow(oldTargetWin);
        }

        event->acceptProposedAction();
    }

//    if (s_draggedDock == this ){
//        this->setParent(nullptr);
//        this->show();
//    }

}

#include "mainwindow.h"
#include "movabledockwidget.h" //  s_draggedDock

#include <QLabel>
#include <QDragEnterEvent>
//#include <QRubberBand>
#include <QMimeData>
//#include <QRandomGenerator>

QVector<QMainWindow*> ItemWidget::_windows = {};
QMap<QString, QWidget*> ItemWidget::map = {};


// Это чисто для отслеживания перемещения внутри окна
ItemWidget::ItemWidget(QWidget* parent) : QMainWindow(parent) {
    setAcceptDrops(true);
    setWindowTitle(QString::number(rand() % 100));
    resize(600, 400);
    //setAttribute(Qt::WA_DeleteOnClose);

    QLabel* label = new QLabel("Empty Zone", this);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("color: gray; font-style: italic;");
    setCentralWidget(label);
    _windows.push_back(this);

//    m_rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
//    QPalette pal;
//    pal.setBrush(QPalette::Highlight, QBrush(QColor(0, 120, 255, 100)));
//    m_rubberBand->setPalette(pal);
}

void ItemWidget::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasFormat("application/x-dockwidget") && MovableDockWidget::s_draggedDock) {
        event->acceptProposedAction();
    }
}

QWidget* ItemWidget::GetWidget(QString key)
{
//    Mai
    return map[key];
}


void ItemWidget::AddWidget(QString key, QString header, QDockWidget* dock, int win_id)
{
    //_windows.push_back(this);
    this->addDockWidget(Qt::LeftDockWidgetArea, dock);
    map.insert(key, dock);
}

void ItemWidget::deleteWidget(QMainWindow *window)
{
    for (int i = 0; i < _windows.size(); i++){
        if (_windows[i] == window){
            _windows.removeAt(i);
        }
    }

//    for (auto it = _windows.begin(); it != _windows.end(); it++){
//        if (*it.base() == window){
//            _windows.erase(it);
//        }
//    }
}

void ItemWidget::dragMoveEvent(QDragMoveEvent* event) {
    if (MovableDockWidget::s_draggedDock) {
        QPoint pos = event->pos();
        int w = width();
        int h = height();
        QRect rect;

        if (pos.y() < h * 0.2)      rect = QRect(0, 0, w, h * 0.3);
        else if (pos.y() > h * 0.8) rect = QRect(0, h * 0.7, w, h * 0.3);
        else if (pos.x() > w * 0.6) rect = QRect(w * 0.6, 0, w * 0.4, h);
        else                        rect = QRect(0, 0, w * 0.4, h);

//        m_rubberBand->setGeometry(rect);
//        m_rubberBand->show();

        event->acceptProposedAction();
    }
}

void ItemWidget::dragLeaveEvent(QDragLeaveEvent* event) {
    Q_UNUSED(event);
//    m_rubberBand->hide();
}

// Отпускаем док в другое окно
void ItemWidget::dropEvent(QDropEvent* event) {
//    m_rubberBand->hide();

    MovableDockWidget* dock = MovableDockWidget::s_draggedDock;

    if (!dock) return;

    QPoint pos = event->pos();
    int w = width();
    int h = height();

    Qt::DockWidgetArea area = Qt::LeftDockWidgetArea;
    if (pos.y() < h * 0.2) area = Qt::TopDockWidgetArea;
    else if (pos.y() > h * 0.8) area = Qt::BottomDockWidgetArea;
    else if (pos.x() > w * 0.6) area = Qt::RightDockWidgetArea;
    else area = Qt::LeftDockWidgetArea;

    if (dock->isFloating()) {
        dock->hide();
        dock->setFloating(false);
    }
    addDockWidget(area, dock);
    dock->show();
    event->acceptProposedAction();
}

void ItemWidget::closeEvent(QCloseEvent *event) {


//    QList<QDockWidget*> docks = findChildren<QDockWidget*>();

//    for (QDockWidget* dock : docks){
//        dock->setParent(nullptr);
//        dock->setFloating(true);
//    }

    QMainWindow::closeEvent(event);
//    this->deleteLater();
}

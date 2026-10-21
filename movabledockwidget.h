#ifndef MOVABLEDOCKWIDGET_H
#define MOVABLEDOCKWIDGET_H

#include <QDockWidget>

//class QRubberBand;

class MovableDockWidget : public QDockWidget {
    Q_OBJECT
public:
    explicit MovableDockWidget(const QString& name, QWidget* parent = nullptr);

    // Статическая переменная для хранения перетаскиваемого объекта
    static MovableDockWidget* s_draggedDock;

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dragLeaveEvent(QDragLeaveEvent* event) override;
    void dropEvent(QDropEvent* event) override;

//private:
//    QRubberBand* m_rubberBand;
};

#endif // MOVABLEDOCKWIDGET_H

#ifndef CUSTOMMAINWINDOW_H
#define CUSTOMMAINWINDOW_H

#include <QMainWindow>

//class QRubberBand;

class ItemWidget : public QMainWindow {
    Q_OBJECT
public:
    explicit ItemWidget(QWidget* parent = nullptr);
    QWidget* GetWidget(QString key);
    void AddWidget(QString key, QString header, QDockWidget* dock, int win_id);
    static void deleteWidget(QMainWindow* window);
    static QVector<QMainWindow*> _windows;
    static QMap<QString, QWidget*> map;

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dragLeaveEvent(QDragLeaveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void closeEvent(QCloseEvent *event) override;

//private:
//    QRubberBand* m_rubberBand;
};

#endif // CUSTOMMAINWINDOW_H

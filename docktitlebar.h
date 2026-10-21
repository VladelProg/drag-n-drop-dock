#ifndef DOCKTITLEBAR_H
#define DOCKTITLEBAR_H

#include <QLabel>
#include <QPoint>

class QMouseEvent;

class DockTitleBar : public QLabel {
    Q_OBJECT
public:
    explicit DockTitleBar(const QString& title, QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    QPoint m_dragStartPosition;
};

#endif // DOCKTITLEBAR_H

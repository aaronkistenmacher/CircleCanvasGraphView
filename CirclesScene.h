#ifndef CIRCLESSCENE_H
#define CIRCLESSCENE_H

#include <QGraphicsScene>

class QColorDialog;

class CirclesScene : public QGraphicsScene
{
    Q_OBJECT

public:
    CirclesScene(QObject *parent = nullptr);

public slots:
    void tempSetColorForSelected(const QColor &color);
    void resetColorForSelected();

    // Sets color for selected and sets working color.
    void finalizeColor(const QColor &color);

    void deleteSelected();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    QColor mLastColor;

    qreal mPrevMouseY;
};

#endif // CIRCLESSCENE_H

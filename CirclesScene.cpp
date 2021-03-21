#include "CirclesScene.h"

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QtDebug>

CirclesScene::CirclesScene(QObject *parent)
: QGraphicsScene(parent)
, mLastColor(Qt::green)
{

}

void CirclesScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsItem *item = itemAt(mouseEvent->scenePos(), QTransform());

    if (mouseEvent->buttons() & Qt::RightButton) {
        // Start zoom event
        mPrevMouseY = mouseEvent->scenePos().y();
    }
    else {
        // Allow shift to select multiple in addition to ctrl
        if (item && (mouseEvent->modifiers() & Qt::ShiftModifier)) {
            item->setSelected(!item->isSelected());
        }
        else if (!item) {
            static const qreal radius = 50;

            const qreal x = mouseEvent->scenePos().x();
            const qreal y = mouseEvent->scenePos().y();

            QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(x - radius, y - radius, 2*radius, 2*radius);
            circle->setBrush(mLastColor);
            circle->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
            this->addItem(circle);
            if (!(mouseEvent->modifiers() & Qt::ShiftModifier)) {
                clearSelection();
            }
            circle->setSelected(true);
        }
        else {
            QGraphicsScene::mousePressEvent(mouseEvent);
        }
    }
}

void CirclesScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    // Scale circles by mouse y position delta
    if (mouseEvent->buttons() & Qt::RightButton) {
        qreal deltaY = mPrevMouseY - mouseEvent->scenePos().y();
        for(auto *item : selectedItems()) {
            auto *circle = qgraphicsitem_cast<QGraphicsEllipseItem *>(item);

            qreal centerX = circle->rect().x() + circle->rect().width()/2;
            qreal centerY = circle->rect().y() + circle->rect().height()/2;

            qreal radius = circle->rect().height()/2 + deltaY;

            // Reasonable max/mins
            if (radius < 10) {
                radius = 10;
            }
            else if (radius > 300) {
                radius = 300;
            }

            circle->setRect(centerX - radius, centerY - radius, 2*radius, 2*radius);
            circle->update();
        }
        mPrevMouseY = mouseEvent->scenePos().y();
    }
    else {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

static void updateColorForItems(const QList<QGraphicsItem *> &items, const QColor &color)
{
    for(auto *item : items) {
        auto *circle = qgraphicsitem_cast<QGraphicsEllipseItem *>(item);

        circle->setBrush(color);
        circle->update();
    }
}

void CirclesScene::tempSetColorForSelected(const QColor &color)
{
    updateColorForItems(selectedItems(), color);
}

void CirclesScene::resetColorForSelected()
{
    updateColorForItems(selectedItems(), mLastColor);
}

void CirclesScene::finalizeColor(const QColor &color)
{
    mLastColor = color;
    updateColorForItems(selectedItems(), mLastColor);
}

void CirclesScene::deleteSelected()
{
    for(auto *item : selectedItems()) {
        removeItem(item);
        delete item;
    }
}
























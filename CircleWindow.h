#pragma once

#include <QMainWindow>

class CirclesScene;
class QColorDialog;
class QGraphicsView;

class CircleWindow : public QMainWindow
{
    Q_OBJECT

public:
    CircleWindow(QWidget *parent = nullptr);

    bool eventFilter(QObject *object, QEvent *event) override;

private slots:
    void showColorDialog();

private:
    CirclesScene *mScene;
    QGraphicsView *mView;

    QColorDialog *mColorDialog = nullptr;
};

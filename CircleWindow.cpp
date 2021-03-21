#include "CircleWindow.h"
#include "CirclesScene.h"

#include <QColorDialog>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QToolBar>

CircleWindow::CircleWindow(QWidget *parent)
: QMainWindow(parent)
, mScene(new CirclesScene(this))
, mView(new QGraphicsView(this))
{
    resize(1280, 1024);

    mScene->setBackgroundBrush(Qt::lightGray);
    mScene->setSceneRect(0, 0, 1000, 1000);

    mView->setScene(mScene);

    setCentralWidget(mView);

    auto *toolBar = new QToolBar(this);

    auto *colorChangeAction = toolBar->addAction("CC");
    connect(colorChangeAction, &QAction::triggered, this, &CircleWindow::showColorDialog);
    connect(mScene, &CirclesScene::selectionChanged, [colorChangeAction, this](){
        colorChangeAction->setEnabled(mScene->selectedItems().length() > 0);
    });
    colorChangeAction->setEnabled(false);

    addToolBar(Qt::LeftToolBarArea, toolBar);

    installEventFilter(this);
}

// Captures delete or backspace key and delete selected circles
bool CircleWindow::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent->key() == Qt::Key_Delete || keyEvent->key() == Qt::Key_Backspace) {
            mScene->deleteSelected();

            return true;
        }
    }

    return QMainWindow::eventFilter(object, event);
}

void CircleWindow::showColorDialog()
{
    if (!mColorDialog) {
        mColorDialog = new QColorDialog(this);

        connect(mColorDialog, &QColorDialog::currentColorChanged, mScene, &CirclesScene::tempSetColorForSelected);
        connect(mColorDialog, &QColorDialog::colorSelected, mScene, &CirclesScene::finalizeColor);
        connect(mColorDialog, &QColorDialog::rejected, mScene, &CirclesScene::resetColorForSelected);
    }

    mColorDialog->show();
}


#include "mainwindow.h"
#include "graphics/GraphicsView.h"
#include "graphics/GraphicsScene.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_view(new GraphicsView(this)),
      m_scene(new GraphicsScene(this))
{
    m_view->setScene(m_scene);
    setCentralWidget(m_view);

    createMenus();
    createToolbars();
    statusBar()->showMessage("Ready");


}


void MainWindow::createMenus()
{
    QMenu* fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction("Exit", this, &MainWindow::close);

    QMenu* editMenu = menuBar()->addMenu("&Edit");
    QMenu* viewMenu = menuBar()->addMenu("&View");
    QMenu* helpMenu = menuBar()->addMenu("&Help");
}

void MainWindow::createToolbars()
{
    QToolBar* toolbar = addToolBar("Main Toolbar");

    QAction* lineAction = toolbar->addAction("Line");
    connect(lineAction, &QAction::triggered, this, [this]() {
        m_scene->setDrawingMode(ItemType::Line);
        statusBar()->showMessage("Drawing mode: Line");
    });

    QAction* selectAction = toolbar->addAction("Select");
    connect(selectAction, &QAction::triggered, this, [this]() {
        m_scene->setDrawingMode(ItemType::Select);
        statusBar()->showMessage("Mode: Select");
    });
}

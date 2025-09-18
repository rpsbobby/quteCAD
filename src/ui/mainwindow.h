#ifndef QUTECAD_MAINWINDOW_H
#define QUTECAD_MAINWINDOW_H

#include <QMainWindow>

class GraphicsView;
class GraphicsScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow() override = default;

    private:
        GraphicsView *m_view;
        GraphicsScene *m_scene;

        void createMenus();
        void createToolbars();
};

#endif //QUTECAD_MAINWINDOW_H
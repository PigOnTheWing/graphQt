#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTextStream>
#include <QTabBar>
#include "graph.h"
#include "graphnode.h"
#include "graphmain.h"
#include "tab.h"
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() Q_DECL_OVERRIDE;

private slots:
    void open();

    void save();

    void newNode();

    void connectNode();

    void deleteTab(int index);

    void newTab();

    void clear();

    void spanningTree();

private:
    int next_tab = 0;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

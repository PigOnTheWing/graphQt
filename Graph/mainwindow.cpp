#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->setTabsClosable(true);

    QAction* clear = ui->menuBar->addAction("X");

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save);
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::deleteTab);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newTab);
    connect(ui->actionAdd_Node, &QAction::triggered, this, &MainWindow::newNode);
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::connectNode);
    connect(ui->actionFind_Tree, &QAction::triggered, this, &MainWindow::spanningTree);
    connect(clear, &QAction::triggered, this, &MainWindow::clear);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open", "/home/smol/Documents", "Graph models (*.gr)");

    if (fileName != "")
    {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadWrite))
            return;

        GraphMain* g = new GraphMain(nullptr, 0, 0, 1920, 1080);

        int nodeCount = file.readLine().toInt();

        for (int i = 0; i < nodeCount; i++)
            g->addNode(i * 50, i * 50, 50, 50);

        QString line;

        while(!file.atEnd())
        {
            line = file.readLine();
            QStringList connections = line.split(" ");

            for (int i = 1; i < connections.length(); i++)
                g->connectNodes(connections[0].toInt(), connections[i].toInt());
        }

        Tab* t = new Tab(g, ui->tabWidget);
        ui->tabWidget->addTab(t, fileName);
    }
}

void MainWindow::save()
{
    Tab* t = dynamic_cast<Tab*>(ui->tabWidget->currentWidget());

    if (t != nullptr)
    {
        QString fileName;
        if (t->isNew())
            fileName = QFileDialog::getSaveFileName(this, "Save", "/home/smol/Documents", "Graph models (*.gr)");
        else
            fileName = ui->tabWidget->tabText(ui->tabWidget->currentIndex());

        QFile file(fileName);

        if (!file.open(QIODevice::WriteOnly))
            return;

        QTextStream stream(&file);
        stream << t->graph()->toString();
    }
}

void MainWindow::newNode()
{
    Tab* t = dynamic_cast<Tab*>(ui->tabWidget->currentWidget());

    if (t != nullptr)
        t->setAdd();
}

void MainWindow::connectNode()
{
    Tab* t = dynamic_cast<Tab*>(ui->tabWidget->currentWidget());

    if (t != nullptr)
        t->setConnect();
}

void MainWindow::deleteTab(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::newTab()
{
    Tab* t = new Tab(ui->tabWidget);
    ui->tabWidget->addTab(t, "New " + QString::number(next_tab++));
}

void MainWindow::clear()
{
    Tab* t = dynamic_cast<Tab*>(ui->tabWidget->currentWidget());

    if (t != nullptr)
        t->clear();
}

void MainWindow::spanningTree()
{
    Tab* t = dynamic_cast<Tab*>(ui->tabWidget->currentWidget());

    if (t != nullptr)
    {
        QString fileName = ui->tabWidget->tabText(ui->tabWidget->currentIndex());
        if (t->isNew())
            fileName = "home/smol/Documents/" + fileName;
        else
            fileName.chop(3);

        fileName += "_spanning.gr";

        Tab* spanningT = new Tab(t->graph()->spanningTree(), ui->tabWidget);
        ui->tabWidget->addTab(spanningT, fileName);
    }
}

#include "tab.h"

Tab::Tab(GraphMain *g, QWidget *parent) : QWidget(parent)
{
    setViewLayout();

    _graph = g;

    view = new QGraphicsView(this);
    view->resize(parent->width(), parent->height());
    scene = new QGraphicsScene( );

    view->setScene(scene);
    scene->addItem(g);

    existing = true;
}

Tab::~Tab()
{
    delete _graph;
    delete view;
}

void Tab::setViewLayout()
{
    QVBoxLayout* l = new QVBoxLayout();
    l->setContentsMargins(0, 0, 0, 0);
    setLayout(l);
}

Tab::Tab(QWidget* parent) : QWidget(parent)
{
    setViewLayout();

    _graph = new GraphMain(nullptr, 0, 0, 1920, 1080);

    view = new QGraphicsView(this);
    view->resize(parent->width(), parent->height());
    //view->resize(1920, 1080);
    scene = new QGraphicsScene();

    view->setScene(scene);
    scene->addItem(_graph);
}

void Tab::setScene(GraphMain *g)
{
    _graph = g;
    scene->addItem(g);
}

bool Tab::isNew()
{
    return !existing;
}

GraphMain *Tab::graph()
{
    return _graph;
}

void Tab::setAdd()
{
    _graph->setAdd();
}

void Tab::setConnect()
{
    _graph->setConnect();
}

void Tab::clear()
{
    _graph->clear();
}

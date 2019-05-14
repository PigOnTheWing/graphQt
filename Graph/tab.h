#ifndef TAB_H
#define TAB_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include "graphmain.h"

class Tab : public QWidget
{
    Q_OBJECT

    bool existing = false;
    GraphMain* _graph;
    QGraphicsView* view;
    QGraphicsScene* scene;

    void setViewLayout();
public:
    explicit Tab(QWidget* parent = nullptr);
    explicit Tab(GraphMain* g, QWidget *parent = nullptr);
    ~Tab() override;

    void setScene(GraphMain* g);
    bool isNew();
    GraphMain* graph();
    void setAdd();
    void setConnect();
    void clear();
};

#endif // TAB_H

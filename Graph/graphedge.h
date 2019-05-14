#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include <QGraphicsLineItem>
#include "graphnode.h"

class GraphEdge : public QGraphicsLineItem
{
    GraphNode* _from;
    GraphNode* _to;
    bool visited = false;
public:
    GraphEdge(GraphNode* n1, GraphNode* n2);
    ~GraphEdge() override;

    bool isVisted();
    void setVisited(bool val);

    GraphNode* from();
    GraphNode* to();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // GRAPHEDGE_H

#include "graphedge.h"

GraphEdge::GraphEdge(GraphNode *from, GraphNode *to)
{
    _from = from;
    _to = to;
    QGraphicsLineItem();
}

GraphEdge::~GraphEdge()
{

}

bool GraphEdge::isVisted()
{
    return visited;
}

void GraphEdge::setVisited(bool val)
{
    visited = val;
}

GraphNode *GraphEdge::from()
{
    return _from;
}

GraphNode *GraphEdge::to()
{
    return _to;
}

void GraphEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen prevPen = painter->pen();
    QPen pen;
    pen.setWidth(2);

    if (visited)
        pen.setColor(Qt::blue);

    painter->setPen(pen);
    painter->drawLine(_from->centre(), _to->centre());

    painter->setPen(prevPen);
}

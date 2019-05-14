#include "graphnode.h"
#include "graphedge.h"

GraphNode::GraphNode(int id, QRectF bounding)
{
    this->_id = id;
    setRect(bounding);
    setFlag(ItemIsMovable);
}

GraphNode::GraphNode(int id, qreal x, qreal y, qreal w, qreal h)
{
    this->_id = id;
    setRect(x, y, w, h);
    setFlag(ItemIsMovable);
}

GraphNode::~GraphNode()
{
    for (GraphEdge* con : connections)
        delete con;
}

void GraphNode::addConnection(GraphEdge* node)
{
    connections.append(node);
}

QList<GraphEdge*> GraphNode::getConnections()
{
    return connections;
}

int GraphNode::id()
{
    return _id;
}

void GraphNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qreal dx = event->lastPos().x() - event->pos().x();
    qreal dy = event->lastPos().y() - event->pos().y();
    setRect(rect().x() - dx, rect().y() - dy, rect().width(), rect().height());
}

void GraphNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen prevPen = painter->pen();
    QPen pen;
    pen.setWidth(5);
    painter->setPen(pen);
    painter->drawEllipse(rect());
    painter->drawText(rect(), Qt::AlignCenter, QString::number(_id));
    painter->setPen(prevPen);
}

QPointF GraphNode::centre()
{
    QPointF c(rect().x() + rect().width() / 2, rect().y() + rect().height() / 2);
    return c;
}

bool GraphNode::isVisited()
{
    return visited;
}

void GraphNode::setVisited(bool val)
{
    visited = val;
}

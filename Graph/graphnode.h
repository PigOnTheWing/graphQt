#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QRectF>
#include <QPointF>
#include <QList>
#include <QPainter>


class GraphEdge;

class GraphNode : public QGraphicsEllipseItem
{
public:
    GraphNode(int id, QRectF bounding);
    GraphNode(int id, qreal x, qreal y, qreal w, qreal h);
    ~GraphNode() override;

    void addConnection(GraphEdge* node);
    QList<GraphEdge*> getConnections();
    int id();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QPointF centre();

    bool isVisited();
    void setVisited(bool val);

private:
    int _id;
    bool visited = false;
    QList<GraphEdge*> connections;
};

#endif // GRAPHNODE_H

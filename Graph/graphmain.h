#ifndef GRAPHMAIN_H
#define GRAPHMAIN_H

#include "graphedge.h"
#include <QObject>
#include <QGraphicsItem>

class GraphMain : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit GraphMain(QObject* parent, QRectF rect);
    explicit GraphMain(QObject* parent, qreal x, qreal y, qreal w, qreal h);
    ~GraphMain() override;
    QRectF boundingRect() const override;
    void addNode(QRectF rect);
    void addNode(qreal x, qreal y, qreal w, qreal h);
    void addConnection(QPointF pos);
    void addConnection(qreal x, qreal y);
    void connectNodes(int i1, int i2);
    void clearVisited();
    GraphMain* spanningTree();
    QString toString();

    void setAdd();
    void setConnect();
    void clear();

signals:
    void singleClick(QGraphicsSceneMouseEvent* e);
    void buttonPress(QGraphicsSceneMouseEvent* e);

public slots:
    void addNodeEvent(QGraphicsSceneMouseEvent* e);
    void connectNode(QGraphicsSceneMouseEvent* e);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int next_id = 0;
    int currentFrom = -1;
    QPointF cursorPosition;
    QRectF rect;
    QList<GraphNode*> nodes;
    QPen pen;
    QBrush brush;
};

#endif // GRAPHMAIN_H

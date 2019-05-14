#include "graphmain.h"

GraphMain::GraphMain(QObject* parent, QRectF rect) : QObject(parent), QGraphicsItem()
{
    this->rect = rect;
    pen.setWidth(5);
    brush.setColor(Qt::red);
}

GraphMain::GraphMain(QObject* parent, qreal x, qreal y, qreal w, qreal h) : QObject(parent), QGraphicsItem()
{
    this->rect = QRectF(x, y, w, h);
    setFlag(ItemIsMovable);
}

GraphMain::~GraphMain()
{
    for (GraphNode* node : nodes)
        delete node;
}

QRectF GraphMain::boundingRect() const
{
    return rect;
}

void GraphMain::addNode(QRectF rect)
{
    GraphNode* node = new GraphNode(next_id++, rect);
    nodes.append(node);
    update();
}

void GraphMain::addNode(qreal x, qreal y, qreal w, qreal h)
{
    GraphNode* node = new GraphNode(next_id++, x, y, w, h);
    nodes.append(node);
    update();
}


void GraphMain::addConnection(qreal x, qreal y)
{
    QPointF pos(x, y);
    addConnection(pos);
}

void GraphMain::addConnection(QPointF pos)
{
    if (currentFrom == -1)
    {
        for (GraphNode* node : nodes) {
            if (node->rect().contains(pos))
            {
                currentFrom = node->id();
                cursorPosition = pos;
            }
        }
    }
    else
    {
        for (GraphNode* node : nodes) {
            if (node->rect().contains(pos) && node->id() != nodes[currentFrom]->id())
                connectNodes(currentFrom, node->id());
        }
        currentFrom = -1;
    }
    update();
}

void GraphMain::connectNodes(int i1, int i2)
{
    GraphEdge* e1 = new GraphEdge(nodes[i1], nodes[i2]);
    GraphEdge* e2 = new GraphEdge(nodes[i2], nodes[i1]);
    nodes[i1]->addConnection(e1);
    nodes[i2]->addConnection(e2);
    update();
}

void GraphMain::clearVisited()
{
    for (GraphNode* node : nodes) {
        node->setVisited(false);
        for (GraphEdge* edge : node->getConnections()) {
            edge->setVisited(false);
        }
    }
}

GraphMain* GraphMain::spanningTree()
{
    clearVisited();

    GraphMain* sTree = new GraphMain(nullptr, rect);

    for (GraphNode* node : nodes) {
        sTree->addNode(node->rect());
    }

    nodes[0]->setVisited(true);
    for (int i = 0; i < nodes.length(); i++) {
        for (GraphEdge* edge : nodes[i]->getConnections())
        {
            if (!edge->to()->isVisited())
            {
                edge->to()->setVisited(true);
                sTree->connectNodes(i, edge->to()->id());
            }
        }
    }
    return sTree;
}

QString GraphMain::toString()
{
    QString graphString;
    graphString.append(QString::number(nodes.length()));
    graphString.append("\n");

    for (GraphNode* node : nodes)
    {
        graphString.append(QString::number(node->id()));

        for (GraphEdge* con : node->getConnections()) {
            graphString.append(" ");
            graphString.append(QString::number(con->to()->id()));
        }

        graphString.append("\n");
    }
    update();

    return graphString;
}

void GraphMain::setAdd()
{
    clear();
    connect(this, &GraphMain::singleClick, this, &GraphMain::addNodeEvent);
}

void GraphMain::setConnect()
{
    clear();
    connect(this, &GraphMain::buttonPress, this, &GraphMain::connectNode);
    connect(this, &GraphMain::singleClick, this, &GraphMain::connectNode);
}

void GraphMain::clear()
{
    disconnect(this, &GraphMain::buttonPress, nullptr, nullptr);
    disconnect(this, &GraphMain::singleClick, nullptr, nullptr);
}

void GraphMain::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(Qt::red);

    if (currentFrom != -1)
    {
        GraphNode* from = nodes[currentFrom];
        painter->drawLine(static_cast<int>(from->centre().x()), static_cast<int>(from->centre().y()),
                          static_cast<int>(cursorPosition.x()), static_cast<int>(cursorPosition.y()));
    }

    for (GraphNode* node : nodes) {

        for (GraphEdge* con : node->getConnections()) {
            if (node->id() < con->to()->id())
                con->paint(painter, option, widget);
        }

        node->paint(painter, option, widget);
    }
}

void GraphMain::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (currentFrom != -1)
    {
        cursorPosition = event->pos();
        update();
        return;
    }

    for (GraphNode* node : nodes) {
        if (node->rect().contains(event->lastPos()))
            node->mouseMoveEvent(event);
    }
    update();
}

void GraphMain::addNodeEvent(QGraphicsSceneMouseEvent *e)
{
    addNode(e->pos().x(), e->pos().y(), 50, 50);
}

void GraphMain::connectNode(QGraphicsSceneMouseEvent *e)
{
    addConnection(e->pos());
}

void GraphMain::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit buttonPress(event);
}

void GraphMain::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit singleClick(event);
}


#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    graph.CreateGraph();
    bfsButton = new QPushButton("Start BFS", this);
    bfsButton->move(10, 10);
    connect(bfsButton, SIGNAL(clicked()), this, SLOT(startBFS()));
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter paint(this);
    std::vector<Node*> nodes = graph.getNodes();
    std::vector<Arch*> arches = graph.getArches();
    for (Node*& node : nodes)
    {
        QRect rectangle(node->getCoord().second*100+30, node->getCoord().first*100+30, 30, 30);
        QString string;
        string.setNum(node->getValue());
        paint.setPen(Qt::black);
        if (node->getType() == 1)
            paint.setBrush(Qt::white);
        else if (node->getType() == 2)
            paint.setBrush(Qt::red);
        else if (node->getType() == 3)
            paint.setBrush(Qt::blue);
        else if (node->getType() == 4)
            paint.setBrush(Qt::green);
        paint.drawEllipse(rectangle);
        paint.drawText(rectangle, Qt::AlignCenter, string);
    }
    for (Arch*& arch : arches)
    {
        int radius = 15;
        QPoint startP(arch->getSourceNode()->getCoord().second*100+45, arch->getSourceNode()->getCoord().first * 100+45);
        QPoint endP(arch->getDestinationNode()->getCoord().second * 100+45, arch->getDestinationNode()->getCoord().first*100+45);
        double angle = std::atan2(endP.y() - startP.y(), endP.x() - startP.x());
        startP.setX(startP.x() + radius * cos(angle));
        startP.setY(startP.y() + radius * sin(angle));
        endP.setX(endP.x() - radius * cos(angle));
        endP.setY(endP.y() - radius * sin(angle));
        paint.drawLine(startP, endP);
    }
    QRect remainingRect(830, 30, 600, 600);
    paint.setPen(Qt::black);
    paint.setBrush(Qt::black);
    paint.drawRect(remainingRect);
    int numSmallSquares = 6;
    int smallSquareSize = remainingRect.width() / numSmallSquares;
    for (int row = 0; row < numSmallSquares; row++) {
        for (int col = 0; col < numSmallSquares; col++) {
            QRect smallSquare(remainingRect.left() + col * smallSquareSize,remainingRect.top() + row * smallSquareSize,
                smallSquareSize,smallSquareSize);
            paint.setPen(Qt::gray);
            paint.setBrush(Qt::black);
            paint.drawRect(smallSquare);
        }
    }
    for (Node*& node : nodes)
    {
        QRect rectangle(node->getCoord().second *100+ 830, node->getCoord().first * 100 + 30, 100, 100);
        paint.setPen(Qt::gray);
        if (node->getType() == 1)
            paint.setBrush(Qt::white);
        else if (node->getType() == 2)
            paint.setBrush(Qt::red);
        else if (node->getType() == 3)
            paint.setBrush(Qt::blue);
        else if (node->getType() == 4)
            paint.setBrush(Qt::green);
        paint.drawRect(rectangle);
    }
}

MainWindow::~MainWindow()
{
    delete bfsButton;
}

void MainWindow::startBFS()
{
    graph.BFS();
    update();
}

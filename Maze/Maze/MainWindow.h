#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Graph.h"
#include <QPainter>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent* event);
    ~MainWindow();
private slots:
    void startBFS();
private:
    Ui::MainWindowClass ui;
    Graph graph;
    QPushButton* bfsButton;
};

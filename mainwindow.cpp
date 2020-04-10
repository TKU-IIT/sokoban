#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVarLengthArray>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Wall Object
    wall = new QPixmap(":/res/brick.jpg");
    Wall = new QLabel(this);
    Wall->setPixmap(*wall);
    Wall->setScaledContents(true);
    Wall->setGeometry(0,0,50,50);
    //Pixmap Pathes
    front = new QPixmap(":/res/main_character(front).png");
    back = new QPixmap(":/res/main_character(back).png");
    left = new QPixmap(":/res/main_character(left).png");
    right = new QPixmap(":/res/main_character(right).png");
    //Character Object
    player_facing = new QLabel(this);
    player_facing->setGeometry(50,50,50,50);
    player_facing->setPixmap(*front);
    player_facing->setScaledContents(true);
    QRectF a ;
    QPainter* p;
    drawBackground(p,a);
}
void MainWindow::drawBackground(QPainter *painter, const QRectF &rect)
{
    const int gridSize = 25;

    qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
    qreal top = int(rect.top()) - (int(rect.top()) % gridSize);

    QVarLengthArray<QLineF, 100> lines;

    for (qreal x = left; x < rect.right(); x += gridSize)
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
    for (qreal y = top; y < rect.bottom(); y += gridSize)
        lines.append(QLineF(rect.left(), y, rect.right(), y));

    qDebug() << lines.size();

    painter->drawLines(lines.data(), lines.size());
}
void MainWindow::keyPressEvent(QKeyEvent* key){
    if(key->key() == Qt::Key_Up){
        emit character_turn_back();
        if(player_facing->y()>=50)
            player_facing->move(player_facing->x(),player_facing->y()-50);
    }
    if(key->key() == Qt::Key_Down){
        emit character_turn_front();
        if(player_facing->y()<=MainWindow::size().height()-100)
            player_facing->move(player_facing->x(),player_facing->y()+50);
    }
    if(key->key() == Qt::Key_Left){
        emit character_turn_left();
        if(player_facing->x()>=50)
            player_facing->move(player_facing->x()-50,player_facing->y());
    }
    if(key->key() == Qt::Key_Right){
        emit character_turn_right();
        if(player_facing->x()<=MainWindow::size().width()-100)
        player_facing->move(player_facing->x()+50,player_facing->y());
    }
}
void MainWindow::character_turn_back(){
    player_facing->setPixmap(*back);
}
void MainWindow::character_turn_front(){
    player_facing->setPixmap(*front);
}
void MainWindow::character_turn_left(){
    player_facing->setPixmap(*left);
}
void MainWindow::character_turn_right(){
    player_facing->setPixmap(*right);
}
MainWindow::~MainWindow()
{
    delete ui;
}





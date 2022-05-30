#include <QVBoxLayout>
#include <QFrame>
#include <QMainWindow>



QVBoxLayout *initVBox(QMainWindow *parent) {
    QVBoxLayout *vbox = new QVBoxLayout;
    QWidget *widget = new QWidget(parent);
    widget->setLayout(vbox);
    widget->show();
    parent->setCentralWidget(widget);
    return vbox;
}

QFrame* makeHLine() {
    QFrame *fr = new QFrame();
    fr->setFrameShape(QFrame::HLine);
    fr->setFrameShadow(QFrame::Sunken);
    return fr;
}
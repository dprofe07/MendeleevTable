#ifndef QTMENDELEEV_UIFUNCTIONS_H
#define QTMENDELEEV_UIFUNCTIONS_H

#include <QHBoxLayout>
#include <QComboBox>
#include <QVBoxLayout>
#include <QString>
#include <QLabel>
#include <QFrame>

void initHBox(QHBoxLayout*& hbox, QString lblText, QComboBox*& widget, QVBoxLayout*& vbox, int width = 0, bool needStretch = true) {
    if (needStretch) hbox = new QHBoxLayout;
    //  Label
    QLabel *lbl = new QLabel(lblText);
    lbl->setAlignment(Qt::AlignTop);
    hbox->addWidget(lbl);
    if (needStretch) hbox->addStretch(1);
    //  Widget
    widget = new QComboBox;
    if (width != 0) {
        widget->setMaximumWidth(width);
        widget->setMinimumWidth(width);
    }
    hbox->addWidget(widget);
    //  VBoxLayout
    if (needStretch) vbox->addLayout(hbox);
}

template <class T>
void initHBox(QHBoxLayout*& hbox, QString lblText, T*& widget, QVBoxLayout*& vbox, int width = 0, bool needStretch = true) {
    if (needStretch) hbox = new QHBoxLayout;
    //  Label
    QLabel *lbl = new QLabel(lblText);
    lbl->setAlignment(Qt::AlignTop);
    hbox->addWidget(lbl);
    if (needStretch) hbox->addStretch(1);
    //  Widget
    widget = new T;
    widget->setAlignment(Qt::AlignRight);
    if (width != 0) {
        widget->setMaximumWidth(width);
        widget->setMinimumWidth(width);
    }
    hbox->addWidget(widget);
    //  VBoxLayout
    if (needStretch) vbox->addLayout(hbox);
}

QFrame* makeHLine();

QVBoxLayout* initVBox(QMainWindow* parent);

#endif //QTMENDELEEV_UIFUNCTIONS_H

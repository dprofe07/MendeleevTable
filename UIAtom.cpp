#define LST

#include "UIAtom.h"
#include "MendeleevTable.h"
#include "UIFunctions.h"
#include "exceptions.h"
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QTextStream>


void UIAtom::initUI() {
    this->initMenu();
    this->setWindowTitle("Таблица Менделеева");

    QFont font("Arial", 13);
    this->setFont(font);

    this->vbox = initVBox(this);

    // Number
    initHBox(this->hboxNum, "Номер: ", this->spbNumber, this->vbox, 50);
    this->spbNumber->setMinimum(1);
    this->spbNumber->setMaximum(118);
    // Symbol
    initHBox(this->hboxSymbol, "Символ: ", this->txtSymbol, this->vbox, 50);
    this->txtSymbol->setMaxLength(2);
    //Name
    initHBox(this->hboxName, "Название: ", this->txtName, this->vbox);

    { // Position
        initHBox(this->hboxPosition, "Расположение: ", this->spbPeriod, this->vbox, 50);
        this->spbPeriod->setMinimum(1);
        this->spbPeriod->setMaximum(7);
        initHBox(this->hboxPosition, "/", this->spbGroup, this->vbox, 50, false);
        this->spbGroup->setMinimum(1);
        this->spbGroup->setMaximum(8);
        initHBox(this->hboxPosition, "/", this->cmbSubGroup, this->vbox, 50, false);
        this->cmbSubGroup->addItem("A");
        this->cmbSubGroup->addItem("B");
    } // Position

    // Charge
    initHBox(this->hboxCharge, "Заряд:", this->spbCharge, this->vbox);

    // relMass
    initHBox(this->hboxRelMass, "A<sub>r</sub>", this->lblRelMass, this->vbox);
    // Metal
    initHBox(this->hboxMetal, "Металлические свойства: ", this->lblMetal, this->vbox);
    // HLine
    this->vbox->addWidget(makeHLine());
    // Protons & Neutrons & Electrons
    initHBox(this->hboxPNE, "p<sup>+</sup>, n<sup>0</sup>, e<sup>-</sup>: ", this->lblPNE, this->vbox);
    // Valency
    initHBox(this->hboxValency, "Валентность", this->lblValency, this->vbox);
    // ElectronScheme
    initHBox(this->hboxElScheme, "Электронная схема: ", this->lblElScheme, this->vbox);
    // ElectronFormula
    initHBox(this->hboxElFormule, "Электронная формула", this->lblElFormula, this->vbox);
    // НСО, ВСО
    initHBox(this->hboxSO, "Степени окисления: ", this->lblSO, this->vbox);


    connect(this->spbNumber, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UIAtom::updNum);
    connect(this->txtSymbol, &QLineEdit::textEdited, this, &UIAtom::updSym);
    connect(this->txtName, &QLineEdit::textEdited, this, &UIAtom::updName);
    connect(this->spbPeriod, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UIAtom::updPos);
    connect(this->spbGroup, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UIAtom::updPos);
    connect(this->cmbSubGroup, &QComboBox::currentTextChanged, this, &UIAtom::updPos);
    connect(this->spbCharge, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UIAtom::changeCharge);

    this->update(updateTypes::NUMBER);
}

void UIAtom::initMenu() {
    QAction *aQuit = new QAction("&Выход", this);

    aQuit->setShortcut(tr("CTRL+Q"));

    QMenu *mFile;
    mFile = this->menuBar()->addMenu("&Файл");

    mFile->addAction(aQuit);

    connect(aQuit, &QAction::triggered, qApp, &QApplication::quit);
}



void UIAtom::update(updateTypes upd) {
    if (!this->needUpdate)
        return;
    this->needUpdate = false;
    QString strSymbol = this->txtSymbol->text();
    if (strSymbol.length() == 2)
        this->txtSymbol->setText((QString)strSymbol[0].toUpper() + strSymbol[1].toLower());
    else if (strSymbol.length() == 1)
        this->txtSymbol->setText(strSymbol[0].toUpper());

    this->txtName->setText(this->txtName->text().toLower());

    switch (upd) {
        case updateTypes::NUMBER: {
            int num = this->spbNumber->value();
            try {
                this->selectedElement = MendeleevTable::fromNumber(num);
            } catch (ElementNotFoundException) {
                this->needUpdate = true;
                return;
            }
            break;
        }
        case updateTypes::SYMBOL: {
            QString str = this->txtSymbol->text();
            try {
                this->selectedElement = MendeleevTable::fromSymbol(str.toStdString());
            } catch (ElementNotFoundException) {
                this->needUpdate = true;
                return;
            }
            break;
        }
        case updateTypes::NAME: {
            QString str = this->txtName->text();
            try {
                this->selectedElement = MendeleevTable::fromName(str.toStdString());
            } catch (ElementNotFoundException) {
                this->needUpdate = true;
                return;
            }
            break;
        }
        case updateTypes::POSITION: {
            int period = this->spbPeriod->value(),
                group = this->spbGroup->value();
            bool subgroup = this->cmbSubGroup->currentText() == "A";
            try {
                this->selectedElement = MendeleevTable::fromPosition(period, group, subgroup);
            } catch (std::vector<int> vec) {
                this->selectedElement = MendeleevTable::fromNumber(vec[0]);
            } catch (ElementNotFoundException) {
                this->needUpdate = true;
                return;
            }
            break;
        }
        case updateTypes::CHARGE: {
            this->selectedElement.setZ(this->spbCharge->value());
            break;
        }
    }
    this->spbNumber->setValue(this->selectedElement.getNumber());
    this->txtSymbol->setText(QString::fromStdString(this->selectedElement.getSymbol()));
    this->txtName->setText(QString::fromStdString(this->selectedElement.getName()));
    this->spbPeriod->setValue(this->selectedElement.getPeriod());
    this->spbGroup->setValue(this->selectedElement.getGroup());
    this->cmbSubGroup->setCurrentIndex(this->selectedElement.getSubGroup() ? 0 : 1);

    this->spbCharge->setMaximum(selectedElement.getMaxOxid());
    this->spbCharge->setMinimum(selectedElement.getMinOxid());

    this->lblRelMass->setText(QString::number(this->selectedElement.getRelMass()));
    switch(this->selectedElement.getMetal()) {
        case Metal::METAL:
            this->lblMetal->setText("Металл");
            break;
        case Metal::NONMETAL:
            this->lblMetal->setText("Неметалл");
            break;
        case Metal::UNKNOWN:
            this->lblMetal->setText("Неизвестно");
            break;
    }
    this->lblPNE->setText(QString::fromStdString(this->selectedElement.getNumberOfPNE()));
    this->lblValency->setText(QString::number(this->selectedElement.getValency()));
    this->lblElScheme->setText(QString::fromStdString(this->selectedElement.getElectronGroupPosition()));

    this->lblElFormula->setText(QString::fromStdString(this->selectedElement.getElectronSubGroupPosition()));
    this->lblSO->setText(
            "НСО = " + QString::number(this->selectedElement.getMinOxid()) +
            "<br/>ВСО = " + QString::number(this->selectedElement.getMaxOxid())
            );
    this->needUpdate = true;
}
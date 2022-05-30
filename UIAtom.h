#ifndef QTMENDELEEV_UIATOM_H
#define QTMENDELEEV_UIATOM_H

#include <QWidget>
#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "Element.h"

enum class updateTypes {
    NUMBER,
    SYMBOL,
    NAME,
    POSITION,
    CHARGE
};

class UIAtom : public QMainWindow {
private:
    QVBoxLayout *vbox;
    QHBoxLayout *hboxNum;
    QSpinBox *spbNumber;
    QHBoxLayout *hboxSymbol;
    QLineEdit *txtSymbol;
    QHBoxLayout *hboxName;
    QLineEdit *txtName;
    QHBoxLayout *hboxPosition;
    QSpinBox *spbPeriod;
    QSpinBox *spbGroup;
    QComboBox *cmbSubGroup;
    QHBoxLayout *hboxCharge;
    QSpinBox *spbCharge;
    QHBoxLayout *hboxRelMass;
    QLabel *lblRelMass;
    QHBoxLayout *hboxMetal;
    QLabel *lblMetal;
    QHBoxLayout *hboxPNE;
    QLabel *lblPNE;
    QHBoxLayout *hboxElScheme;
    QLabel *lblElScheme;
    QHBoxLayout *hboxElFormule;
    QLabel *lblElFormula;
    QHBoxLayout *hboxValency;
    QLabel *lblValency;
    QHBoxLayout *hboxLocalEoAndRa;
    QLabel *lblLocalEoAndRa;
    QHBoxLayout *hboxSO;
    QLabel *lblSO;
    Element selectedElement;
    bool needUpdate = true;

    Q_OBJECT
    void initUI();
    void initMenu();
private slots:
    void update(updateTypes upd);
    void updNum() {
        this->update(updateTypes::NUMBER);
    }
    void updSym() {
        this->update(updateTypes::SYMBOL);
    }
    void updName() {
        this->update(updateTypes::NAME);
    }
    void updPos() {
        this->update(updateTypes::POSITION);
    }
    void changeCharge() {
        this->selectedElement.setZ(this->spbCharge->value());
        this->update(updateTypes::CHARGE);
    }
public:
    UIAtom () : QMainWindow(nullptr) {
        initUI();
    }
};


#endif //QTMENDELEEV_UIATOM_H

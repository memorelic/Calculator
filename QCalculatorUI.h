#ifndef _QCALCULATORUI_H_
#define _QCALCULATORUI_H_

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

#include "ICalculator.h"
#include <QDebug>

class QCalculatorUI : public QWidget
{
    Q_OBJECT
private:
    QLineEdit*      m_edit;
    QPushButton*    m_buttons[20];
    ICalculator*    m_cal;

private:
    QCalculatorUI();
    bool construct();
private slots:
    void onButtonClicked();
public:
    static QCalculatorUI* NewInstance();
    void show();
    void setCalculator(ICalculator* cal);
    ICalculator* getCalculator();
    ~QCalculatorUI();
};

#endif // _QCALCULATORUI_H_

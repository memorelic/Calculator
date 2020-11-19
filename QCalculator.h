#ifndef _QCALCULATOR_H_
#define _QCALCULATOR_H_

#include "QCalculatorUI.h"
#include "QCalculatorDec.h"
#include "ICalculator.h"

class QCalculator
{
private:
    QCalculatorUI *m_ui;
    QCalculatorDec m_cal;

    QCalculator();
    bool construct();
public:
    static QCalculator* NewInstance();
    void show();
    ~QCalculator();
};

#endif // QCALCULATOR_H

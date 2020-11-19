#ifndef _QCALCULATORDEC_H_
#define _QCALCULATORDEC_H_

#include <QString>
#include <QQueue>
#include <QStack>
#include <QDebug>

#include "ICalculator.h"

class QCalculatorDec : public ICalculator
{
protected:
    QString m_exp;
    QString m_result;

protected:
    bool isDigitOrDot(QChar c);
    bool isSymbol(QChar c);
    bool isSign(QChar c);
    bool isNumber(QString s);
    bool isOperator(QString s);
    bool isLeft(QString s);
    bool isRight(QString s);
    int priority(QString s);


    QString calculate(QQueue<QString> &exp);
    QString calculate(QString lvalue, QString op, QString rvalue);

    QQueue<QString> split(const QString& exp);
    // 检查括号是否匹配
    bool match(QQueue<QString>& exp);
    bool transform(QQueue<QString>& exp, QQueue<QString>& output);
public:
    QCalculatorDec();
    ~QCalculatorDec();

    bool expression(const QString& exp);
    QString result();

};

#endif // !_QCALCULATORDEC_H_

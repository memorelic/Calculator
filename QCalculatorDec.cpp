#include "QCalculatorDec.h"

QCalculatorDec::QCalculatorDec()
{
    m_exp = ("");
    m_result = ("");
}

QCalculatorDec::~QCalculatorDec()
{

}

bool QCalculatorDec::expression(const QString &exp)
{
    bool ret = false;

    QQueue<QString> spExp = split(exp);
    QQueue<QString> postExp;

    m_exp = exp;

    if (transform(spExp, postExp))
    {
        m_result = calculate(postExp);

        ret = (m_result != "Error");
    }
    else
    {
        m_result = "Error";
    }

    return ret;
}

/*
QString QCalculatorDec::expression()
{

}
*/

QString QCalculatorDec::calculate(QString lvalue, QString op, QString rvalue)
{
    QString ret = "Error";

    if (isNumber(lvalue) && isNumber(rvalue))
    {
        double lp = lvalue.toDouble();
        double rp = rvalue.toDouble();

        if (op == "+")
        {
            ret.sprintf("%f", lp + rp);
        }
        else if (op == "-")
        {
            ret.sprintf("%f", lp - rp);
        }
        else if (op == "*")
        {
            ret.sprintf("%f", lp * rp);
        }
        else if (op == "/")
        {
            const double P = 0.00000000000000001;

            if ((-P < rp) && (rp < P))
            {
                ret = "Error";
            }
            else
            {
                ret.sprintf("%f", lp / rp);
            }
        }
        else
        {
            ret = "Error";
        }
    }

    return ret;
}

QString QCalculatorDec::calculate(QQueue<QString> &exp)
{
    QString ret = "Error";
    QStack<QString> stack;

    while(!exp.isEmpty())
    {
        QString e = exp.dequeue();

        if(isNumber(e))
        {
            stack.push(e);
        }
        else if (isOperator(e))
        {
            QString rvalue = !stack.isEmpty() ? stack.pop() : "";
            QString lvalue = !stack.isEmpty() ? stack.pop() : "";

            QString result = calculate(lvalue, e, rvalue);

            if(result != "Error")
            {
                stack.push(result);
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    if (exp.isEmpty() && stack.size() == 1 && isNumber(stack.top()))
    {
        ret = stack.pop();
    }

    return ret;
}

QString QCalculatorDec::result()
{
    return m_result;
}

bool QCalculatorDec::isDigitOrDot(QChar c)
{
    return (('0' <= c) && (c <= '9')) || (c == ".");
}

bool QCalculatorDec::isSymbol(QChar c)
{
    return isOperator(c) || (c == '(') || (c == ')');
}

bool QCalculatorDec::isSign(QChar c)
{
    return (c == '+') || (c == '-');
}

bool QCalculatorDec::isNumber(QString s)
{
    bool ret = false;

    s.toDouble(&ret);

    return ret;
}

bool QCalculatorDec::isOperator(QString s)
{
    return (s == "+") || (s == "-")
        || (s == "*") || (s == "/");
}

bool QCalculatorDec::isLeft(QString s)
{
    return s == "(";
}

bool QCalculatorDec::isRight(QString s)
{
    return s == ")";
}

int QCalculatorDec::priority(QString s)
{
    int ret = 0;

    if ( (s == "+") || (s == "-") )
    {
        ret = 1;
    }

    if ( (s == "*") || (s == "/") )
    {
        ret = 2;
    }

    return ret;
}

bool QCalculatorDec::match(QQueue<QString> &exp)
{
    bool ret = true;
    QStack<QString> stack;
    int len = exp.length();

    for(int i=0; i<len; i++)
    {
        if (isLeft(exp[i]))
        {
            stack.push(exp[i]);
        }
        else if (isRight(exp[i]))
        {
            if (!stack.isEmpty() && isLeft(stack.top()))
            {
                stack.pop();
            }
            else
            {
                ret = false;
                break;
            }
        }
    }

    return ret;
}

QQueue<QString> QCalculatorDec::split(const QString &exp)
{
    QQueue<QString> ret;
    QString num = "";
    QString pre = "";

    for (int i=0; i<exp.length(); i++)
    {
        if (isDigitOrDot(exp[i]))
        {
            num+=exp[i];
            pre = exp[i];
        }
        else if (isSymbol(exp[i]))
        {
            if (!num.isEmpty())
            {
                ret.enqueue(num);
                num.clear();
            }

            if (isSign(exp[i]) && ((pre == "") || (pre == "(") || isOperator(pre)))
            {
                num += exp[i];
            }
            else
            {
                ret.enqueue(exp[i]);
            }

            pre = exp[i];
        }
    }

    if (!num.isEmpty())
    {
        ret.enqueue(num);
    }

    return ret;
}

bool QCalculatorDec::transform(QQueue<QString> &exp, QQueue<QString> &output)
{
    bool ret = match(exp);
    QStack<QString> stack;

    output.clear();

    while(ret && !exp.isEmpty())
    {
        QString e = exp.dequeue();

        if (isNumber(e))
        {
            output.enqueue(e);
        }
        else if (isOperator(e))
        {
            while(!stack.isEmpty() && (priority(e) <= priority(stack.top())))
            {
                output.enqueue(stack.pop());
            }

            stack.push(e);
        }
        else if (isLeft(e))
        {
            stack.push(e);
        }
        else if (isRight(e))
        {
            while(!stack.isEmpty() && !isLeft(stack.top()))
            {
                output.enqueue(stack.pop());
            }

            if (!stack.isEmpty())
            {
                stack.pop();
            }
        }
        else
        {
            ret = false;
        }
    }

    // 清空栈
    while(!stack.isEmpty())
    {
        output.enqueue(stack.pop());
    }

    // 转换失败清空
    if (!ret)
    {
        output.clear();
    }

    return ret;
}

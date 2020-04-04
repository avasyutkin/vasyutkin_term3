#include "qhttpcontroller.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QEventLoop>
#include <QBitArray>
#include <string>
#include <iostream>
#include <QString>


QHTTPController::QHTTPController(QObject *parent) : QObject(parent)
{
    nam = new QNetworkAccessManager();
}

void QHTTPController::GetNetworkValue()
{
    QNetworkRequest request;
    request.setUrl(QUrl("https://www.rbc.ru/crypto/currency/btcusd"));
    QNetworkReply * reply;
    QEventLoop eventloop;
    connect(nam, &QNetworkAccessManager::finished, &eventloop, &QEventLoop::quit);
    reply = nam -> get(request);
    //обработка reply
    eventloop.exec(); //запуск цикла ожидания. Приложение обрабатывает остальные сигналы, пока не поступит сигнал QEventLoop::quit
    QByteArray replyString = reply -> readAll();
    emit signalSendToQML(QString(replyString), slotPageInfo(replyString), currentratecost(replyString), currentratestate(replyString), boolforcolorlab_4(replyString));
    qDebug() << reply -> url()
             << reply -> rawHeaderList()
             << reply -> readAll();
}

QString QHTTPController::slotPageInfo(QString replyString)
{
    int a = replyString.indexOf("<div class=\"chart__subtitle js-chart-value\">");
    int b = replyString.indexOf("<span class=\"chart__change");
    int c = b - a;
    int d = replyString.indexOf("<span class=\"chart__change");
    int e = replyString.indexOf("<div class=\"chart__description\">");
    int f = e - d;
    QString currentrateall = replyString.mid(a, c) + " USD" + replyString.mid(d, f);
    qDebug() << a << b << c << d << e << f << currentrateall;
    return currentrateall;
}

QString QHTTPController::currentratecost(QString replyString)
{
    int a = replyString.indexOf("<div class=\"chart__subtitle js-chart-value\">");
    int b = replyString.indexOf("<span class=\"chart__change");
    int c = b - a;
    QString currentratecost = replyString.mid(a, c);
    return currentratecost;
}

bool QHTTPController::boolforcolorlab_4(QString replyString)
{
    int a = replyString.indexOf("<span class=\"chart__change");
    int b = replyString.indexOf("<div class=\"chart__description\">");
    int c = b - a;
    QString currentratestate = replyString.mid(a, c);
    std::string strforcolor = currentratestate.toLocal8Bit().constData();
    bool boolforcolor = 1;
    if (strforcolor.find("-"))
        boolforcolor = 0;

    return boolforcolor;
}

QString QHTTPController::currentratestate(QString replyString)
{
    int a = replyString.indexOf("<span class=\"chart__change");
    int b = replyString.indexOf("<div class=\"chart__description\">");
    int c = b - a;
    QString currentratestate = replyString.mid(a, c);
    return currentratestate;
}



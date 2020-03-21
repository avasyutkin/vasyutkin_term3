#include "qhttpcontroller.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QEventLoop>
#include <QBitArray>

QHTTPController::QHTTPController(QObject *parent) : QObject(parent)
{
    nam = new QNetworkAccessManager();
}

void QHTTPController::GetNetworkValue()
{
    QNetworkRequest request;
    //request.setUrl(QUrl("https://meduza.io/"));
    request.setUrl(QUrl("http://go.com"));
    QNetworkReply * reply;
    QEventLoop eventloop;
    connect(nam, &QNetworkAccessManager::finished, &eventloop, &QEventLoop::quit);
    reply = nam -> get(request);
    //обработка reply
    eventloop.exec(); //запуск цикла ожидания. Приложение обрабатывает остальные сигналы, пока не поступит сигнал QEventLoop::quit
    QByteArray replyString = reply -> readAll();
    emit signalSendToQML(QString(replyString));
    qDebug() << reply -> url()
             << reply -> rawHeaderList()
             << reply -> readAll();
}
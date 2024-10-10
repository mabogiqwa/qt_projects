#ifndef NLPMANAGER_H
#define NLPMANAGER_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

class NLPManager : public QObject
{
    Q_OBJECT

public:
    explicit NLPManager(QObject *parent = nullptr);
    void analyzeText(const QString &text);

signals:
    void textAnalysisComplete(const QString &result); // Signal emitted when analysis is complete

private slots:
    void onNetworkReplyFinished(); // Slot to handle network replies

private:
    QNetworkAccessManager *networkManager; // QNetworkAccessManager to perform network requests
};

#endif // NLPMANAGER_H



#include "nlpmanager.h"

NLPManager::NLPManager(QObject *parent)
    : QObject(parent), networkManager(new QNetworkAccessManager(this))
{
    
}

void NLPManager::analyzeText(const QString &text)
{
    QNetworkRequest request(QUrl("YOUR_API_URL"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    QJsonObject json;
    json["text"] = text;

    QNetworkReply *reply = networkManager->post(request, QJsonDocument(json).toJson());
    
    connect(reply, &QNetworkReply::finished, this, &NLPManager::onNetworkReplyFinished);
}

void NLPManager::onNetworkReplyFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        QString analysisResult;

        if (jsonDoc.isObject()) {
            QJsonObject jsonObject = jsonDoc.object();
            analysisResult = jsonObject["result"].toString(); 
        }

        emit textAnalysisComplete(analysisResult);

        reply->deleteLater(); // Clean up the reply object
    }
}


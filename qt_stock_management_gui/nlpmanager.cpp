#include "nlpmanager.h"

NLPManager::NLPManager(QObject *parent)
    : QObject(parent), networkManager(new QNetworkAccessManager(this))
{
    // Initialize any necessary members here
}

void NLPManager::analyzeText(const QString &text)
{
    // Prepare the network request (replace "YOUR_API_URL" with the actual API URL)
    QNetworkRequest request(QUrl("YOUR_API_URL"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Create the JSON object to send in the request
    QJsonObject json;
    json["text"] = text; // Assuming the API accepts a "text" field

    // Send the request (this assumes the API expects a POST request)
    QNetworkReply *reply = networkManager->post(request, QJsonDocument(json).toJson());

    // Connect the reply finished signal to the appropriate slot
    connect(reply, &QNetworkReply::finished, this, &NLPManager::onNetworkReplyFinished);
}

void NLPManager::onNetworkReplyFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        QString analysisResult;

        // Process the JSON response to extract the analysis result
        if (jsonDoc.isObject()) {
            QJsonObject jsonObject = jsonDoc.object();
            analysisResult = jsonObject["result"].toString(); // Adjust this based on your API response
        }

        // Emit the signal with the result
        emit textAnalysisComplete(analysisResult);

        reply->deleteLater(); // Clean up the reply object
    }
}


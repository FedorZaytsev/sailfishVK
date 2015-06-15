#ifndef VKNETWORKACCESSMANAGER_H
#define VKNETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>

class VKNetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit VKNetworkAccessManager(QObject *parent = 0);

signals:

public slots:

};

#endif // VKNETWORKACCESSMANAGER_H

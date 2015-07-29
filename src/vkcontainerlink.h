#ifndef VKCONTAINERLINK_H
#define VKCONTAINERLINK_H

#include "vkabstractcontainer.h"
#include "vkstorage.h"

class VKContainerLink : public VKAbstractContainer
{
    Q_OBJECT
public:
    explicit VKContainerLink(QObject *parent = 0);
    static VKContainerLink *fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users, QVector<int> userIds = QVector<int>());

    Q_INVOKABLE QString url() { return m_url; }
    Q_INVOKABLE QString title() { return m_title; }
    Q_INVOKABLE QString description() { return m_description; }

    void setUrl(QString arg) { m_url = arg; }
    void setTitle(QString arg) { m_title = arg; }
    void setDescription(QString arg) { m_description = arg; }

signals:

public slots:
private:
    QString m_url;
    QString m_title;
    QString m_description;
};

#endif // VKCONTAINERLINK_H

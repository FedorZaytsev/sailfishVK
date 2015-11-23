#ifndef VKCONTAINERLINK_H
#define VKCONTAINERLINK_H

#include "vkabstractcontainer.h"
#include "vkstorage.h"

class VKContainerLink : public VKAbstractContainer
{
    Q_OBJECT
public:
    explicit VKContainerLink(VKStorage *storage, QObject *parent = 0);
    static QSharedPointer<VKContainerLink> fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users);

    Q_INVOKABLE QString url() { return m_url; }
    Q_INVOKABLE QString title() { return m_title; }
    Q_INVOKABLE QString description() { return m_description; }

    void setUrl(QString arg);
    void setTitle(QString arg);
    void setDescription(QString arg);

signals:

public slots:
private:
    QString m_url;
    QString m_title;
    QString m_description;
};

#endif // VKCONTAINERLINK_H

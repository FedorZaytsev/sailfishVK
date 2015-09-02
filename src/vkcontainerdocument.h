#ifndef VKCONTAINERDOCUMENT_H
#define VKCONTAINERDOCUMENT_H

#include "vkabstractcontainer.h"
#include "vkstorage.h"

class VKContainerDocument;
class VKContainerDocument : public VKAbstractContainer
{
    Q_OBJECT
public:
    explicit VKContainerDocument(QObject *parent = 0);
    static QSharedPointer<VKContainerDocument> fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users, QVector<int> userIds = QVector<int>());

    Q_INVOKABLE int id() { return m_id; }
    Q_INVOKABLE int ownerId() { return m_ownerId; }
    Q_INVOKABLE QString title() { return m_title; }
    Q_INVOKABLE int size() { return m_size; }
    Q_INVOKABLE QString ext() { return m_ext; }
    Q_INVOKABLE QString url() { return m_url; }
    Q_INVOKABLE QString photo100() { return m_photo100; }
    Q_INVOKABLE QString photo130() { return m_photo130; }


    void setId(int arg) { m_id = arg; }
    void setOwnerId(int arg) { m_ownerId = arg; }
    void setTitle(QString arg) { m_title = arg; }
    void setSize(int arg) { m_size = arg; }
    void setExt(QString arg) { m_ext = arg; }
    void setUrl(QString arg) { m_url = arg; }
    void setPhoto100(QString arg) { m_photo100 = arg; }
    void setPhoto130(QString arg) { m_photo130 = arg; }

signals:

public slots:
private:
    int m_id;
    int m_ownerId;
    QString m_title;
    int m_size;
    QString m_ext;
    QString m_url;
    QString m_photo100;
    QString m_photo130;
};

#endif // VKCONTAINERDOCUMENT_H

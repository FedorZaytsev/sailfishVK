#ifndef VKABSTRACTCONTAINER_H
#define VKABSTRACTCONTAINER_H

#include <QObject>
#include <QDebug>
#include <QQmlEngine>
#include <QJsonObject>
#include <QJsonArray>

#define SET_ARG(param, arg) do{ bool b = false; if (param != arg) { b = true; } param = arg; if (b) { emit dataChanged(this); } }while(0)
#define SET_ARG_NOCHECK(param, arg) do{ param = arg; emit dataChanged(this); }while(0)

class VKAbstractHandler;
class VKAbstractContainer : public QObject
{
    Q_OBJECT
public:
    explicit VKAbstractContainer(QObject *parent = 0);
    virtual void complete(VKAbstractHandler* h);
    virtual void copyTo(VKAbstractContainer* container);

    int type() { return m_type; }

    void printOwnership();

    enum ContainerType {
        eVKContainerAbstract,
        eVKContainerAttachment,
        eVKContainerAudio,
        eVKContainerChatIcon,
        eVKContainerDialog,
        eVKContainerDocument,
        eVKContainerLink,
        eVKContainerMessage,
        eVKContainerMessageAction,
        eVKContainerPhoto,
        eVKContainerSticker,
        eVKContainerUser,
        eVKContainerVideo,
        eVKContainerWall,
        eVKContainerWallReply,
    };

signals:
    void dataChanged(VKAbstractContainer* container);
public slots:
protected:
    int m_type;
};

#endif // VKABSTRACTCONTAINER_H

#ifndef VKABSTRACTCONTAINER_H
#define VKABSTRACTCONTAINER_H

#include <QObject>
#include <QDebug>
#include <QQmlEngine>
#include <QJsonObject>
#include <QJsonArray>
#include "ivkcompletable.h"

#define SET_ARG_NOCHECK(param, arg) do{ param = arg; }while(0)/*\
    do{ \
        param = arg; \
        if (!m_objectChanging) { \
            qDebug()<<"bad bad boy, inform object that you will change it, before actially changing"; \
            Q_ASSERT(0); \
        } else { \
            emit dataChanged(this); \
        } \
    }while(0)*/

#define SET_ARG(param, arg) do{ if (param != arg) { param = arg; }else{ return; } }while(0)/*\
    do{ \
        if (param != arg) { \
            SET_ARG_NOCHECK(param, arg); \
        } \
    }while(0)*/

#define UPDATE_ARG_CHECK(obj, func, sfunc, updated) \
    do{\
        if (func() != obj->func()) { \
            sfunc(obj->func()); \
            updated = true; \
        } \
    }while(0)

#define UPDATE_ARG_CHECK_SHARED(obj, func, sfunc, updated) \
    do{\
        if (*(func().data()) != *(obj->func().data())) { \
            sfunc(obj->func()); \
            updated = true; \
        } \
    }while(0)



class VKContainerUser;
class VKStorage;
class VKAbstractContainer : public IVKCompletable
{
    Q_OBJECT
public:
    explicit VKAbstractContainer(VKStorage* storage, QObject *parent = 0);
    virtual void    complete(QSharedPointer<VKContainerUser> c);
    virtual void    copyTo(VKAbstractContainer* container);

    int             type() const;
    void            beginObjectChange();
    void            endObjectChange();
    void            emitChange();
    VKStorage*      storage() const;
    bool            isValid() const;
    void            setValid();
    void            setInvalid();
    void            setValid(bool b);

    void            printOwnership();

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
    void            dataChanged(VKAbstractContainer* container);
public slots:
protected:
    int m_type;
private:
    VKStorage* m_storage;
    bool m_valid;
};

#endif // VKABSTRACTCONTAINER_H

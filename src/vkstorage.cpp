#include "vkstorage.h"
#include "vkcontainerchaticon.h"


VKStorage::VKStorage(QObject *parent) :
    QObject(parent)
{
    m_ourUserId = 0;
    //FOR DEBUG ONLY
    m_accessToken = "2c1d185c5b1a708a0f619fc1b13828d2e1286d99bf4871d6141baeea4001fa3a50fc7c86959f3110c9c04";
    m_ourUserId = 16143988;
}

VKStorage::~VKStorage()
{
    qDebug()<<"destruct storage";
    QSqlDatabase::database().close();
}

void VKStorage::init() {
    /*
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    db.setHostName("localhost");
    if (!db.open()) {
        qDebug()<< QString("Cannot open QSQLITE database with name data, errors: '%1' '%2'").arg(db.lastError().databaseText()).arg(db.lastError().driverText());
        return;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS common(param_name TEXT, param TEXT)");
    query.exec("CREATE TABLE IF NOT EXISTS users"
               "(id INTEGER PRIMARY KEY, first_name TEXT NOT NULL, second_name TEXT NOT NULL, photo_50 TEXT, photo_100 TEXT, photo_200 TEXT)");
    query.exec("CREATE TABLE IF NOT EXISTS messages"
               "(id INTEGER PRIMARY KEY, date INTEGER, incoming INTEGER, user_id REAL, read_state INTEGER, body TEXT, is_chat INTEGER, chat_id INTEGER)");
    query.exec("CREATE TABLE IF NOT EXISTS dialogs"
               "(id INTEGER PRIMARY KEY, unread_count INTEGER, is_chat INTEGER, name TEXT, icon1 TEXT, icon2 TEXT, icon3 TEXT, icon4 TEXT)");


    QSqlQuery sss;
    sss.exec("SELECT * from common");
    while (sss.next()) {
        qDebug()<<sss.value(0).toString()<<sss.value(1).toString();
    }

    query.exec("SELECT param FROM common WHERE param_name = 'user_id'");
    if (query.next()) {
        m_ourUserId = query.value(0).toString().toInt();
        qDebug()<<"ourUserId"<<m_ourUserId;
    } else {
        qDebug()<<"no our user id";
    }

    query.exec("SELECT param FROM common WHERE param_name = 'access_token'");
    if (query.next()) {
        m_accessToken = query.value(0).toString();
        qDebug()<<"accessToken"<<m_accessToken;
    } else {
        qDebug()<<"no access token";
    }*/
}



void VKStorage::addUser(QSharedPointer<VKContainerUser> user) {
    if (user->id() == ourUserId() && m_ourUser.isNull()) {
        m_ourUser = user;
        return;
    }
    Q_ASSERT(0);
    /*QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO users(id, first_name, second_name, photo_50, photo_100, photo_200) VALUES(:id, :fname, :sname, :photo50, :photo100, :photo200)");
    query.bindValue(":id", user->id());
    query.bindValue(":fname", user->firstName());
    query.bindValue(":sname", user->lastName());
    query.bindValue(":photo50",user->iconSmall());
    query.bindValue(":photo100",user->iconMedium());
    query.bindValue(":photo200",user->iconLarge());
    qDebug()<<user->iconMedium();
    query.exec();*/
}

QSharedPointer<VKContainerUser> VKStorage::getUserById(int userId) {
    if (userId == m_ourUserId) {
        return m_ourUser;
    }
    Q_ASSERT(0);
/*
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE id = :userid");
    query.bindValue(":userid",userId);
    query.exec();
    if (query.next()) {
        return VKContainerUser::fromSql(this, query);
    } else {
        Q_ASSERT(0);
        return NULL;
    }
*/
    return QSharedPointer<VKContainerUser>();
}

void VKStorage::addMessage(QSharedPointer<VKContainerMessage> message) {
    Q_UNUSED(message);
    Q_ASSERT(0);
/*    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO messages(id, date, incoming, user_id, read_state, body, is_chat, chat_id)"
                  "VALUES(:id, :date, :incoming, :userid, :readstate, :body, :ischat, :chatid)");
    query.bindValue(":id", message->msgId());
    query.bindValue(":date", message->date().toTime_t());
    query.bindValue(":incoming", message->isIncoming() ? 1 : 0);
    query.bindValue(":userid", message->user()->id());
    query.bindValue(":readstate", message->readState() ? 1 : 0);
    query.bindValue(":body", message->body());
    query.bindValue(":ischat", message->isChat() ? 1 : 0);
    query.bindValue(":chatid", message->chatId());
    query.exec();
*/
}

QSharedPointer<VKContainerMessage> VKStorage::getMessageById(int messageId) {
    Q_UNUSED(messageId);
    Q_ASSERT(0);
/*
    QSqlQuery query;
    query.prepare("SELECT * FROM messages WHERE id = :msgid");
    query.bindValue("::msgid", messageId);
    query.exec();
    if (query.next()) {
        return VKContainerMessage::fromSql(this, query);
    } else {
        Q_ASSERT(0);
        return NULL;
    }
    */
    return QSharedPointer<VKContainerMessage>();
}

void VKStorage::addDialog(QSharedPointer<VKContainerDialog> dialog) {
    Q_UNUSED(dialog);
    Q_ASSERT(0);
/*    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO dialogs(id, unread_count, is_chat, name, icon1, icon2, icon3, icon4)"
                  "VALUES(:id, :unreadcount, :ischat, :name, :icon1, :icon2, :icon3, :icon4)");
    query.bindValue(":id", dialog->chatId());
    query.bindValue(":unreadCount", dialog->unreadCount());
    query.bindValue(":ischat", dialog->isChat() ? 1 : 0);
    query.bindValue(":name", dialog->chatName());

    VKContainerChatIcon* icon = dialog->chatIcon();
    query.bindValue(":icon1",icon->get(0));
    query.bindValue(":icon2",icon->get(1));
    query.bindValue(":icon3",icon->get(2));
    query.bindValue(":icon4",icon->get(3));

    query.exec();*/
}

QSharedPointer<VKContainerDialog> VKStorage::getDialogById(int dialogId) {
    Q_UNUSED(dialogId);
    Q_ASSERT(0);
/*    QSqlQuery query;
    query.prepare("SELECT * FROM dialogs WHERE id = :dialogid");
    query.bindValue(":dialogid",dialogId);
    query.exec();
    if (query.next()) {
        return VKContainerDialog::fromSql(this, query);
    } else {
        Q_ASSERT(0);
        return NULL;
    }*/
    return QSharedPointer<VKContainerDialog>();
}

bool VKStorage::isAuthorizred() {
    return m_accessToken != "" && m_ourUserId != 0;
}

QString VKStorage::accessToken() const {
    Q_ASSERT(m_accessToken.length());
    return m_accessToken;
}

void VKStorage::setAccessToken(QString accessToken) {
    //qDebug()<<"aceesTokent set";
    //Q_ASSERT(accessToken != "");
    m_accessToken = accessToken;
    /*QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO common(param_name, param) VALUES('access_token', :token)");
    query.bindValue(":token",accessToken);
    query.exec();*/
}

bool VKStorage::userExist(int id) const {
    Q_UNUSED(id);
    Q_ASSERT(0);
   /* QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE id = :userid LIMIT 1");
    query.bindValue(":userid",id);
    query.exec();
    return query.next();*/
    return NULL;
}

void VKStorage::getHistory() {
    Q_ASSERT(0);
   /* QSqlQuery query;
    query.exec("SELECT * FROM dialogs LIMIT 20");
    QList<VKAbstractContainer*> result;
    while (query.next()) {
        result.push_back(VKContainerDialog::fromSql(this, query));
    }
    emit passToScript(result);*/
}

int VKStorage::ourUserId() const {
    Q_ASSERT(m_ourUserId);
    return m_ourUserId;
}

void VKStorage::setOurUserId(int ourUserId) {
    //qDebug()<<"set user id"<<ourUserId;
    //Q_ASSERT(ourUserId);
    m_ourUserId = ourUserId;
    /*QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO common(param_name, param) VALUES('user_id', :userid)");
    query.bindValue(":userid",QString::number(ourUserId));
    query.exec();*/
}

void VKStorage::debugPrint() {
    Q_ASSERT(0);
    /*QSqlQuery query;
    query.prepare("SELECT * FROM dialogs");
    query.exec();
    while (query.next()) {
        qDebug()<<query.value("id").toInt()<<query.value("unread_count").toInt()<<query.value("is_chat").toInt()<<query.value("name").toString();
    }*/
}

int VKStorage::getUnread(int idx) {
    Q_ASSERT(0);
    qDebug()<<"get unread"<<idx;
    Q_ASSERT(idx);
/*
    QSqlQuery query;
    query.prepare("SELECT unread_count FROM dialogs WHERE id = :dialogid");
    query.bindValue(":dialogid",idx);
    query.exec();
    if (query.next()) {
        return query.value(0).toInt();
    } else {
        qDebug()<<"no data from SELECT, may be new dialog?"<<idx;
        return 0;
    }*/

    return 0;
}



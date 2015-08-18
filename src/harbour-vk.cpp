#define VK_MAJOR_VERSION 1
#define VK_MINOR_VERSION 0
#define VK_DEVELOP_STATE "Beta"

#include <sailfishapp.h>
#include "vk.h"

#include <QtQml>
#include "debug.h"
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <execinfo.h>
#include <signal.h>
#include "vkpixmapprovider.h"
#include "vkabstractcontainer.h"
#include "vkcontainerdialog.h"
#include "vkcontainermessage.h"
#include "vkcontainermessageaction.h"
#include "vkcontaineruser.h"
#include "vkcontainerchaticon.h"
#include "qmllist.h"
#include "vkstorage.h"
#include "vkhandlerdialogs.h"
#include "vklongpollserver.h"
#include "vkcontainerattachments.h"
#include "vkcontainerphoto.h"
#include "qmlnetworkaccessmanagerfactory.h"
#include "vklpeventtype.h"
#include "vklpabstract.h"
#include "vklpmessagedelete.h"
#include "vklpmessageflagschange.h"
#include "vklpmessageflagsreset.h"
#include "vklpmessageflagsset.h"
#include "vklpmessagemarkincoming.h"
#include "vklpmessagenew.h"
#include "vklpuseroffline.h"
#include "vklpuseronline.h"
#include "vkusertypinghelper.h"

QFile global__logFile;
QString global__appVersion = QString("Sailfish %1.%2 %3").arg(VK_MAJOR_VERSION).arg(VK_MINOR_VERSION).arg(VK_DEVELOP_STATE);
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

void createLogFile() {

    QString path = QString("%1/logs").arg(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));

    QDir dir(path);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString fpath = QString("%1/sailVK_%2.log").arg(path).arg(QDateTime::currentDateTime().toString("yy_M_d_h_m_s"));

    global__logFile.setFileName(fpath);
    if(!global__logFile.open(QIODevice::WriteOnly)) {
        qDebug()<<"cannot open file"<<fpath;
    }

    qInstallMessageHandler(myMessageOutput);

    qWarning()<<"Application version"<<VK_MAJOR_VERSION<<VK_MINOR_VERSION<<VK_DEVELOP_STATE<<"log path"<<fpath;
}

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {

    QString stringType;
    switch (type) {
    case QtDebugMsg:
        stringType = "D";
        break;
    case QtWarningMsg:
        stringType = "W";
        break;
    case QtCriticalMsg:
        stringType = "C";
        break;
    case QtFatalMsg:
        stringType = "Fatal";
        break;
    default:
        stringType = "Unknown";
    }

    QString functionName(context.function);
    functionName = functionName.mid(0, functionName.indexOf('('));

    QString logString = QString("[%1] %2:%3 - %4\n")
            .arg(stringType)
            .arg(functionName)
            .arg(context.line)
            .arg(msg);

    if (global__logFile.isOpen()) {
        QTextStream stream(&global__logFile);
        stream << logString;
    }

    QTextStream stderrStream(stderr, QIODevice::WriteOnly);

    stderrStream<<logString;

    global__logFile.flush();
    if (getVK()) {
        getVK()->addDebugLogLine(logString);
    }
}

void handler(int sig) {
    void *array[10];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 10);

    // print out all the frames to stderr
    qDebug()<<"Error: signal"<<sig;
    backtrace_symbols_fd(array, size, global__logFile.handle());
    exit(sig);
}

int main(int argc, char *argv[]) {

    QCoreApplication::setApplicationName("harbour-vk");

    createLogFile();
    signal(SIGSEGV, handler);
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    qmlRegisterType<VK>("harbour.vk.VK", 1, 0, "VK");
    qmlRegisterType<VKLongPollServer>();
    qmlRegisterType<VKContainerDialog>();
    qmlRegisterType<VKContainerMessage>();
    qmlRegisterType<VKContainerMessageAction>();
    qmlRegisterType<VKContainerUser>();
    qmlRegisterType<VKAbstractContainer>();
    qmlRegisterType<VKContainerChatIcon>();
    qmlRegisterType<VKAbstractHandler>();
    qmlRegisterType<VKHandlerDialogs>();
    qmlRegisterType<VKStorage>();
    qmlRegisterType<QmlList>();
    qmlRegisterType<VKContainerAttachments>("harbour.vk.VK", 1, 0, "VKContainerAttachments");
    qmlRegisterType<VKContainerPhoto>();
    qmlRegisterType<VKLPAbstract>();
    qmlRegisterType<VKLPMessageDelete>();
    qmlRegisterType<VKLPMessageFlagsChange>();
    qmlRegisterType<VKLPMessageFlagsReset>();
    qmlRegisterType<VKLPMessageFlagsSet>();
    qmlRegisterType<VKLPMessageMarkIncoming>();
    qmlRegisterType<VKLPMessageNew>();
    qmlRegisterType<VKLPUserOffline>();
    qmlRegisterType<VKLPUserOnline>();
    qmlRegisterType<VKUserTypingHelper>("harbour.vk.VK", 1, 0, "UserTypingHelper");
    qmlRegisterUncreatableType<VKLPFlags>("harbour.vk.VK", 1, 0, "VKLPFlags","Cannot create VKLPFlags class");
    qmlRegisterUncreatableType<VKLPEventType>("harbour.vk.VK", 1, 0, "VKLPEventType","Cannot create VKLPEventType class");

    QQmlEngine* engine = view->engine();
    QObject::connect(engine, &QQmlEngine::quit, app.data(), &QGuiApplication::quit);
    engine->setNetworkAccessManagerFactory(new QmlNetworkAccessManagerFactory);

    view->setSource(SailfishApp::pathTo("qml/harbour-vk.qml"));
    view->show();

    qDebug()<<"exec";

    int result = app->exec();

    return result;
}


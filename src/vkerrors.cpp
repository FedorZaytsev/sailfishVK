#include "vk.h"


void VK::errorHandler(QJsonObject obj, VKAbstractHandler *handler) {
    if (obj.value("error_code").type() != QJsonValue::Double) {
        qFatal("Error occurred, but error_code not found or has a different type");
    }
    int error_code = int(obj.value("error_code").toDouble(-1));
    switch (error_code) {
    case VK::ERROR_UNKNOWN: {
        PendingRequest* request = new PendingRequest;
        QObject::connect(request, &PendingRequest::timeoutRequest, this, &VK::timerRequest);
        request->request(handler);
    } break;
    case VK::ERROR_APP_TURNED_OFF: {
        displayErrorMessage("VK::ERROR_APP_TURNED_OFF", VK::ERROR_HANDLER_NOTHING);
    } break;
    case VK::ERROR_UNKNOWN_METHOD: {
        displayErrorMessage("VK::ERROR_UNKNOWN_METHOD", VK::ERROR_HANDLER_NOTHING);
    } break;
    case VK::ERROR_WRONG_SIGNATURE: {
        displayErrorMessage("VK::ERROR_WRONG_SIGNATURE", VK::ERROR_HANDLER_RELOGIN);
    } break;
    case VK::ERROR_AUTHORIZATION: {
        displayErrorMessage("VK::ERROR_AUTHORIZATION", VK::ERROR_HANDLER_RELOGIN);
    } break;
    case VK::ERROR_TOO_MANY_REQUESTS: {
        displayErrorMessage("VK::ERROR_TOO_MANY_REQUESTS", VK::ERROR_HANDLER_RESTART);
    } break;
    case VK::ERROR_NO_PERMISSION: {
        displayErrorMessage("VK::ERROR_NO_PERMISSION", VK::ERROR_HANDLER_RELOGIN_INFORM);
    } break;
    case VK::ERROR_WRONG_SYNTAX: {
        displayErrorMessage("VK::ERROR_WRONG_SYNTAX", VK::ERROR_HANDLER_NOTHING);
    } break;
    case VK::ERROR_TOO_MANY_SIMILAR_REQUESTS: {
        displayErrorMessage("VK::ERROR_TOO_MANY_SIMILAR_REQUESTS", VK::ERROR_HANDLER_NOTHING);
    } break;
    case VK::ERROR_SERVER_ERROR: {
        displayErrorMessage("VK::ERROR_SERVER_ERROR", VK::ERROR_HANDLER_RESTART);
    } break;
    case VK::ERROR_TEST_MODE: {
        displayErrorMessage("VK::ERROR_TEST_MODE", VK::ERROR_HANDLER_NOTHING);
    } break;
    case VK::ERROR_CAPTHA: {
        //displayCaptha();
        //qDebug()<<"ERROR: CAPTHA";

    } break;
    case VK::ERROR_ACCESS_DENIED: {
        displayErrorMessage("VK::ERROR_ACCESS_DENIED", VK::ERROR_HANDLER_NOTHING);
    } break;
    case VK::ERROR_HTTPS_ONLY:
    case VK::ERROR_HTTPS_SAME: {
        qDebug()<<"HTTPS ONLY";
    } break;
    case VK::ERROR_REVALIDATE_USER: {
        displayErrorMessage("VK::ERROR_REVALIDATE_USER", VK::ERROR_HANDLER_RESTART);
    } break;
    case VK::ERROR_METHOD_ONLY_FOR_STANDALONE:
    case VK::ERROR_METHOD_ONLY_FOR_STANDALONE_OR_OPEN_API: {
        displayErrorMessage("VK::ERROR_METHOD_ONLY_FOR_STANDALONE", VK::ERROR_HANDLER_NOTHING);
    } break;
    case VK::ERROR_NEED_CONFORMATION: {
        qDebug()<<"Need conformation";
    } break;
    case VK::ERROR_METHOD_WRONG_PARAMS: {
        displayErrorMessage("VK::ERROR_METHOD_WRONG_PARAMS", VK::ERROR_HANDLER_NOTHING);
    } break;
    case VK::ERROR_WRONG_API_ID: {
        displayErrorMessage("VK::ERROR_WRONG_API_ID", VK::ERROR_HANDLER_NOTHING);
    } break;
    case VK::ERROR_WRONG_USER_ID: {
        displayErrorMessage("VK::ERROR_WRONG_USER_ID", VK::ERROR_HANDLER_NOTHING);
    } break;
    case VK::ERROR_WRONG_TIMESTAMP: {
        displayErrorMessage("VK::ERROR_WRONG_TIMESTAMP", VK::ERROR_HANDLER_NOTHING);
    } break;
    case VK::ERROR_ALBUM_ACCESS_DENIED: {
        displayErrorMessage("VK::ERROR_ALBUM_ACCESS_DENIED", VK::ERROR_HANDLER_NOTHING);
    } break;
    case VK::ERROR_AUDIO_ACCESS_DENIED: {
        displayErrorMessage("VK::ERROR_AUDIO_ACCESS_DENIED", VK::ERROR_HANDLER_NOTHING);
    } break;
    case VK::ERROR_GROUP_ACCESS_DENIED: {
        displayErrorMessage("VK::ERROR_GROUP_ACCESS_DENIED", VK::ERROR_HANDLER_NOTHING);
    } break;
    case VK::ERROR_ALBUM_IS_FULL: {
        displayErrorMessage("VK::ERROR_ALBUM_IS_FULL", VK::ERROR_HANDLER_NOTHING);
    } break;
    case VK::ERROR_COINS: {
        displayErrorMessage("VK::ERROR_COINS", VK::ERROR_HANDLER_NOTHING);
    } break;
    case VK::ERROR_ADVERTISEMENT_NO_PERMISSION: {
        displayErrorMessage("VK::ERROR_ADVERTISEMENT_NO_PERMISSION", VK::ERROR_HANDLER_NOTHING);
    } break;
    case VK::ERROR_ADVERTISEMENT_ERROR: {
        displayErrorMessage("VK::ERROR_ADVERTISEMENT_ERROR", VK::ERROR_HANDLER_NOTHING);
    } break;
    default: {
        qCritical()<<"Unknown error got from server, error_id ="<<error_code<<"handler"<<handler->name();
        QJsonValue errorMsg = obj.value("error_msg");
        if (errorMsg.type() == QJsonValue::String) {
            qCritical()<<"error_msg"<<errorMsg.toString();
        } else {
            qCritical()<<"no error_msg";
        }
    }
    }
}

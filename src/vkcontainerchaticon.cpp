#include "vkcontainerchaticon.h"

VKContainerChatIcon::VKContainerChatIcon(QObject *parent) :
    VKAbstractContainer(parent)
{
    m_type = eVKContainerChatIcon;
}

VKContainerChatIcon::~VKContainerChatIcon()
{
}

void VKContainerChatIcon::add(QString icon) {
    Q_ASSERT(m_icons.length() < 4);
    m_icons.append(process(icon));
    emit dataChanged(this);
}

QString VKContainerChatIcon::get(int idx) {
    if (m_icons.length() <= idx)
        return "";
    return m_icons.at(idx);
}

QString VKContainerChatIcon::process(QString icon){
    return icon;
}

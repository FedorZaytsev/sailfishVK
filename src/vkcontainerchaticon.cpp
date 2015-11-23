#include "vkcontainerchaticon.h"

VKContainerChatIcon::VKContainerChatIcon(VKStorage *storage, QObject *parent) :
    VKAbstractContainer(storage, parent)
{
    m_type = eVKContainerChatIcon;
    setValid();
}

VKContainerChatIcon::~VKContainerChatIcon()
{
}

void VKContainerChatIcon::add(QString icon) {
    Q_ASSERT(m_icons.length() < 4);
    icon = process(icon);
    if (!m_icons.contains(icon)) {
        m_icons.append(process(icon));
    }
    emit dataChanged(this);
}

QString VKContainerChatIcon::get(int idx) const {
    if (m_icons.length() <= idx)
        return "";
    return m_icons.at(idx);
}

QString VKContainerChatIcon::process(QString icon){
    return icon;
}

QList<QString> VKContainerChatIcon::icons() const {
    return m_icons;
}

bool VKContainerChatIcon::operator==(const VKContainerChatIcon &a) {

    auto icons1 = icons();
    auto icons2 = a.icons();

    if (icons1.size() != icons2.size()) {
        return false;
    }

    for (auto e: icons1) {
        if (!icons2.contains(e)) {
            return false;
        }
    }

    return true;
}

bool VKContainerChatIcon::operator!=(const VKContainerChatIcon &a) {
    return !(*this == a);
}

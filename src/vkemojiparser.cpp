#include "vkemojiparser.h"
#include "vkemojiparserdata.h"

VKEmojiParser::VKEmojiParser(QObject *parent) :
    QObject(parent)
{
}

void VKEmojiParser::parse(QString &s) {
    static bool compiled = false;

    if (!compiled) {
        precompile();
        compiled = true;
    }

    for (int idx = 0;idx<s.size();idx++) {
        for (auto e: global__precompiledBegins) {
            if ((s[idx].unicode() & 0xFF00)>>8 == e) {
                int m = match(s, idx);
                if (m) {
                    qDebug()<<"replacing";
                    idx += replace(s, idx, m);
                }
            }
        }
    }
    qDebug()<<"result"<<s;
}

int VKEmojiParser::match(QString &s, int idx) {
    for (unsigned int i=0;i<sizeof(global__emoji)/4;i++) {
        int m = match(s, idx, global__emoji + i);
        if (m) {
            return m;
        }
    }
    return 0;
}

int VKEmojiParser::match(QString &s, int idx, const uint *ptr) {

    uint emoji = *ptr;

    ushort high = (emoji & 0xFFFF0000) >> 16;
    ushort low = emoji & 0x0000FFFF;

    if (high == 0x0 && s[idx].unicode() == low) {   //if smile request only 2 bytes
        qDebug()<<toString({low});
        return 1;
    }

    if (idx + 1 < s.size() && s[idx].unicode() == high && s[idx+1].unicode() == low) {
        qDebug()<<toString({high, low});
        return 2;
    }

    return 0;

}

int VKEmojiParser::replace(QString &s, int idx, int size) {
    QVector<ushort> v;
    for (int i=0;i<size;i++) {
        v.push_back(s[idx+i].unicode());
    }
    auto sr = getLink(toString(v));
    s.replace(idx, size, sr);
    return sr.length();
}

void VKEmojiParser::precompile() {

    for (unsigned int i=0;i<sizeof(global__emoji)/4;i++) {
        auto emoji = global__emoji[i];
        uchar value = 0x0;
        if ((emoji & 0xFFFF0000) == 0x0) {
            value = (emoji & 0x0000FF00) >> 8;
        } else {
            value = (emoji & 0xFF000000) >> 24;
        }
        if (!global__precompiledBegins.contains(value)) {
            global__precompiledBegins.append(value);
        }
    }
    qDebug()<<"compiled, precompiled data is"<<global__precompiledBegins;
}

QString VKEmojiParser::toString(QVector<ushort> v) {
    QString s;
    for (auto e: v){
        s+= QString::number(e,16);
    }
    return s.toUpper();
}

QString VKEmojiParser::getLink(QString s) {
    qDebug()<<"get link"<<s;
    return QString("<img src=\"../emoji/%1.png\">").arg(s);
}


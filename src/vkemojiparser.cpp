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
                qDebug()<<"s find"<<idx<<s.size();
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
    for (unsigned int i=0;i<sizeof(global__emoji)/sizeof(global__emoji[0]);i++) {
        int m = match(s, idx, global__emoji + i);
        if (m) {
            return m;
        }
    }

    qDebug()<<QString("VKEmojiParser::match cannot find emoji smile, may be smile lost? %1 %2\n").arg(QString::number(s[idx].unicode(), 16)).arg(QString::number(s[idx+1].unicode(), 16));
    return 0;
}

int VKEmojiParser::match(QString &s, int idx, const uint64 *ptr) {

    uint emoji = *ptr;

    if (highWord(emoji) == 0x0 && s[idx].unicode() == lowWord(emoji)) {   //if smile request only 2 bytes
        qDebug()<<toString({lowWord(emoji)});
        return 1;
    }

    if (    idx + 1 < s.size() &&
            highDword(emoji)    == 0x0 &&
            s[idx].unicode()    == highWord(emoji) &&
            s[idx+1].unicode()  == lowWord(emoji))
    {                                                                       //4 byte
        qDebug()<<toString({highWord(emoji), lowWord(emoji)});
        return 2;
    }

    if (    idx + 3 < s.size() &&
            s[idx].unicode()    == highWord(highDword(emoji)) &&
            s[idx+1].unicode()  == lowWord(highDword(emoji)) &&
            s[idx+2].unicode()    == highWord(lowDword(emoji)) &&
            s[idx+3].unicode()  == lowWord(lowDword(emoji)))
    {                                                                       // 8 bytes
        qDebug()<<toString({highWord(highDword(emoji)), lowWord(highDword(emoji)), highWord(lowDword(emoji)), lowWord(lowDword(emoji))});
        return 4;
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

    for (unsigned int i=0;i<sizeof(global__emoji)/sizeof(global__emoji[0]);i++) {
        auto emoji = global__emoji[i];
        uchar value = 0x0;
        if (highDword(emoji) == 0x0 && highWord(emoji) == 0x0) {        //2 byte emoji
            value = (emoji & 0x0000FF00) >> 8;
        } else if (highDword(emoji) == 0x0) {
            value = (emoji & 0xFF000000) >> 24;
        } else {
            value = (emoji & 0xFF00000000000000) >> 56;
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

ushort VKEmojiParser::highWord(uint64 n) {
    return (n & 0xFFFF0000) >> 16;
}

ushort VKEmojiParser::lowWord(uint64 n) {
    return n & 0x0000FFFF;
}

uint VKEmojiParser::highDword(uint64 n) {
    return (n & 0xFFFFFFFF00000000) >> 32;
}

uint VKEmojiParser::lowDword(uint64 n) {
    return n & 0x00000000FFFFFFFF;
}



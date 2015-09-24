#ifndef VKEMOJIPARSER_H
#define VKEMOJIPARSER_H

#include <QObject>

typedef unsigned long long uint64;

class VKEmojiParser : public QObject
{
    Q_OBJECT
public:
    explicit VKEmojiParser(QObject *parent = 0);

    void parse(QString &s);
    int match(QString &s, int idx);
    int match(QString &s, int idx, const uint64 *ptr);
    int replace(QString &s, int idx, int size);

private:
    void precompile();
    QString toString(QVector<ushort> v);
    QString getLink(QString s);
    ushort highWord(uint64 n);
    ushort lowWord(uint64 n);
    uint highDword(uint64 n);
    uint lowDword(uint64 n);
signals:

public slots:
private:
};

#endif // VKEMOJIPARSER_H

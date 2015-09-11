#ifndef VKEMOJIPARSER_H
#define VKEMOJIPARSER_H

#include <QObject>

class VKEmojiParser : public QObject
{
    Q_OBJECT
public:
    explicit VKEmojiParser(QObject *parent = 0);

    void parse(QString &s);
    int match(QString &s, int idx);
    int match(QString &s, int idx, const uint *ptr);
    int replace(QString &s, int idx, int size);

private:
    void precompile();
    QString toString(QVector<ushort> v);
    QString getLink(QString s);
signals:

public slots:
private:
};

#endif // VKEMOJIPARSER_H

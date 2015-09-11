#ifndef VKTEXTWRAP_H
#define VKTEXTWRAP_H

//Class used for implementing custom word wrap, becouse original Qt wrap mode
//works incorrectly with images inserted in text via html tags

#include <QObject>
#include <QFontMetricsF>

class VKTextWrap : public QObject
{
    Q_OBJECT
public:
    explicit VKTextWrap(QObject *parent = 0);

    Q_INVOKABLE void setFont(QString s, int size);
    Q_INVOKABLE QString process(QString s, float width);

    QFontMetricsF& metrics() {return *m_metrics;}
private:
    int imgHtmlTag(QString &s, int idx, qreal &elWidth);
    int getImgHtmlWidth(QString &s, int idx, qreal &width);
    bool needNewLine(qreal w, qreal elWidth, qreal maxWidth);
    void processWord(QString &s, int &lastPosition, int &i, qreal &w, qreal width, qreal symbolSize);
signals:

public slots:
private:
    QFontMetricsF *m_metrics;
};

#endif // VKTEXTWRAP_H

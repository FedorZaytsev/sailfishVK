#include "vktextwrap.h"

VKTextWrap::VKTextWrap(QObject *parent) :
    QObject(parent)
{
    m_metrics = nullptr;
}

void VKTextWrap::setFont(QString s, int size) {
    qDebug()<<s<<size;
    m_metrics = new QFontMetricsF(QFont(s, size));
}

QString VKTextWrap::process(QString s, float width) {

    qDebug()<<"string"<<s<<"width"<<width;

    Q_ASSERT(m_metrics);

    qreal w = 0.0f;
    qreal spaceWidth = metrics().width(' ');

    int lastPosition = 0;
    int i;
    for (i=0;i<s.size();i++) {
        qDebug()<<"checking symbol"<<s[i]<<"at position"<<i<<metrics().width(s[i]);
        qreal imgWidth = 0.0f;
        int count = imgHtmlTag(s, i, imgWidth);
        if (count) {
            qDebug()<<"img html tag found";
            if (needNewLine(w, imgWidth, width)) {
                qDebug()<<"requesting newline"<<w<<imgWidth;
                w = 0;
                s.insert(i,'\n');
                i += 1;
            }
            i += count;
            w += imgWidth;
            lastPosition = i+1;
        } else if (s[i].isSpace()) {
            qDebug()<<"space found at"<<i<<"s ="<<s.mid(i, 10);

            processWord(s, lastPosition, i, w, width, spaceWidth);
        }
    }
    qDebug()<<"processing last word";
    processWord(s, lastPosition, i, w, width, 0);
    return s;
}

void VKTextWrap::processWord(QString &s, int &lastPosition, int &i, qreal &w, qreal width, qreal symbolSize) {
    auto wordWidth = metrics().width(s.midRef(lastPosition, i-lastPosition).toString());
    qDebug()<<"word width"<<wordWidth;

    if (!needNewLine(w, wordWidth + symbolSize, width)) {   //if word + space symbol is fitting the width
        qDebug()<<"fitting line w ="<<w<<"adding"<<wordWidth + symbolSize;
        w += wordWidth + symbolSize;
    } else if (!needNewLine(w, wordWidth, width)) {         //if only additional word if fitting the width, but space symbol not
        qDebug()<<"only word fits andding newline at space position";
        w = .0f;
        s[i] = '\n';
    } else if (!needNewLine(0, wordWidth, width)) {         //if word is too large to put it in this line;
        qDebug()<<"word doesn't fit this line, requesting newline";
        w = wordWidth;
        s[lastPosition-1] = '\n';
    } else {                                                //if word is too large to put it in one line
        qDebug()<<"word is too large"<<lastPosition<<i;
        qreal _w = 0.0f;
        for (int idx=lastPosition;idx<i-2;idx++) {
            _w += metrics().width(s[idx]);
            if (_w + metrics().width(s[idx+1]) > width) {
                qDebug()<<"requesting newline at position"<<idx;
                s.insert(idx,'\n');
                i++;
                idx++;
                _w = 0.0f;

            }
        }
    }
    if (i+1 < s.size() && !s[i+1].isSpace()) {
        qDebug()<<"updated lastPosition: prev"<<lastPosition<<"new"<<i+1;
        lastPosition = i+1;
    }
    qDebug()<<"finish";
}

QStringRef skipSpace(const QStringRef &s) {
    for (int i=0;i<s.size();i++) {
        if (!s.at(i).isSpace()) {
            return s.mid(i);
        }
    }
    return QStringRef();
}

int VKTextWrap::imgHtmlTag(QString &s, int idx, qreal &elWidth) {
    if (s[idx] == '<') {

        qDebug()<<"html tag found at"<<idx<<"in string"<<s.mid(0,10);

        auto idxLast = s.indexOf('>',idx);
        auto sMid = s.midRef(idx+1, idxLast-idx);


        //skip white space
        sMid = skipSpace(sMid);

        //check is image
        if (sMid.indexOf("img") != 0 || sMid.indexOf("width") == -1) {
            qDebug()<<"I think this is not img tag"<<sMid<<"becouse"<<(sMid.indexOf("img")!=0)<<(sMid.indexOf("width") == -1);
            return 0;
        }

        sMid = sMid.mid(sMid.indexOf("width") + QString("width").length());

        sMid = skipSpace(sMid);

        if (sMid.at(0) != '=') {
            qDebug()<<"We don't have '='"<<sMid;
            return 0;
        }

        sMid = skipSpace(sMid.mid(1));

        if (sMid.at(0) == '"') {
            sMid = sMid.mid(1);
        }

        int i;
        for (i=0;i<sMid.size() && sMid.at(i).isDigit();i++) {}

        bool ok = false;
        int width = sMid.mid(0, i).toInt(&ok);
        Q_ASSERT(ok);

        elWidth = width;

        qDebug()<<"found img tag with width"<<width<<"and size"<<idxLast - idx;

        return idxLast - idx;
    }

    return 0;
}

bool VKTextWrap::needNewLine(qreal w, qreal elWidth, qreal maxWidth) {
    return w + elWidth > maxWidth;
}


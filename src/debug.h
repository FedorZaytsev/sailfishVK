#ifndef DEBUG_H
#define DEBUG_H


#ifdef QT_NO_DEBUG
    #define X_ASSERT(cond) ((!(cond)) ? qDebug()<<"ERROR:\n"<<"File:"<<__FILE__<<"\nLine"<<__LINE__<<"\nDescription"<<(#cond) : qt_noop())
#else
    #define X_ASSERT(cond) Q_ASSERT(cond)
#endif

#endif // DEBUG_H

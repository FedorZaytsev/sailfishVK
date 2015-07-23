#ifndef DEBUG_H
#define DEBUG_H

#include <QDebug>

/*#ifdef QT_NO_DEBUG
    #define X_ASSERT(cond) ((!(cond)) ? qDebug()<<"ERROR:\n"<<"File:"<<__FILE__<<"\nLine"<<__LINE__<<"\nDescription"<<(#cond) : qt_noop())
#else
    #define X_ASSERT(cond) Q_ASSERT(cond)
#endif
*/

void vk_assert(const char* cond, const char* file, int line);

#if defined(Q_ASSERT)
#undef Q_ASSERT
#endif

#if defined(QT_NO_DEBUG) && !defined(QT_FORCE_ASSERTS)
#  define Q_ASSERT(cond) qt_noop()
#else
#  if defined(VK_DEBUG)
#    define Q_ASSERT(cond) ((!(cond)) ? qt_assert(#cond,__FILE__,__LINE__) : qt_noop())
#  else
#    define Q_ASSERT(cond) ((!(cond)) ? vk_assert(#cond,__FILE__,__LINE__) : qt_noop())
#  endif
#endif

#endif // DEBUG_H

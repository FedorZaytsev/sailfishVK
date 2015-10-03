#ifndef VKSTORAGECOMPARATOR_H
#define VKSTORAGECOMPARATOR_H

#include <QDateTime>
#include <QSharedPointer>

class VKStorageComparator
{
public:
    
    template< typename T1, typename T2>
    bool operator() (T1 const& t1, T2 const& t2);
};

template< typename T1, typename T2>
bool VKStorageComparator::operator()(const T1 &t1, const T2 &t2)
{
    return t1->date() > t2->date();
}

#endif // VKSTORAGECOMPARATOR_H

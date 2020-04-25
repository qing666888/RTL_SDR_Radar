#include <QDebug>
#include "Logger/Logger.h"

Logger::Logger(int size) : _size(size)
{
}

Logger::~Logger()
{

}

void Logger::push(const QString &text, TypeLog type)
{
    Q_UNUSED(type)
    QMutexLocker locker(&_mutex);
    if(_stack.size() < _size)
        _stack.push(text);
}

QString Logger::pop()
{
    QMutexLocker locker(&_mutex);
    if(!_stack.isEmpty())
        return _stack.pop();
    else
        return QString();
}

bool Logger::isEmpty()
{
    QMutexLocker locker(&_mutex);
    return _stack.isEmpty();
}

int32_t Logger::size()
{
    return _size;
}

int32_t Logger::countMsg()
{
    QMutexLocker locker(&_mutex);
    return _stack.size();
}



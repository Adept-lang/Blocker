#include "exampleobject.h"
#include <QDebug>

ExampleObject::ExampleObject(QObject *parent) :
    QObject(parent),
    m_message(""),
    m_message_2("")
{

}

bool ExampleObject::running() const
{
    return m_running;
}

QString ExampleObject::message() const
{
    return m_message;
}

QString ExampleObject::message_2() const
{
    return m_message_2;
}

// Самый важный метод, в котором будет выполняться "полезная" работа объекта
void ExampleObject::run()
{
    count = 0;
    // Переменная m_running отвечает за работу объекта в потоке.
    // При значении false работа завершается
    while (m_running)
    {
        count++;
        emit sendMessage(m_message); // Высылаем данные, которые будут передаваться в другой поток
        qDebug() << m_message << " " << m_message_2 << " " << count;
    }
    emit finished();
}

void ExampleObject::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(running);
}

void ExampleObject::setMessage(QString message)
{
    if (m_message == message)
        return;

    m_message = message;
    emit messageChanged(message);
}

void ExampleObject::setMessage_2(QString message_2)
{
    if (m_message_2 == message_2)
        return;

    m_message_2 = message_2;
    emit message_2Changed(message_2);
}

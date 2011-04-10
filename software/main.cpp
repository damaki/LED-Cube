#include <QtGui/QApplication>
#include "mainwindow.h"

#include <iostream>

#include <windef.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "effect_base.h"

void service_thread(boost::asio::io_service *pIO)
{
    for (;;)
    {
        try
        {
            pIO->run();
            break;
        }
        catch (...)
        {
            // Erm... what to do?
        }
    }
}

int main(int argc, char *argv[])
{
    boost::asio::io_service io;
    boost::asio::io_service::work work(io);
    boost::thread io_thread(service_thread, &io);

    QApplication a(argc, argv);
    MainWindow w(io);
    w.show();
    const int result = a.exec();

    io.stop();
    io_thread.join();

    return result;
}

#include <gtest/gtest.h>

#include <QApplication>
#include <QDebug>

#define private public

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    qDebug() << "start dde-clipboardloader test cases ..............";
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    qDebug() << "end dde-clipboardloader test cases ..............";
    return ret;
}

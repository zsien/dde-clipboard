#include <gtest/gtest.h>

#include "itemwidget.h"
#include "itemdata.h"

#include <QFile>

class TstItemWidget : public testing::Test
{
public:
    void SetUp() override
    {
        QByteArray buf;

        // 复制文件时产生的数据，用于测试
        QFile file1(":/qrc/file.buf");
        if (!file1.open(QIODevice::ReadOnly)) {
            qWarning() << "file open failed";
            file1.close();
        } else {
            buf = file1.readAll();
        }
        m_fileData = new ItemData(buf);

        // 复制文本时产生的数据，用于测试
        QFile file2(":/qrc/text.buf");
        if (!file2.open(QIODevice::ReadOnly)) {
            qWarning() << "file open failed";
            file2.close();
        } else {
            buf = file2.readAll();
        }
        m_textData = new ItemData(buf);

        // 复制图片（非图片，图片文件属于文件类型）时产生的数据，用于测试
        QFile file3(":/qrc/image.buf");
        if (!file3.open(QIODevice::ReadOnly)) {
            qWarning() << "file open failed";
            file3.close();
        } else {
            buf = file3.readAll();
        }
        m_imageData = new ItemData(buf);
    }

    void TearDown() override
    {
        delete m_fileData;
        delete m_textData;
        delete m_imageData;
    }

    QPointer<ItemData> m_fileData;
    QPointer<ItemData> m_textData;
    QPointer<ItemData> m_imageData;
};

TEST_F(TstItemWidget, coverageTest)
{
    ItemWidget w(m_fileData);

    QPixmap testPix(":/qrc/testPix.png");

    FileIconData data;
    w.setThumnail(testPix);
    w.setThumnail(data);
    w.setFileIcon(testPix);
    w.setFileIcon(data);

    QList<QPixmap> list;
    list << testPix;
    list << testPix;
    w.setFileIcons(list);

    ASSERT_EQ(w.itemData()->urls().first().toLocalFile(), "/home/diesel/Desktop/截图录屏_deepin-terminal_20201114221419.png");
}

TEST_F(TstItemWidget, textTest)
{
    ItemWidget w(m_textData);
    ASSERT_TRUE(w.text().contains("1234567890abcdefg"));
}

TEST_F(TstItemWidget, propertyTest)
{
    ItemWidget w(m_imageData);

    QString text = "abcdefghijklmnopqrstuvwxyz";
    w.setText(text, QString::number(text.length()));
    w.setAlpha(120);
    w.setOpacity(0.5);
}

TEST_F(TstItemWidget, method_getCornerGeometryList_Test)
{
    QRectF rectF(0, 0, 100, 100);
    QSizeF sizeF(50, 50);

    ASSERT_EQ(ItemWidget::getCornerGeometryList(rectF, sizeF).size(), 4);
}

TEST_F(TstItemWidget, method_getIconPixmap_Test)
{
    ASSERT_TRUE(ItemWidget::getIconPixmap(QIcon::fromTheme("close"), QSize(24, 24), 1.25, QIcon::Normal, QIcon::On).isNull());
}

TEST_F(TstItemWidget, method_GetFileIcon_Test)
{
    ASSERT_TRUE(ItemWidget::GetFileIcon("123.png").isNull());//不存在的图片
}

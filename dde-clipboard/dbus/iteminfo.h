#ifndef ITEMINFO_H
#define ITEMINFO_H
#include <QDBusArgument>
#include <QDateTime>
#include <QUrl>

#include "constants.h"

typedef struct {
    QStringList cornerIconList;
    QIcon fileIcon;
} FileIconData;

enum DataType {
    Unknown,
    Text,
    Image,
    File
};

struct ItemInfo {
    QMap<QString, QByteArray> m_formatMap;
    DataType m_type = Unknown;
    QList<QUrl> m_urls;
    bool m_hasImage = false;
    QVariant m_variantImage;
    QSize m_pixSize;
    bool m_enable;
    QString m_text;
    QDateTime m_createTime;
    QList<FileIconData> m_iconDataList;
};

Q_DECLARE_METATYPE(ItemInfo)

#endif //ITEMINFO_H


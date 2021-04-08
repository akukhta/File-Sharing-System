#include "GUINodeItem.h"

//const QIcon GUINodeItem::iconsArr[7] =
//{
//    QIcon("Resources/Node.png"),
//    QIcon("Resources/Bin.png"),
//    QIcon("Resources/Text.png"),
//    QIcon("Resources/Mus.png"),
//    QIcon("Resources/Vid.png"),
//    QIcon("Resources/Code.png"),
//    QIcon("Resources/Pic.png")
//};


GUINodeItem::GUINodeItem(QTreeWidget *widget, std::string const &name, std::string const &deletingDate, GUINodeItemType type)
    : type(type)
{
    rootItem = new QTreeWidgetItem(widget);
    rootItem->setText(2, QString::fromStdString(name));

    if (type == GUINodeItemType::UpCom)
        return;

    rootItem->setText(3, QString::fromStdString(deletingDate));

    if (type == GUINodeItemType::Node)
    {
        rootItem->setIcon(1, iconsArr[Node]);
    }
    else
    {
        rootItem->setIcon(1, filter(name));
    }
    //rootItem->setForeground(2,QBrush(QPixmap("Resourses/Test.jpeg")));
    rootItem->setCheckState(0, Qt::Unchecked);

//    if (!itemsIsLoaded)
//    {
//        rootItem->addChild(new QTreeWidgetItem());
//    }

//    else
//    {
//        for (auto file : fileNames)
//        {
//            auto item = new QTreeWidgetItem(rootItem.get());
//            item->setText(1,QString::fromStdString(file));
//            item->setText(2,QString::fromStdString(deletingDate));
//            item->setCheckState(0, Qt::Unchecked);
//        }
//    }

    //return std::move(rootItem);
}

QIcon GUINodeItem::filter(const std::string &name)
{
    std::string ext = name.substr(name.find_last_of(".") + 1);

    for (auto & ch : ext)
        ch = tolower(ch);

    //Format for audio files
    if (ext == "mp3" || ext == "ogg" || ext == "pcm" || ext == "wav"
        || ext == "aiff" || ext == "aac" || ext == "wma" || ext == "flac"
        || ext == "alac" || ext == "wma")
        return iconsArr[Mus];

    //Format for text and books files
    else if (ext == "txt" || ext == "rtf" || ext == "doc" || ext == "docx"  ||
        ext == "pdf" || ext == "odt" || ext == "fb2" || ext == "epub" ||
        ext == "mobi" || ext == "djvu")
        return iconsArr[Text];

    //Format for video files
    else if (ext == "mkv" || ext == "mp4" || ext == "webm" || ext == "3gp"
        || ext == "mpeg" || ext == "wmv" || ext == "avi" || ext == "mpg"
        || ext == "mpeg4" || ext == "mpg2")
        return iconsArr[Vid];

    //Format for code files
    else if (ext == "php" || ext == "c" || ext == "cpp" || ext == "h" || ext == "hpp"
        || ext == "cs" || ext == "erb" || ext == "go" || ext == "ipynb" ||
        ext == "py" || ext == "pyc" || ext == "pyo" || ext == "r" || ext == "rb"
        || ext == "rs" || ext == "sh")
        return iconsArr[Code];

    //Format for image files
    else if (ext == "gif" || ext == "jpeg" || ext == "bmp" || ext == "png"
        || ext == "wmg")
        return iconsArr[Pic];

    //Other - probably just binaries files
    else
        return iconsArr[Bin];
}

QTreeWidgetItem* GUINodeItem::getGUIItem()
{
    return rootItem;
}

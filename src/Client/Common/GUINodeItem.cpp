#include "GUINodeItem.h"

std::unique_ptr<QTreeWidgetItem> GUINodeItem::getGUIItem(QTreeWidget *widget, std::string const &name, std::string const &deletingDate, GUINodeItemType type)
{
    std::unique_ptr<QTreeWidgetItem> rootItem = std::make_unique<QTreeWidgetItem>(widget);
    rootItem->setText(2, QString::fromStdString(name));
    rootItem->setText(3, QString::fromStdString(deletingDate));

    if (type == GUINodeItemType::Node)
    {
        rootItem->setIcon(1, iconsArr[Node]);
    }
    else
    {
        rootItem->setIcon(1, )
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

    return std::move(rootItem);
}

const QIcon &GUINodeItem::filter(const std::string &name)
{
    std::string ext = name.substr(name.find_last_of(".") + 1);
}

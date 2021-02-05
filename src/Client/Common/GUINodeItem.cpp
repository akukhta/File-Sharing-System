#include "GUINodeItem.h"

GUINodeItem::GUINodeItem(Node const & node) : Node(node)
{ };

void GUINodeItem::addFiles(std::vector<std::string> const & files)
{
//    if (!itemsIsLoaded)
//        items.erase(items.begin());

//    for (auto const & file : files)
//        fileNames.push_back(file);

//    for (auto const & file : fileNames)
//    {
//        items.push_back(new QTreeWidgetItem);
//        (*items.end())->setText(0,QString::fromStdString(file));
//        (*items.end())->setText(1,QString::fromStdString(deletingDate));
//        rootItem->addChild((*items.end()));
//    }
}

std::unique_ptr<QTreeWidgetItem> GUINodeItem::getGUIItem(QTreeWidget *widget)
{
    std::unique_ptr<QTreeWidgetItem> rootItem = std::make_unique<QTreeWidgetItem>(widget);
    rootItem->setText(0, QString::fromStdString(nodeID));
    rootItem->setText(1, QString::fromStdString(deletingDate));

    if (!itemsIsLoaded)
    {
        rootItem->addChild(new QTreeWidgetItem());
    }

    else
    {
        for (auto file : fileNames)
        {
            auto item = new QTreeWidgetItem(rootItem.get());
            item->setText(0,QString::fromStdString(file));
            item->setText(1,QString::fromStdString(deletingDate));
        }
    }

    return std::move(rootItem);
}

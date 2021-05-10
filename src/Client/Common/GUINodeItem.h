#pragma once
#include <vector>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QIcon>
#include <memory>
#include <sstream>
#include <iomanip>

class GUINodeItem
{
public:
    enum class GUINodeItemType : char {Node, File, UpCom};
    GUINodeItem(QTreeWidget *widget, std::string const &name, std::string const &deletingDate, GUINodeItemType type = GUINodeItemType::Node);
    QTreeWidgetItem* getGUIItem();
    bool isGotten = false;

private:

    enum Icons {Node, Bin, Text, Mus, Vid, Code, Pic, Up};

    const QIcon iconsArr[8] =
    {
        QIcon("Resources/Node.png"),
        QIcon("Resources/Bin.png"),
        QIcon("Resources/Text.png"),
        QIcon("Resources/Mus.png"),
        QIcon("Resources/Vid.png"),
        QIcon("Resources/Code.png"),
        QIcon("Resources/Pic.png"),
        QIcon("Resources/Up.png")
    };

    QIcon filter(std::string const &name);
    QTreeWidgetItem* rootItem;
    GUINodeItemType type;
};

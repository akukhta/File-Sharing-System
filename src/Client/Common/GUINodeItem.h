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
    enum class GUINodeItemType : bool {Node = false, File = true};
    static std::unique_ptr<QTreeWidgetItem> getGUIItem(QTreeWidget *widget, std::string const &name, std::string const &deletingDate, GUINodeItemType type = GUINodeItemType::Node);
private:
    enum Icons {Node, Bin, Doc, Mus, Vid, Exe};
    static QIcon iconsArr[];
    QIcon const & filter(std::string const &name);
};

static QIcon iconsArr[] = {
    QIcon("Resources/Node.png"),
    QIcon("Resources/Node.png"),
    QIcon("Resources/Node.png"),
    QIcon("Resources/Node.png"),
    QIcon("Resources/Node.png"),
    QIcon("Resources/Node.png")
};


#pragma once
#include <vector>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <memory>
#include <sstream>
#include <iomanip>
#include "Common/Node.h"

class GUINodeItem : protected Node
{
public:
    GUINodeItem(Node const & node);
    void addFiles(std::vector<std::string> const & files);
    std::unique_ptr<QTreeWidgetItem> getGUIItem(QTreeWidget *widget);
};



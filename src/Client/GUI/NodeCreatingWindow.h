#pragma once
#include <QDialog>
#include <vector>
#include <QFileDialog>
#include <QListWidgetItem>
#include <chrono>
#include <filesystem>

namespace Ui {
class NodeCreatingWindow;
}

class NodeCreatingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NodeCreatingWindow(QWidget *parent = nullptr);
    ~NodeCreatingWindow();
    std::vector<QString> getFileNames();
    long long getLifeTimeInMins();

private slots:
    void on_selectDirectoryBtn_clicked();

    void on_filesList_itemClicked(QListWidgetItem *item);

    void on_createBtn_clicked();

private:
    Ui::NodeCreatingWindow *ui;
    QString directoryPath;
    std::vector<QString> fileNames;
    void updateList();
    const QStringList lifeTimes = {"1 minute", "5 minutes" ,"30 minutes", "1 hour", "3 hours", "6 hours", "12 hours", "24 hours"};
};


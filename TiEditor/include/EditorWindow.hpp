#ifndef EDITORWINDOW_HPP
#define EDITORWINDOW_HPP

#include <QMainWindow>
#include <QFileSystemModel>
#include <QSettings>
#include <TiCCompile.hpp>

namespace Ui {
class EditorWindow;
}

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorWindow(QWidget *parent = 0);
    ~EditorWindow();
    
    void save();
    int getTabOfItem(const QString &path);
    void openFile(const QString &path);
private Q_SLOTS:
    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_actionFonz_triggered();

    void on_actionQuit_triggered();
    
    void on_actionNew_triggered();
    
    void on_actionSave_triggered();
    
    void on_actionCompile_triggered();

    void on_actionSet_main_directory_triggered();
    
    void on_actionSet_toolkit_triggered();
    
    void on_editorTab_closeTab(int index);

private:
    Ui::EditorWindow *ui;

    QFileSystemModel *m_fileSystemModel;
    TiCCompile *m_compileWindow = nullptr;
};

#endif // EDITORWINDOW_HPP

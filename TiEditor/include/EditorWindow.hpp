#ifndef EDITORWINDOW_HPP
#define EDITORWINDOW_HPP

#include <QMainWindow>
#include <QFileSystemModel>
#include <TiHighlighter.hpp>
#include <QSettings>

namespace Ui {
class EditorWindow;
}

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorWindow(QWidget *parent = 0);
    ~EditorWindow();

private Q_SLOTS:
    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_actionFonz_triggered();

    void on_actionQuit_triggered();
    
    void on_actionNew_triggered();
    
    void on_actionSave_triggered();

    void on_actionSet_main_directory_triggered();

private:
    Ui::EditorWindow *ui;

    QFileSystemModel *m_fileSystemModel;
    TiHighlighter *m_highlighter;
};

#endif // EDITORWINDOW_HPP

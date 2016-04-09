#include <EditorWindow.hpp>
#include <ui_EditorWindow.h>

#include <QDebug>
#include <QDir>
#include <CodeEditor.hpp>
#include <QFontDialog>
#include <QFontMetrics>
#include <QFileDialog>


EditorWindow::EditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorWindow)
{
    QCoreApplication::setApplicationName("TiSuite");
    QCoreApplication::setOrganizationDomain("maximaximal.com");
    QCoreApplication::setOrganizationName("maximaximal");

    ui->setupUi(this);

    QSettings settings;
    settings.beginGroup("EditorWindow");

    QString projectDir = settings.value("project-dir", QDir::homePath()).toString();

    m_fileSystemModel = new QFileSystemModel();
    m_fileSystemModel->setRootPath(projectDir);
    ui->treeView->setModel(m_fileSystemModel);
    ui->treeView->setRootIndex(m_fileSystemModel->index(projectDir));
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    
    ui->editorTabs->setTabsClosable(true);

    settings.endGroup();
    
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_triggered()), Qt::UniqueConnection);
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_triggered()), Qt::UniqueConnection);
    connect(ui->actionCompile, SIGNAL(triggered()), this, SLOT(on_actionCompile_triggered()), Qt::UniqueConnection);
    connect(ui->editorTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(on_editorTab_closeTab(int)), Qt::UniqueConnection);
    connect(ui->actionSet_toolkit, SIGNAL(triggered()), this, SLOT(actionSet_toolkit()), Qt::UniqueConnection);
}

EditorWindow::~EditorWindow()
{
    if(m_compileWindow)
        delete m_compileWindow;
    
    delete m_fileSystemModel;
    delete ui;
}
void EditorWindow::save()
{
    for(int i = 0; i < ui->editorTabs->count(); ++i)
    {
        CodeEditor *editor = dynamic_cast<CodeEditor*>(ui->editorTabs->widget(i));
        if(editor) {
            editor->save();
        }
    }
}
int EditorWindow::getTabOfItem(const QString &path)
{
    int i = 0;
    for(i = 0; i < ui->editorTabs->count(); ++i)
    {
        CodeEditor *editor = dynamic_cast<CodeEditor*>(ui->editorTabs->widget(i));
        if(editor) {
            if(editor->filepath() == path) {
                return i;
            }
        }
    }
    return -1;
}
void EditorWindow::openFile(const QString &path)
{
    CodeEditor *editor = new CodeEditor(ui->editorTabs);
    editor->setFilepath(path);
    QStringList strList = path.split(QDir::separator());
    ui->editorTabs->addTab(editor, strList.back());
    
    connect(editor, &QsciScintilla::textChanged, this, [editor, strList, this]() {
        ui->editorTabs->setTabText(ui->editorTabs->currentIndex(), 
                                   strList.back() + "*");
    });
}
void EditorWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString path = index.data(QFileSystemModel::FilePathRole).toString();
    
    if(m_fileSystemModel->isDir(index)) {
        return;
    }

    // Check if the item is already in one of the tabs. 
    int id = getTabOfItem(path);
    if(id != -1) {
        ui->editorTabs->setCurrentIndex(id);
        return;
    }
    
    QFile file(path);
    if(!file.exists()) {
        //Error!
        return;
    }
 
    openFile(path);
}

void EditorWindow::on_actionFonz_triggered()
{
    QSettings settings;
    settings.beginGroup("EditorWindow");
    bool ok;
    QFont font = QFontDialog::getFont(&ok);
    if(ok) {
        settings.setValue("font", font);
    }
    settings.endGroup();
}

void EditorWindow::on_actionNew_triggered()
{
    save();
    QString path = QFileDialog::getSaveFileName(this, tr("New File"), m_fileSystemModel->rootPath() + "/Program.82c", tr("82c Files (*.82c)"));
    if(path != "") {
        openFile(path);
    }
}
void EditorWindow::on_actionCompile_triggered()
{
    if(ui->editorTabs->currentWidget() != nullptr) {
        if(!m_compileWindow) {
            m_compileWindow = new TiCCompile();
        }
        m_compileWindow->show();
        
        QSettings settings;
        settings.beginGroup("EditorWindow");
        m_compileWindow->compile(static_cast<CodeEditor*>(ui->editorTabs->currentWidget())->filepath(), 
                        settings.value("toolkit").toString());
    }
}

void EditorWindow::on_actionSave_triggered()
{
    CodeEditor *editor = dynamic_cast<CodeEditor*>(ui->editorTabs->currentWidget());
    if(editor) {
        editor->save();
        QStringList strList = editor->filepath().split(QDir::separator());
        ui->editorTabs->setTabText(ui->editorTabs->currentIndex(), strList.back());
    }
}

void EditorWindow::on_actionQuit_triggered()
{
    close();
}
void EditorWindow::on_actionSet_toolkit_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this);
    QSettings settings;
    settings.beginGroup("EditorWindow");
    settings.setValue("toolkit", dir);
    settings.endGroup();
}
void EditorWindow::on_actionSet_main_directory_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this);
    QSettings settings;
    settings.beginGroup("EditorWindow");
    settings.setValue("project-dir", dir);
    settings.endGroup();
    m_fileSystemModel->setRootPath(dir);
    ui->treeView->setRootIndex(m_fileSystemModel->index(dir));
}
void EditorWindow::on_editorTab_closeTab(int index)
{  
    if(index != -1) {
        QWidget *tab = ui->editorTabs->widget(index);
        ui->editorTabs->removeTab(index);
        
        delete tab;
        tab = 0;
    }
}

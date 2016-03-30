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

    QString font;


    font = settings.value("font", "Monospace").toString();


    ui->textEdit->setFont(QFont(font));
    ui->textEdit->setStyleSheet("QPlainTextEdit {"
                                "background-color: #fdf6e3;"
                                "color: #073642;"
    "}");

    const int tabStop = 4;  // 4 characters

    QFontMetrics metrics(ui->textEdit->font());
    ui->textEdit->setTabStopWidth(tabStop * metrics.width(' '));

    m_highlighter = new TiHighlighter(ui->textEdit->document());

    settings.endGroup();
    
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_triggered()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_triggered()));
}

EditorWindow::~EditorWindow()
{
    delete m_fileSystemModel;
    delete m_highlighter;
    delete ui;
}

void EditorWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString path = index.data(QFileSystemModel::FilePathRole).toString();
    QFile *file = new QFile(path);

    if(!m_fileSystemModel->isDir(index)) {
        file->open(QFile::ReadWrite | QFile::Text | QFile::Truncate);
        ui->textEdit->document()->setPlainText(file->readAll());
        ui->textEdit->setFilepath(path);
        ui->textEdit->setFile(file);
    }
}

void EditorWindow::on_actionFonz_triggered()
{
    QSettings settings;
    settings.beginGroup("EditorWindow");
    bool ok;
    QFont font = QFontDialog::getFont(&ok, ui->textEdit->font());
    if(ok) {
        ui->textEdit->setFont(font);
        settings.setValue("font", font);
    }
    settings.endGroup();
}

void EditorWindow::on_actionNew_triggered()
{
    if(ui->textEdit->changed()) {
        ui->textEdit->save();
    }
    QString path = QFileDialog::getSaveFileName(this, tr("New File"), m_fileSystemModel->rootPath() + "/Program.82c", tr("82c Files (*.82c)"));
    if(path != "") {
        QFile *file = new QFile(path);
        
        file->open(QFile::ReadWrite | QFile::Text | QFile::Truncate);
        
        ui->textEdit->setFile(file);
        ui->textEdit->setFilepath(path);
    }
}

void EditorWindow::on_actionSave_triggered()
{
    ui->textEdit->save();
}

void EditorWindow::on_actionQuit_triggered()
{
    close();
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

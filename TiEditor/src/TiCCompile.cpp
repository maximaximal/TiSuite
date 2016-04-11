#include <TiCCompile.hpp>
#include <ui_TiCCompile.h>

#include <memory>
#include <tic/Lexer.hpp>
#include <tic/SourceBlock.hpp>
#include <tic/AST.hpp>
#include <tic/Type.hpp>
#include <tic/ast/Node.hpp>
#include <tic/ast/List.hpp>
#include <tic/ast/Command.hpp>
#include <tic/ast/Variable.hpp>
#include <tic/ast/VariableDeclaration.hpp>
#include <tic/Config.hpp>
#include <boost/shared_ptr.hpp>
#include <QPlainTextEdit>

#include <Q_DebugStream.hpp>

using std::cout;
using std::endl;

class ASTTreeItem : public QTreeWidgetItem
{
public:
    ASTTreeItem(QTreeWidgetItem *parent, tic::ast::Node *node, int i) 
        : QTreeWidgetItem(parent), m_node(node)
    {
        setText(0, QString::number(i));
        setText(1, QString::fromStdString(node->toString()));
        
        if(node->type() == tic::ast::NodeType::Command) {
            setText(2, QString::fromStdString(static_cast<tic::ast::Command*>(node)->command()));
        }
        if(node->type() == tic::ast::NodeType::VariableDeclaration) {
            tic::ast::VariableDeclaration *decl = static_cast<tic::ast::VariableDeclaration*>(node);
            setText(2, QString::fromStdString("(" + decl->type()->toString() + ") " + decl->varName()));
        }
        if(node->type() == tic::ast::NodeType::Variable) {
            tic::ast::Variable *var = static_cast<tic::ast::Variable*>(node);
            setText(2, QString::fromStdString(var->varName()));
        }
    }
    virtual ~ASTTreeItem()
    {
        
    }
    
    tic::ast::Node* node()
    {
        return m_node;
    }
private:
    tic::ast::Node *m_node;
};

TiCCompile::TiCCompile(tic::ErrorHandler *errorHandler)
    : ui(new Ui::TiCCompile), m_errorHandler(errorHandler)
{
    ui->setupUi(this);
    
    m_lexer.reset(new tic::Lexer());
    m_outputMGR.reset(new tic::OutputMgr());
    m_ast.reset(new tic::AST(errorHandler, m_outputMGR.get()));
    
    m_ast->initPython(QCoreApplication::arguments().count(), 
                   QCoreApplication::arguments().toVector().data()->toLocal8Bit().data());
}
TiCCompile::~TiCCompile()
{
    delete ui;
}
void TiCCompile::clear()
{
    ui->tokenList->clear();
    ui->astTree->clear();
    ui->dbgOut->clear();
    ui->outputs->clear();
    
    m_errorHandler->clearErrors();
}
void TiCCompile::parseAstTree(tic::ast::List* list, QTreeWidgetItem *item, int *i)
{
    for(auto node : *(list))
    {
        ++*i;
        boost::shared_ptr<tic::ast::List> subList = boost::dynamic_pointer_cast<tic::ast::List>(node);
        if(subList) {
            //This is an additional list!
            ASTTreeItem *subItem = new ASTTreeItem(item, static_cast<tic::ast::Node*>(subList.get()), *i);
            
            parseAstTree(subList.get(), subItem, i);
        } else {
            // Just output the node. 
            if(node)
                item->addChild(new ASTTreeItem(item, node.get(), *i));
            else {
                QTreeWidgetItem *subItem = new QTreeWidgetItem(item);
                subItem->setText(0, QString::number(*i));
                subItem->setText(1, "Invalid Node");
            }
        }
    }
}
void TiCCompile::compile(const QString& file, const QString& toolkit)
{
    clear();
    m_lexer->clear();
    
    using namespace tic;
    
    Q_DebugStream dbg(std::cout, std::cerr, ui->dbgOut);
    
    cout << "Using TiC version " << TIC_VERSION << endl;
    
    std::unique_ptr<SourceBlock> block(new SourceBlock());
    block->readFromFile(file.toStdString());
    m_lexer->lex(std::move(block));
    m_lexer->setRootBlock(file.toStdString());
    for(auto token : m_lexer->rootSourceBlock()->tokenVector())
    {
        ui->tokenList->addItem(QString(TokenType::getTypename(token.first)) + ": \"" + QString::fromStdString(token.second) + "\"");
    }
    m_ast->generateFromTokenizedBlock(m_lexer->rootSourceBlock());
    m_ast->generateTICode(toolkit.toStdString());
    
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->astTree);
    item->setText(0, QString::number(0));
    item->setText(1, "Root List");
    ui->astTree->addTopLevelItem(item);
    
    int i = 0;
    
    parseAstTree(m_ast->rootList(), item, &i);
    
    for(auto file : *(m_outputMGR->files()))
    {
        QPlainTextEdit *edit = new QPlainTextEdit(QString::fromStdString(file.second), this);
        edit->setFont(QFont("Monospace"));
        ui->outputs->addTab(edit, QString::fromStdString(file.first));
    }
}

#include <TiCCompile.hpp>
#include <ui_TiCCompile.h>

#include <memory>
#include <tic/Lexer.hpp>
#include <tic/SourceBlock.hpp>
#include <tic/AST.hpp>
#include <tic/ast/Node.hpp>
#include <tic/ast/List.hpp>
#include <tic/ast/Command.hpp>
#include <boost/shared_ptr.hpp>

#include <Q_DebugStream.hpp>

class ASTTreeItem : public QTreeWidgetItem
{
public:
    ASTTreeItem(QTreeWidgetItem *parent, tic::ast::Node *node) 
        : QTreeWidgetItem(parent), m_node(node)
    {
        setText(0, QString::fromStdString(node->toString()));
        
        if(node->type() == tic::ast::NodeType::Command) {
            setText(1, QString::fromStdString(static_cast<tic::ast::Command*>(node)->command()));
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

TiCCompile::TiCCompile()
    : ui(new Ui::TiCCompile)
{
    ui->setupUi(this);
}
TiCCompile::~TiCCompile()
{
    
}
void TiCCompile::clear()
{
    ui->tokenList->clear();
    ui->astTree->clear();
    ui->dbgOut->clear();
}
void TiCCompile::parseAstTree(tic::ast::List* list, QTreeWidgetItem *item)
{
    for(auto node : *(list))
    {
        boost::shared_ptr<tic::ast::List> subList = boost::dynamic_pointer_cast<tic::ast::List>(node);
        if(subList) {
            //This is an additional list!
            ASTTreeItem *subItem = new ASTTreeItem(item, static_cast<tic::ast::Node*>(subList.get()));
            
            parseAstTree(subList.get(), subItem);
        } else {
            // Just output the node. 
            item->addChild(new ASTTreeItem(item, node.get()));
        }
    }
}
void TiCCompile::compile(const QString& file, const QString& toolkit)
{
    clear();
    
    using namespace tic;
    
    Q_DebugStream dbg(std::cout, ui->dbgOut);
    
    Lexer lexer;
    ErrorHandler errorHandler;
    OutputMgr output;
    AST ast(&errorHandler, &output);
    
    ast.initPython(QCoreApplication::arguments().count(), 
                   QCoreApplication::arguments().toVector().data()->toLocal8Bit().data());
    
    std::unique_ptr<SourceBlock> block = std::make_unique<SourceBlock>();
    block->readFromFile(file.toStdString());
    lexer.lex(std::move(block));
    lexer.setRootBlock(file.toStdString());
    for(auto token : lexer.rootSourceBlock()->tokenVector())
    {
        ui->tokenList->addItem(QString(TokenType::getTypename(token.first)) + ": \"" + QString::fromStdString(token.second) + "\"");
    }
    ast.generateFromTokenizedBlock(lexer.rootSourceBlock());
    ast.generateTICode(toolkit.toStdString());
    
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->astTree);
    item->setText(0, "Root List");
    ui->astTree->addTopLevelItem(item);
    
    parseAstTree(ast.rootList(), item);
}

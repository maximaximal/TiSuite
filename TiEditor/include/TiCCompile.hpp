#ifndef TICCOMPILE_HPP
#define TICCOMPILE_HPP

#include <QDialog>
#include <QTreeWidgetItem>
#include <tic/ast/List.hpp>
#include <tic/AST.hpp>
#include <tic/Lexer.hpp>
#include <tic/OutputMGR.hpp>

namespace Ui {
    class TiCCompile;
}

class TiCCompile : public QDialog
{
    Q_OBJECT
public:
    
    TiCCompile(tic::ErrorHandler *errorHandler);
    virtual ~TiCCompile();
    
    void clear();
    void compile(const QString &file, const QString &toolkit);
    void parseAstTree(tic::ast::List *list, QTreeWidgetItem *item, int *i);
private:
    Ui::TiCCompile *ui;
    tic::ErrorHandler *m_errorHandler;
    tic::OutputMGR *m_outputMGR;
    tic::Lexer *m_lexer;
    tic::AST *m_ast;
    
};

#endif

#ifndef TICCOMPILE_HPP
#define TICCOMPILE_HPP

#include <QDialog>
#include <QTreeWidgetItem>
#include <tic/ast/List.hpp>

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
    void parseAstTree(tic::ast::List *list, QTreeWidgetItem *item);
private:
    Ui::TiCCompile *ui;
    tic::ErrorHandler *m_errorHandler;
    
};

#endif

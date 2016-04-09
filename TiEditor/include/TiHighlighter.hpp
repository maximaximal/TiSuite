#ifndef TIHIGHLIGHTER_HPP
#define TIHIGHLIGHTER_HPP

#include <Qsci/qscilexercustom.h>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class QTextDocument;

class TiHighlighter : QsciLexerCustom
{
    Q_OBJECT

public:
    TiHighlighter(QTextDocument *parent = 0);
    
    virtual void styleText(int start, int end);
private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};

#endif // TIHIGHLIGHTER_HPP

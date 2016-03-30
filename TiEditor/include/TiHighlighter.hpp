#ifndef TIHIGHLIGHTER_HPP
#define TIHIGHLIGHTER_HPP

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class QTextDocument;

class TiHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    TiHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

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

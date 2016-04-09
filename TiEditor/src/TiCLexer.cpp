// This module implements the TiCLexer class.
//
// Copyright (c) 2015 Riverbank Computing Limited <info@riverbankcomputing.com>
// 
// This file is part of QScintilla.
// 
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the Free Software Foundation and appearing in
// the file LICENSE included in the packaging of this file.  Please review the
// following information to ensure the GNU General Public License version 3.0
// requirements will be met: http://www.gnu.org/copyleft/gpl.html.
// 
// If you do not wish to use this file under the terms of the GPL version 3.0
// then you may purchase a commercial license.  For more information contact
// info@riverbankcomputing.com.
// 
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

// This has been modified to work as a Lexer for Advanced TiBasic. 

#include <TiCLexer.hpp>

#include <qcolor.h>
#include <qfont.h>
#include <qsettings.h>

#include <tic/ast/Unsafe.hpp>

// The ctor.
TiCLexer::TiCLexer(QObject *parent, bool caseInsensitiveKeywords)
    : QsciLexer(parent),
      fold_atelse(false), fold_comments(false), fold_compact(true),
      fold_preproc(true), style_preproc(false), dollars(true),
      highlight_triple(true), highlight_hash(false), highlight_back(false),
      highlight_escape(false), vs_escape(false),
      nocase(caseInsensitiveKeywords)
{
    m_tibasicKeywords.append(tic::ast::Unsafe::generateTiTokensList());
    m_tibasicKeywords.append(tic::ast::Unsafe::generateTiVarsList());
    
    
}


// The dtor.
TiCLexer::~TiCLexer()
{
}


// Returns the language name.
const char *TiCLexer::language() const
{
    return "Advanced TiBasic (TiC)";
}


// Returns the lexer name.
const char *TiCLexer::lexer() const
{
    return (nocase ? "cppnocase" : "cpp");
}


// Return the set of character sequences that can separate auto-completion
// words.
QStringList TiCLexer::autoCompletionWordSeparators() const
{
    QStringList wl;

    wl << "::" << "->" << ".";

    return wl;
}


// Return the list of keywords that can start a block.
const char *TiCLexer::blockStartKeyword(int *style) const
{
    if (style)
        *style = Keyword;

    return "case catch class default do else finally for if private "
           "protected public struct try union while function program unsafe";
}


// Return the list of characters that can start a block.
const char *TiCLexer::blockStart(int *style) const
{
    if (style)
        *style = Operator;

    return "{";
}


// Return the list of characters that can end a block.
const char *TiCLexer::blockEnd(int *style) const
{
    if (style)
        *style = Operator;

    return "}";
}


// Return the style used for braces.
int TiCLexer::braceStyle() const
{
    return Operator;
}


// Return the string of characters that comprise a word.
const char *TiCLexer::wordCharacters() const
{
    return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_#";
}


// Returns the foreground colour of the text for a style.
QColor TiCLexer::defaultColor(int style) const
{
    switch (style)
    {
    case Default:
        return QColor("#839496");

    case Comment:
    case CommentLine:
        return QColor("#586e75");

    case CommentDoc:
    case CommentLineDoc:
    case PreProcessorCommentLineDoc:
        return QColor("#586e75");

    case Number:
        return QColor("#6c71c4");

    case Keyword:
        return QColor("#268bd2");

    case DoubleQuotedString:
    case SingleQuotedString:
    case RawString:
        return QColor("#dc322f");

    case PreProcessor:
        return QColor("#dc322f");

    case Operator:
    case UnclosedString:
        return QColor("#dc322f");

    case VerbatimString:
    case TripleQuotedVerbatimString:
    case HashQuotedString:
        return QColor("#dc322f");

    case Regex:
        return QColor("0x3f, 0x7f, 0x3f");

    case CommentDocKeyword:
        return QColor("#93a1a1");

    case CommentDocKeywordError:
        return QColor("#93a1a1");

    case PreProcessorComment:
        return QColor("#93a1a1");

    case InactiveDefault:
    case InactiveUUID:
    case InactiveCommentLineDoc:
    case InactiveKeywordSet2:
    case InactiveCommentDocKeyword:
    case InactiveCommentDocKeywordError:
    case InactivePreProcessorCommentLineDoc:
        return QColor("#93a1a1");

    case InactiveComment:
    case InactiveCommentLine:
    case InactiveNumber:
    case InactiveVerbatimString:
    case InactiveTripleQuotedVerbatimString:
    case InactiveHashQuotedString:
        return QColor("#93a1a1");

    case InactiveCommentDoc:
        return QColor("#93a1a1");

    case InactiveKeyword:
        return QColor("#93a1a1");

    case InactiveDoubleQuotedString:
    case InactiveSingleQuotedString:
    case InactiveRawString:
        return QColor("#93a1a1");

    case InactivePreProcessor:
        return QColor("#93a1a1");

    case InactiveOperator:
    case InactiveIdentifier:
    case InactiveGlobalClass:
        return QColor("#93a1a1");

    case InactiveUnclosedString:
        return QColor("#93a1a1");

    case InactiveRegex:
        return QColor("#93a1a1");

    case InactivePreProcessorComment:
        return QColor("#93a1a1");

    case UserLiteral:
        return QColor("#859900");

    case InactiveUserLiteral:
        return QColor("#93a1a1");

    case TaskMarker:
        return QColor("#d33682");

    case InactiveTaskMarker:
        return QColor("#d33682");
    }

    return QsciLexer::defaultColor(style);
}


// Returns the end-of-line fill for a style.
bool TiCLexer::defaultEolFill(int style) const
{
    switch (style)
    {
    case UnclosedString:
    case InactiveUnclosedString:
    case VerbatimString:
    case InactiveVerbatimString:
    case Regex:
    case InactiveRegex:
    case TripleQuotedVerbatimString:
    case InactiveTripleQuotedVerbatimString:
    case HashQuotedString:
    case InactiveHashQuotedString:
        return true;
    }

    return QsciLexer::defaultEolFill(style);
}


// Returns the font of the text for a style.
QFont TiCLexer::defaultFont(int style) const
{
    QFont f;

    switch (style)
    {
    case Comment:
    case InactiveComment:
    case CommentLine:
    case InactiveCommentLine:
    case CommentDoc:
    case InactiveCommentDoc:
    case CommentLineDoc:
    case InactiveCommentLineDoc:
    case CommentDocKeyword:
    case InactiveCommentDocKeyword:
    case CommentDocKeywordError:
    case InactiveCommentDocKeywordError:
    case TaskMarker:
    case InactiveTaskMarker:
        f = QsciLexer::defaultFont(style);
        f.setBold(false);
        break;

    case Keyword:
    case InactiveKeyword:
    case Operator:
    case InactiveOperator:
        f = QsciLexer::defaultFont(style);
        f.setBold(true);
        break;

    case DoubleQuotedString:
    case InactiveDoubleQuotedString:
    case SingleQuotedString:
    case InactiveSingleQuotedString:
    case UnclosedString:
    case InactiveUnclosedString:
    case VerbatimString:
    case InactiveVerbatimString:
    case Regex:
    case InactiveRegex:
    case TripleQuotedVerbatimString:
    case InactiveTripleQuotedVerbatimString:
    case HashQuotedString:
    case InactiveHashQuotedString:
        f = QsciLexer::defaultFont(style);
        f.setItalic(true);
        break;

    default:
        f = QsciLexer::defaultFont(style);
    }

    return f;
}


// Returns the set of keywords.
const char *TiCLexer::keywords(int set) const
{
    // The first set of keywords is from TiC
    if (set == 1)
        return
            "function program unsafe return num str lst mat";

    if (set == 3)
        return m_tibasicKeywords.c_str();
    
    return 0;
}


// Returns the user name of a style.
QString TiCLexer::description(int style) const
{
    switch (style)
    {
    case Default:
        return tr("Default");

    case InactiveDefault:
        return tr("Inactive default");

    case Comment:
        return tr("C comment");

    case InactiveComment:
        return tr("Inactive C comment");

    case CommentLine:
        return tr("C++ comment");

    case InactiveCommentLine:
        return tr("Inactive C++ comment");

    case CommentDoc:
        return tr("JavaDoc style C comment");

    case InactiveCommentDoc:
        return tr("Inactive JavaDoc style C comment");

    case Number:
        return tr("Number");

    case InactiveNumber:
        return tr("Inactive number");

    case Keyword:
        return tr("Keyword");

    case InactiveKeyword:
        return tr("Inactive keyword");

    case DoubleQuotedString:
        return tr("Double-quoted string");

    case InactiveDoubleQuotedString:
        return tr("Inactive double-quoted string");

    case SingleQuotedString:
        return tr("Single-quoted string");

    case InactiveSingleQuotedString:
        return tr("Inactive single-quoted string");

    case UUID:
        return tr("IDL UUID");

    case InactiveUUID:
        return tr("Inactive IDL UUID");

    case PreProcessor:
        return tr("Pre-processor block");

    case InactivePreProcessor:
        return tr("Inactive pre-processor block");

    case Operator:
        return tr("Operator");

    case InactiveOperator:
        return tr("Inactive operator");

    case Identifier:
        return tr("Identifier");

    case InactiveIdentifier:
        return tr("Inactive identifier");

    case UnclosedString:
        return tr("Unclosed string");

    case InactiveUnclosedString:
        return tr("Inactive unclosed string");

    case VerbatimString:
        return tr("C# verbatim string");

    case InactiveVerbatimString:
        return tr("Inactive C# verbatim string");

    case Regex:
        return tr("JavaScript regular expression");

    case InactiveRegex:
        return tr("Inactive JavaScript regular expression");

    case CommentLineDoc:
        return tr("JavaDoc style C++ comment");

    case InactiveCommentLineDoc:
        return tr("Inactive JavaDoc style C++ comment");

    case KeywordSet2:
        return tr("Secondary keywords and identifiers");

    case InactiveKeywordSet2:
        return tr("Inactive secondary keywords and identifiers");

    case CommentDocKeyword:
        return tr("JavaDoc keyword");

    case InactiveCommentDocKeyword:
        return tr("Inactive JavaDoc keyword");

    case CommentDocKeywordError:
        return tr("JavaDoc keyword error");

    case InactiveCommentDocKeywordError:
        return tr("Inactive JavaDoc keyword error");

    case GlobalClass:
        return tr("Global classes and typedefs");

    case InactiveGlobalClass:
        return tr("Inactive global classes and typedefs");

    case RawString:
        return tr("C++ raw string");

    case InactiveRawString:
        return tr("Inactive C++ raw string");

    case TripleQuotedVerbatimString:
        return tr("Vala triple-quoted verbatim string");

    case InactiveTripleQuotedVerbatimString:
        return tr("Inactive Vala triple-quoted verbatim string");

    case HashQuotedString:
        return tr("Pike hash-quoted string");

    case InactiveHashQuotedString:
        return tr("Inactive Pike hash-quoted string");

    case PreProcessorComment:
        return tr("Pre-processor C comment");

    case InactivePreProcessorComment:
        return tr("Inactive pre-processor C comment");

    case PreProcessorCommentLineDoc:
        return tr("JavaDoc style pre-processor comment");

    case InactivePreProcessorCommentLineDoc:
        return tr("Inactive JavaDoc style pre-processor comment");

    case UserLiteral:
        return tr("User-defined literal");

    case InactiveUserLiteral:
        return tr("Inactive user-defined literal");

    case TaskMarker:
        return tr("Task marker");

    case InactiveTaskMarker:
        return tr("Inactive task marker");

    case EscapeSequence:
        return tr("Escape sequence");

    case InactiveEscapeSequence:
        return tr("Inactive escape sequence");
    }

    return QString();
}


// Returns the background colour of the text for a style.
QColor TiCLexer::defaultPaper(int style) const
{
    // USe solarized dark colors
    switch (style)
    {
    case UnclosedString:
    case InactiveUnclosedString:
        return QColor("#586e75");

    case VerbatimString:
    case InactiveVerbatimString:
    case TripleQuotedVerbatimString:
    case InactiveTripleQuotedVerbatimString:
        return QColor("#586e75");

    case Regex:
    case InactiveRegex:
        return QColor("#93a1a1");

    case RawString:
    case InactiveRawString:
        return QColor("#dc322f");

    case HashQuotedString:
    case InactiveHashQuotedString:
        return QColor("#d33682");
    }

    return QColor("#002b36");
}


// Refresh all properties.
void TiCLexer::refreshProperties()
{
    setAtElseProp();
    setCommentProp();
    setCompactProp();
    setPreprocProp();
    setStylePreprocProp();
    setDollarsProp();
    setHighlightTripleProp();
    setHighlightHashProp();
    setHighlightBackProp();
    setHighlightEscapeProp();
    setVerbatimStringEscapeProp();
}


// Read properties from the settings.
bool TiCLexer::readProperties(QSettings &qs,const QString &prefix)
{
    fold_atelse = qs.value(prefix + "foldatelse", false).toBool();
    fold_comments = qs.value(prefix + "foldcomments", false).toBool();
    fold_compact = qs.value(prefix + "foldcompact", true).toBool();
    fold_preproc = qs.value(prefix + "foldpreprocessor", true).toBool();
    style_preproc = qs.value(prefix + "stylepreprocessor", false).toBool();
    dollars = qs.value(prefix + "dollars", true).toBool();
    highlight_triple = qs.value(prefix + "highlighttriple", false).toBool();
    highlight_hash = qs.value(prefix + "highlighthash", false).toBool();
    highlight_back = qs.value(prefix + "highlightback", false).toBool();
    highlight_escape = qs.value(prefix + "highlightescape", false).toBool();
    vs_escape = qs.value(prefix + "verbatimstringescape", false).toBool();

    return true;
}


// Write properties to the settings.
bool TiCLexer::writeProperties(QSettings &qs,const QString &prefix) const
{
    qs.setValue(prefix + "foldatelse", fold_atelse);
    qs.setValue(prefix + "foldcomments", fold_comments);
    qs.setValue(prefix + "foldcompact", fold_compact);
    qs.setValue(prefix + "foldpreprocessor", fold_preproc);
    qs.setValue(prefix + "stylepreprocessor", style_preproc);
    qs.setValue(prefix + "dollars", dollars);
    qs.setValue(prefix + "highlighttriple", highlight_triple);
    qs.setValue(prefix + "highlighthash", highlight_hash);
    qs.setValue(prefix + "highlightback", highlight_back);
    qs.setValue(prefix + "highlightescape", highlight_escape);
    qs.setValue(prefix + "verbatimstringescape", vs_escape);

    return true;
}


// Set if else can be folded.
void TiCLexer::setFoldAtElse(bool fold)
{
    fold_atelse = fold;

    setAtElseProp();
}


// Set the "fold.at.else" property.
void TiCLexer::setAtElseProp()
{
    emit propertyChanged("fold.at.else",(fold_atelse ? "1" : "0"));
}


// Set if comments can be folded.
void TiCLexer::setFoldComments(bool fold)
{
    fold_comments = fold;

    setCommentProp();
}


// Set the "fold.comment" property.
void TiCLexer::setCommentProp()
{
    emit propertyChanged("fold.comment",(fold_comments ? "1" : "0"));
}


// Set if folds are compact
void TiCLexer::setFoldCompact(bool fold)
{
    fold_compact = fold;

    setCompactProp();
}


// Set the "fold.compact" property.
void TiCLexer::setCompactProp()
{
    emit propertyChanged("fold.compact",(fold_compact ? "1" : "0"));
}


// Set if preprocessor blocks can be folded.
void TiCLexer::setFoldPreprocessor(bool fold)
{
    fold_preproc = fold;

    setPreprocProp();
}


// Set the "fold.preprocessor" property.
void TiCLexer::setPreprocProp()
{
    emit propertyChanged("fold.preprocessor",(fold_preproc ? "1" : "0"));
}


// Set if preprocessor lines are styled.
void TiCLexer::setStylePreprocessor(bool style)
{
    style_preproc = style;

    setStylePreprocProp();
}


// Set the "styling.within.preprocessor" property.
void TiCLexer::setStylePreprocProp()
{
    emit propertyChanged("styling.within.preprocessor",(style_preproc ? "1" : "0"));
}


// Set if '$' characters are allowed.
void TiCLexer::setDollarsAllowed(bool allowed)
{
    dollars = allowed;

    setDollarsProp();
}


// Set the "lexer.cpp.allow.dollars" property.
void TiCLexer::setDollarsProp()
{
    emit propertyChanged("lexer.cpp.allow.dollars",(dollars ? "1" : "0"));
}


// Set if triple quoted strings are highlighted.
void TiCLexer::setHighlightTripleQuotedStrings(bool enabled)
{
    highlight_triple = enabled;

    setHighlightTripleProp();
}


// Set the "lexer.cpp.triplequoted.strings" property.
void TiCLexer::setHighlightTripleProp()
{
    emit propertyChanged("lexer.cpp.triplequoted.strings",
            (highlight_triple ? "1" : "0"));
}


// Set if hash quoted strings are highlighted.
void TiCLexer::setHighlightHashQuotedStrings(bool enabled)
{
    highlight_hash = enabled;

    setHighlightHashProp();
}


// Set the "lexer.cpp.hashquoted.strings" property.
void TiCLexer::setHighlightHashProp()
{
    emit propertyChanged("lexer.cpp.hashquoted.strings",
            (highlight_hash ? "1" : "0"));
}


// Set if back-quoted strings are highlighted.
void TiCLexer::setHighlightBackQuotedStrings(bool enabled)
{
    highlight_back = enabled;

    setHighlightBackProp();
}


// Set the "lexer.cpp.backquoted.strings" property.
void TiCLexer::setHighlightBackProp()
{
    emit propertyChanged("lexer.cpp.backquoted.strings",
            (highlight_back ? "1" : "0"));
}


// Set if escape sequences in strings are highlighted.
void TiCLexer::setHighlightEscapeSequences(bool enabled)
{
    highlight_escape = enabled;

    setHighlightEscapeProp();
}


// Set the "lexer.cpp.escape.sequence" property.
void TiCLexer::setHighlightEscapeProp()
{
    emit propertyChanged("lexer.cpp.escape.sequence",
            (highlight_escape ? "1" : "0"));
}


// Set if escape sequences in verbatim strings are allowed.
void TiCLexer::setVerbatimStringEscapeSequencesAllowed(bool allowed)
{
    vs_escape = allowed;

    setVerbatimStringEscapeProp();
}


// Set the "lexer.cpp.verbatim.strings.allow.escapes" property.
void TiCLexer::setVerbatimStringEscapeProp()
{
    emit propertyChanged("lexer.cpp.verbatim.strings.allow.escapes",
            (vs_escape ? "1" : "0"));
}

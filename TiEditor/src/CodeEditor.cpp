/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <CodeEditor.hpp>


CodeEditor::CodeEditor(QWidget *parent) : QsciScintilla(parent), m_changed(false)
{
    connect(this, SIGNAL(textChanged()), this, SLOT(textChanged()));
    QSettings settings;
    settings.beginGroup("EditorWindow");
    
    QString font;


    font = settings.value("font", "Monospace").toString();

    QFont qFont(font);

    setFont(qFont);
    setStyleSheet("QsciScintilla {"
                                "background-color: #fdf6e3;"
                                "color: #073642;"
    "}");

    const int tabStop = 4;  // 4 characters

    setTabWidth(4);
    setMarginWidth(0, 40);
    setMarginLineNumbers(3, true);
    setMarginType(0, QsciScintilla::NumberMargin);
    setAutoIndent(true);
    setBraceMatching(QsciScintilla::StrictBraceMatch);
    setAutoCompletionSource(QsciScintilla::AcsAll);
    setAutoCompletionFillupsEnabled(true);
    setAutoCompletionThreshold(2);
    setCaretWidth(10);
    setUtf8(true);
    
    m_highlighter = new TiCLexer(this);
    m_highlighter->setDefaultFont(qFont);
    setLexer(m_highlighter);
    
    settings.endGroup();
}
CodeEditor::~CodeEditor()
{
    if(m_highlighter)
        delete m_highlighter;
}

void CodeEditor::textChanged()
{
    m_changed = true;
}
void CodeEditor::setFilepath(const QString &path)
{
    m_path = path;
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    
    clear();
    
    qDebug() << "Open " << path;
    
    QTextStream inStream(&file);
    while(!inStream.atEnd()) 
    {
        append(inStream.readLine() + "\n");
    }
}
const QString &CodeEditor::filepath()
{
    return m_path;
}
bool CodeEditor::changed()
{
    return m_changed;
}
void CodeEditor::save()
{
    QFile out(m_path);
    
    if(!out.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    
    QTextStream stream(&out);
    stream << text();
    stream.flush();
}
void CodeEditor::handleError(const tic::Error& error)
{
    setCursorPosition(error.line(), 0);
    annotate(error.line(), QString::fromStdString(error.msg()), QsciScintilla::AnnotationBoxed);
}

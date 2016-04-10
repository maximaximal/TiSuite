#ifndef Q_DEBUGSTREAM_H
#define Q_DEBUGSTREAM_H

// Taken from http://www.qtforum.org/article/39768/redirecting-std-cout-std-cerf-qdebug-to-qtextedit.html

#include <iostream>
#include <streambuf>
#include <string>

#include <QTextEdit>

class Q_DebugStream : public std::basic_streambuf<char>
{
public:
    Q_DebugStream(std::ostream &stream, std::ostream &stream2, QTextEdit* text_edit) : m_stream(stream), m_stream2(stream2)
    {
        log_window = text_edit;
        m_old_buf = stream.rdbuf();
        m_old_buf2 = stream2.rdbuf();
        stream.rdbuf(this);
        stream2.rdbuf(this);
    }
    
    ~Q_DebugStream()
    {
        m_stream.rdbuf(m_old_buf);
        m_stream2.rdbuf(m_old_buf2);
    }
    
    static void registerQDebugMessageHandler(){
        qInstallMessageHandler(myQDebugMessageHandler);
    }
    
private:
    
    static void myQDebugMessageHandler(QtMsgType, const QMessageLogContext &, const QString &msg)
    {
        std::cout << msg.toStdString().c_str();
    }
    
protected:
    
    //This is called when a std::endl has been inserted into the stream
    virtual int_type overflow(int_type v)
    {
        if (v == '\n')
        {
            log_window->append("");
        }
        return v;
    }
    
    
    virtual std::streamsize xsputn(const char *p, std::streamsize n)
    {
        QString str(p);
        if(str.contains("\n")){
            QStringList strSplitted = str.split("\n");
            
            log_window->moveCursor (QTextCursor::End);
            log_window->insertPlainText (strSplitted.at(0)); //Index 0 is still on the same old line
            
            for(int i = 1; i < strSplitted.size(); i++){
                log_window->append(strSplitted.at(i));
            }
        }else{
            log_window->moveCursor (QTextCursor::End);
            log_window->insertPlainText (str);
        }
        return n;
    }
    
private:
    std::ostream &m_stream;
    std::ostream &m_stream2;
    std::streambuf *m_old_buf;
    std::streambuf *m_old_buf2;
    QTextEdit* log_window;
};


#endif // Q_DEBUGSTREAM_H

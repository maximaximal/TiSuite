#pragma once

#include <map>
#include <string>

namespace tic
{
/**
 * @brief Handles and writes the output of toolkits. 
 * 
 * The output has to be in the respective tibasic dialect used by the toolkit. It can then be 
 * compiled by a compiler of your choice. 
 */
class OutputMgr
{
public:
    typedef std::map<std::string, std::string> FilesMap;
    
    OutputMgr();
    virtual ~OutputMgr();
    
    const std::string& file(const std::string &path);
    void setFile(const std::string &path, const std::string &content);
    void setFileFromPython(const std::string &path, const std::string &content);
    
    FilesMap* files();
    
    virtual void write();
private:
    FilesMap m_files;
};
}
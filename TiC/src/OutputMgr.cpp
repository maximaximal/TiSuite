#include <tic/OutputMgr.hpp>
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

namespace tic
{
OutputMgr::OutputMgr()
{

}
OutputMgr::~OutputMgr()
{

}
const std::string &OutputMgr::file(const std::string &path)
{
    return m_files[path];
}
void OutputMgr::setFile(const std::string &path, const std::string &content)
{
    m_files[path] = content;
}
void OutputMgr::setFileFromPython(const std::string &path, const std::string &content)
{
    setFile(path, content);
}
OutputMgr::FilesMap *OutputMgr::files()
{
    return &m_files;
}
void OutputMgr::write()
{
    cout << "Writing files from the OutputMGR [default implementation]" << endl;
    for(auto &file : m_files) 
    {
        cout << "Writing file \"" << file.first << "\"." << endl;
        std::ofstream outFile(file.first);
        if(outFile.is_open()) {
            outFile << file.second;
        } else {
            cout << "[Write Error] The file \"" << file.first << "\" could not be written!" << endl;
        }
        outFile.close();
    }
}
}
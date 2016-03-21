#include <boost/program_options.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <tic/Lexer.hpp>
#include <tic/SourceBlock.hpp>
#include <tic/AST.hpp>

using std::cout;
using std::endl;
using namespace tic;

int main(int argc, char** argv)
{
    boost::program_options::options_description desc("Allowed Options");
    desc.add_options()
        ("help", "produce help message")
        ("input-file", boost::program_options::value<std::vector<std::string>>(), "input file (to compile)")
    ;
    
    boost::program_options::positional_options_description p;
    p.add("input-file", -1);
    
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).
        options(desc).positional(p).run(), vm);
    
    bool compile = false;
    
    if(vm.count("help")) {
        cout << "Usage: " << endl;
        cout << desc;
        return 0;
    }
    
    Lexer lexer;
    ErrorHandler handler;
    AST ast(&handler);
    
    if(vm.count("input-file")) {
        cout << "Input files: " << endl;
        for(auto &file : vm["input-file"].as<std::vector<std::string>>())
        {
            cout << "    \"" << file << "\"" << endl;
            std::unique_ptr<SourceBlock> block = std::make_unique<SourceBlock>();
            block->readFromFile(file);
            lexer.lex(std::move(block));
            lexer.setRootBlock(file);
            ast.generateFromTokenizedBlock(lexer.rootSourceBlock());
        }
    }
}

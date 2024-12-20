#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "Lexer.h"
#include "Parser.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>

class CodeGenerator {
public:
    CodeGenerator(llvm::LLVMContext& context, llvm::Module& module);

    // Generate LLVM code for the add function and main
    void generateLLVM(const FunctionNode& funcNode);

private:
    llvm::LLVMContext& context;
    llvm::Module& module;
    llvm::IRBuilder<> builder;

    llvm::Function* createAddFunction();
    llvm::Function* createMainFunction();
    llvm::Value* createAddCall(llvm::Function* addFunc, llvm::Value* x, llvm::Value* y);
};

#endif

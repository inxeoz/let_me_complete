#ifndef SIMPLELLVM_H
#define SIMPLELLVM_H

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Type.h>
#include <vector>
#include <string>
#include <optional>

namespace SimpleLLVM {

    class CompilerContext {
    public:
        llvm::LLVMContext Context;
        llvm::IRBuilder<> Builder;
        llvm::Module* Module;

        explicit CompilerContext(const std::string &moduleName);
        ~CompilerContext();

        std::optional<llvm::Module*> createModule(const std::string& moduleName);
        std::optional<llvm::Function*> createFunction(const std::string& returnTypeStr,
                                                      const std::vector<std::string>& argTypesStr,
                                                      const std::string& funcName);
        std::optional<llvm::Function*> addFunctionToModule(const std::string& returnTypeStr,
                                                           const std::vector<std::string>& argTypesStr,
                                                           const std::string& funcName);
        std::optional<llvm::BasicBlock*> createBasicBlock(llvm::Function* function, const std::string& blockName);
        static std::optional<llvm::Instruction*> addInstructionToBlock(llvm::BasicBlock* block, llvm::Instruction* instruction);

        llvm::Value* createAddInstruction(llvm::Value* lhs, llvm::Value* rhs);
        llvm::Value* createSubInstruction(llvm::Value* lhs, llvm::Value* rhs);
        llvm::Value* createMulInstruction(llvm::Value* lhs, llvm::Value* rhs);
        llvm::ReturnInst* createReturn(llvm::Value* returnValue);
        llvm::Value* createLoadInstruction(llvm::Value* pointer);
        void createStoreInstruction(llvm::Value* value, llvm::Value* pointer);

        llvm::IRBuilder<>& getBuilder();
        llvm::LLVMContext& getContext();
        void printModule() const;

    private:
        std::optional<llvm::Type*> parseType(const std::string& typeStr);
        std::optional<llvm::FunctionType*> createFunctionType(const std::string& returnTypeStr,
                                                              const std::vector<std::string>& argTypesStr);
    };

} // namespace SimpleLLVM

#endif // SIMPLELLVM_H

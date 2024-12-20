#include "SimpleLLVM.h"

namespace SimpleLLVM {

    CompilerContext::CompilerContext(const std::string &moduleName)
        : Builder(Context), Module(new llvm::Module(moduleName, Context)) {}

    CompilerContext::~CompilerContext() {
        delete Module;
    }

    std::optional<llvm::Module*> CompilerContext::createModule(const std::string& moduleName) {
        if (!Module) {
            Module = new llvm::Module(moduleName, Context);
            return Module;
        }
        return std::nullopt;
    }

    std::optional<llvm::Function*> CompilerContext::createFunction(const std::string& returnTypeStr,
                                                                  const std::vector<std::string>& argTypesStr,
                                                                  const std::string& funcName) {
        auto funcTypeOpt = createFunctionType(returnTypeStr, argTypesStr);
        if (!funcTypeOpt) return std::nullopt;
        auto funcType = *funcTypeOpt;
        llvm::Function* function = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, funcName, *Module);
        return function;
    }

    std::optional<llvm::Function*> CompilerContext::addFunctionToModule(const std::string& returnTypeStr,
                                                                       const std::vector<std::string>& argTypesStr,
                                                                       const std::string& funcName) {
        auto function = createFunction(returnTypeStr, argTypesStr, funcName);
        if (function && Module) {
            return *function;
        }
        return std::nullopt;
    }

    std::optional<llvm::BasicBlock*> CompilerContext::createBasicBlock(llvm::Function* function, const std::string& blockName) {
        if (function) {
            return llvm::BasicBlock::Create(Context, blockName, function);
        }
        return std::nullopt;
    }

    std::optional<llvm::Instruction*> CompilerContext::addInstructionToBlock(llvm::BasicBlock* block, llvm::Instruction* instruction) {
        if (block) {
            block->getInstList().push_back(instruction);
            return instruction;
        }
        return std::nullopt;
    }

    llvm::Value* CompilerContext::createAddInstruction(llvm::Value* lhs, llvm::Value* rhs) {
        return Builder.CreateAdd(lhs, rhs, "addtmp");
    }

    llvm::Value* CompilerContext::createSubInstruction(llvm::Value* lhs, llvm::Value* rhs) {
        return Builder.CreateSub(lhs, rhs, "subtmp");
    }

    llvm::Value* CompilerContext::createMulInstruction(llvm::Value* lhs, llvm::Value* rhs) {
        return Builder.CreateMul(lhs, rhs, "multmp");
    }

    llvm::ReturnInst* CompilerContext::createReturn(llvm::Value* returnValue) {
        return llvm::ReturnInst::Create(Context, returnValue);
    }

    llvm::Value* CompilerContext::createLoadInstruction(llvm::Value* pointer) {
        llvm::Type* ptrType = pointer->getType()->getPointerElementType();
        return Builder.CreateLoad(ptrType, pointer, "loadtmp");
    }

    void CompilerContext::createStoreInstruction(llvm::Value* value, llvm::Value* pointer) {
        Builder.CreateStore(value, pointer);
    }

    llvm::IRBuilder<>& CompilerContext::getBuilder() {
        return Builder;
    }

    llvm::LLVMContext& CompilerContext::getContext() {
        return Context;
    }

    void CompilerContext::printModule() const {
        if (Module) {
            Module->print(llvm::outs(), nullptr);
        }
    }

    std::optional<llvm::Type*> CompilerContext::parseType(const std::string& typeStr) {
        if (typeStr == "i1") return llvm::Type::getInt1Ty(Context);
        if (typeStr == "i8") return llvm::Type::getInt8Ty(Context);
        if (typeStr == "i16") return llvm::Type::getInt16Ty(Context);
        if (typeStr == "i32") return llvm::Type::getInt32Ty(Context);
        if (typeStr == "i64") return llvm::Type::getInt64Ty(Context);
        if (typeStr == "f32") return llvm::Type::getFloatTy(Context);
        if (typeStr == "f64") return llvm::Type::getDoubleTy(Context);
        if (typeStr == "void") return llvm::Type::getVoidTy(Context);

        // Add more types as needed
        if (typeStr == "i128") return llvm::Type::getInt128Ty(Context);
        if (typeStr == "fp128") return llvm::Type::getFP128Ty(Context);  // 128-bit floating point type
        if (typeStr == "i1x1") return llvm::Type::getInt1Ty(Context)->getPointerTo();  // Pointer to i1 type

        // Add complex types like arrays, structs, or pointers
        if (typeStr == "i32[]") return llvm::ArrayType::get(llvm::Type::getInt32Ty(Context), 0);  // Array of i32 (length is unspecified)
        if (typeStr == "i32*") return llvm::PointerType::get(llvm::Type::getInt32Ty(Context), 0);  // Pointer to i32
        if (typeStr == "f64*") return llvm::PointerType::get(llvm::Type::getDoubleTy(Context), 0);  // Pointer to f64



        return std::nullopt;
    }


    std::optional<llvm::FunctionType*> CompilerContext::createFunctionType(const std::string& returnTypeStr,
                                                                          const std::vector<std::string>& argTypesStr) {
        auto returnType = parseType(returnTypeStr);
        if (!returnType) return std::nullopt;

        std::vector<llvm::Type*> argTypes;
        for (const auto& argTypeStr : argTypesStr) {
            auto argType = parseType(argTypeStr);
            if (!argType) return std::nullopt;
            argTypes.push_back(*argType);
        }

        return llvm::FunctionType::get(*returnType, argTypes, false);
    }

} // namespace SimpleLLVM

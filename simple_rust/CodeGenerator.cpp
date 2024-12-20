#include "CodeGenerator.h"

CodeGenerator::CodeGenerator(llvm::LLVMContext& context, llvm::Module& module)
    : context(context), module(module), builder(context) {}

llvm::Function* CodeGenerator::createAddFunction() {
    llvm::FunctionType* funcType = llvm::FunctionType::get(llvm::Type::getInt32Ty(context),
                                                           {llvm::Type::getInt32Ty(context), llvm::Type::getInt32Ty(context)}, false);
    llvm::Function* func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "add", module);

    llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", func);
    builder.SetInsertPoint(entry);

    llvm::Function::arg_iterator args = func->arg_begin();
    llvm::Value* x = &*args++;
    llvm::Value* y = &*args++;

    llvm::Value* sum = builder.CreateAdd(x, y, "sum");
    builder.CreateRet(sum);

    return func;
}

llvm::Function* CodeGenerator::createMainFunction() {
    llvm::FunctionType* funcType = llvm::FunctionType::get(llvm::Type::getInt32Ty(context), false);
    llvm::Function* func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);

    llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", func);
    builder.SetInsertPoint(entry);

    // Declare local variables for x and y
    llvm::Value* x = builder.CreateAlloca(llvm::Type::getInt32Ty(context), nullptr, "x");
    llvm::Value* y = builder.CreateAlloca(llvm::Type::getInt32Ty(context), nullptr, "y");

    // Store values into x and y
    builder.CreateStore(llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 10), x);
    builder.CreateStore(llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 20), y);

    // Create call to add function
    llvm::Function* addFunc = module.getFunction("add");
    llvm::Value* addResult = createAddCall(addFunc, x, y);

    // Create a return instruction from main
    builder.CreateRet(addResult);

    return func;
}

llvm::Value* CodeGenerator::createAddCall(llvm::Function* addFunc, llvm::Value* x, llvm::Value* y) {
    // Load the values from x and y
    llvm::Value* xVal = builder.CreateLoad(llvm::Type::getInt32Ty(context), x, "xVal");
    llvm::Value* yVal = builder.CreateLoad(llvm::Type::getInt32Ty(context), y, "yVal");

    // Call the add function with x and y
    return builder.CreateCall(addFunc, {xVal, yVal});
}

void CodeGenerator::generateLLVM(const FunctionNode& funcNode) {
    // Create add function
    llvm::Function* addFunc = createAddFunction();

    // Create main function
    llvm::Function* mainFunc = createMainFunction();
}

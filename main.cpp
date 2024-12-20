
#include "simple_rust/Lexer.h"
#include "simple_rust/Parser.h"
#include "simple_rust/CodeGenerator.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/IRBuilder.h>
#include <iostream>
#include <memory>


int main() {
    // Initialize lexer with a simple input string (e.g., a function declaration)
    std::string input = "fn add(a: i32, b: i32) -> i32 { return a + b; } fn main() { let x = 10; let y = 20; let result = add(x, y); println(result); }";

    Lexer lexer(input);

    // Initialize parser with the lexer
    Parser parser(lexer);

    // Parse the function definition (returns a unique pointer to ASTNode)
    std::unique_ptr<ASTNode> funcNodePtr = parser.parseFunction();

    // Cast to FunctionNode if the parsed node is indeed a function
    FunctionNode* funcNode = dynamic_cast<FunctionNode*>(funcNodePtr.get());
    if (!funcNode) {
        std::cerr << "Error: Failed to parse function definition." << std::endl;
        return -1;
    }

    // Set up LLVM context and module for code generation
    llvm::LLVMContext context;
    llvm::Module module("example_module", context);
    CodeGenerator codeGen(context, module);

    // Generate LLVM IR for the function
    codeGen.generateLLVM(*funcNode);

    // Print the generated module (LLVM IR)
    module.print(llvm::outs(), nullptr);

    return 0;
}

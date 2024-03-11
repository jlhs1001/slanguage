//
// Created by Liam Seewald on 3/7/24.
//

#ifndef SLANG_IRGENERATOR_H
#define SLANG_IRGENERATOR_H

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

#include "AST.h"
#include "NodeVisitor.h"

// TODO: Add comprehensive comments to this file

class IRGenerator : public NodeVisitor {
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    std::map<std::string, llvm::Value *> namedValues;

    // create an anonymous function and a basic block to hold the code
    llvm::Function *function;
    llvm::BasicBlock *entry;

    // create a printf prototype
    llvm::Function *PrintfFunc;

    // this is here only temporarily.
    // TODO: Move this to a more appropriate location
    llvm::Function *getPrintfPrototype() {
        // Function Prototype for printf
        std::vector<llvm::Type *> printfArgs = {builder->getInt8Ty()->getPointerTo()};
        auto printfType = llvm::FunctionType::get(builder->getInt32Ty(), printfArgs, true);
        return llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "println", module.get());
    }

//    // Utility to create a call to printf
//    void printf(const char *format, std::vector<llvm::Value *> args) {
//        auto formatStr = builder->CreateGlobalStringPtr(format);
//        std::vector<llvm::Value *> finalArgs = {formatStr};
//        finalArgs.insert(finalArgs.end(), args.begin(), args.end());
//        builder->CreateCall(PrintfFunc, finalArgs);
//    }

    // General printf function
    void printf(const char *format, std::vector<llvm::Value *> args) {
        auto formatStr = builder->CreateGlobalStringPtr(format);
        std::vector<llvm::Value *> finalArgs = {formatStr};
        finalArgs.insert(finalArgs.end(), args.begin(), args.end());
        builder->CreateCall(PrintfFunc, finalArgs);
    }

    // Overloaded printf specifically for double values
    void printf(double value) {
        auto formatStr = builder->CreateGlobalStringPtr("%f\n");

        // Correctly create a double value constant within the LLVM context
        auto doubleType = llvm::Type::getDoubleTy(*context); // Ensure the context is dereferenced if it's a pointer
        auto doubleValue = llvm::ConstantFP::get(doubleType, value);

        builder->CreateCall(PrintfFunc, {
                formatStr,
                builder->CreateFPCast(doubleValue, doubleType) // Ensure the cast is to the correct double type
        });
    }

    llvm::Value *lastValue = nullptr;

public:
//    void initializeContext();

    IRGenerator() {
        context = std::make_unique<llvm::LLVMContext>();
        module = std::make_unique<llvm::Module>("slang", *context);
        builder = std::make_unique<llvm::IRBuilder<>>(*context);

        // Adjusted to return an i32 instead of void
        function = llvm::Function::Create(llvm::FunctionType::get(llvm::Type::getInt32Ty(*context), false),
                                          llvm::Function::ExternalLinkage, "main", module.get());
        entry = llvm::BasicBlock::Create(*context, "entry", function);
        builder->SetInsertPoint(entry);

//        // Define two integer constants
//        llvm::Value *val1 = llvm::ConstantInt::get(*context, llvm::APInt(32, 5));
//        llvm::Value *val2 = llvm::ConstantInt::get(*context, llvm::APInt(32, 3));
//
//        // Perform an addition operation
//        llvm::Value *sum = builder->CreateAdd(val1, val2, "sum");
//
//        // Adjusted to return the sum
//        builder->CreateRet(sum);

        // Initialize printf prototype
        std::vector<llvm::Type *> printfArgs = {builder->getInt8Ty()->getPointerTo()};
        auto printfType = llvm::FunctionType::get(builder->getInt32Ty(), printfArgs, true);
        PrintfFunc = llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "println", module.get());

        // Print out the module IR to stdout
//        module->print(llvm::outs(), nullptr);
    }


    // temp function
    void logModule() {
        module->print(llvm::outs(), nullptr);
    }

public:
    void visit(ProgramNode *node) override;

    void visit(PrintNode *node) override;

    void visit(NumberNode *node) override;

    void visit(ExpressionNode *node) override;

    void visit(BinaryExpressionNode *node) override;

    void visit(UnaryExpressionNode *node) override;
//    void visit(class IdentifierNode *node) override;
//    void visit(class AssignmentNode *node) override;
};


#endif //SLANG_IRGENERATOR_H

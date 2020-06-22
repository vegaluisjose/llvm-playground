#include "llvm/Analysis/IVUsers.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Pass.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/FormatVariadic.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Transforms/Utils.h"
#include "llvm/Transforms/Utils/Mem2Reg.h"
#include "llvm/Transforms/Utils/ModuleUtils.h"

#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace llvm;
using namespace std;

namespace {

  struct Instr : public ModulePass {
    static char ID;

    Instr() : ModulePass(ID) { }

    ~Instr() {}

    string stringifyValue(Value &V) {
      string ValueString;
      raw_string_ostream ValueStream(ValueString);
      ValueStream << V;
      return ValueStream.str();
    }

    string stringifyPtr(Value &V) {
      string PtrString;
      raw_string_ostream PtrStream(PtrString);
      PtrStream << &V;
      return PtrStream.str();
    }

    string stringifyType(Type *T) {
      string TypeString;
      raw_string_ostream TypeStream(TypeString);
      TypeStream << *T;
      return TypeStream.str();
    }

    virtual bool runOnModule(Module &M) {

      for (auto &F : M) {
        for (auto &B : F) {
          for (auto &I : B) {
            errs() << I.getOpcodeName() << "\n";
          }
        }
      }

      return false;
    }

  };
}

char Instr::ID = 0;

static RegisterPass<Instr> Y("instr", "pass for printing instructions");

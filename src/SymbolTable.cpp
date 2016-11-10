#include "SymbolTable.h"

SymbolTable::SymbolTable() {
}

SymbolTable& SymbolTable::operator=(const SymbolTable& table) {
    this->entryList = table.entryList;
    return *this;
}

SymbolTable::~SymbolTable() {
}

void SymbolTable::clear() {
    entryList.clear();
}

bool SymbolTable::existsSymbol(std::string id) const {
    return entryList.find(id) != entryList.end();
}

Symbol SymbolTable::getSymbol(std::string id) const {
    return entryList.at(id);
}

std::vector<std::string> SymbolTable::getUninitializedFunctions() {
    std::map<std::string, Symbol>::iterator iter;
    std::vector<std::string> functions;

    for(iter = entryList.begin(); iter != entryList.end(); iter++) {
        if(!entryList[iter->first].initialized)
            functions.push_back(iter->first);
    }

    return functions;
}

void SymbolTable::addSymbol(std::string id, Symbol newSymbol) {
    entryList[id] = newSymbol;
}

void SymbolTable::setInitializedSymbol(std::string id) {
    entryList[id].initialized = true;
}

void SymbolTable::setSymbolData(const std::string id, TreeNode* data) {
    if(entryList[id].data) {
        delete entryList[id].data;
        entryList[id].data = 0;
    }

    entryList[id].data = data;
}

llvm::Value* SymbolTable::useVariable(std::string id){
  if (!existsSymbol(id)) { //Variable never declared
      ERROR_LOGGER->log(ErrorLogger::SEMANTIC, "Undeclared variable " + id);
      return NULL;
  } else {
      return allocations[id]; //Gets its value
  }
}

void SymbolTable::allocateVariable(std::string id, llvm::Value* v){
    if (v!= NULL)
      allocations[id] = v;
    allocations[id] = IR::Zero;
}

void SymbolTable::updateVariable (std::string id, llvm::Value * value){
    if (!existsSymbol(id) ) { //Variable never declared
        std::cout << "Variable not declared: " << id.c_str() << std::endl;
    } else {
        allocations[id] = value; //Updates its value
    }
}

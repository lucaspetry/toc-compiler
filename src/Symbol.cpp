#include "Symbol.h"

Symbol::Symbol() {
    this->dataType = Data::UNKNOWN;
    this->idType = Symbol::UNKNOWN;
    this->initialized = false;
    this->encapsulation = false;
}

Symbol::Symbol(Data::Type dataType, IdentifierType idType, bool initialized, TreeNode* data) {
    this->dataType = dataType;
    this->idType = idType;
    this->initialized = initialized;
    this->data = data;
    this->encapsulation = false;
}

Symbol::~Symbol() {
}

TreeNode* Symbol::getData() {
    return this->data;
}

Data::Type Symbol::getDataType() const {
    return this->dataType;
}

void Symbol::setEncapsulation(bool value){
    this->encapsulation = value;
}

Symbol::IdentifierType Symbol::getType() const {
    return this->idType;
}

bool Symbol::isInitialized() const {
    return this->initialized;
}

void Symbol::setDataType(Data::Type type) {
    this->dataType = type;
}

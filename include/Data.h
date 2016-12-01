#ifndef DATA_H_
#define DATA_H_

#include "LLVM.h"
#include <string>

/**
 * Dados
 */
namespace Data {

    /**
     * Tipos de dados
     */
    enum Type {
        UNKNOWN = -1,
        BOO = 1,
        FLT = 3,
        INT = 2,
        STR = 4,
        OBJ = 5,
        VOID = 6
    };

    /**
     * Obter o tipo de forma textual
     * @param type tipo de dado
     * @return texto do tipo
     */
    std::string toString(Data::Type type);

    llvm::Type* toLLVMType(Data::Type type);

}

#endif

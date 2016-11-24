#ifndef DATA_H_
#define DATA_H_

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
        VOID = 5
    };

    /**
     * Obter o tipo de forma textual
     * @param type tipo de dado
     * @return texto do tipo
     */
    std::string toString(Data::Type type);

}

#endif
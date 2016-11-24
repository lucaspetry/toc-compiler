#ifndef SYMBOL_H_
#define SYMBOL_H_

#include "TreeNode.h"

class Scope;

/**
 * Símbolo gerado na análise sintática
 */
class Symbol {

    friend class Scope;

    public:
        /**
         * Tipo do identificador representado pelo símbolo
         */
        enum IdentifierType {
            UNKNOWN,
            FUNCTION,
            VARIABLE
        };

        /**
         * Construir um símbolo padrão
         */
        Symbol();

        /**
         * Construir um símbolo
         * @param dataType
         * @param idType
         * @param initialized
         * @param data
         */
        Symbol(Data::Type dataType, IdentifierType idType, bool initialized, TreeNode* data = NULL);

        /**
         * Destruir o símbolo
         */
        virtual ~Symbol();

        /**
         * Obter o dado correspondente ao símbolo
         * @return nodo da árvore sintática correspondente
         */
        const TreeNode* getData() const;

        /**
         * Obter o tipo de dado do símbolo
         * @return tipo de dado do símbolo
         */
        Data::Type getDataType() const;

        /**
         * Obter o tipo do identificador do símbolo
         * @return tipo do identificador do símbolo
         */
        IdentifierType getType() const;

        /**
         * Verificar se o símbolo foi inicializado
         * @return true se o símbolo já foi inicializado
         */
        bool isInitialized() const;

        /**
         * Definir o tipo de dado
         * @param type tipo de dado do símbolo
         */
        void setDataType(Data::Type type);

    private:
        Data::Type dataType;
        IdentifierType idType;
        bool initialized;
        TreeNode* data;

};

#endif

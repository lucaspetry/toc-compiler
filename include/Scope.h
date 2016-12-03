#ifndef SCOPE_H_
#define SCOPE_H_

#include "LLVM.h"
#include "Symbol.h"
#include <map>
#include <string>
#include <vector>

class CodeBlock;
class TreeNode;

typedef std::map<std::string, llvm::Value*> MemoryMap;

/**
 * Escopo da tabela de símbolos
 */
class Scope {

    friend class SymbolTable;

    public:
        /**
         * Construir um escopo
         * @param parent escopo pai
         */
        Scope(Scope* parent = NULL);

        /**
         * Destruir o escopo
         */
        virtual ~Scope();

        /**
         * Operador de atribuição de escopos
         * @param scope escopo a ser copiado
         * @return novo escopo
         */
        Scope& operator=(const Scope& scope);

        /**
         * Limpar todo o conteúdo do escopo
         */
        void clear();

        /**
         * Obter o pai do escopo
         * @return o escopo pai
         */
        Scope* getParent();

        /**
         * Definir o escopo pai
         * @param parent escopo pai
         */
        void setParent(Scope* parent);

        /**
         * Obter um símbolo do escopo
         * @param id identificador do símbolo
         * @return o símbolo encontrado
         */
        Symbol getSymbol(std::string id) const;

        /**
         * Verificar se um símbolo existe
         * @param id identificador do símbolo
         * @return true se o símbolo existe
         */
        bool existsSymbol(std::string id) const;

        /**
         * Verificar se um símbolo já foi inicializado
         * @param id identificador do símbolo
         * @return true se o símbolo já foi inicializado
         */
        bool isSymbolInitialized(std::string id) const;

        /**
         * Adicionar um novo símbolo ao escopo
         * @param id identificador do símbolo
         * @param newSymbol novo símbolo a ser adicionado
         */
        void addSymbol(const std::string id, Symbol newSymbol);

        /**
         * Inicializar um símbolo do escopo
         * @param id identificador do símbolo
         */
        void setInitializedSymbol(const std::string id, TreeNode* data = NULL);
        /**
         * Setar o encapsulamento de um atributo
         * @param id identificador do símbolo
         * @param encapsulation publico ou privado
         */
        void setEncapsulation(std::string id, int encapsulation);
        /**
         * Definir o dado correspondente ao símbolo
         * @param id identificador do símbolo
         * @param data nodo da árvore sintática correspondente ao símbolo
         */
        void setSymbolData(const std::string id, TreeNode* data);

        /**
         * Atribuir um tipo a todos os tipos desconhecidos
         * @param type tipo a ser atribuído
         */
        void setUnknownTypes(Data::Type type);

        /**
         * Obter o mapa de alocações de memória
         * @return mapa de alocações
         */
        MemoryMap getMemoryMap() const;

        /**
         * Obter a alocação de uma variável
         * @param id identificador da variável
         * @return alocação da variável
         */
        llvm::Value* getVariableAllocation(std::string id);

        /**
         * Atualizar o valor alocado pelo LLVM para uma variável
         * @param id identificador da variável
         * @param value alocação da variável
         */
        void updateVariableAllocation(std::string id, llvm::Value* value);

    private:
        Scope* parent;
        std::map<std::string, Symbol> entryList;
        MemoryMap allocations;
        int indentation;
        CodeBlock* code;
        TreeNode* structure;
        TreeNode* lastStatement;

};

#endif

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "LLVM.h"
#include "Data.h"
#include <memory>
#include <string>

class CodeBlock;
class Symbol;
class Scope;
class TreeNode;

typedef std::map<std::string, llvm::Value*> MemoryMap;

/**
 * Table de símbolos
 */
class SymbolTable {

        friend class TreeNode;
    friend class SemanticAnalyzer;
    friend class Function;

    public:
        /**
         * Construir uma tabela de símbolos padrão
         */
        SymbolTable();

        /**
         * Destruir a tabela de símbolos
         */
        virtual ~SymbolTable();

        /**
         * Operador de atribuição de tabelas de símbolos
         * @param table tabela de símbolos a ser copiada
         * @return nova tabela de símbolos
         */
        SymbolTable& operator=(const SymbolTable& table);

        /**
         * Criar um novo escopo
         */
        void newScope();

        /**
         * Retornar para o escopo anterior ao atual
         */
        void returnScope();

        /**
         * Adicionar nova linha de código ao escopo atual
         * @param line linha de código
         */
        void pushLineScope(TreeNode* line);

        /**
         * Obter o bloco de código atual
         * @return bloco de código atual
         */
        CodeBlock* getCurrentCodeBlock();

        /**
         * Obter a estrutura pai do escopo atual
         * @return a estrutura
         */
        TreeNode* getParentStructure();

        void setCurrentStructure(TreeNode* node);

        TreeNode* getLastStatement();

        void setLastStatement(TreeNode* node);

        /**
         * Obter a indentação atual
         * @return a indentação atual
         */
        int getCurrentIndentation();

        /**
         * Limpar todo o conteúdo da tabela de símbolos
         */
        void clear();

        /**
         * Obter um símbolo da tabela
         * @param id identificador do símbolo
         * @param checkParentScope true se deseja verificar também os escopos mais externos
         * @return o símbolo encontrado
         */
        Symbol getSymbol(std::string id, bool checkParentScope = false) const;

        /**
         * Verificar se um símbolo existe
         * @param id identificador do símbolo
         * @param checkParentScope true se deseja verificar também os escopos mais externos
         * @return true se o símbolo existe
         */
        bool existsSymbol(std::string id, bool checkParentScope = false) const;

        /**
         * Verificar se um símbolo já foi inicializado
         * @param id identificador do símbolo
         * @param checkParentScope true se deseja verificar também os escopos mais externos
         * @return true se o símbolo já foi inicializado
         */
        bool isSymbolInitialized(std::string id, bool checkParentScope = false) const;

        /**
         * Adicionar um novo símbolo à tabela
         * @param id identificador do símbolo
         * @param newSymbol novo símbolo a ser adicionado
         */
        void addSymbol(const std::string id, Symbol newSymbol);

        /**
         * Inicializar um símbolo da tabela
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
         * Obter as alocações de memória
         * @return mapa de alocações
         */
        MemoryMap getAllocations() const;

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
        Scope* currentScope;

};

#endif

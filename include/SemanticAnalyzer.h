#ifndef SEMANTICANALYZER_H_
#define SEMANTICANALYZER_H_

#include "ErrorLogger.h"
#include "CodeBlock.h"
#include "TocFunction.h"
#include "SymbolTable.h"
#include "Array.h"
#include "Integer.h"
#include "Variable.h"
#include "BinaryOperation.h"
#include "Conditional.h"
#include "TypeCasting.h"
#include "String.h"
#include "VariableDeclaration.h"
#include "Loop.h"
#include "LLVM.h"

#include <ctype.h>
#include <string>
#include <vector>

extern ErrorLogger* ERROR_LOGGER;

/**
 * Analisador semântico
 */
class SemanticAnalyzer {

    public:
        /**
         * Construir o analisador semântico
         */
        SemanticAnalyzer();

        /**
         * Destruir o analisador semântico
         */
        virtual ~SemanticAnalyzer();

        /**
         * Criar um novo escopo na tabela de símbolos
         */
        void newScope();

        /**
         * Retornar para o escopo anterior ao atual da tabela
         */
        void returnScope();

        /**
         * Definir o escopo atual
         * @param indentation número de indentações
         */
        void setScope(float indentation);

        /**
         * Adicionar nova linha de código ao escopo atual
         * @param line linha de código
         */
        void pushLineScope(TreeNode* line);

        /**
         * Obter o bloco de código da estrutura atual
         * @return bloco de código
         */
        CodeBlock* getCurrentBody();

        /**
         * Obter a indentação atual
         * @return a indentação atual
         */
        int getCurrentIndentation();

        /**
         * Atribuir um tipo a todos os tipos desconhecidos
         * @param type tipo a ser atribuído
         * @param codeBlock bloco de código a ser corrigido
         */
        void setUnknownTypes(Data::Type type, CodeBlock* codeBlock);

        /**
         * Analisar o programa (última função executada na análise sintática)
         */
        void analyzeProgram();

        /**
         * Analisar a criação de um novo escopo
         */
        void analyzeScopeCreation();

        /**
         * Analisar...
         * @param op
         */
        void analyzeCasting(BinaryOperation* op);

        /**
         * Analisar...
         * @param op
         */
        void analyzeRelationalOperationCasting(BinaryOperation* op);

        /**
         * Analisar a declaração de Loop each
         * @param id
         */
        void analyzeLoop(std::string id);

        /**
         * Verificar o uso de um identificador.
         * @param id identificador
         * @return true se o identificador pode ser usado
         */
        bool checkIdentifier(std::string id) const;

        /**
         * Declarar uma variável
         * @param varId
         * @param dataType
         * @param size
         * @return nodo correspondente à declaração
         */
        TreeNode* declareVariable(std::string varId, Data::Type dataType, int size = 0);

        /**
         * Declarar uma função
         * @param id identificador da função
         * @param params parâmetros da função
         * @param body corpo da função
         * @param ret retorno da função
         * @return nodo correspondente à declaração da função
         */
        TreeNode* declareFunction(std::string id, CodeBlock* params, CodeBlock* body, TreeNode* ret);

        /**
         * Declarar um condicional
         * @param expression expressão booleana do condicional
         * @param body corpo se expression for true
         * @return nodo correspondente à declaração do condicional
         */
        TreeNode* declareCondition(TreeNode* expression, CodeBlock* body);

        /**
         * Declarar ação secundário de um condicional
         * @param body corpo se a condição for false
         * @return nodo correspondente à declaração do condicional
         */
        TreeNode* declareElseCondition(CodeBlock* body);

        /**
         * Declarar uma chamada de print
         * @param param parâmetro a ser impresso na tela
         * @return nodo correspondente à declaração da função
         */
        TreeNode* declarePrint(TreeNode* param);

        /**
         * Atribuir um valor a uma variável
         * @param varId
         * @param index
         * @return
         */
        TreeNode* assignVariable(std::string varId, TreeNode* value, TreeNode* index = NULL);

        /**
         * Declarar e atribuir um valor a uma variável
         * @param varId
         * @param dataType
         * @param size
         * @return nodo correspondente à declaração
         */
        TreeNode* declareAssignVariable(std::string id, Data::Type dataType, TreeNode* value, int size = 0);

        /**
         * Declarar uma estrutura de repetição
         * @param init expressão de inicialização de variável
         * @param test expressão de teste de condição
         * @param attribuition expressão de atribuição de valor
         * @return nodo correspondente à declaração
         */
        TreeNode* declareLoop(TreeNode* init, TreeNode* test, TreeNode* attribuition);

        /**
         * Usar uma variável
         * @param varId
         * @param index
         * @return nodo correspondente à variável
         */
        TreeNode* useVariable(std::string varId, TreeNode* index = NULL);

    public:
        SymbolTable symbolTable;
        TreeNode* currentStructure;
        TreeNode* lastStructure;

};

#endif

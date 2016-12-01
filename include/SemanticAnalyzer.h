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
#include "Object.h"

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
         * Analisar a declaração de Array
         * @param id identificador da variavel
         * @param size posições do array
         * @param attribuition valores atribuidos ao array
         */
        void analyzeArray(std::string id, int size, TreeNode* attribuition);

        /**
         * Analisar a declaração de Array
         * @param id identificador da variavel
         * @param size posições do array
         */
        void analyzeAssignArray(std::string id, TreeNode* size);

        /**
         * Verificar o uso de um identificador.
         * @param id identificador
         * @return true se o identificador pode ser usado
         */
        bool checkIdentifier(std::string id) const;

        /**
         * Converter um nodo para o tipo especificado, se necessário
         * @param type tipo de destino
         * @param node nodo a ser convertido
         * @return o novo nodo do tipo especificado
         */
        TreeNode* cast(Data::Type type, TreeNode* node) const;

        /**
         * Declarar uma variável
         * @param varId
         * @param dataType
         * @param size
         * @return nodo correspondente à declaração
         */
        TreeNode* declareVariable(std::string varId, Data::Type dataType, int size = 0);

        TreeNode* declareBinaryOperation(TreeNode* left, BinaryOperation::Type op, TreeNode* right);

        /**
         * Declarar uma função
         * @param id identificador da função
         * @param params parâmetros da função
         * @param body corpo da função
         * @param returnType tipo de retorno da função
         * @return nodo correspondente à declaração da função
         */
        TreeNode* declareFunction(std::string id, CodeBlock* params, CodeBlock* body, Data::Type returnType);

        /**
         * Declarar de metodo
         * @param id identificador da metodo
         * @param params parâmetros da metodo
         * @param body corpo da metodo
         * @param returnType tipo de retorno da metodo
         * @param encapsulation encapsulamento do metodo
         * @return nodo correspondente à declaração da metodo
         */
        TreeNode* declareMethod(std::string id, CodeBlock* params, CodeBlock* body, Data::Type returnType, int encapsulation);

        /**
         * Declarar o retorno de uma função
         * @param ret expressão de retorno da função
         * @return nodo correspondente à declaração de retorno da função
         */
        TreeNode* declareFunctionReturn(TreeNode* ret);

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
         * Declarar uma estrutura de repetição
         * @param init expressão de inicialização de variável
         * @param test expressão de teste de condição
         * @param attribuition expressão de atribuição de valor
         * @return nodo correspondente à declaração
         */
        TreeNode* declareLoop(TreeNode* init, TreeNode* test, TreeNode* attribuition);

        /**
         * Declarar uma chamada de print
         * @param param parâmetro a ser impresso na tela
         * @return nodo correspondente à declaração da função
         */
        TreeNode* declarePrint(TreeNode* param);

        /**
         * Declarar um objeto
         * @param param id nome da classe
         * @param param parametros da classe
         * @param body corpo da classe
         * @return nodo correspondente a declaração do objeto
         */
        TreeNode* declareObject(std::string id, CodeBlock* param, CodeBlock* body);

        /**
         * Declarar atributos de um objeto
         * @param id nome do atributo
         * @param encapsulation valor do encapsulamento
         * @param type tipo do atributo
         * @param size posições do array
         * @return nodo correspondente à declaração de atributo
         */
        TreeNode* declareAttribute(std::string id, Data::Type type, int encapsulation, int size = 0);

        /**
         * Declarar atributos de um objeto
         * @param id nome do atributo
         * @param type tipo do atributo
         * @param encapsulation valor do encapsulamento
         * @param value valor a ser atribuido
         * @param size posições do array
         * @return nodo correspondente à declaração de atributo
         */
        TreeNode* declareAssignAttribute(std::string id, Data::Type type, int encapsulation, TreeNode* value, int size = 0);

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
         * Usar uma variável
         * @param varId
         * @param index
         * @return nodo correspondente à variável
         */
        TreeNode* useVariable(std::string varId, TreeNode* index = NULL);

    public:
        SymbolTable symbolTable;
        TreeNode* currentStructure;
        TreeNode* lastStatement;

};

#endif

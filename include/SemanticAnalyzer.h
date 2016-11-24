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
#include "TypeCasting.h"
#include "String.h"
#include "VariableDeclaration.h"
#include "LLVM.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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
         * Atribuir um valor a uma variável
         * @param varId 
         * @param index 
         * @return 
         */
        TreeNode* assignVariable(std::string varId, TreeNode* index = NULL);
    
        /**
         * Declarar e atribuir um valor a uma variável
         * @param varId 
         * @param dataType 
         * @param size 
         * @return nodo correspondente à declaração
         */
        TreeNode* declareAssignVariable(std::string id, Data::Type dataType, int size = 0);
    
        /**
         * Usar uma variável
         * @param varId 
         * @param index  
         * @return nodo correspondente à variável
         */
        TreeNode* useVariable(std::string varId, TreeNode* index = NULL);

    private:
        SymbolTable symbolTable;
};

#endif

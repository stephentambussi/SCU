/*
 * File:	checker.h
 *
 * Description:	This file contains the public function declarations for the
 *		semantic checker for Simple C.
 */

# ifndef CHECKER_H
# define CHECKER_H
# include <string>
# include "Scope.h"

Scope *openScope();
Scope *closeScope();

void openStruct(const std::string &name);
void closeStruct(const std::string &name);

void declareSymbol(const std::string &name, const Type &type, bool = false);

Symbol *defineFunction(const std::string &name, const Type &type);
Symbol *checkIdentifier(const std::string &name);

Type checkArrayIndex(const Type &left, const Type &right);
Type checkCall(const Type &left, const Parameters &args);
Type checkDirectRef(const Type &left, const std::string &id);
Type checkIndirectRef(const Type &left, const std::string &id);
Type checkNot(const Type &left);
Type checkNeg(const Type &left);
Type checkDeref(const Type &left);
Type checkAddr(const Type &left, const bool &lvalue);
Type checkSizeof(const Type &left, const std::string &typespec, unsigned int ptrs);
Type checkTypeCast(const Type &left, const std::string &typespec, unsigned int ptrs);
Type checkMul(const Type &left, const Type &right);
Type checkDiv(const Type &left, const Type &right);
Type checkMod(const Type &left, const Type &right);
Type checkAdd(const Type &left, const Type &right);
Type checkSub(const Type &left, const Type &right);
Type checkLT(const Type &left, const Type &right);
Type checkGT(const Type &left, const Type &right);
Type checkLEQ(const Type &left, const Type &right);
Type checkGEQ(const Type &left, const Type &right);
Type checkEqual(const Type &left, const Type &right);
Type checkNotEqual(const Type &left, const Type &right);
Type checkLogicalAnd(const Type &left, const Type &right);
Type checkLogicalOr(const Type &left, const Type &right);
void checkAssignment(const Type &left, const Type &right, const bool &leftVal);
void checkReturn(const Type &t, const Type &return_type);
void checkWhile(const Type &t);
void checkFor(const Type &t);
void checkIf(const Type &t);

# endif /* CHECKER_H */

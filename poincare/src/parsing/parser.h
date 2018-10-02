#ifndef POINCARE_PARSING_PARSER_H
#define POINCARE_PARSING_PARSER_H

/* A precedence-climbing parser is implemented hereafter.
 * It is a trade-off between
 *   a readable but less efficient recursive-descent parser
 * and
 *   an efficient but less readable shunting-yard parser. */

#include "tokenizer.h"

#include <poincare/addition.h>
#include <poincare/division.h>
#include <poincare/equal.h>
#include <poincare/factorial.h>
#include <poincare/matrix.h>
#include <poincare/multiplication.h>
#include <poincare/opposite.h>
#include <poincare/parenthesis.h>
#include <poincare/power.h>
#include <poincare/square_root.h>
#include <poincare/store.h>
#include <poincare/subtraction.h>
#include <poincare/symbol.h>

namespace Poincare {

class Parser {
public:
  Parser(const char * input) :
    m_tokenizer(input),
    m_currentToken(Token(Token::Type::Undefined)),
    m_nextToken(m_tokenizer.popToken()) {}
  Expression parse();

  Expression parseNumber(Expression leftHandSide);
  Expression parsePlus(Expression leftHandSide);
  Expression parseTimes(Expression leftHandSide);
  Expression parseSlash(Expression leftHandSide);
  Expression parseMinus(Expression leftHandSide);
  Expression parsePower(Expression leftHandSide);
  Expression parseLeftParenthesis(Expression leftHandSide);
  Expression parseSquareRoot(Expression leftHandSide);
  Expression parseBang(Expression leftHandSide);
  Expression parseEqual(Expression leftHandSide);
  Expression noParse(Expression leftHandSide);
private:
  Expression parseUntil(Token::Type stoppingType);
  void popToken() {
    m_currentToken = m_nextToken;
    m_nextToken = m_tokenizer.popToken();
  }
  bool canPopToken(Token::Type stoppingType);

  Tokenizer m_tokenizer;
  Token m_currentToken;
  Token m_nextToken;
};

}

#endif
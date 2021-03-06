#include "parser/ParseTreeNode.hpp"
#include "parser/ParseTreeNodeVisitorDot.hpp"
#include "parser/Parser.hpp"
#include <gtest/gtest.h>
//---------------------------------------------------------------------------
namespace pljit {
//---------------------------------------------------------------------------
TEST(ParserDot, DotFormat0) {
    const std::string code = "BEGIN\n"
                             "RETURN 42\n"
                             "END.";
    SourceCodeManagement scm(code);
    Parser parser(scm);
    std::unique_ptr<NonTerminalParseTreeNode> parse_tree = parser.ParseFunctionDefinition();
    testing::internal::CaptureStdout();
    ParseTreeNodeVisitorDot visitor;
    visitor.Visit(*parse_tree);
    const std::string expected = "digraph {\n"
                                 "0 [label=\"FunctionDefinition\"];\n"
                                 "0 -> 1\n"
                                 "1 [label=\"CompoundStatement\"];\n"
                                 "1 -> 2\n"
                                 "2 [label=\"BEGIN\"];\n"
                                 "1 -> 4\n"
                                 "4 [label=\"StatementList\"];\n"
                                 "4 -> 5\n"
                                 "5 [label=\"Statement\"];\n"
                                 "5 -> 6\n"
                                 "6 [label=\"RETURN\"];\n"
                                 "5 -> 8\n"
                                 "8 [label=\"AdditiveExpression\"];\n"
                                 "8 -> 9\n"
                                 "9 [label=\"MultiplicativeExpression\"];\n"
                                 "9 -> 10\n"
                                 "10 [label=\"UnaryExpression\"];\n"
                                 "10 -> 11\n"
                                 "11 [label=\"PrimaryExpression\"];\n"
                                 "11 -> 12\n"
                                 "12 [label=\"Literal: 42\"];\n"
                                 "1 -> 14\n"
                                 "14 [label=\"END\"];\n"
                                 "0 -> 16\n"
                                 "16 [label=\".\"];\n"
                                 "}\n";
    EXPECT_EQ(testing::internal::GetCapturedStdout(), expected);
}
//---------------------------------------------------------------------------
TEST(ParserDot, DotFormat1) {
    const std::string code = "PARAM width, height;\n"
                             "BEGIN\n"
                             "width := 1000;\n"
                             "RETURN width * height\n"
                             "END.";
    SourceCodeManagement scm(code);
    Parser parser(scm);
    std::unique_ptr<NonTerminalParseTreeNode> parse_tree = parser.ParseFunctionDefinition();
    testing::internal::CaptureStdout();
    ParseTreeNodeVisitorDot visitor;
    visitor.Visit(*parse_tree);
    const std::string expected = "digraph {\n"
                                 "0 [label=\"FunctionDefinition\"];\n"
                                 "0 -> 1\n"
                                 "1 [label=\"ParameterDeclarations\"];\n"
                                 "1 -> 2\n"
                                 "2 [label=\"PARAM\"];\n"
                                 "1 -> 4\n"
                                 "4 [label=\"DeclaratorList\"];\n"
                                 "4 -> 5\n"
                                 "5 [label=\"Identifier: width\"];\n"
                                 "4 -> 7\n"
                                 "7 [label=\",\"];\n"
                                 "4 -> 9\n"
                                 "9 [label=\"Identifier: height\"];\n"
                                 "1 -> 11\n"
                                 "11 [label=\";\"];\n"
                                 "0 -> 13\n"
                                 "13 [label=\"CompoundStatement\"];\n"
                                 "13 -> 14\n"
                                 "14 [label=\"BEGIN\"];\n"
                                 "13 -> 16\n"
                                 "16 [label=\"StatementList\"];\n"
                                 "16 -> 17\n"
                                 "17 [label=\"Statement\"];\n"
                                 "17 -> 18\n"
                                 "18 [label=\"AssignmentExpression\"];\n"
                                 "18 -> 19\n"
                                 "19 [label=\"Identifier: width\"];\n"
                                 "18 -> 21\n"
                                 "21 [label=\":=\"];\n"
                                 "18 -> 23\n"
                                 "23 [label=\"AdditiveExpression\"];\n"
                                 "23 -> 24\n"
                                 "24 [label=\"MultiplicativeExpression\"];\n"
                                 "24 -> 25\n"
                                 "25 [label=\"UnaryExpression\"];\n"
                                 "25 -> 26\n"
                                 "26 [label=\"PrimaryExpression\"];\n"
                                 "26 -> 27\n"
                                 "27 [label=\"Literal: 1000\"];\n"
                                 "16 -> 29\n"
                                 "29 [label=\";\"];\n"
                                 "16 -> 31\n"
                                 "31 [label=\"Statement\"];\n"
                                 "31 -> 32\n"
                                 "32 [label=\"RETURN\"];\n"
                                 "31 -> 34\n"
                                 "34 [label=\"AdditiveExpression\"];\n"
                                 "34 -> 35\n"
                                 "35 [label=\"MultiplicativeExpression\"];\n"
                                 "35 -> 36\n"
                                 "36 [label=\"UnaryExpression\"];\n"
                                 "36 -> 37\n"
                                 "37 [label=\"PrimaryExpression\"];\n"
                                 "37 -> 38\n"
                                 "38 [label=\"Identifier: width\"];\n"
                                 "35 -> 40\n"
                                 "40 [label=\"*\"];\n"
                                 "35 -> 42\n"
                                 "42 [label=\"MultiplicativeExpression\"];\n"
                                 "42 -> 43\n"
                                 "43 [label=\"UnaryExpression\"];\n"
                                 "43 -> 44\n"
                                 "44 [label=\"PrimaryExpression\"];\n"
                                 "44 -> 45\n"
                                 "45 [label=\"Identifier: height\"];\n"
                                 "13 -> 47\n"
                                 "47 [label=\"END\"];\n"
                                 "0 -> 49\n"
                                 "49 [label=\".\"];\n"
                                 "}\n";
    EXPECT_EQ(testing::internal::GetCapturedStdout(), expected);
}
//---------------------------------------------------------------------------
TEST(ParserDot, DotFormat2) {
    const std::string code = "PARAM width, height, depth;\n"
                             "VAR volume;\n"
                             "CONST density = 42;\n"
                             "BEGIN\n"
                             "volume := width * height;\n"
                             "RETURN density * volume\n"
                             "END.";
    SourceCodeManagement scm(code);
    Parser parser(scm);
    std::unique_ptr<NonTerminalParseTreeNode> parse_tree = parser.ParseFunctionDefinition();
    testing::internal::CaptureStdout();
    ParseTreeNodeVisitorDot visitor;
    visitor.Visit(*parse_tree);
    const std::string expected = "digraph {\n"
                                 "0 [label=\"FunctionDefinition\"];\n"
                                 "0 -> 1\n"
                                 "1 [label=\"ParameterDeclarations\"];\n"
                                 "1 -> 2\n"
                                 "2 [label=\"PARAM\"];\n"
                                 "1 -> 4\n"
                                 "4 [label=\"DeclaratorList\"];\n"
                                 "4 -> 5\n"
                                 "5 [label=\"Identifier: width\"];\n"
                                 "4 -> 7\n"
                                 "7 [label=\",\"];\n"
                                 "4 -> 9\n"
                                 "9 [label=\"Identifier: height\"];\n"
                                 "4 -> 11\n"
                                 "11 [label=\",\"];\n"
                                 "4 -> 13\n"
                                 "13 [label=\"Identifier: depth\"];\n"
                                 "1 -> 15\n"
                                 "15 [label=\";\"];\n"
                                 "0 -> 17\n"
                                 "17 [label=\"VariableDeclarations\"];\n"
                                 "17 -> 18\n"
                                 "18 [label=\"VAR\"];\n"
                                 "17 -> 20\n"
                                 "20 [label=\"DeclaratorList\"];\n"
                                 "20 -> 21\n"
                                 "21 [label=\"Identifier: volume\"];\n"
                                 "17 -> 23\n"
                                 "23 [label=\";\"];\n"
                                 "0 -> 25\n"
                                 "25 [label=\"ConstantDeclarations\"];\n"
                                 "25 -> 26\n"
                                 "26 [label=\"CONST\"];\n"
                                 "25 -> 28\n"
                                 "28 [label=\"InitDeclaratorList\"];\n"
                                 "28 -> 29\n"
                                 "29 [label=\"InitDeclarator\"];\n"
                                 "29 -> 30\n"
                                 "30 [label=\"Identifier: density\"];\n"
                                 "29 -> 32\n"
                                 "32 [label=\"=\"];\n"
                                 "29 -> 34\n"
                                 "34 [label=\"Literal: 42\"];\n"
                                 "25 -> 36\n"
                                 "36 [label=\";\"];\n"
                                 "0 -> 38\n"
                                 "38 [label=\"CompoundStatement\"];\n"
                                 "38 -> 39\n"
                                 "39 [label=\"BEGIN\"];\n"
                                 "38 -> 41\n"
                                 "41 [label=\"StatementList\"];\n"
                                 "41 -> 42\n"
                                 "42 [label=\"Statement\"];\n"
                                 "42 -> 43\n"
                                 "43 [label=\"AssignmentExpression\"];\n"
                                 "43 -> 44\n"
                                 "44 [label=\"Identifier: volume\"];\n"
                                 "43 -> 46\n"
                                 "46 [label=\":=\"];\n"
                                 "43 -> 48\n"
                                 "48 [label=\"AdditiveExpression\"];\n"
                                 "48 -> 49\n"
                                 "49 [label=\"MultiplicativeExpression\"];\n"
                                 "49 -> 50\n"
                                 "50 [label=\"UnaryExpression\"];\n"
                                 "50 -> 51\n"
                                 "51 [label=\"PrimaryExpression\"];\n"
                                 "51 -> 52\n"
                                 "52 [label=\"Identifier: width\"];\n"
                                 "49 -> 54\n"
                                 "54 [label=\"*\"];\n"
                                 "49 -> 56\n"
                                 "56 [label=\"MultiplicativeExpression\"];\n"
                                 "56 -> 57\n"
                                 "57 [label=\"UnaryExpression\"];\n"
                                 "57 -> 58\n"
                                 "58 [label=\"PrimaryExpression\"];\n"
                                 "58 -> 59\n"
                                 "59 [label=\"Identifier: height\"];\n"
                                 "41 -> 61\n"
                                 "61 [label=\";\"];\n"
                                 "41 -> 63\n"
                                 "63 [label=\"Statement\"];\n"
                                 "63 -> 64\n"
                                 "64 [label=\"RETURN\"];\n"
                                 "63 -> 66\n"
                                 "66 [label=\"AdditiveExpression\"];\n"
                                 "66 -> 67\n"
                                 "67 [label=\"MultiplicativeExpression\"];\n"
                                 "67 -> 68\n"
                                 "68 [label=\"UnaryExpression\"];\n"
                                 "68 -> 69\n"
                                 "69 [label=\"PrimaryExpression\"];\n"
                                 "69 -> 70\n"
                                 "70 [label=\"Identifier: density\"];\n"
                                 "67 -> 72\n"
                                 "72 [label=\"*\"];\n"
                                 "67 -> 74\n"
                                 "74 [label=\"MultiplicativeExpression\"];\n"
                                 "74 -> 75\n"
                                 "75 [label=\"UnaryExpression\"];\n"
                                 "75 -> 76\n"
                                 "76 [label=\"PrimaryExpression\"];\n"
                                 "76 -> 77\n"
                                 "77 [label=\"Identifier: volume\"];\n"
                                 "38 -> 79\n"
                                 "79 [label=\"END\"];\n"
                                 "0 -> 81\n"
                                 "81 [label=\".\"];\n"
                                 "}\n";
    EXPECT_EQ(testing::internal::GetCapturedStdout(), expected);
}
//---------------------------------------------------------------------------
} // namespace pljit
//---------------------------------------------------------------------------

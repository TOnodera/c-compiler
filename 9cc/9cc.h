#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// トークンの種類
typedef enum
{
    TK_RESERVED, // 記号
    TK_INDENT,   // 識別子
    TK_NUM,      // 整数トークン
    TK_EOF,      // 入力の終わりを表す
} TokenKind;

typedef struct Token Token;

struct Token
{
    TokenKind kind;
    Token *next;
    int val;   // kindがNUMの場合、その数値
    char *str; // トークン文字列
    int len;   // トーケンの
};

extern Token *token; // 現在着目しているトークン
// 入力プログラム
extern char *user_input;

// 抽象構文木のノードの種類
typedef enum
{
    ND_ADD, // +
    ND_SUB, // -
    ND_MUL, // *
    ND_DIV, // /
    ND_NUM, // 整数
    ND_EQ,  // ==
    ND_NE,  // !=
    ND_LT,  // <
    ND_LE,  // <=
} NodeKind;

struct Node
{
    NodeKind kind;
    struct Node *lhs;
    struct Node *rhs;
    int val; // kindが整数の場合のみ使う
};

typedef struct Node Node;

Node *new_node(NodeKind kind);
Node *new_node_num(int val);
Node *expr();
Node *equality();
Node *relational();
Node *add();
Node *primary();
Node *mul();
void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);
bool consume(char *op);
void expect(char *op);
int expect_number();
bool at_eof();
Token *new_token(TokenKind kind, Token *cur, char *str, int len);
bool startswith(char *p, char *q);
Token *tokenize();
void gen(Node *node);
Node *unary();
Node *new_binary(NodeKind kind, Node *lhs, Node *rhs);
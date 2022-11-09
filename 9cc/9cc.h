// トークンの種類
typedef enum
{
    TK_RESERVED, // 記号
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
    int len;   // トークンの長さ
};

Token *token; // 現在着目しているトークン

// 抽象構文木のノードの種類
typedef enum
{
    ND_ADD, // +
    ND_SUB, // -
    ND_MUL, // *
    ND_DIV, // /
    ND_NUM, // 整数
} NodeKind;

struct Node
{
    NodeKind kind;
    struct Node *lhs;
    struct Node *rhs;
    int val; // kindが整数の場合のみ使う
};

typedef struct Node Node;

// 入力プログラム
char *user_input;

Node *new_node(NodeKind kind, Node *lhs, Node *rhs);
Node *new_node_num(int val);
Node *expr();
Node *primary();
Node *mul();
void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);
bool consume(char op);
void expect(char op);
int expect_number();
bool at_eof();
Token *new_token(TokenKind kind, Token *cur, char *str);
Token *tokenize(char *p);
void gen(Node *node);
Node *unary();
Node *new_node(NodeKind kind, Node *lhs, Node *rhs)
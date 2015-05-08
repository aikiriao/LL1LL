#ifndef SHARE_H_INCLUDED
#define SHARE_H_INCLUDED

/* エラー時の文字列バッファの長さ */
#define LINE_BUF_SIZE (100)

/* LL1LLの値の不完全型宣言(配列で参照される...) */
typedef struct LL1LL_Value_tag *LL1LL_Value;

/* LL1LLの型の種類 */
typedef enum {
  LL1LL_INT_TYPE,     /* 整数型 */
  LL1LL_DOUBLE_TYPE,  /* 倍精度実数型 */
  LL1LL_BOOLEAN_TYPE, /* 論理型 */
  LL1LL_OBJECT_TYPE,  /* 参照型(配列や文字列など, ポインタを介するもの) */
  LL1LL_NULL_TYPE,    /* NULL型 */
} LL1LL_TypeKind;

/* LL1LLのオブジェクトの種類 */
typedef enum {
  ARRAY_OBJECT,   /* 配列オブジェクト */
  STRING_OBJECT,  /* 文字列オブジェクト */
  /* CLASS_OBJECT coming soon! */
} LL1LL_ObjectType;

/* LL1LLの配列の構造体 */
typedef struct {
  int size;           /* 配列の要素数 */
  int alloc_size;     /* 割り当てサイズ */
  LL1LL_Value *array; /* 配列そのもの */
} LL1LL_Array;

/* LL1LLの文字列の構造体 */
typedef struct {
  LL1LL_Boolean is_literal; /* リテラルか否か */
  char          *string;    /* 文字列そのもの */
} LL1LL_String;

/* LL1LLのオブジェクトの構造体:双方向リスト */
typedef struct LL1LL_Object_tag {
  LL1LL_ObjectType type;  /* オブジェクトの種類 */
  unsigned int marked:1;  /* マークされたか(GC用) */
  union { /* 中身 */
    LL1LL_Array  array;  
    LL1LL_String string;
    /* LL1LL_Class class; comming soon! */
  } u;
  struct LL1LL_Object_tag *prev; /* 前の要素 */
  struct LL1LL_Object_tag *next; /* 次の要素 */
} LL1LL_Object;

/* LL1LLの論理型：実体は列挙型 */
typedef enum {
  LL1LL_FALSE = 0,  /* 偽 */
  LL1LL_TRUE  = 1,  /* 真 */
} LL1LL_Boolean;

/* LL1LLの値の構造体 */
typedef struct LL1LL_Value_tag {
  LL1LL_TypeKind type;  /* 型 */
  union {
    int           int_value;      /* 整数値 */
    double        double_value;   /* 倍精度実数 */
    LL1LL_Boolean boolean_value;  /* 論理値 */
    LL1LL_Object  *object;        /* オブジェクト参照 */
  } u;
};

/* 入力ソース */
extern FILE* input_source;

#endif /* SHARE_H_INCLUDED */
// 头文件：类型的定义和 API 的声明

typedef int E;

typedef struct {
	E* elements;
	int capacity;
	int size;
} Vector;

// 构造函数
Vector* vector_create(void);
// 析构函数
void  vector_destroy(Vector* v);

void push_back(Vector* v, E val);

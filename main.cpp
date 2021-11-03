#include <iostream>
#include <list>

using namespace std;

enum meta_type_t
{
    _int,
    _float,
    _double
};

struct node {
    node *prev;
    meta_type_t type;
    uint8_t size;
    node *next;
};

#define meta_type(type) _##type
//#define meta(type,x) type,x
#define meta_int(x) int,x
#define meta_float(x) float,x
#define meta_double(x) double,x

#define member(_1,_2,_3,_4,_5,_6) \
    _1 _2; \
    _3 _4; \
    _5 _6;

#define node_decl(_1,_2,_3,_4,_5,_6) \
    node node_##_2; \
    node node_##_4; \
    node node_##_6;

#define node_value(_1,_2,_3,_4,_5,_6) \
    node_##_2.prev = nullptr; \
    node_##_2.type = meta_type(_1); \
    node_##_2.size = sizeof(_1); \
    node_##_2.next = &node_##_4; \
    node_##_4.prev = &node_##_2; \
    node_##_4.type = meta_type(_3); \
    node_##_4.size = sizeof(_3); \
    node_##_4.next = &node_##_6; \
    node_##_6.prev = &node_##_4; \
    node_##_6.type = meta_type(_5); \
    node_##_6.size = sizeof(_5); \
    node_##_6.next = nullptr; \
    meta_data.push_back(node_##_2); \
    meta_data.push_back(node_##_4); \
    meta_data.push_back(node_##_6);

#define STRUCT_META(name,...) \
    struct name { member(__VA_ARGS__) }; \
    list<node> meta(struct name) { \
        list<node> meta_data; \
        node_decl(__VA_ARGS__); \
        node_value(__VA_ARGS__); \
        return meta_data; \
    }

STRUCT_META(xx,
            meta_int(a),
            meta_float(b),
            meta_double(c)
            )

struct x
{
    int a;
    float b;
    double c;
};


list<node> meta(struct x)
{
    list<node> meta_data;

    node node_a;
    node node_b;
    node node_c;

    node_a.prev = nullptr;
    node_a.type = _int;
    node_a.size = sizeof(int);
    node_a.next = &node_b;

    node_b.prev = &node_a;
    node_b.type = _float;
    node_b.size = sizeof(float);
    node_b.next = &node_c;

    node_c.prev = &node_b;
    node_c.type = _double;
    node_c.size = sizeof(double);
    node_c.next = nullptr;

    meta_data.push_back(node_a);
    meta_data.push_back(node_b);
    meta_data.push_back(node_c);
}

int main()
{

    struct xx v;
    list<node> nodes = meta(v);

    return 0;
}

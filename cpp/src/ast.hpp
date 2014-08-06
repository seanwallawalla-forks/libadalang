#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <iostream>

class ASTNode {
public:
    virtual ~ASTNode() {}
    int ref = 0;
    virtual std::string repr() { return "not impl"; }
    virtual std::string __name() { return "ASTNode"; }
    void inc_ref() { ref++; }
    int dec_ref() {
        ref--; 
        if (ref <= 0) {
            delete this;
            return true;
        }
        return false;
    }
};

template <typename T> class ASTList : public ASTNode {
protected:
public:
    std::vector<T> vec;
    std::string repr() { return vec_repr(vec); };
    ~ASTList() { 
        #if DEBUG_MODE
        printf("DELETING VECTOR\n");
        #endif
        vec_dec_ref (vec); 
    }
};

template <typename T> inline void vec_free (std::vector<T>& vec) { for (auto el : vec) el.free(); } 
template <typename T> inline void vec_free (std::vector<T*>& vec) { for (auto el : vec) el->free(); } 

template <typename T> inline std::string vec_repr (std::vector<T>& vec) {
    std::string res;
    for (auto el : vec) {
        if (res != "") res.append(", ");
        res.append(el.repr());
    }
    res.insert(0, "[");
    res.append("]");
    return res;
}

template <typename T> inline std::string vec_repr (std::vector<T*>& vec) {
    std::string res;
    for (auto el : vec) {
        if (res != "") res.append(", ");
        res.append(el->repr());
    }
    res.insert(0, "[");
    res.append("]");
    return res;
}

template <typename T> inline void vec_dec_ref (std::vector<T*>& vec) { for (auto el : vec) el->dec_ref(); }
template <typename T> inline void vec_dec_ref (std::vector<T>& vec) { for (auto el : vec) el.dec_ref(); }

#endif

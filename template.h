#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_


//定义一个非类型模版参数
template <unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M]){
    return N - M;
}

#endif //_TEMPLATE_H_
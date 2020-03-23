#include<map>
#include <iostream>
using namespace std;
typedef union dt_precond_optval_s {

    public:

    int    value;
    double dvalue;
    void  *pvalue;

    dt_precond_optval_s() { value=0; dvalue=0; pvalue=0; }
    dt_precond_optval_s(int val_) : value(val_) {}
    dt_precond_optval_s(double dval_) : dvalue(dval_) {}
    dt_precond_optval_s(void  *pval_) : pvalue(pval_) {}

} dt_precond_optval_t;

void union_test()
{
    int append = 1, skip_markvtx = 2, flag = 3, sethole = 4, sort = 5, dissected = 6, mask_tag = 7;
    int copy_attachment = 8;
    int keep_holeassign = 9;
    int copy_drcinfo = 10;
  
    std::map<int, dt_precond_optval_t> m_default;
    m_default.insert(std::make_pair(33, append));
    m_default.insert(std::make_pair(34, skip_markvtx));
    m_default.insert(std::make_pair(35, sethole));
    m_default.insert(std::make_pair(46, sort));
    m_default.insert(std::make_pair(48, dissected));
    m_default.insert(std::make_pair(52, copy_attachment));
    m_default.insert(std::make_pair(53, keep_holeassign));
    m_default.insert(std::make_pair(62, mask_tag));
    m_default.insert(std::make_pair(64, copy_drcinfo));

    std::map<int, dt_precond_optval_t>::iterator iter;
    iter = m_default.find(33);
    int out = iter->second.dvalue;
    cout << out << "\n";

}

int main()
{
    union_test();
    return 0;
}

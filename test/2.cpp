#include "src.hpp"
#if defined (_UNORDERED_MAP_)  || (defined (_LIST_)) || (defined (_MAP_)) || (defined (_SET_)) || (defined (_UNORDERED_SET_))||(defined (_GLIBCXX_MAP)) || (defined (_GLIBCXX_UNORDERED_MAP))
BOOM :)
#endif
#include<iostream>

int main() {
    freopen("2.in", "r", stdin);
    freopen("2.out", "w", stdout);
//    srand(0);
//    clock_t start, end;
//    start = clock();
    ESet<long long> s[25];
    ESet<long long>::iterator it;
    int op, lst=0, it_a=-1, valid = 0, cnt=1;
    while (scanf("%d", &op) != EOF) {
        long long a, b, c;
//        if(cnt==213){
//            printf("!!!");
//        }
        switch (op) {
            case 0: {
                scanf("%lld%lld", &a, &b);
                auto p=s[a].emplace(b);
                if(p.second) {
                	it_a = a;
                    it = p.first;
                    valid = 1;
                }
                break;
            }
            case 1:
                scanf("%lld%lld", &a, &b);
                if (valid && it_a==a && *it == b)valid = 0;
                s[a].erase(b);
                break;
            case 2:
                scanf("%lld", &a);
                s[++lst] = s[a];
                break;
            case 3: {
                scanf("%lld%lld", &a, &b);
                auto it2 = s[a].find(b);
                if (it2 != s[a].end()) {
                    printf("true\n");
                    it_a = a;
                    it = it2;
                    valid = 1;
                } else
                    printf("false\n");
                cnt++;
                break;
            }
            case 4:
                scanf("%lld%lld%lld", &a, &b, &c);
                printf("%d\n", s[a].range(b, c));
                cnt++;
                break;
            case 5:
                if (valid){
                    auto it2=it;
                    if (it==--it2)valid = 0;
                }
                if (valid)
                    printf("%lld\n", *(--it));
                else
                    printf("-1\n");
                cnt++;
                break;
            case 6:
                if (valid) {
                    auto it2=++it;
                    if (it==++it2)valid = 0;
                    else printf("%lld\n", *it);
                }
                if (!valid)
                    printf("-1\n");
                cnt++;
                break;
        }
    }
//    end = clock(); //程序结束用时
//    double endtime = (double) (end - start) / CLOCKS_PER_SEC;
//    printf("time=%lf s\n", endtime);
    return 0;
}

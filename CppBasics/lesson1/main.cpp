#include <iostream>

int main(){
    std::cout << "Hi!" << std::endl;
    int n;
    std::cin >> n;
    for(int i=0;i<15;i++){
         n=n+5;
    } 
    std::cout << n << std::endl;
    return 0;
}

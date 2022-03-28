#define WINDOWS

#include <iostream>
using namespace std;

// YAGNI... KISS... LOL, I HAVE INFINITE TIME CHEAT

/** мне просто стало любопытно, можно ли так и как
 * @brief waints any key to be pressed
 *  
 */
void wait(){
    #ifdef LINUX
        system("read");
    #else 
        #ifdef WINDOWS
        system("pause");
        #endif
    #endif
}

/**
 * @brief clears console screen
 * 
 */
void clsc(){
    #ifdef WINDOWS
        system("cls");
    #else
        #ifdef LINUX
            printf("\033c");
        #endif
    #endif
}

const int two1 = 4, two2 = 7;

void Lesson4(){
    clsc();
    int tasknum;
    cout << "Enter 1...5 to task or 0 to exit" << endl;
    cin >> tasknum;
    while (!(tasknum>=1 && tasknum<=5) && tasknum!=0) {
        clsc();
    cout << "!!!Enter 1...5 to task or 0 to exit!!!" << endl;
        cin >> tasknum;
	}
    switch(tasknum){
        case 0:
        {
            exit(0);
        }
        case 1:
        {
            clsc();
            int a,b;
            cout << "Enter 2 numbers : " << endl;  // мне было лень городить функцию проверки числа, и так намакаронил
            cin >> a >> b;
            ((a+b)>=10 && (a+b)<=20)?(cout<<"true"<<endl):(cout<<"false"<<endl);
            wait();
            Lesson4();
        }
        case 2:
        {
            clsc();
            cout << two1 << endl << two2 << endl;
            ( ((two1 == 10)&&(two2 == 10)) || (two1+two2 == 10))?(cout<<"true"<<endl):(cout<<"false"<<endl);
            wait();
            Lesson4();
        }
        case 3:
        {
            clsc();
            cout << "Your numbers: ";
            for(int i = 1;i < 50;i += 2){
                cout << i <<" ";
            }
            cout << endl;            
            wait();
            Lesson4();
        }
        case 4:
        {
            clsc();
            int num=0;
            cout << "enter any number: ";
            cin >> num;
            for(int i = 2; ;i++){
                if(i==num){
                    cout << num << " is simple"<<endl;
                    break;
                }
                if(!(num%i)){
                    cout << num << " is not simple, it can be divided by " << i << endl;
                    break;
                }
            }
            wait();
            Lesson4();
        }
        case 5:
        {
            clsc();
            int year=0;
            cout << "enter year(1...3000): ";
            cin >> year;
            ( !(year%4) && (year%100) || !(year%400) )?(cout<<"leap year"<<endl):(cout<<"usual year"<<endl);
            wait();
            Lesson4();
        }
        default:
        {
            cout << "LOL HOW" << endl;
            wait();
            Lesson4();
        }
    }
    wait();
}

int main(){
    Lesson4();
    
    return 0;
}

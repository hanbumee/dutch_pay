///created by hanbum-god
///gae ddock-ddock in-jeong in-jeong
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

int main(){

    map<int, string> name;
    cout << "\n\n\n\n";
    cout << "name your friend one by one(in english)" << endl;
    cout << "when you're done, type '!'" << endl << endl;
    cout << "usage) \nyour friends:\nbabo (enter)" << endl;
    cout << "mung-chung (enter)" << endl;
    cout << "jigak" << endl;
    cout << "! (enter)" << endl << endl;
    cout << "\n\nyour group:[babo(0), mungchung(1), jigak(2)]\nright?[y/n]:y\n";
    cout << "\n\nwho spent money?\n";
    cout << "when you're done, type '!'" << endl << endl;
    cout << "usage) person_paid\thow_much\tfriend[0]_attended?(yes:1 no:0)\tfriend[1]_attended?(yes:1 no:0)\tfriend[2]_attended?(yes:1 no:0)" << endl;
    cout << "0 10000 1 1 0  \t(babo가         10000원을    babo, mung-chung 과 사용)\n";
    cout << "1 20000 1 1 1  \t(mung-chung이   20000원을    babo, mung-chung, jigak 과 사용)\n";

    cout << "\n\n\n\n\n\nname your friend one by one(in english)" << endl;
    cout << "when you're done, type '!'" << endl << endl;
    int num = 0;
    while(1){
        string in;
        cin >> in;
        if(in == "!"){
            break;
        }
        name.insert(make_pair(num, in));
        num++;
    }

    int money_table[num][num];
    for(int i = 0; i < num; i++){
        for(int j = 0; j < num; j++){
            money_table[i][j] = 0;
        }
    }

    map<int, string>::iterator iter = name.begin();

    cout << "\n\nyour group:[";
    for(; iter != name.end(); iter++){
        cout << iter->second << "(" << iter->first << ")" <<", ";
    }
    cout <<"\b\b]"<<endl;
    
    cout <<"right? [y/n]:";
    char right;
    cin >> right;
    if(right != 'y'){
        cout << "다시하셈ㅅㄱ" << endl;
        return 0;
    }

    cout << "\n\nwho spent money?";
    cout << "when you're done, type '!'" << endl << endl;
    while(1){

        string in;
        getline(cin, in);
        
        if(in.length() == 0) continue;
        if(in[0] == '!') break;
        if(in[0] < '0' || in[0] > '9') return 0;

        int who_paid = 0;
        int how_much = 0;
        int num_spent = 0;

        int error = 0;

        int who_joined[num];
        for(int i = 0; i < num; i++) who_joined[i] = 0;
        
        int pos = 0;
        for(;in[pos] != ' '; pos++){
            who_paid = who_paid*10 + in[pos]-'0';
        }
        
        pos++;
        for(;in[pos] != ' '; pos++){
            how_much = how_much*10 + in[pos]-'0';
        }
        pos++;
        for(int i = 0; i < num; i++){
            int attend;
            attend = in[pos] - '0';
            pos+=2;
            if(attend != 0 && attend != 1){
                cout << "input error" <<num << endl;
                error = 1;
                break;
            }
            if(attend == 1){
                if(who_joined[i] == 1){
                    cout << "input error  "<< num << endl;
                    error = 1;
                    break;
                }else{
                    who_joined[i] = 1;
                    num_spent++;
                }
            }
        }

        if(error == 1) continue;
        
        how_much /= num_spent;

        for(int i = 0; i < num; i++){
            if(i == who_paid || who_joined[i] == 0) continue;
            money_table[i][who_paid] += how_much;
        }

        cout << who_paid << " " << how_much << " " << endl;

        for(int i = 0; i < num; i++){
            cout << " \t" << name[i];
        }
        for(int i = 0; i < num; i++){
            cout << "\n" <<name[i];
            for(int j = 0; j < num; j++){
                cout << "\t" << money_table[i][j];
            }
        }cout<<endl;
      
    }

    for(int i = 0; i < num; i++){
        for(int j = 0; j < i; j++){
            if(money_table[i][j] > money_table[j][i]){
                money_table[i][j] -= money_table[j][i];
                money_table[j][i] = 0;
            }else{
                money_table[j][i] -= money_table[i][j];
                money_table[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < num; i++){
            cout << " \t" << name[i];
        }
        for(int i = 0; i < num; i++){
            cout << "\n" <<name[i];
            for(int j = 0; j < num; j++){
                cout << "\t" << money_table[i][j];
            }
        }cout<<endl;

    int sink;
    int nowsink;
    int nextsink;
    for(int i = 0; i < num; i++){
        int sum = 0;
        for(int j = 0; j < num; j++){
            sum += money_table[i][j];
        }
        if(sum == 0) sink = i;//sink가 두명 이상이면?
    }
    nowsink = sink;
    
    bool done = 0;
    int sinkdone[num];
    int sinkdonenum = 0;
    for(int i = 0; i < num; i++) sinkdone[i] = 0;

    while(!done){      
        //find next sink;
        for(int i = 0; i < num; i++){// 마찬가지로 RACE condition 고려안됨
            int found = 1;
            if(i == nowsink) continue;
            int passedsink = 0;
            for(int k = 0; k < sinkdonenum; k++){
                if(i == sinkdone[k]){
                    passedsink = 1;
                    break;
                }
            }
            if(passedsink) continue;
            for(int j = 0; j < num; j++){
                if(money_table[i][j] != 0 && j != nowsink) {
                    found = 0;
                    break;
                }
            }
            if(found) nextsink = i;
        }
        cout << "sink found" << endl;
        cout << "nowsink " << name[nowsink] << ",  nextsink " << name[nextsink] << endl;
        for(int i = 0; i < num; i++){
            if(i == nowsink || i == nextsink) continue;
            if(money_table[i][nowsink] != 0) {
                int to_now = money_table[i][nowsink];
                money_table[i][nowsink] = 0;
                int l = i;
                int j;
                bool end = 0;

                while(!end){
                    for(int k = 0; k < num; k++){
                        if(k == nowsink) continue;
                        if(money_table[l][k] != 0){
                            j = k;
                            break;
                        }
                    }
                    money_table[l][j] += to_now;
                    l = j;
                    if(l == nextsink){
                        money_table[l][nowsink] += to_now;
                        end = 1;
                        break;
                    }
                }

            }
        }

        for(int i = 0; i < num; i++){
            int outcount = 0;
            for(int j = 0; j < num; j++){
                if(money_table[i][j] != 0) outcount++;
            }
            if(outcount > 1) break;
            if(i == num-1) done = 1;
        }
        
        sinkdone[sinkdonenum++] = nowsink;
        nowsink = nextsink;

        for(int i = 0; i < num; i++){
            cout << " \t" << name[i];
        }
        for(int i = 0; i < num; i++){
            cout << "\n" <<name[i];
            for(int j = 0; j < num; j++){
                cout << "\t" << money_table[i][j];
            }
        }cout<<endl;
    }
    cout << endl << endl;
    for(int i = 0; i < num; i++){
        if(i == sink) continue;
        for(int j = 0; j < num; j++){
            if(money_table[i][j] != 0){
                cout << name[i] << " -> " << name[j] << " " << money_table[i][j] << endl;
                break;
            }
        }
    }
    cout << endl;

    for(int i = 0; i < num; i++){
        int in_sum = 0, out_sum = 0;
        for(int j = 0; j < num; j++){
            in_sum += money_table[j][i];
            out_sum += money_table[i][j];
        }
        cout << name[i] << "\t" << in_sum - out_sum <<endl;
    }
    return 0;
}
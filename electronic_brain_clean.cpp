///created by hanbum-god
///gae ddock-ddock in-jeong in-jeong
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

int input_names(map<int, string> &name) {
    cout << "\n\n";
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

    cout << "\n\n\n\nname your friend one by one(in english)" << endl;
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
    return num;
}

void make_money_table(int **money_table, int totalPeople) {
    money_table = (int **)malloc(sizeof(int *) * totalPeople);

    for(int i = 0; i < totalPeople; i++){
        money_table[i] = (int *)malloc(sizeof(int) * totalPeople);

        for(int j = 0; j < totalPeople; j++){
            money_table[i][j] = 0;
        }
    }
}

bool check_input_group(map<int, string> &name) {

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
    } else return 1;
}

void input_who_spent_money(map<int, string> &name, int totalPeople, int** money_table){
    cout << "\n\nwho spent money?";
    cout << "when you're done, type '!'" << endl << endl;
 
    while(1){//'!'인풋을 받을 때까지 입력을 받음(n차)

        string input_spent;
        getline(cin, input_spent);
        
        if(input_spent.length() == 0) continue;
        if(input_spent[0] == '!') break;
        if(input_spent[0] < '0' || input_spent[0] > '9') return;//예외처리 해야함
        cout << "input: " << input_spent << endl;
        int who_paid = 0;//누가 계산했니
        int how_much = 0;//얼마 계산했니
        int this_attend_count = 0;//이번 장소에 몇명 있었니

        int error = 0;

        int who_joined[totalPeople];
        for(int i = 0; i < totalPeople; i++) who_joined[i] = 0;
        
        int pos = 0;
        for(;input_spent[pos] != ' '; pos++){
            who_paid = who_paid*10 + input_spent[pos]-'0';
        }
        
        pos++;
        for(;input_spent[pos] != ' '; pos++){
            how_much = how_much*10 + input_spent[pos]-'0';
        }
        pos++;
        for(int i = 0; i < totalPeople; i++){
            int attend;
            attend = input_spent[pos] - '0';
            pos+=2;
            if(attend != 0 && attend != 1){
                cout << "input error" <<totalPeople << endl;
                error = 1;
                break;
            }
            if(attend == 1){
                if(who_joined[i] == 1){
                    cout << "input error  "<< totalPeople << endl;
                    error = 1;
                    break;
                }else{
                    who_joined[i] = 1;
                    this_attend_count++;
                }
            }
        }

        cout << "input: " << input_spent << endl;
        if(error == 1) continue;
        
        how_much /= this_attend_count;

        cout << "input: " << input_spent << endl;

        for(int i = 0; i < totalPeople; i++){
            if(i == who_paid || who_joined[i] == 0) continue;
            money_table[i][who_paid] += how_much;
        }

        cout << "input: " << input_spent << endl;

        cout << who_paid << " " << how_much << " " << endl;

        for(int i = 0; i < totalPeople; i++){
            cout << " \t" << name[i];
        }
        for(int i = 0; i < totalPeople; i++){
            cout << "\n" <<name[i];
            for(int j = 0; j < totalPeople; j++){
                cout << "\t" << money_table[i][j];
            }
        }cout<<endl;
    }

}

void remove_cross(int **money_table, int totalPeople) {

    for(int i = 0; i < totalPeople; i++){
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
    
}

int find_first_sink(int **money_table, int totalPeople) {
    int sink;
    for(int i = 0; i < totalPeople; i++){
        int sum = 0;
        for(int j = 0; j < totalPeople; j++){
            sum += money_table[i][j];
        }
        if(sum == 0) sink = i;//sink가 두명 이상이면?
    }
    return sink;
}

void print_money_table(map<int, string> &name, int totalPeople, int** money_table) {
    for(int i = 0; i < totalPeople; i++){
        cout << " \t" << name[i];
    }
    for(int i = 0; i < totalPeople; i++){
        cout << "\n" <<name[i];
        for(int j = 0; j < totalPeople; j++){
            cout << "\t" << money_table[i][j];
        }
    }cout<<endl;
}

int find_next_sink(map<int, string> &name, int totalPeople, int** money_table, vector<int> &sinkdone, int sink_passed_num, int nowsink) {
    //find next sink;
    int nextsink;
    for(int i = 0; i < totalPeople; i++){// 마찬가지로 RACE condition 고려안됨
        int found = 1;
        if(i == nowsink) continue;
        int passedsink = 0;
        for(int k = 0; k < sink_passed_num; k++){
            if(i == sinkdone[k]){
                passedsink = 1;
                break;
            }
        }
        if(passedsink) continue;
        for(int j = 0; j < totalPeople; j++){
            if(money_table[i][j] != 0 && j != nowsink) {
                found = 0;
                break;
            }
        }
        if(found) nextsink = i;
    }
    cout << "sink found" << endl;
    cout << "nowsink " << name[nowsink] << ",  nextsink " << name[nextsink] << endl;
    
    return nextsink;
}

void remove_and_add_to_next_sink(int totalPeople, int** money_table, int nowsink, int nextsink, int sender) {
    int money_to_now = money_table[sender][nowsink];
    money_table[sender][nowsink] = 0;
    int middle;
    bool end = 0;

    //낙수효과 
    //nowsink로는 송금하는 sender가 nextsink로는 송금하지 않는 경우 
    //중간에 돈을 잃어버리는 현상 발생
    //이때 money_table이 그리는 graph는 계층구조를 가지는 트리 형태이므로
    //중간에 아무데나 거쳐서 nextsink까지만 가게하면 된다.
    //근데 이런 경우 없을수도 있음 그냥 혹시나 해서 한거임
    while(!end){
        for(int k = 0; k < totalPeople; k++){
            if(k == nowsink) continue;
            if(money_table[sender][k] != 0){
                middle = k;
                break;
            }
        }
        money_table[sender][middle] += money_to_now;
        sender = middle;
        if(sender == nextsink){
            money_table[sender][nowsink] += money_to_now;
            end = 1;
            break;
        }
    }
}

bool is_reduce_done(int **money_table, int totalPeople) {
    //각 사람마다 송금횟수 count, 최종 완료(모든사람의 outcount가 1 이하) 인지 검사
    for(int i = 0; i < totalPeople; i++){
        int outcount = 0;//송금횟수
        for(int j = 0; j < totalPeople; j++){
            if(money_table[i][j] != 0) outcount++;
        }
        if(outcount > 1) return 0;
    }
    return 1;
}

int reduce_next_sink_table(map<int, string> &name, int totalPeople, int** money_table) {
    
    int sink = find_first_sink(money_table, totalPeople);
    int nowsink = sink;
    int nextsink;
    bool done = 0;
    vector<int> sink_passed;
    int sink_passed_count = 0;
    for(int i = 0; i < totalPeople; i++) {
        sink_passed.push_back(0);
    }

    while(!is_reduce_done(money_table, totalPeople)){     

        nextsink = find_next_sink(name, totalPeople, money_table, sink_passed, sink_passed_count, nowsink); 
        
        //now_sink로 보내는 애들을 찾는다.
        for(int i = 0; i < totalPeople; i++){
            if(i == nowsink || i == nextsink) continue;
            if(money_table[i][nowsink] != 0) {//nowsink로 송금하는 금액이 있다면
                remove_and_add_to_next_sink(totalPeople, money_table, nowsink, nextsink, i);
            }
        }

        //nowsink는 이제 모두 전달 하였으니 더이상 고려하지 않기 위해 sink_passed에 넣고, sink_passed_count를 증가시킨다.
        sink_passed[sink_passed_count++] = nowsink;
        nowsink = nextsink;

        print_money_table(name, totalPeople, money_table);
    }
    return sink;
}

void print_result(map<int, string> &name, int totalPeople, int** money_table, int sink) {
    cout << endl << endl;
    for(int i = 0; i < totalPeople; i++){
        if(i == sink) continue;
        for(int j = 0; j < totalPeople; j++){
            if(money_table[i][j] != 0){
                cout << name[i] << " -> " << name[j] << " " << money_table[i][j] << endl;
                break;
            }
        }
    }
    cout << endl;

    for(int i = 0; i < totalPeople; i++){
        int in_sum = 0, out_sum = 0;
        for(int j = 0; j < totalPeople; j++){
            in_sum += money_table[j][i];
            out_sum += money_table[i][j];
        }
        cout << name[i] << "\t" << in_sum - out_sum <<endl;
    }
}

int main(){

    map<int, string> name;
    int** money_table;

    int totalPeople = input_names(name);
    make_money_table(money_table, totalPeople);
    if(!check_input_group(name)) return 0;
    input_who_spent_money(name, totalPeople, money_table);

    remove_cross(money_table, totalPeople);
    print_money_table(name, totalPeople, money_table);

    int sink = reduce_next_sink_table(name, totalPeople, money_table);

    print_result(name, totalPeople, money_table, sink);
    
    for(int i = 0; i < totalPeople; i++) {
        free(money_table[i]);
    }free(money_table);

    return 0;
}
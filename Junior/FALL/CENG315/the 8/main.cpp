#include <iostream>
#include <string>
#include <iostream>
#include <climits>
#include <cmath>
#include <string>
#include <ctime>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <forward_list>
#include <cmath>
#include <random>
#include <cstring>
#include <cstdlib>
#include <fstream>



//DO NOT ADD OTHER LIBRARIES

using namespace std;


class HashTable{
    int prime;

    vector<vector<pair<long,string> > > table;

public:

    HashTable(int prime);

    void insert(int x,string str);

    int hashFunction(int x){
        return (x % prime);
    }

    bool isIn(int x);

    int numOfPatterns(int x);

    vector<pair<long,string> > get(int x);

};

HashTable::HashTable(int prime){
    this->prime = prime;
    table.resize(prime);
}


void HashTable::insert(int x,string str){

    int hash = this->hashFunction(x);
    pair<long,string> p;
    p.first = x;
    p.second = str;
    table[hash].push_back(p);

}

bool HashTable::isIn(int x){

    int hash = hashFunction(x);

    if (table[hash].size()==0) return false;
    else return true;
}

int HashTable::numOfPatterns(int x){


    int hash = hashFunction(x);

    return table[hash].size();

}

vector<pair<long,string> > HashTable::get(int x){
    int hash = hashFunction(x);
    return table[hash];

}




vector<int> the8(const string& text, const vector<string>& patterns){

    vector<int> shifts; //DO NOT CHANGE THIS



    int N = text.size();
    int M = patterns[0].size();
    int hash,s = 26;
    int K = patterns.size();
    long sum,p,h =1 ;
    string str;
    int prime = 13099;

    for (int i = 0; i < M - 1; i++)
        h = (h * s) % prime;

    HashTable table = HashTable(prime);


    for(int i = 0; i < K; ++i){
        str = patterns[i];
        p = 0;

        for (int j = 0; j < M; j++)
        {
            p = (s * p + str[j]%97) % prime;
        }
        table.insert(p,str);
    }


    long t = 0;
    for (int i = 0; i < M; i++)
    {
        t = (s * t + text[i]%97) % prime;
    }



    bool flag;
    for(int i = 0; i < N-M; ++i){

        if(table.isIn(t)){

            vector<pair<long,string> > pts = table.get(t);

            for(int pt = 0; pt < pts.size(); pt++){
                flag = true;
                string str = pts[pt].second;
                int j;

                for(j = 0; j < M; j++){
                    if(text[i+j] != str[j]){
                        flag = false;
                        break;
                    }
                }
                if(flag) {

                    shifts.push_back(i);
                    break;
                }


            }

        }
        if ( i < N-M )
        {
            t = (s*(t - (text[i]%97)*h) + text[i+M]%97)%prime;


            if (t < 0)
                t = (t + prime);
        }
    }








    return shifts; //DO NOT CHANGE THIS
}





int main()
{
    vector<int> correct;
    vector<string> patterns;
    ifstream output("output_big");
    ifstream text("text_big");
    ifstream pat("patterns_big");
    string input_txt; text >> input_txt;
    for(int i = 0 ; i < 1000; i++)
    {
        int x; output >> x;
        string s; pat >> s;
        correct.push_back(x);
        patterns.push_back(s);

    }
    vector<int> res = the8(input_txt, patterns);
    bool c = true;
    for(int i = 0; i < correct.size(); i++)
    {
        if(correct[i] != res[i])
        {
            c = false;
            break;
        }

    }
    if(c) cout << "Correct";
    else cout << "Failed";

    return 0;
}
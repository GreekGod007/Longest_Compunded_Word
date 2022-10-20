#include <bits/stdc++.h>
using namespace std;

   struct trie{
	    struct trie* arr[26];
	    bool end = false;
	    trie() {
		    memset(arr,0,sizeof(arr));
		    end = false;
	    }
    };

    trie* root;

    void insert(string s){
        trie* node = root;
        /* 
         * inserting the string in reverse order as we will search from the
         * end (i.e. suffix) of the word while using DP.
         */
        for(int i = s.length()-1; i >= 0; i--) {
            char ch = s[i];
            if(!node->arr[ch-'a']) {
                node->arr[ch-'a'] = new trie();
            }
            node = node->arr[ch-'a'];
        }
        node->end = true;
    }
    
    
     vector<string> compounded_word(vector<string>& words) {
        sort(words.begin(), words.end(), [](const string& w1, const string& w2) {
            return (w1.size() < w2.size());
        });
        
        vector<string> ret;
        root = new trie();
        
        for(string w : words) {
            if(w.length() == 0)
                continue;
            
            vector<bool> dp(w.length()+1, false);
            dp[0] = true;
            for(int i = 0; i < w.length(); i++) {
                trie* node = root;
                for(int j = i; j >= 0; j--) {
                    /* 
                     * instead of keeping the smaller words into a map and 
                     * searching in the map after doing substr() which is O(n)
                     * operation, trie is being used here to achieve constant 
                     * time search operation of current suffix
                     */ 
                    if(node->arr[w[j]-'a'] == NULL)
                        break;
                    node = node->arr[w[j]-'a'];
                    if(dp[j] && node->end) {
                        dp[i+1] = true;
                        break;
                    }
                }
            }
            
            if(dp[w.length()])
                ret.push_back(w);
            
            insert(w);
        }
        
        string first="",second="";
        
        for(string x:ret){
            if(x.length()>first.length()){
                second=first;
                first=x;
            }
           else if(x.length()>second.length()){
                    second=x;
                }
        }
        
        cout<<first<<"  "<<second<<endl;
        
        return ret;
    }
    




int main(){
	
    clock_t Start;
    clock_t Finish;

    Start = clock();
//    for(int i = 0; i < 10000000; i++)
//        ;    
	
	
	string s;
	ifstream in("Input_02.txt");
	vector<string> v;
	while(getline(in,s)){
		v.push_back(s);
	}
	
	compounded_word(v);
	

    Finish = clock();

   double time_taken = double(Finish - Start) / double(CLOCKS_PER_SEC);

	cout << time_taken<<"sec"<<endl;;

    system("pause");
    
	return 0;
}

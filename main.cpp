#include <bits/stdc++.h>
using namespace std;

string expansion(string rpt){
    string output = "";
    int ctr = 0;
    
    for (int i = 0; i < 8, ctr < 32; i++) {
        string str = "";
        if(i == 0){
            str+=rpt[31];
            str+=rpt.substr(ctr, 4);
            str+=rpt[ctr];
            output+=str;
        }
        else if(i == 7){
            str+=rpt[ctr];
            str+=rpt.substr(ctr, 4);
            str+=rpt[0];
            output+=str;
        }
        else{
            str+=rpt[ctr-1];
            str+=rpt.substr(ctr, 4);
            str+=rpt[ctr+4];
            output+=str;
        }
        ctr+=4;
    }
    
    
    assert(output.size() == 48);
    return output;
}


string func_xor(string rpt, string key){
    string output = "";
    
    for (int i = 0; i < rpt.size(); i++) {
        if(rpt[i] == key[i]){
            output+='0';
        }
        else{
            output+='1';
        }
    }
    
    return output;
}


string s_box_sub(string rpt, int s_box[4][16]){
    string output = "";
    int ctr = 0;
    //cout<<"rpt : "<<rpt<<endl;
    for (int i = 0; i < 8; i++) {
        /* code */
        string row = "", col = "";
        
        string str = rpt.substr(ctr, 6);
        //cout<<"str : "<<str<<endl;
        row += str[0];
        row += str[5];
        string temp = str.substr(4, 1);
        col += temp;
        
        //cout<<"row : "<<row<<" col : "<<col<<endl;
        
        int rows = stoi(row, 0, 2);
        int cols = stoi(col, 0, 2);
        
        int val = s_box[rows][cols];
        std::string binary = std::bitset<4>(val).to_string(); //to binary
        
        output+=binary;
    }
    
    return output;
}


string function_box(string rpt, string key, int rd){
    
    int s_boxes[2][4][16] = { {14, 4,  13, 1, 2,  15, 11, 8,  3,  10, 6,  12, 5,
          9,  0,  7,  0, 15, 7,  4,  14, 2,  13, 1,  10, 6,
          12, 11, 9,  5, 3,  8,  4,  1,  14, 8,  13, 6,  2,
          11, 15, 12, 9, 7,  3,  10, 5,  0,  15, 12, 8,  2,
          4,  9,  1,  7, 5,  11, 3,  14, 10, 0,  6,  13 },
          { 15, 1,  8,  14, 6,  11, 3, 4,  9,  7,  2,  13, 12,
          0,  5,  10, 3,  13, 4,  7, 15, 2,  8,  14, 12, 0,
          1,  10, 6,  9,  11, 5,  0, 14, 7,  11, 10, 4,  13,
          1,  5,  8,  12, 6,  9,  3, 2,  15, 13, 8,  10, 1,
          3,  15, 4,  2,  11, 6,  7, 12, 0,  5,  14, 9 } };
    
    string expanded_rpt = expansion(rpt);
    string updated_rpt = func_xor(rpt, key);
    
    if(rd == 1)
        updated_rpt = s_box_sub(updated_rpt, s_boxes[0]);
    if(rd == 2)
        updated_rpt = s_box_sub(updated_rpt, s_boxes[1]);
    
    return updated_rpt;
}

string encryption(string plain_text, string key){
    string lpt, rpt;
    lpt = plain_text.substr(0, 32);
    rpt = plain_text.substr(32, 32);

    //round 1
    string output1 = function_box(rpt, key, 1);
    output1 = func_xor(output1, lpt);
    
    string output2 = function_box(output1, key, 2);
    output2 = func_xor(rpt, output2);
    
    string out = output2+output1;
    
    return out;
}

int main()
{
   string str;
   cout<<"Enter 8 character string for encryption : ";
   cin>>str;
   string pt;
   
   for (int i = 0; i < 8; i++) {
       /* code */
       int val = int(str[i]);
       std::string binary = std::bitset<8>(val).to_string(); //to binary
       pt += binary;
       //std::cout<<binary<<"\n";
   }
   
    string key;
    cout<<"Enter key of 6 characters : ";
    cin>>key;
    string bit_key;
    
    for (int i = 0; i < 6; i++) {
       /* code */
       int val = int(key[i]);
       std::string binary = std::bitset<8>(val).to_string(); //to binary
       bit_key += binary;
       //std::cout<<binary<<"\n";
   }
    
   cout<<pt<<"\n"<<bit_key<<endl;
   
   cout<<"Encrypted text in binary form is : "<<encryption(pt, bit_key)<<endl;

   return 0;
}



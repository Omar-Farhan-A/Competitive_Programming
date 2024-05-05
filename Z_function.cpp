vector<int> Z_function(string s){
    int n=s.size();
    vector<int>z(n);
    int l=0,r=0;
    for(int i=1;i<n;i++){
        if(i<r){
            z[i]=min(z[i-l],r-i);
        }
        while (i+z[i]<n&&s[z[i]]==s[z[i]+i]){
            z[i]++;
        }
        if(i+z[i]>r){
            r=i+z[i];
            l=i;
        }
    }
    return z;
}

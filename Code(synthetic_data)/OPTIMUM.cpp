#include<bits/stdc++.h>
using namespace std;
int n,m,k;
set<int>E;
set<int>h;
vector<int>d;
vector<set<int> >Ei;//OPS
vector<set<int> >ei;//Sub-fun:f()
vector<int>K,b;
int value_max=0;
//Submodular function
bool cmp(pair<int,double> a, pair<int,double> b) {
    return a.second > b.second;
}
int f(int *Xe){
	int value[n];
	int value_sum=0;
	memset(value,0,sizeof(value));
	for(int i=0;i<ei.size();i++){
		for(set<int>::iterator it=ei[i].begin();it!=ei[i].end();++it) {
			//cout<<*it<<" ";
			value[*it-1]+=Xe[i];
		}
		//cout<<endl;
	}
	for(int i=0;i<n;i++){
		//cout<<value[i]<<" ";
		if(value[i]<=d[i])
			value_sum+=value[i];
	}
	//cout<<"f(x)= "<<value_sum<<endl;
	return value_sum;
}
bool delete_branch(int *X){
	for(int j=0;j<m;j++){
		int xEj=0;
		for(set<int>::iterator it=Ei[j].begin();it!=Ei[j].end();it++){
			xEj+=X[*it-1];
		}
		if(xEj>K[j]){
			//cout<<"false"<<endl;
			return false;
		}	
	}
	return true;
}
void dfs(const int n,int cur,int *X,int *Xmax){
    if(cur == n){
    	
        	int value=f(X);
        	if(value_max<value){
        		value_max=value;
        		for(int i=0;i<n;i++){
        			Xmax[i]=X[i];
				}
			}
		
    }
    else{
        for(int i = 0;i <= b[cur];i++){
            X[cur] = i;
            if(!delete_branch(X)){
            	for(int j=cur;j<n;j++)
            	X[j]=0;
            	break;
			}
            dfs(n,cur+1,X,Xmax);
        }
    }
    return;
}
void in_put(){
	//cout<<"输入e个数n，groups个数m："<<endl;
	cin>>n>>m;
	int e;
	set<int>e1;
	//cout<<"输入E1...Em：（集合不可有交集）"<<endl;
	for(int i=0;i<m;i++){
  		while(cin>>e){
			e1.insert(e);
			if(cin.get()=='\n') break;
		}
		Ei.push_back(e1);
		e1.clear();
	}
	//cout<<"输入k1...km："<<endl;
	for(int i=0;i<m;i++){
		int ki;
		cin>>ki;
		k+=ki;
		K.push_back(ki);
	}
	//cout<<"输入b1...bn："<<endl;
	for(int i=0;i<n;i++){
		int a;cin>>a;
		b.push_back(a);
	}
	return;
}
void input_Sub(){
	int e,dl;
	set<int>e1;
	int Xe[n];
	//cout<<"输入次模所需的n个集合（集合可有交集）"<<endl;
	for(int i=0;i<n;i++){
		while(cin>>e){
			e1.insert(e);
			if(cin.get()=='\n') break;
		}
		ei.push_back(e1);
		e1.clear();
	}
	//cout<<"输入次模集合的溢出条件数"<<endl; 
	for(int i=0;i<n;i++){
		cin>>dl;
		d.push_back(dl);
	}
	return;		
}
int main(){
	freopen("input.txt","r",stdin);
	clock_t start,finish;
	in_put();
	input_Sub(); 
	int X[n],Xmax[n];
	memset(X,0,sizeof(X));
	memset(Xmax,0,sizeof(Xmax));
	freopen("Optimum_output.txt","w",stdout);
	start=clock();
	dfs(n,0,X,Xmax);
	cout<<"Max(f(x))："<<endl<<value_max<<endl;
	cout<<"The selected elements are as follows：:"<<endl; 
	for(int i=0;i<n;i++)
		cout<<Xmax[i]<<" ";
	finish=clock();
	printf("\nt=\n%.5lf ",(double)(finish-start)/CLOCKS_PER_SEC);
	fclose(stdout);

	return 0;
}

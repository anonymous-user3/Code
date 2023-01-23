#include<bits/stdc++.h>
using namespace std;
int n,m,k;
set<int>E;
set<int>h;
int d;
vector<set<int> >Ei;//OPS
vector<set<int> >ei;//Sub-fun:f()
vector<int>K,b;
int f_ans=0;
int Rand(){
	return rand()<<15|rand();
} 
//Submodular function
bool cmp(pair<int,double> a, pair<int,double> b) {
    return a.second > b.second;
}
int f(int *Xe){
	f_ans++;
	int value[3000];
	memset(value,0,sizeof(value));
	int value_sum=0;
	memset(value,0,sizeof(value));
	for(int i=0;i<ei.size();i++){
		for(set<int>::iterator it=ei[i].begin();it!=ei[i].end();++it) {
			//cout<<*it<<" ";
			value[*it-1]+=Xe[i];
		}
		//cout<<endl;
	}
	for(int i=0;i<3000;i++){
		//cout<<value[i]<<" ";
		if(value[i]<=d)
			value_sum+=value[i];
	}
	//cout<<"f(x)= "<<value_sum<<endl;
	return value_sum;
}
void choose_random(){
	srand((unsigned)time(NULL));
	set<int> vec;
	int X[n];
	memset(X,0,sizeof(X));
	for(int j=0;j<m;j++){
		int kj=K[j];
		vec.clear();
		for(set<int>::iterator it=Ei[j].begin();it!=Ei[j].end();it++){
				int t=*it-1;
				vec.insert(t);
		}
		while(kj>0){
			int l=vec.size();
			if(l==0)
				break;
			//cout<<"l="<<l<<endl; 
			int ans=Rand()%l;
			set<int>::iterator it1=vec.begin();
			for(int i=0;i<=ans;i++){
				it1++;
			}
			int t=*it1;
			int f1=f(X);
				X[t]++;
			int f2=f(X);
			if(f1>f2||X[t]>b[t]){
				X[t]--;
				vec.erase(t);
			}
			kj--;
		}
	}
	cout<<"Max(f(x))£º"<<endl;
	cout<<f(X)<<endl;
	cout<<"The selected elements are as follows£º"<<endl;
	for(int i=0;i<n;i++)
		cout<<X[i]<<" ";
	cout<<endl;
	return ;
} 
void in_put(){

	cin>>n>>m;
	int e;
	set<int>e1;

	for(int i=0;i<m;i++){
  		while(cin>>e){
			e1.insert(e);
			if(cin.get()=='\n') break;
		}
		Ei.push_back(e1);
		e1.clear();
	}
	
	for(int i=0;i<m;i++){
		int ki;
		cin>>ki;
		k+=ki;
		K.push_back(ki);
	}

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
	
	for(int i=0;i<n;i++){
		while(cin>>e){
			e1.insert(e);
			if(cin.get()=='\n') break;
		}
		ei.push_back(e1);
		e1.clear();
	}
	
	cin>>d;
	return;		
}
int main(){
	f_ans=0;
	freopen("input.txt","r",stdin);
	clock_t start,finish;
	in_put();
	input_Sub();
	freopen("Random_output.txt","w",stdout);
	start=clock();
	choose_random();
	cout<<"The calculation times of submodular function:"<<endl<<f_ans<<endl;
	finish=clock();
	printf("time= %.5lf ",(double)(finish-start)/CLOCKS_PER_SEC);
	fclose(stdout);
	return 0;
}

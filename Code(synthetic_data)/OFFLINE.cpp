#include<bits/stdc++.h>
using namespace std;
int n,m,k;
set<int>E;
set<int>h;
vector<int>d;
vector<set<int> >Ei;//OPS
vector<set<int> >ei;//Sub-fun:f()
vector<int>K,b;
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

int BinarySearchPivot(int *X,double theta,int lt,int i){
	int ls=1;
	int Xe[n];
	memset(Xe,0,sizeof(Xe));
	for(int j=0;j<n;j++)
	Xe[j]=X[j];
	//cout<<"lt= "<<lt<<endl;
	//cout<<"theta= "<<theta<<endl;
	if(lt<ls)
		return 0; 
	Xe[i]+=lt;
	double num=(f(Xe)-f(X))/lt;
	//cout<<"num= "<<num<<endl;
	Xe[i]-=lt;	
	if(num>=theta)
		return lt;
	Xe[i]+=1;
	num=f(Xe)-f(X);
	//cout<<"num1= "<<num<<endl;
	if(num<theta)
		return 0;
	Xe[i]-=1;
	while(lt>ls+1){
	 	int m=floor((ls+lt)/2);
	 	Xe[i]+=m;
	 	int f1=f(Xe);
	 	int f2=f(X);
	 	num=(f1-f2)/m;
	 	//cout<<"m=  num3= theta= num3-theta="<<m<<" "<<num<<" "<<theta<<" "<<num-theta<<endl;
	 	if(num>=theta)
	 		ls=m;
	 	else
	 		lt=m;
	 	Xe[i]-=m;
	 }
	 //cout<<"ls= "<<ls<<endl;
	 return ls;
}
void ThresholdGreedy(){
	int count[n];
	int Xmax[n];
	int X[n];
	memset(X,1,sizeof(X));
	memset(Xmax,0,sizeof(Xmax));
	vector< pair<int,double> > vec;
	for(int j=0;j<m;j++){
		int kj=K[j];
		vec.clear();
		while(true){
			vec.clear();
			for(set<int>::iterator it=Ei[j].begin();it!=Ei[j].end();it++){
				int t=*it-1;
				//cout<<"e,j,b,k "<<*it<<" "<<j+1<<" "<<b[t]<<" "<<K[j]<<endl;
				if(X[t]==0)
					continue;
				int lt=min(b[t]-Xmax[t],kj);
				if(lt<=0)
					continue;
				int l=BinarySearchPivot(Xmax,1e-8,lt,t);
				int f_unadd,f_add;
				f_unadd=f(Xmax);
				//cout<<"f_unadd= "<<f_unadd<<endl; 
				Xmax[t]+=l;
				f_add=f(Xmax);
				//cout<<"f_add= "<<f_add<<endl; 
				Xmax[t]-=l;
				double value=0;
				if(l!=0)
					value=1.0*(f_add-f_unadd)/l;
				//cout<<"l,value: "<<l<<" "<<value<<endl;
				pair<int,double> c(t,value);
	    		vec.push_back(c);
				count[t]=l;
			}
			sort(vec.begin(),vec.end(),cmp);
			//cout<<vec[0].first+1<<" "<<vec[0].second<<" "<<kj<<endl;
			if(kj<=0||vec.size()==0||vec[0].second<=0)
				break;
			int t=vec[0].first;
			if(kj>=count[t]){
				Xmax[t]+=count[t];
				kj-=count[t];
			}	
			else{
				Xmax[t]+=kj;
				kj=0;
			}
			X[t]=0;
		}	
	}
	cout<<"Max(f(x))£º"<<endl;
	cout<<f(Xmax)<<endl;
	cout<<"The selected elements are as follows£º"<<endl;
	for(int i=0;i<n;i++)
	cout<<Xmax[i]<<" ";
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
	freopen("Offline_output.txt","w",stdout);
	start=clock();
	ThresholdGreedy(); 
	finish=clock();
	printf("time= %.5lf ",(double)(finish-start)/CLOCKS_PER_SEC);
	fclose(stdout);
	return 0;
}

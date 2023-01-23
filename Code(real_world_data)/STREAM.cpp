#include<bits/stdc++.h>
using namespace std;
int n,m,k;
set<int>E;
set<int>h;
int d;
vector<set<int> >Ei;//OPS
vector<set<int> >ei;//Sub-fun:f()
vector<int>K,b;
int Xv[1000][1000];
double ep=0.1;
int f_ans=0;
clock_t start,finish;
//Submodular function
bool cmp(pair<int,double> a, pair<int,double> b) {
    return a.second > b.second;
}
int f(int *Xe){
	f_ans++;
	int value[2900];
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
	for(int i=0;i<2900;i++){
		//cout<<value[i]<<" ";
		if(value[i]<=d)
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
	 	if(num>=theta)
	 		ls=m;
	 	else
	 		lt=m;
	 	Xe[i]-=m;
	 }
	 //cout<<"ls= "<<ls<<endl;
	 return ls;
}
void ThresholdGreedy(int *X){
	int count[n];
	int Xmax[n];
	memset(Xmax,0,sizeof(Xmax));
	cout<<"The remaining elements after filtering are as follows:"<<endl;
	for(int i=0;i<n;i++)
	cout<<X[i]<<" ";
	cout<<endl;
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
				//cout<<"lt="<<lt<<endl;
				if(lt<=0)
					continue;
				int l=BinarySearchPivot(Xmax,1e-8,lt,t);
				int f_unadd,f_add;
				f_unadd=f(Xmax);
				Xmax[t]+=l;
				f_add=f(Xmax);
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
			if(kj<=0||vec.size()==0||vec[0].second<=0)
				break;
			int t=vec[0].first;
			//cout<<"vec:"<<vec[0].first<<" "<<vec[0].second<<" "<<kj<<endl;
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
	cout<<"Max(f(x))£º" <<endl;
	cout<<f(Xmax)<<endl;
	cout<<"The selected elements are as follows£º"<<endl;
	for(int i=0;i<n;i++)
	cout<<Xmax[i]<<" ";
	cout<<endl;
	return ;
}
void OPS(){
	int alpha=0,beta=0,eta=0,i,j; 
	double gama=0.1;
	int Xe[n];
	double H[200];
	int dmax=0; 
	memset(Xe,0,sizeof(Xe));
	for(int i=0;i<n;i++){
		Xe[i]=1;
		dmax=max(dmax,f(Xe));
		alpha=max(alpha,f(Xe));
		beta=max(alpha,eta);
		double beta_ep=beta/(1+ep);
		int al_k=2*k*alpha;
		int down=ceil(log(beta_ep)/(log(1+ep)));
		int up =(log(al_k)/log(1+ep));
		h.clear();
		for(int t=down;t<=up;t++){	
			double p=pow((1+ep),t);	
			//cout<<"v= "<<p;
				H[t]=p;
				h.insert(t);			
		} 
		if(h.size()>499)
		cout<<"Waring£¡£¡" <<endl;
		//cout<<"±éÀúv"<<endl; 				
		for(set<int>::iterator it=h.begin();it!=h.end();it++){
			int t=*it;
			
			double v=H[t]/(2*k);
			//cout<<"v/2k= "<<H[t]<<" "<<k<<" "<<v<<endl;
			int j=0;
			for(j=0;j<Ei.size();j++){
				if(Ei[j].find(i+1)!=Ei[j].end())
					break;
			}
			 
			int xvEj=0;
		
			for(set<int>::iterator it1=Ei[j].begin();it1!=Ei[j].end();it1++){
					xvEj+=Xv[t][*it1-1];
			}
			//for(int o=0;o<n;o++)
			//cout<<Xv[t][o]<<" ";
			//cout<<endl;
			//cout<<"xvEj= "<<xvEj<<"  K[j]= "<<K[j]<<endl;
			if(xvEj<K[j]){
				int lt=min((b[i]-Xv[t][i]),(K[j]-xvEj));
				int l=BinarySearchPivot(Xv[t],v,lt,i);
				//cout<<"l= "<<l<<" ";
				Xv[t][i]+=l;
				
				//for(int o=0;o<n;o++)
				//cout<<Xv[t][o]<<" ";
				//cout<<endl;
			}
		}
		for(set<int>::iterator it=h.begin();it!=h.end();it++){
			int t=*it;
			eta=max(eta,f(Xv[t]));
		}
		//cout<<"eta= "<<eta<<endl;
		Xe[i]=0;
	}
	int X[n];
	memset(X,0,sizeof(X));
	for(set<int>::iterator it=h.begin();it!=h.end();it++){
		int t=*it;
		for(int i=0;i<n;i++){
			if(Xv[t][i]>0)
				X[i]=1;
		}
	}
//	for(int i=0;i<n;i++)
//	cout<<X[i]<<" ";
//	cout<<endl;
	ThresholdGreedy(X); 
	return;
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
	in_put();
	input_Sub(); 
	freopen("Stream_output.txt","w",stdout);
	start=clock();
	OPS();
	cout<<"The calculation times of submodular function:"<<endl<<f_ans<<endl;
	finish=clock();
	printf("time= %.5lf ",(double)(finish-start)/CLOCKS_PER_SEC);
	fclose(stdout);
	return 0;
}

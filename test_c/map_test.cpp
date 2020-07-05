#include<iostream>
#include<deque>
#include<unordered_map>
#include<set>

using namespace std;

class A{
public:
	A(int x): a(x){};
	~A(){};
	void printd(){
		cout<<a<<endl;
	}
	bool operator<(const A& aa) const
	{
		return aa.a < this->a;
	}
	void mod(int x) const{
		//a = x;
	}
private:
	int a;
};

int map_test()
{
	deque<A*> aq;
	aq.push_back(new A(1));
	//A* tmp = aq.front();
	//tmp->printd();
	unordered_map<int,set<A>> map;
	//cout<<map.max_size()<<endl;
	set<A> sa;
	A* aa = new A(2);
	sa.insert(*aa);
	map[1] = sa;
	unordered_map<int, set<A>>::iterator it;
	for(it=map.begin(); it!=map.end(); ++it){
		//  modify the first element in set , this way is work
		//set<A>& tmp = it->second;
	    //A at = *(tmp.begin());
		//at.mod(4);
		//tmp.erase(tmp.begin());
		//tmp.insert(at);
		//A xx = *(tmp.begin());		
		//xx.printd();
		// modify the first element in set , this way doesn't work
		//*(it->second.begin()).mod(4); 
		it->second.begin()->mod(4); 
	}
//	for(it=map.begin(); it!=map.end(); ++it){
//		
//		set<A>& tmp = it->second;
//		A xx = *(tmp.begin());		
//		xx.printd();
//	}	
	return 0;
}


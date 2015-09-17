#include <bitset>
bitset<1005> test;

int main(){
	test.count(); // 统计1的个数
	test.set();   // 所有位置都设为1 
	test.reset(); // 所有位置都设为0	
	test.any();   // 是否有1
	return 0;
}

#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;

//���֡���ÿ�λ���Ψһȷ��һ��Ԫ��λ��
int partition(int A[], int low, int high)
{
	int pivot = A[low];    //һ�������ε���̲İ汾���Ե�1��λ��Ϊ��׼
	while (low < high){
		while (low < high && A[high] >= pivot){
			--high;
		}
		A[low] = A[high];  //���Ȼ�׼С��Ԫ���ƶ������
		while (low < high && A[low] <= pivot){
			++low;
		}
		A[high] = A[low];  //���Ȼ�׼С��Ԫ���ƶ����Ҷ�
	}
	A[low] = pivot;
	return low;
}

int r = 5;
//A[low..high]
int select_rank_k(int A[], int low, int high, int k)
{
	int r_group = ceil((high - low + 1)*1.0 / r);//ceilȡ���ޣ��ܹ���Ϊr_group����
	//����ÿ��������ֵ������A[]��ǰ��
	for (int i = 1; i <= r_group; ++i) {
		sort(&A[low + (i - 1)*r], &A[(low + i*r - 1) > high ? high : (low + i*r - 1)]);
		swap(A[low + i - 1], A[low + (i-1)*r + r / 2]);
	}
	//���ÿ�������ֵ����ֵ(������A[low]λ�ã�������ÿ��Ż��ֺ���)
	sort(&A[low], &A[low + r_group]);
	swap(A[low], A[r_group / 2]);
	int cur = partition(A, low, high);
	if (cur == k-1){
		return A[cur];
	}
	else if (cur < k){
		return select_rank_k(A, cur + 1, high, k);
	}
	else{
		return select_rank_k(A, low, cur - 1, k);
	}
}

int main(void)
{
	int A[15] = {4,1,10,9,7,12,8,2,15};
	printf("%d\n", select_rank_k(A, 1, 5, 2));
	return 0;
}

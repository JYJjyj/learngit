#include"bitmap.h"

size_t GetSize(size_t capacity)
{
	return capacity / (8 * sizeof(uint64_t)) + 1;
}
void BitMapInit(BitMap* bm, size_t capacity)
{
	if (bm == NULL)
		return;
	bm->data = (uint64_t*)malloc(8 * GetSize(capacity));
	bm->capacity = capacity;
}

void GetOffset(size_t index, size_t* n, size_t* offset)
{
	//n 为第几个uint，offset为在这个uint中第几位
	*n = index / (sizeof(uint64_t)* 8);
		*offset = index % (sizeof(uint64_t)* 8);
}

void BitMapSet(BitMap* bm, size_t index)
{
	if (bm == NULL)
		return;
	if (index >= bm->capacity)
		return;
	size_t n;
	size_t offset;
	GetOffset(index, &n, &offset);
	uint64_t ret = 1;
		ret <<=offset;
	bm->data[n] |= ret;
}

 void BitMapUnSet(BitMap* bm, size_t index)
{
    if(bm==NULL)
        return;
    if(index>=bm->capacity)
        return;
    uint64_t ret=0xFFFFFFFFFFFFFFFF;
    size_t n=0;
    size_t offset=0;
    GetOffset(index,&n,&offset);
    ret^=(1ul<<offset);
    bm->data[n]&=ret;
    //bm->data[n] &= ~(1ul << offset);以上两句可以替换为这个，
}

int BitMapTest(BitMap* bm, size_t index)
{
   if(bm==NULL)
       return -1;
   if(index>=bm->capacity)
       return -1;
   size_t n=0;
   size_t offset=0;
   GetOffset(index,&n,&offset);
   //int ret = (bm->data[n]&(1ul<<offset));
   //return ret != 0 ? 1 : 0;
   uint64_t tmp;
   tmp = bm->data[n];
   tmp>>=offset;
   tmp &= 1;
   if(tmp==0)
       return 0;
   else
       return 1;
}
//把所有位都设置为1
void BitMapClear(BitMap* bm)
{
    if(bm==NULL)
        return;
    memset(bm->data,0,GetSize(bm->capacity)*sizeof(uint64_t));
}

void BitMapFill(BitMap* bm)
{
    if(bm==NULL)
        return;
    memset(bm->data,0xFF,GetSize(bm->capacity)*sizeof(uint64_t));
}

 void BitMapDestroy(BitMap* bm)
{
    if(NULL == bm)
        return;    
    free(bm->data);
    bm->capacity=0;
    bm = NULL;
}
////////////////////////////////////测试代码//////////////////////////////////////////////
#define __TESTHEAD__  printf("-------------------------------------------%s--------------------------------------------\n",__FUNCTION__);
void TestInit()
{
	BitMap bm;
	size_t capacity = 1000;
	BitMapInit(&bm, capacity);
	printf("capacity: expect 1000   expect %lu", bm.capacity);
}


void TestBitMapSet()
{
    __TESTHEAD__;
    BitMap bm;
    BitMapInit(&bm,150);
    BitMapSet(&bm,20);
    size_t i=0;
    for(;i<GetSize(bm.capacity);i++)
    {
        printf("[%lu]:%lu",i,bm.data[i]);
    }
    printf("\n");
}
void TestBitMapUnSet()
{
    __TESTHEAD__;
    BitMap bm;
    BitMapInit(&bm,150);
    BitMapUnSet(&bm,20);
    size_t i;
    for(i=0;i<GetSize(bm.capacity);i++)
    {
        printf("[%lu]:%lu",i,bm.data[i]);
    }
    printf("\n");
}
void TestBitMapTest()
{
    __TESTHEAD__;
    BitMap bm;
    BitMapInit(&bm,150);
    BitMapSet(&bm,20);
    int ret = BitMapTest(&bm,20);
    int ret1 = BitMapTest(&bm,110);
    printf("expect 1 ,actual %d\n",ret);
    printf("expect 0 ,actual %d\n",ret1);
}
void TestBitMapClear()
{
    __TESTHEAD__;
    BitMap bm;
    BitMapInit(&bm,150);
    BitMapSet(&bm,20);
    BitMapSet(&bm,125);
    size_t i;
    for(i=0;i<GetSize(bm.capacity);i++)
    {
        printf("[%lu]:%lu",i,bm.data[i]);
    }
    printf("\n");
    BitMapClear(&bm);
    for(i=0;i<GetSize(bm.capacity);i++)
    {
        printf("[%lu]:%lu",i,bm.data[i]);
    }
    printf("\n");
}
void TestBitMapFill()
{
    __TESTHEAD__;
    BitMap bm;
    BitMapInit(&bm,150);
    BitMapSet(&bm,20);
    BitMapSet(&bm,125);
    size_t i;
    for(i=0;i<GetSize(bm.capacity);i++)
    {
        printf("[%lu]:%lx",i,bm.data[i]);
    }
    printf("\n");
    BitMapFill(&bm);
    for(i=0;i<GetSize(bm.capacity);i++)
    {
        printf("[%lu]:%lx",i,bm.data[i]);
    }
    printf("\n");
}
void TestBitMapDestroy()
{
    __TESTHEAD__;
    BitMap bm;
    BitMapInit(&bm,150);
    BitMapSet(&bm,20);
    BitMapSet(&bm,125);
    size_t i;
    for(i=0;i<GetSize(bm.capacity);i++)
    {
        printf("[%lu]:%lx",i,bm.data[i]);
    }
    printf("\n");
    BitMapDestroy(&bm);
    printf("capacity  expect : 0   actual : %lu\n",bm.capacity);
}
void test()
{
	TestInit();
   TestBitMapSet();
   TestBitMapUnSet();
   TestBitMapTest();
   TestBitMapClear();
   TestBitMapFill();
   TestBitMapDestroy();
}
int main()
{
	test();
	return 0;
	system("pause");
}

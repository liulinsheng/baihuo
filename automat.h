#ifndef automat_h
#define automat_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
typedef struct tm timeform;
#define MaxVerNum 10
#define INFINITY 10000


/******************************************************/

typedef struct _Goods{

	int id;				//排号
	char name[32]; 		//商品名
	long int isbn;		//编号
	float price;		//价格
	char type[32];		//分类
	time_t atime;		//时间
	int sign;			//标记
	int integral;		//积分

}Goods;

typedef struct  _TreeNodeGoods{
	Goods *data;
	struct _TreeNodeGoods *left, *right;
}TreeNode;

typedef struct _TreeGoods{
	TreeNode *root;
}Tree;

typedef struct _nodeGoods{
	Goods  *data;//数据域
	struct _nodeGoods *next;//指针域

}NodeGoods;//定义一个链栈

typedef struct _linkedListBook{
	NodeGoods *head;
	NodeGoods *tail;
	NodeGoods *current;

}List_Goods;

/***************************链表***************************/
List_Goods *initList_Goods();
NodeGoods *Find_Goods_name_node(List_Goods *list,char name[]);

List_Goods *Find_Goods_name(List_Goods *list,char name[]);
List_Goods *Find_Goods_Isbn(List_Goods *list,long int isbn);
List_Goods *Find_Goods_Type(List_Goods *list,char type[]);

NodeGoods *PromptFind_Goods_name(List_Goods *list);

int Order_Number();
Goods *PromptInput_Data(List_Goods *list);
void addTail_Goods(List_Goods *list);
void delNode_Goods(List_Goods *list);
void GoodsToFile(List_Goods *list);
void GoodsToFile_Del(List_Goods *list);
void addTail_Goods_File(List_Goods *list,Goods *data);
void GoodsFromFile(List_Goods *list);
void Free_Goodslist(NodeGoods *list);
void display_Goods(NodeGoods *goods);

/****************************树*************************/
void CreateTree(Tree *tree, Goods *data);
void displayTree_Goods(TreeNode *tree);
void InOrder(TreeNode *tree);
void GoodsFromFile_Tree(Tree *tree);
void FreeTree_Goods(TreeNode *tree);

/****************************图*************************/

typedef struct _VertexType{
	char address[30];//顶点储存的信息
}VertexType;

typedef int EdgeType;

typedef struct _MGraph{
	VertexType vexs[MaxVerNum];//存放节点信息
	EdgeType edges[MaxVerNum][MaxVerNum];//邻接矩阵
	int vnum,enumw;//顶点数和边数
}MGraph;

void CreateMGraph(MGraph *G,VertexType *data,int edgeData[MaxVerNum][MaxVerNum]);//建立并返回空图
void initVnum(VertexType *data);//初始化顶点
void initEdge(int edgeData[MaxVerNum][MaxVerNum]);//初始化边
int SelectAddress();
void ShortestPath(MGraph *G, int P[MaxVerNum], int D[MaxVerNum], VertexType *data,int vertex,int end);
void Navigate();


/****************************************************/
void Seek_name();
void Seek_Reward();
void Seek_Type();
void Seek_Menu();
/************************************************/
void Goods_MenuCheck();
void Goods_MenuAdd();
void Goods_MenuDel();
void Goods_Menu();
void Money();

void Main_Menu();
/************************************************************/
typedef struct _User{
	long int number;			//用户账号
	char name[20]; 				//用户名
	char password[30];			//密码
	int integral;				//积分

}User;


typedef struct _node
{
	User  *data;
	struct _node *next;

}NodeUser;

typedef struct _linkedList
{
	NodeUser *head;
	NodeUser *tail;
	NodeUser *current;

}List_User;

typedef struct  _TreeNode{
	User *data;
	struct _TreeNode *left, *right;
}TreeNode_User;

typedef struct _Tree{
	TreeNode_User *root;
}Tree_User;


/********************************链表******************************/

List_User *initList_User();
void addTail_User(List_User *list,User *data);
void Free_Userlist(NodeUser *list);
void UserToFile_list(List_User *list);//将用户信息存入文件夹
void UserFromFile_list(List_User *list);//从文件夹读取用户信息

/********************************树*******************************/

void CreateTree_User(Tree_User *tree, User *data);
void displayTree_User(TreeNode_User *tree);
void InOrder_User(TreeNode_User *tree);
void FreeTree_User(TreeNode_User *tree);
void UserFromFile_Tree(Tree_User *tree);

User *Input_User_Data();
TreeNode_User *Tree_Search_User(TreeNode_User *tree,long int number);
long int SignIn_User();
void UserToFile(User *user);

void SignIn_User_Menu();
void User_Menu(User *user);
void Recharge_User(long int number);



#endif



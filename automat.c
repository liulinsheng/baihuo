#include<sqlite3.h>
#include"automat.h"

float money = 0.025;

/********************************图***********************************/

void CreateMGraph(MGraph *G,VertexType *data,int edgeData[MaxVerNum][MaxVerNum]){
	int i,j,k,w;
	G->vnum =  10;//顶点数
	G->enumw = 15;//边数
	for (i = 0; i < G->vnum; ++i){
		G->vexs[i] = data[i];
	}//获取顶点信息，建立顶点表
	for (i = 0; i < G->vnum; ++i){
		for (j = 0; j < G->vnum; ++j){
			G->edges[i][j] = edgeData[i][j];//邻接矩阵的值赋给两点的边即距离
		}
	}
	return;
}//创建有向图储存

void initVnum(VertexType *data){
	strcpy(data[0].address,"零食小吃区");
	strcpy(data[1].address,"蔬菜水果区");
	strcpy(data[2].address,"生活用品区");
	strcpy(data[3].address,"冰冻冷藏区");
	strcpy(data[4].address,"日常服饰区");
	strcpy(data[5].address,"肉类海鲜区");
	strcpy(data[6].address,"名烟名酒区");
	strcpy(data[7].address,"美妆配饰区");
	strcpy(data[8].address,"家具家电区 ");
	strcpy(data[9].address,"珠宝钟表区");
	return ;
}//给顶点命名

void initEdge(int edgeData[MaxVerNum][MaxVerNum]){

	for (int i = 0; i < 10; ++i){
		for (int j = 0; j < 10; ++j){
			edgeData[i][j] = INFINITY;
		}
	}
	edgeData[0][1] = edgeData[1][0] = 11;
	edgeData[0][2] = edgeData[2][0] = 16;
	edgeData[0][3] = edgeData[3][0] = 21;

	edgeData[1][5] = edgeData[5][1] = 20;
	edgeData[1][6] = edgeData[6][1] = 5;

	edgeData[2][4] = edgeData[4][2] = 18;

	edgeData[3][4] = edgeData[4][3] = 10;
	edgeData[3][7] = edgeData[7][3] = 17;

	edgeData[4][6] = edgeData[6][4] = 12;
	edgeData[4][7] = edgeData[7][4] = 14;

	edgeData[5][6] = edgeData[6][5] = 10;
	edgeData[5][8] = edgeData[8][5] = 21;

	edgeData[6][8] = edgeData[8][6] = 17;
	edgeData[6][9] = edgeData[9][6] = 11;

	edgeData[7][9] = edgeData[9][7] = 21;

	return;
}

int SelectAddress(){
	system("clear");
	int flat;
	int vertex;
	printf(" -----------------------------------欢迎来到大洋百货-------------------------------------\n");
	printf("                              Welcome to Dayang mall                               \n");
	printf("----------------------------------                               ------------------------\n");
	printf("                                        1.零食小吃区                                         \n");
	printf("                                                                                         \n");
	printf("                                        2.蔬菜水果区                                         \n");
	printf("                                                                                         \n");
	printf("                                        3.生活用品区                                         \n");
	printf("                                                                                         \n");
	printf("                                        4.冰冻冷藏区                                       \n");
	printf("                                                                                         \n");
	printf("                                        5.日常服饰区                                         \n");
	printf("                                                                                         \n");
	printf("                                        6.肉类海鲜区                                         \n");
	printf("                                                                                         \n");
	printf("                                        7.名烟名酒区                                         \n");
	printf("                                                                                         \n");
	printf("                                        8.美妆配饰区                                         \n");
	printf("                                                                                         \n");
	printf("                                        9.家具家电区                                         \n");
	printf("                                                                                         \n");
	printf("                                        10.珠宝钟表区                                        \n");
	printf("----------------------------------                               ------------------------\n");
	printf("----------------------------------------yangyang为您导航-------------------------------------\n");
	printf("                                                                                         \n");
	printf("请问您的当前位置为？\n");
	printf("                                                                                         \n");
	scanf("%d",&flat);
	switch(flat){
		case 1:		vertex = 0;
				break;
		case 2:		vertex = 1;
				break;
		case 3:		vertex = 2;
				break;
		case 4:		vertex = 3;
				break;
		case 5:		vertex = 4;
				break;
		case 6:		vertex = 5;
				break;
		case 7:		vertex = 6;
				break;
		case 8:		vertex = 7;
				break;
		case 9:		vertex = 8;
				break;
		case 10:	vertex = 9;
				break;
	}
	return vertex;
}//把地点传入


void ShortestPath(MGraph *G, int P[MaxVerNum], int D[MaxVerNum], VertexType *data,int vertex,int end){
	int i,j,k,pre,min;
	int sign = 0;
	int final[MaxVerNum] = {0};
	final[vertex] = 1;
	for (i = 0; i < G->vnum; ++i){
		D[i] = G->edges[vertex][i];
		P[i] = -1;
	}
	D[vertex] = 0;
	final[vertex] = 1;
	P[vertex] = -1;
	for (i = 1; i < G->vnum; ++i){
		min = INFINITY + 1;
		for (k = 0; k < G->vnum; ++k){
			if (final[k] == 0 && D[k]< min){
				j = k;
				min = D[k];
			}
		}
		final[j] = 1;
		for (k = 0; k < G->vnum; ++k){
			if (final[k] == 0 && (D[j] + G->edges[j][k] < D[k])){
				D[k] = D[j] + G->edges[j][k];
				P[k] = j;
			}
		}
	}

	for (i = 0; i < G->vnum; ++i){
		if(i != end)	continue;
		printf("                                                                                       \n");
		printf("路程大约:%d \n m",D[i] ); 
		printf("                                                                                       \n");
		printf("为您规划行程最短路线: %s", data[i].address);
		printf("                                                                                       \n");
		pre = P[i];
		while(pre > 0 || (sign == 0 && pre == 0)){
			printf(" <<%s",data[pre].address );
			if(pre == 0)	sign = 1;
			pre = P[pre];
		}
		printf(" <<%s",data[vertex].address);
		printf("\n");
	}
	return;

}

void Navigate(){
	int i,j,start,end;
	int P[MaxVerNum];
	int D[MaxVerNum];
	int edgeData[MaxVerNum][MaxVerNum];

	VertexType data[MaxVerNum];

	MGraph *graph = (MGraph *)malloc(sizeof(MGraph));
	initEdge(edgeData);
	initVnum(data);
	CreateMGraph(graph,data,edgeData);
	start = SelectAddress();
	printf("                                                                                         \n");
	printf("请问您想要到达的终点为?\n");
	printf("                                                                                         \n");
	scanf("%d",&end);
	printf("                                                                                         \n");
	ShortestPath(graph, P, D, data,start,end - 1);

	return;
}





/***********************************************************/

List_Goods *initList_Goods (){

	List_Goods *list = (List_Goods *)malloc(sizeof(List_Goods));
	list->head = NULL;
	list->tail = NULL;
	list->current = NULL;

	return list;
}//链表初始化

NodeGoods *Find_Goods_name_node(List_Goods *list,char name[]){
	NodeGoods *tmp = list->head;
	while(tmp != NULL && strcmp(tmp->data->name,name)){
		tmp = tmp->next;
	}
	return tmp;
}//通过name查找节点并返回

List_Goods *Find_Goods_name(List_Goods *list,char name[]){
	NodeGoods *tmp = list->head;
	while(tmp != NULL){
		if( !strcmp(tmp->data->name,name)){
			tmp->data->sign = 1;
		}
		tmp = tmp->next;
	}
	return list;
}//通过name查找节点并返回

List_Goods *Find_Goods_Isbn(List_Goods *list,long int isbn){
	NodeGoods *tmp = list->head;
	while(tmp != NULL){
		if( tmp->data->isbn == isbn){
			tmp->data->sign = 1;			
		}
		tmp = tmp->next;
	}
	return list;
}//通过isbn查找节点并返回

List_Goods *Find_Goods_Type(List_Goods *list,char type[]){
	NodeGoods *tmp = list->head;
	while(tmp != NULL){
		if( !strcmp(tmp->data->type,type)){
			tmp->data->sign = 1;	
		}
		tmp = tmp->next;
	}
	return list;
}//通过type查找节点并返回

NodeGoods *PromptFind_Goods_name(List_Goods *list){
	char name[20];
	NodeGoods *goods;
	printf("                                                                                         \n");
	printf("\n请输入您要删除的商品名\n");
	printf("                                                                                         \n");
	scanf("%s",name);
	goods = Find_Goods_name_node(list,name);//调用函数找到该被删除的商品名称

	return goods;//返回该被删除的商品名称
}

int Order_Number(){
	int order = 1,id = 0;
	int integral,sign;
	long int isbn;
	char name[32],reward[32],type[32];
	float price;
	time_t atime;

	FILE *fp;//FILE结构体，fp表示文件指针类型
	fp = fopen("goods.txt", "r");//fopen表示打开文件夹r表示读文件
	if (fp != NULL)
	{
		while(!feof(fp)){//feof函数用来检测文件读写位置指针是否已到文件尾
			fscanf(fp,"%d",&id);
			fscanf(fp,"%s",name);//读入商品名
			fscanf(fp,"%ld",&isbn);
			fscanf(fp,"%f",&price);
			fscanf(fp,"%s",type);
			fscanf(fp,"%ld",&atime);
			fscanf(fp,"%d",&sign);
			fscanf(fp,"%d",&integral);
			order = id + 1;
		}//格式化读函数
		fclose(fp);

	}else{
		printf("文件打开失败 ！\n");
	}
	return order;

}

Goods *PromptInput_Data(List_Goods *list){
	Goods *goods = (Goods *)malloc(sizeof(Goods));
	int id;
	int integral;
	float price;
	long int isbn;
	char name[32];
	char type[32];
	id = Order_Number();
	goods->id = id;
	goods->sign = 0;
	goods->atime = time(0);
	printf("请输入商品名\n");
	scanf("%s",name);
	strcpy(goods->name,name);

	printf("请输入编号\n");
	scanf("%ld",&isbn);
	goods->isbn = isbn;

	printf("请输入类型\n");
	scanf("%s",type);
	strcpy(goods->type,type);

	printf("请输入价格\n");
	scanf("%f",&price);
	goods->price = price;

	printf("请输入积分\n");
	scanf("%d",&integral);
	goods->integral = integral;

	return goods;

}//输入信息

void addTail_Goods(List_Goods *list){

	NodeGoods *node = (NodeGoods *)malloc(sizeof(NodeGoods));
	node->data = PromptInput_Data(list);
	node->next = NULL;

	if(list->head == NULL){
		list->head = node;
	}else{
		list->tail->next = node;
	}
	list->tail = node;

	return;
}//头插法储存信息


void delNode_Goods(List_Goods *list){
	NodeGoods *node = PromptFind_Goods_name(list);
	if(node == list->head){
		if(list->head->next == NULL){
			list->head = list->tail = NULL;
		}else{
			list->head = list->head->next;
		}
	}else{
		NodeGoods *tmp = list->head;
		while(tmp != NULL && tmp->next != node){
			tmp = tmp->next;
		}
		if(tmp != NULL){
			tmp->next = node->next;
		}
	}
	free(node);

	return;
}

void GoodsToFile(List_Goods *list){

	NodeGoods *tmp = list->head;
	FILE *fp;
	fp = fopen("goods.txt","a");//a意为打开文本文件进行追加
	if (fp != NULL)
	{
		while(tmp != NULL){
			fprintf(fp, "%d\t\t", tmp->data->id);
			fprintf(fp, "%s\t\t", tmp->data->name);
			fprintf(fp, "%ld\t\t", tmp->data->isbn);
			fprintf(fp, "%.2f\t\t", tmp->data->price);
			fprintf(fp, "%s\t\t", tmp->data->type);
			fprintf(fp, "%ld\t\t", tmp->data->atime);
			fprintf(fp, "%d\t\t", tmp->data->sign);
			fprintf(fp, "%d\n",tmp->data->integral);

			tmp = tmp->next;
		}
		fclose(fp);
	}else{
		printf("文件保存失败 ！\n");
	}
}//写商品信息入文件

void GoodsToFile_Del(List_Goods *list){

	NodeGoods *tmp = list->head;
	FILE *fp;
	int id = 0;
	fp = fopen("goods.txt","w");//打开文件用于写
	if (fp != NULL)
	{
		while(tmp != NULL){
			if (tmp->data->price == 0) break;
			id++;
			fprintf(fp, "%d\t\t", id);
			fprintf(fp, "%s\t\t", tmp->data->name);
			fprintf(fp, "%ld\t\t", tmp->data->isbn);
			fprintf(fp, "%.2f\t\t", tmp->data->price);
			fprintf(fp, "%s\t\t", tmp->data->type);
			fprintf(fp, "%ld\t\t", tmp->data->atime);
			fprintf(fp, "%d\t\t", tmp->data->sign);
			fprintf(fp, "%d\n",tmp->data->integral);



			tmp = tmp->next;

		}
		fclose(fp);
	}else{
		printf("文件保存失败 ！\n");
	}
}//写入商品信息

void addTail_Goods_File(List_Goods *list,Goods *data){
	NodeGoods *node = (NodeGoods *)malloc(sizeof(NodeGoods));
	node->data = data;
	node->next = NULL;

	if(list->head == NULL){
		list->head = node;
	}else{
		list->tail->next = node;
	}
	list->tail = node;

	return;
}

void GoodsFromFile(List_Goods *list){
	FILE *fp;
	fp = fopen("goods.txt", "r");//打开文件用于读
	if (fp != NULL)
	{
		while(!feof(fp)){
			Goods *goods = (Goods *)malloc(sizeof(Goods));
			fscanf(fp,"%d",&(goods->id));
			fscanf(fp,"%s",goods->name);
			fscanf(fp,"%ld",&(goods->isbn));
			fscanf(fp,"%f",&(goods->price));
			fscanf(fp,"%s",goods->type);
			fscanf(fp,"%ld",&(goods->atime));
			fscanf(fp,"%d",&(goods->sign));
			fscanf(fp,"%d",&(goods->integral));

			addTail_Goods_File(list,goods);//读取文件信息再调用头插法存入
		}

		fclose(fp);

	}else{
		printf("文件打开失败 ！\n");
	}
	return;
}

void Free_Goodslist(NodeGoods *list){

	NodeGoods *tmp;
	while(list != NULL){
		tmp = list;
		list = list->next;
		free(tmp);
		tmp = NULL;
	}
	return;
}//释放内存，保护磁盘

/************************************************************/


void CreateTree(Tree *tree, Goods *data){
	TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	if (tree->root == NULL){
		tree->root = node;
	}else{
		TreeNode *tmp = tree->root;
		while(tmp != NULL){
			if (data->id < tmp->data->id){
				if (tmp->left == NULL){
					tmp->left = node;
					return;
				}else{
					tmp = tmp->left;
				}
			}else{
				if (tmp->right ==NULL){
					tmp->right = node;
					return;
				}else{
					tmp = tmp->right;
				}
			}
		}
	}
	return;//初始化树
}

void display_Goods(NodeGoods *node){
	timeform *form;	
	form = localtime(&(node->data->atime));
	if( node->data->id > 0){
		printf("--------------------------------------------------------------------------------------\n");

		printf("商品名: %s\t\t", node->data->name);
		printf("编号: %ld\t\t", node->data->isbn);

		printf("类型: %s\t\t", node->data->type);
		printf("价格: %.2f\t", node->data->price);
		printf("积分: %d\t\t",node->data->integral);
		printf("入库时间:%04u-%02u-%02u  %02u:%02u:%02u\n",
				form->tm_year+1900,form->tm_mon+1,form->tm_mday,form->tm_hour,form->tm_min,form->tm_sec );
		printf("---------------------------------------------------------------------------------------\n");
	}
	return;//用链表输出单个节点数据
}


void displayTree_Goods(TreeNode *tree){
	timeform *form;	
	form = localtime(&(tree->data->atime));
	if( tree->data->id > 0){
		printf("---------------------------------------------------------------------------------------\n");
		printf("%d\t\t", tree->data->id);
		printf("商品名: %s\t\t", tree->data->name);
		printf("编号: %ld\t\t", tree->data->isbn);

		printf("类型: %s\t\t", tree->data->type);
		printf("价格: %.2f\t", tree->data->price);
		printf("积分: %d\t\t",tree->data->integral);
		printf("入库时间:%04u-%02u-%02u  %02u:%02u:%02u\n",
				form->tm_year+1900,form->tm_mon+1,form->tm_mday,form->tm_hour,form->tm_min,form->tm_sec );

	}
	return;
}//用树输出全部的商品信息

void InOrder(TreeNode *tree){
	if (tree){
		InOrder(tree->left);
		displayTree_Goods(tree);
		InOrder(tree->right);
	}
	return;
}//

void GoodsFromFile_Tree(Tree *tree){
	FILE *fp;
	fp = fopen("goods.txt", "r");
	if (fp != NULL)
	{
		while(!feof(fp)){
			Goods *goods = (Goods *)malloc(sizeof(Goods));
			fscanf(fp,"%d",&(goods->id));
			fscanf(fp,"%s",goods->name);
			fscanf(fp,"%ld",&(goods->isbn));
			fscanf(fp,"%f",&(goods->price));
			fscanf(fp,"%s",goods->type);
			fscanf(fp,"%ld",&(goods->atime));
			fscanf(fp,"%d",&(goods->sign));
			fscanf(fp,"%d",&(goods->integral));

			CreateTree(tree, goods);
		}

		fclose(fp);

	}else{
		printf("文件打开失败 ！\n");
	}
	return;	
}//用树读文件里的商品信息

void FreeTree_Goods(TreeNode *tree){
	if (tree){
		FreeTree_Goods(tree->left);
		free(tree->data);
		free(tree);
		FreeTree_Goods(tree->right);
	}
}//释放内存


/***************************************************/

void Seek_name(){
	system("clear");//清屏
	char name[20];
	NodeGoods *tmp;
	List_Goods *list1;
	List_Goods *list = initList_Goods();
	GoodsFromFile(list);//调用函数读取信息

	printf("请输入你要查找的商品名\n");
	printf("                                                                                         \n");
	scanf("%s",name);
	list1 = Find_Goods_name(list,name);//调用函数找到匹配商品
	tmp = list1->head;
	while(tmp != NULL){
		if(tmp->data->sign == 1){
			display_Goods(tmp);//输出商品信息
		}
		tmp = tmp->next;
	}

	Free_Goodslist(list->head);//释放内存
	printf("\n");
	printf("请按任意键返回\n");
	getchar();
	getchar();
	system("clear");

	return;
}

void Seek_Isbn(){
	system("clear");
	long int isbn;
	NodeGoods *tmp;
	List_Goods *list1;
	List_Goods *list = initList_Goods();
	GoodsFromFile(list);//读取信息

	printf("请输入你要查找的编号\n");
	scanf("%ld",&isbn);
	list1 = Find_Goods_Isbn(list,isbn);
	tmp = list1->head;
	while(tmp != NULL){
		if(tmp->data->sign == 1){
			display_Goods(tmp);
		}
		tmp = tmp->next;
	}

	Free_Goodslist(list->head);
	printf("\n");
	printf("请按任意键返回\n");
	getchar();
	getchar();
	system("clear");

	return;
}

void Seek_Type(){
	system("clear");
	char type[32];
	NodeGoods *tmp;
	List_Goods *list1;
	List_Goods *list = initList_Goods();
	GoodsFromFile(list);

	printf("请输入你要查找的类型\n");
	scanf("%s",type);
	list1 = Find_Goods_Type(list,type);
	tmp = list1->head;
	while(tmp != NULL){
		if(tmp->data->sign == 1){
			display_Goods(tmp);
		}
		tmp = tmp->next;
	}

	Free_Goodslist(list->head);
	printf("\n");
	printf("请按任意键返回\n");
	getchar();
	getchar();
	system("clear");
}

void Seek_Menu(){
	system("clear");
	char flat;
	while(1){
		printf("*************************************************************************\n");
		printf("*************************************************************************\n");
		printf("                                                                         \n");
		printf("                          请选择你要进行的操作                           \n");
		printf("                                                                         \n");
		printf("                            1.商品名查找                                 \n");
		printf("                                                                         \n");
		printf("                            2.编号查找                                   \n");
		printf("                                                                         \n");
		printf("                            3.类型查找                                   \n");
		printf("                                                                         \n");
		printf("                            4.退出                                       \n");
		printf("                                                                         \n");
		printf("*************************************************************************\n");
		printf("*************************************************************************\n");
		flat = getchar();
		switch(flat){
			case '1':	Seek_name();
					break;
			case '2':	Seek_Isbn();
					break;
			case '3':	Seek_Type();
					break;
			case '4':	system("clear");
					return;
		}

	}


	return;
}



/****************************************************/

void Goods_MenuCheck(){
	system("clear");
	Tree *tree = (Tree *)malloc(sizeof(Tree));
	tree->root = NULL;
	GoodsFromFile_Tree(tree);
	InOrder(tree->root);
	FreeTree_Goods(tree->root);
	printf("\n");
	printf("请按任意键返回\n");
	getchar();
	getchar();
	system("clear");

	return;
}//调用函数完成信息查看

void Goods_MenuAdd(){
	system("clear");
	char flat = 'n';
	List_Goods *list = initList_Goods();
	while(flat != 'y'){

		addTail_Goods(list);
		printf("是否退出y or n\n");
		getchar();
		scanf("%c",&flat);
	}//写入信息
	GoodsToFile(list);//添入文件中
	Free_Goodslist(list->head);
	printf("\n");
	printf("请按任意键返回\n");
	getchar();
	getchar();
	system("clear");

	return;
}

void Goods_MenuDel(){
	system("clear");
	char flat = 'n';
	List_Goods *list = initList_Goods();
	GoodsFromFile(list);
	while(flat != 'y'){
		delNode_Goods(list);
		printf("是否退出y or n\n");
		getchar();
		scanf("%c",&flat);
	}
	GoodsToFile_Del(list);
	Free_Goodslist(list->head);
	printf("\n");
	printf("请按任意键返回\n");
	getchar();
	system("clear");

	return;
}

void Goods_Menu(){
	system("clear");
	char flat;
	Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
	tree->root = NULL;
	UserFromFile_Tree(tree);
	while(1){
		printf("*************************************************************************\n");
		printf("*************************************************************************\n");
		printf("                                                                         \n");
		printf("                        请选择你要进行的操作                             \n");
		printf("                                                                         \n");
		printf("                        1.查看商品                                       \n");
		printf("                                                                         \n");
		printf("                        2.添加商品                                       \n");
		printf("                                                                         \n");
		printf("                        3.删除商品                                       \n");
		printf("                                                                         \n");
		printf("                        4.商品查询                                       \n");
		printf("                                                                         \n");
		printf("                        5.用户信息                                       \n");
		printf("                                                                         \n");
		printf("                        6.返回上层                                       \n");
		printf("                                                                         \n");
		printf("*************************************************************************\n");
		printf("*************************************************************************\n");
		flat = getchar();
		switch(flat){
			case '1':	Goods_MenuCheck();
					break;
			case '2':	Goods_MenuAdd();
					break;
			case '3':	Goods_MenuDel();
					break;
			case '4':	getchar();
					Seek_Menu();
					getchar();
					break;
			case '5':	getchar();
					system("clear");
					InOrder_User(tree->root);
					printf("\n");
					printf("请按任意键返回\n");
					getchar();
					system("clear");
					break;
			case '6':	system("clear");
					FreeTree_User(tree->root);
					return;
		}

	}
	return;
}

void Main_Menu(){
	system("clear");
	char flat;
	while(1){
		printf("*************************************************************************\n");
		printf("*************************************************************************\n");
		printf("                 欢迎使用百货小助手，请选择你要进行的操作              \n");
		printf("*************************************************************************\n");
		printf("*************************************************************************\n");
		printf("                                                                         \n");
		printf("                           1.我是顾客                                    \n");
		printf("                                                                         \n");
		printf("                           2.我是管理者                                  \n");
		printf("                                                                         \n");
		printf("                           3.退出                                        \n");
		printf("                                                                         \n");
		printf("*************************************************************************\n");
		printf("*************************************************************************\n");
		flat = getchar();
		switch(flat){
			case '1':	getchar();
					SignIn_User_Menu();
					getchar();
					break;
			case '2':	getchar();
					Goods_Menu();
					getchar();
					break;
			case '3':	system("clear");
					return;
		}

	}
	return;
}

/**********************用户系统********************************/

List_User *initList_User(){

	List_User *list = (List_User *)malloc(sizeof(List_User));
	list->head = NULL;
	list->tail = NULL;
	list->current = NULL;

	return list;
}//链表初始化

void addTail_User(List_User *list,User *data){

	NodeUser *node = (NodeUser *)malloc(sizeof(NodeUser));
	node->data = data;
	node->next = NULL;

	if(list->head == NULL){
		list->head = node;
	}else{
		list->tail->next = node;
	}
	list->tail = node;

	return;
}//头插法构建链表  

void Free_Userlist(NodeUser *list){

	NodeUser *tmp;
	while(list != NULL){
		tmp = list;
		list = list->next;
		free(tmp);
		tmp = NULL;
	}
	return;
}//释放链表 


void UserToFile_list(List_User *list){

	NodeUser *tmp = list->head;
	FILE *fp;
	fp = fopen("user.txt","a");
	if (fp != NULL)
	{
		while(tmp != NULL){
			fprintf(fp, "%ld\t", tmp->data->number);
		//	fprintf(fp, "%s\t", tmp->data->password);
			fprintf(fp, "%s\t", tmp->data->name);
			fprintf(fp, "%d\n", tmp->data->integral);

			tmp = tmp->next;
		}
		fclose(fp);
	}else{
		printf("文件保存失败 ！\n");
	}
}//输出用户信息

void UserFromFile_list(List_User *list){
	FILE *fp;
	fp = fopen("user.txt", "r");
	if (fp != NULL)
	{
		while(!feof(fp)){
			User *user = (User *)malloc(sizeof(User));
			fscanf(fp, "%ld", &(user->number));
		//	fscanf(fp, "%s", user->password);
			fscanf(fp, "%s", user->name);
			fscanf(fp, "%d",&(user->integral));

			addTail_User(list,user);
		}

		fclose(fp);

	}else{
		printf("文件打开失败 ！\n");
	}
	return;
}//读入用户信息

/************************************************************************/

void CreateTree_User(Tree_User *tree, User *data){
	TreeNode_User *node = (TreeNode_User *)malloc(sizeof(TreeNode_User));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	if (tree->root == NULL){
		tree->root = node;
	}else{
		TreeNode_User *tmp = tree->root;
		while(tmp != NULL){
			if (tmp->data->number > data->number ){
				if (tmp->left == NULL){
					tmp->left = node;
					return;
				}else{
					tmp = tmp->left;
				}
			}else{
				if (tmp->right ==NULL){
					tmp->right = node;
					return;
				}else{
					tmp = tmp->right;
				}
			}
		}
	}
	return;
}

void displayTree_User(TreeNode_User *tree){ 

	if(tree->data->number == 0 || tree->data->number > 1000000000000)       return;
	printf("账号: %ld\t",tree->data->number);
	printf("用户名: %s\t",tree->data->name);
	printf("积分: %d\t", tree->data->integral);

	printf("\n");
	printf("_____________________________________________________________________________________\n");

	return;
}

void InOrder_User(TreeNode_User *tree){
	if (tree){
		InOrder_User(tree->left);
		displayTree_User(tree);
		InOrder_User(tree->right);
	}
	return;
}

void FreeTree_User(TreeNode_User *tree){
	if (tree){
		FreeTree_User(tree->left);
		free(tree->data);
		free(tree);
		FreeTree_User(tree->right);
	}
	return;
}

void UserFromFile_Tree(Tree_User *tree){
	FILE *fp;
	fp = fopen("user.txt", "r");
	if (fp != NULL)
	{
		while(!feof(fp)){
			User *user = (User *)malloc(sizeof(User));
			fscanf(fp, "%ld", &(user->number));
                      //  fscanf(fp, "%s", user->password);
			fscanf(fp, "%s", user->name);
			fscanf(fp, "%d",&(user->integral));

			CreateTree_User(tree, user);
		}

		fclose(fp);

	}else{
		printf("文件打开失败 ！\n");
	}
	return; 
}
/****************************************************************/
void Recharge_User(long int number){
	system("clear");
	FILE *fp;
	char name[32];
	List_Goods *listg;
	NodeGoods *goodsnode;
	listg = initList_Goods();
	GoodsFromFile(listg);

	Tree *treeg = (Tree *)malloc(sizeof(Tree));
	treeg->root = NULL;
	GoodsFromFile_Tree(treeg);

	Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
	TreeNode_User *Treenode;
	tree->root = NULL;
	UserFromFile_Tree(tree);
	Treenode = Tree_Search_User(tree->root,number);
	List_User *list;
	list = initList_User();
	UserFromFile_list(list);
	NodeUser *tmp1 = list->head;
	while(tmp1 != NULL && tmp1->data->number != Treenode->data->number){
		tmp1 = tmp1->next;
	}

	NodeUser *node = tmp1;
	if(node == list->head){
		if(list->head->next == NULL){
			list->head = list->tail = NULL;
		}else{
			list->head = list->head->next;
		}
	}else{
		NodeUser *tmp = list->head;
		while(tmp != NULL && tmp->next != node){
			tmp = tmp->next;
		}
		if(tmp != NULL){
			tmp->next = node->next;
		}
	}
	free(node);

	fp = fopen("user.txt","w");
	memset(fp,0,sizeof(fp));

	InOrder(treeg->root);
	printf("\n");
	printf("请选择您要购买的商品(商品名)\n");
	scanf("%s",name);
	goodsnode = Find_Goods_name_node(listg,name);
	if(goodsnode != NULL){
		printf("选购成功 !\n");
		printf("正在支付...\n");
		sleep(2);
		system("clear");
		printf("支付成功！\n");
		Treenode->data->integral += goodsnode->data->integral;
	}
	UserToFile(Treenode->data);
	NodeUser *tmp2 = list->head;
	while(tmp2 != NULL){
		UserToFile(tmp2->data);
		tmp2 = tmp2->next;
	}
	fclose(fp);
	Free_Userlist(list->head);
	FreeTree_User(tree->root);
	FreeTree_Goods(treeg->root);
	Free_Goodslist(listg->head);

	return;
}



User *Input_User_Data(){
	system("clear");
	long int number;
	char *ch;//返回值应为字符串首地址
	char name[30];
	User *user = (User *)malloc(sizeof(User));
	user->integral = 0;
	printf("*************************************************************************\n");
	printf("*************************************************************************\n");
	printf("请输入你要注册的账户\n");
	scanf("%ld",&number);
	user->number = number;

	printf("请输入用户名\n");
	scanf("%s",name);
	strcpy(user->name,name);

	ch = getpass("请输入密码\n");
	//scanf("%s",password);
	//strcpy(user->password,password);

	printf("\n");
	printf("请按任意键返回\n");
	getchar();
	getchar();
	system("clear");


	return user;
}

TreeNode_User *Tree_Search_User(TreeNode_User *tree,long int number){
	TreeNode_User *ptr = tree;
	while(ptr){
		if ( ptr->data->number == number )  return(ptr);
		if (ptr->data->number > number )        ptr = ptr->left;
		else    ptr = ptr->right;
	}
	return NULL;
}

long int SignIn_User(){
	system("clear");
	long int number;
	char password[50];
	int sign1 = 1, sign2 = 1;
	Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
	TreeNode_User *node;
	tree->root = NULL;
	UserFromFile_Tree(tree);
	printf("请输入账号\n");
	scanf("%ld",&number);

	while(1){
		if(sign1 >= 3){
			printf("账号错误三次 !\n");
			printf("正在退出....\n");
			sleep(2);
			system("clear");
			return 0;

		}else if((node = Tree_Search_User(tree->root,number)) == NULL){
			printf("账号不存在 !\n");
			printf("请重新输入\n");
			scanf("%ld",&number);

			sign1++;

		}else{
			break;
		}
	}
char *ch = getpass("请输入密码\n");
//printf("请输入密码\n");
//	scanf("%s",password);
//	while(1){
//		if(sign2 >= 3){
//			printf("密码错误三次 !\n");
//			printf("正在退出....\n");
//			sleep(2);
//			system("clear");
//			return 0;
//
//		}else if(strcmp(node->data->password,password)){
//			printf("密码错误 !\n");
//			printf("请重新输入\n");
//			scanf("%s",password);
//
//			sign2++;
//		}else{
//			break;
//		}
//	}
	FreeTree_User(tree->root);
	printf("\n");
	printf("正在登入.....\n");
	sleep(2);
	getchar();
	system("clear");

	return number;
}

void UserToFile(User *user){

	FILE *fp;
	fp = fopen("user.txt","a");
	if (fp != NULL){
		if(user->number == 0)       return;
		fprintf(fp, "%ld\t", user->number);
	//	fprintf(fp, "%s\t", user->password);
		fprintf(fp, "%s\t", user->name);
		fprintf(fp, "%d\n", user->integral);

		fclose(fp);
	}else{
		printf("文件保存失败 ！\n");
	}
	return;
}

void User_Menu(User *user){
	char flag;
	int sign = 0;
	TreeNode_User *node;
	Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
	tree->root = NULL;

	while(1){
		printf("*************************************************************************\n");
		printf("*************************************************************************\n");
		printf("                   大洋百货欢迎您: %s\n",user->name                       );
		printf("                                                                         \n");
		printf("                     1.百货导航                                          \n");
		printf("                                                                         \n");
		printf("                     2.选购商品                                          \n");
		printf("                                                                         \n");
		printf("                     3.查看积分                                          \n");
		printf("                                                                         \n");
		printf("                     4.返回上层                                          \n");
		printf("                                                                         \n");
		printf("*************************************************************************\n");
		printf("*************************************************************************\n");
		flag = getchar();
		switch(flag){

			case '1':  	Navigate();
					printf("\n");
					printf("请按任意键返回\n");
					getchar();
					getchar();
					system("clear");
					break;
			case '2':	Recharge_User(user->number);
					printf("\n");
					getchar();
					printf("请按任意键返回\n");
					getchar();
					system("clear");
					break;
			case '3':	system("clear");
					UserFromFile_Tree(tree);
					node = Tree_Search_User(tree->root,user->number);
					printf("***积分可在服务台换代金券，10000分可换5元，20000分可换10元，依次累加***\n");
					printf("您的账号有: %d 积分\n",node->data->integral );
					printf("\n");
					getchar();
					printf("请按任意键返回\n");
					getchar();
					FreeTree_User(tree->root);
					tree->root = NULL;
					system("clear");
					break;
			case '4':   FreeTree_User(tree->root);
				    system("clear");

				    return;
		}

	}
	return;
}


void SignIn_User_Menu(){
	system("clear");
	char flag;
	long int number;
	User *user = (User *)malloc(sizeof(User));
	User *user1;
	Tree_User *tree = (Tree_User *)malloc(sizeof(Tree_User));
	TreeNode_User *node;
	tree->root = NULL;
	UserFromFile_Tree(tree);
	while(1){
		printf("--------------------------欢迎您使用百货小助手-----------------------------------\n");
		printf("                                                                                       \n");
		printf("                                1.登录                                                 \n");
		printf("                                                                                       \n");
		printf("                                2.注册                                                 \n");
		printf("                                                                                       \n");
		printf("                                3.退出                                                 \n");
		printf("                                                                                       \n");
		flag = getchar();
		switch(flag){
			case '1':   UserFromFile_Tree(tree);
				    if((number = SignIn_User(user)) != 0){
					    node = Tree_Search_User(tree->root,number);
					    User_Menu(node->data);

				    }
				    FreeTree_User(tree->root);
				    tree->root = NULL;
				    getchar();
				    break;
			case '2':   user1 = Input_User_Data();
				    UserToFile(user1);
				    FreeTree_User(tree->root);
				    tree->root = NULL;
				    break;
			case '3':   free(user);
				    FreeTree_User(tree->root);
				    getchar();
				    system("clear");

				    return;
		}
	}


	return;
}



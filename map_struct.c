# include<stdio.h>
# include<stdlib.h>
//# include<windows.h>


#define MAXSIZESI 16//地点名称长度

struct map_head_node {//暂定作为数组
	int name;//顶点名称
	struct map_node * map_lnext ;//相邻顶点
};

struct map_node{
	int head_number;//该点在头节点数组中的位置
	int weight;//权值
	struct map_node* mn_next;//next node
};

char situation [][MAXSIZESI] = {
	"0正门", 
	"1二门",
	"2第二教学楼", 
	"3第一教学楼", 
	"4图书馆", 
	"5博达公寓",
	"6第五教学楼", 
	"7第六教学楼",
	"8第十教学楼",
	"9体育场1",
	"10第七教学楼",
	"11音乐厅",
	"12体育场2",
	"13第四教学楼",
	"14第三教学楼"
};//顶点名称保存位置
#define MAP_SIZE sizeof(situation)/MAXSIZESI//地点数量

int sptset[MAP_SIZE];//查找集合
unsigned int distset[MAP_SIZE] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};//距离集合
int all_path[MAP_SIZE][2];

//******************单源最短路径*************************************************
//注意路线的保存 保存时可以考虑使用 2行N列的数组进行保存
struct map_head_node* determine_spt(struct map_head_node *a_node, int *min_number);
int settingpath(const struct map_head_node *a_node);

int find_dis(struct map_head_node *map_head, int source, int end)//更改为两个地点
{
    struct map_head_node *pnode = map_head;
    int n, i = 0;//源点终点

    n = source;
    sptset[source] = 1;//表示已查找过
    distset[source] = 0;//表示距离
    //初始化 集合
    
    while(n != end)
    {//功能为查找distset集合中最小的并且不再spt集合中的head_number和其前驱节点
        pnode = determine_spt(map_head, &n);//查找不在sptset中 但是在distset中
        if(!pnode)//如果返回的是NULL 那么所有顶点的最短路径已经找到
            return 1;//或者说当给出的终点是错误的那么可能会出现这种情况
        settingpath(pnode);//调整路径方便设置spt 固定distset
        sptset[n] = 1;
        all_path[i][0] = pnode->name;
        all_path[i++][1] = n;
    }

	return 0;
}

int settingpath(const struct map_head_node *a_node)
{//调整路径 将一个spt集合确定的顶点的边设置dist 注意当前顶点是需要在spt中已经确定的
    struct map_node *h_node = a_node[0].map_lnext;
    h_node = h_node->mn_next;
    int n = 0;

    if(!sptset[a_node->name])
        return 0;//判断当前是否为确定点 如果为确定点则可以进行 调整路径否则返回0
    while(h_node)
    {//遍历顶点的边
        if(sptset[h_node->head_number])
        {//判断spt集合中是否已经将其加入路径
            h_node = h_node->mn_next;
            continue;//继续寻找边中没有加入路径的成员 即不再spt集合中的值
        }
        distset[h_node->head_number] = distset[a_node->name] + h_node->weight;
        h_node = h_node->mn_next;
        n++;
    }

    return n;//返回值为是否已经设置 考虑会出现路径调整
}

//查找当前顶点最小的值 返回最小值的head_number
int find_min(const struct map_head_node *a_node)
{
    int min = -1;
    int n = -1;
    struct map_node *h_node = a_node->map_lnext;
    h_node = h_node->mn_next;
    //顶点的边
//注意对加入顶点的边 设置
    if(!settingpath(a_node))//调整 在查找最短路径时会按照已经加入sptset集合中的顶点
        return -1;//调整路径
//当前顶点所有边已经为true 在sptset中保存
    while(h_node)
    {
        if(sptset[h_node->head_number])
        {//过滤已经确定的路径
            h_node = h_node->mn_next;
            continue;
        }

        if(min > distset[h_node->head_number])
        {//查找当前顶点边的最小值
            min = distset[h_node->head_number];
            n = h_node->head_number;
        }
        h_node = h_node->mn_next;
    }

    return n;
}

//修改是否使用递归进行查找路径
struct map_head_node* determine_spt(struct map_head_node *a_node, int *min_number)
{
    //查找所有路径顶点的path 找到最短路径的顶点
    //在sptset 中同时其含有边的顶点进行查找最小值
    //注意这里可以转化为 不在sptset集合中但是在distset集合中的最小值 将其加入spt集合
    //而因路径数量的不确定性 所以比较每条路径的distset的最小值之后将其加入spt集合
    //注意此处不对spt进行设置而是将其放入调用函数中进行设置 
    //考虑将其转化为递归所带来的优点
    //暂时不易确定路径 但是可以取得最短路径值
    int source = 0;
    struct map_head_node *min_node = NULL;
    int n, min;

    while(source < MAP_SIZE)
    {
        if(!sptset[source++])
            continue;//过滤没有确定路径的顶点
        if(!min_node)
        {//第一个最小值 因为无法确定 会从哪个位置开始查找和在哪个位置找到可以查找的顶点
            *min_number = find_min(&a_node[source - 1]);
            if(*min_number != -1)
            {
                min_node = &a_node[source - 1];
                min = distset[*min_number];
            }
        }

        n = find_min(&a_node[source - 1]);//对distset中的最小值进行比较
        if(n == -1)
            continue;
        if(min > distset[n])
        {
            min = distset[n];
            *min_number = n;
            min_node = &a_node[source - 1];
        }
    }

    return min_node;
}

//************************地图创建************************************************
int create_mapnode(struct map_head_node *head_map, FILE *Rfmap_txt);

int map_init(struct map_head_node *p_mhnode)
{//对表头结点初始化
	int n = 0;
	int i, status = 1;
	FILE *Rfmap_txt = fopen("datadir/map.txt", "r");

	if (NULL == Rfmap_txt)
		exit(-1);//打开地图文件

	for(i = 0; i < MAP_SIZE && status; i ++)
	{//每次保存一个 头节点 链表
		fscanf(Rfmap_txt, "%d", &n);
		p_mhnode[i].name = n;
		status = create_mapnode(&p_mhnode[i], Rfmap_txt);
	}
 
	fclose(Rfmap_txt);//文件关闭
//返回值为初始化的数量
	return n;
}

//map的创建
int file_data(struct map_node *m_node, FILE* Rfmap_txt);

int create_mapnode(struct map_head_node *head_map, FILE *Rfmap_txt)
{
	int status = 1, i;
	struct map_node *phead = NULL,*pnode = NULL;//为顶点添加相邻顶点

	if(!(head_map->map_lnext = (struct map_node*)malloc(sizeof(struct map_node) ) ) )
		exit(-1);

	phead = head_map->map_lnext;
	//头结点初始化 默认 位置名称为-1 next =NULL 权值为-1
	phead->mn_next = NULL;
	phead->weight = -1;//带空头结点的链表

	for(i = 0; i < MAP_SIZE; i ++)
	{
		if(!(phead->mn_next = (struct map_node*)malloc(sizeof(struct map_node) ) ) )
        exit(-1);
		status = file_data(phead->mn_next, Rfmap_txt);//添加连接节点信息

		phead = phead->mn_next;
		phead->mn_next = NULL;
        if(status == 0)
            break;
		if(status == -1)
			return 0;//到达文件结尾 结束信息填充
	}


	return 1;//当前节点的邻接节点填充完毕
}
//为一个位置添加相邻位置信息

//文件读取 并处理
int file_data(struct map_node *m_node, FILE* Rfmap_txt)
{

	int ch = -1, ch2 = -1;
	int i = 0;

	//读取文件内容 保存到邻接表中注意 文件格式问题
	fscanf(Rfmap_txt, "%d %d", &ch, &ch2);
	m_node->weight = ch;//保存权值
	m_node->head_number = ch2;//保存位置

    ch = fgetc(Rfmap_txt);
	if((ch = getc(Rfmap_txt)) == EOF)
		return -1;//到达文件结尾
	if('\n' == ch)
		return 0;//当前节点的连接结束
	
	return 1;
}



void input_number(void)
{
	int i;

	printf("——————校园导航——————\n");
	for(i = 0; i < MAP_SIZE; i++)
		printf("%d: %s\n",i+1, situation[i]);
	printf("0:退出\n");
	printf("————————————————\n");
    printf("请输入地点前的代号 起点:终点");

	return ;
}


void print_map(struct map_head_node *map_head)
{
    int i;
    struct map_node *pnode = NULL;

    for(i = 0; i < MAP_SIZE; i++)
     {
         pnode = map_head[i].map_lnext;
         pnode = pnode->mn_next;
         while(pnode)
        {
            printf("id:%d weight: %d situation: %d\n", map_head[i].name, pnode->weight, pnode->head_number);
            pnode = pnode->mn_next;
        }
        printf("\n");
     }
    
    return ;
}

void s_allpath(int source, int end);
int id_f(int n);

int main(void)
{
	int source, end;
	struct map_head_node map_head[MAP_SIZE];
	for(source = 0; source < MAP_SIZE; source++)
    	for(end = 0; end < 2; end++)
	    	all_path[source][end] = -1;

    map_init(map_head);
    input_number();
    scanf("%d %d", &source, &end);
    source = id_f(source);
    end = id_f(end);
    if((source == -1) || (end == -1))
    {
        printf("输入错误!\n");
        return -1;
    }
//	print_map(map_head);//遍历图中每个头节点
    find_dis(map_head, source, end);
    s_allpath(source,end);

    return 0;
}


int id_f(int n)
{
	if(n >=  1 && n <= 15)
		return n -1;
	return -1;
}

int path[MAP_SIZE];
void print_path(int n);

void s_allpath(int source, int end)
{
	int i, j, n = 0;

	for(j = 0; j < MAP_SIZE; j++)
	{
		for(i = 0; all_path[i][0] != -1; i++)
			if(end == all_path[i][1])
			{
				path[n++] = all_path[i][1];
				end = all_path[i][0];
			}

	}
	printf("********\n");
	n--;
	printf("path:\n%s-->", situation[source]);
 	for(; n >= 0; n--)
		if(n == 0)
			printf("%s \t pathsize: %d\n", situation[path[n]], distset[path[n]]);
		else
			printf("%s-->", situation[path[n]]);
	return ;

}

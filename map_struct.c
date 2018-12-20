# include<stdio.h>
# include<stdlib.h>
//# include<windows.h>
//����205 402 202 203
#define MAXSIZESI 16//�ص����Ƴ���

struct map_head_node {//�ݶ���Ϊ����
	int name;//��������
	struct map_node * map_lnext ;//���ڶ���
/*
	struct map_head_node* mhn_node;//��һ������ڵ�
*/
};

struct map_node{
	int head_number;//�õ���ͷ�ڵ������е�λ��
	int weight;//Ȩֵ
	struct map_node* mn_next;//next node
};

char situation [][MAXSIZESI] = {
	"0����", 
	"1����",
	"2�ڶ���ѧ¥", 
	"3��һ��ѧ¥", 
	"4ͼ���", 
	"5���﹫Ԣ",
	"6�����ѧ¥", 
	"7������ѧ¥",
	"8��ʮ��ѧ¥",
	"9������1",
	"10���߽�ѧ¥",
	"11������",
	"12������2",
	"13���Ľ�ѧ¥",
	"14������ѧ¥"
};//�������Ʊ���λ��
#define MAP_SIZE sizeof(situation)/MAXSIZESI//�ص�����

int sptset[MAP_SIZE];//���Ҽ���

unsigned int distset[MAP_SIZE] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};//���뼯��

//******************��Դ���·��*************************************************
//������� �����ڲ��ҽ�������ʱ������ַԽ�� ��Ҫ������������ 
//ע��·�ߵı��� ����ʱ���Կ���ʹ�� 2��N�е�������б���
struct map_head_node* determine_spt(struct map_head_node *a_node, int *min_number);
int settingpath(const struct map_head_node *a_node);

int setpath(const struct map_head_node *a_node);

int find_dis(struct map_head_node *map_head)//����Ϊ�����ص�
{
    struct map_head_node *pnode = NULL;
    int source = 0,end = 14, n;//Դ���յ�

    n = source;
    sptset[source] = 1;//��ʾ�Ѳ��ҹ�
    distset[source] = 0;//��ʾ����
    //��ʼ�� ����
    //settingpath(&map_head[source]);//�����
    
    while(n != end)
    {
        pnode = determine_spt(map_head, &n);//���Ҳ���sptset�� ������distset��
        if(!pnode)
            return 1;
        setpath(pnode);
        sptset[n] = 1;
        printf("%d --> %d  pathsize %d \n", pnode->name,n, distset[n] );

    }
    printf("%d --> %d  \n", pnode->name,n);
	return 0;
}

int settingpath(const struct map_head_node *a_node)
{
    struct map_node *h_node = a_node[0].map_lnext;
    h_node = h_node->mn_next;
    int n = 0;

    if(!sptset[a_node->name])
        return 0;//�жϵ�ǰ�Ƿ�Ϊȷ���� ���Ϊȷ��������Խ��� ����·�����򷵻�0
    while(h_node)
    {
        if(sptset[h_node->head_number])
        {//�ж�spt�������Ƿ��Ѿ��������·��
            h_node = h_node->mn_next;
            continue;//����Ѱ�ұ���û�м���·���ĳ�Ա ������spt�����е�ֵ
        }
        distset[h_node->head_number] = distset[a_node->name] + h_node->weight;
        h_node = h_node->mn_next;
        n++;
    }

    return n;//����ֵΪ�Ƿ��Ѿ����� ���ǻ����·������
}
    

int setpath(const struct map_head_node *a_node)
{//������ı߼���dist����
    struct map_node *h_node = a_node[0].map_lnext;
    h_node = h_node->mn_next;
    int n = 0;

    while(h_node)
    {
        if(sptset[h_node->head_number])
        {//�ж�spt�������Ƿ��Ѿ��������·��
            h_node = h_node->mn_next;
            continue;//����Ѱ�ұ���û�м���·���ĳ�Ա ������spt�����е�ֵ
        }
        distset[h_node->head_number] = distset[a_node->name] + h_node->weight;
        
        h_node = h_node->mn_next;
        n++;
    }

    return n;//����ֵΪ�Ƿ��Ѿ����� ���ǻ����·������
}

//���ҵ�ǰ������С��ֵ ������Сֵ��head_number
int find_min(const struct map_head_node *a_node)
{
    int min = -1;
    int n = -1;
    struct map_node *h_node = a_node->map_lnext;
    h_node = h_node->mn_next;
    //����ı�
//ע��Լ��붥��ı� ����
    if(!settingpath(a_node))//���� �ڲ������·��ʱ�ᰴ���Ѿ�����sptset�����еĶ���
        return -1;//����·��
//��ǰ�������б��Ѿ�Ϊtrue ��sptset�б���
    //
    while(h_node)
    {
        if(sptset[h_node->head_number])
        {//�����Ѿ�ȷ����·��
            h_node = h_node->mn_next;
            continue;
        }
        if(min > distset[h_node->head_number])
        {//���ҵ�ǰ����ߵ���Сֵ
            min = distset[h_node->head_number];
            n = h_node->head_number;
        }
        h_node = h_node->mn_next;
    }

    return n;
}

//�޸��Ƿ�ʹ�õݹ���в���·��
struct map_head_node* determine_spt(struct map_head_node *a_node, int *min_number)
{
    //��������·�������path �ҵ����·���Ķ���
    //��sptset ��ͬʱ�京�бߵĶ�����в�����Сֵ
    //ע���������ת��Ϊ ����sptset�����е�����distset�����е���Сֵ �������spt����
    //����·�������Ĳ�ȷ���� ���ԱȽ�ÿ��·����distset����Сֵ֮�������spt����
    //ע��˴�����spt�������ö��ǽ��������ú����н������� 
    //���ǽ���ת��Ϊ�ݹ����������ŵ�
    //��ʱ����ȷ��·�� ���ǿ���ȡ�����·��ֵ
    int source = 0;
    struct map_head_node *min_node = NULL;
    int n;

    while(sptset[source++])
        ;//�жϵ�ǰ���뵽sptset���ϵĶ�������
    if(source == MAP_SIZE)
        return NULL;//���ж���·��ȷ��
    source = 0;
    while(source < MAP_SIZE)
    {
        if(!sptset[source++])
            continue;
        if(!min_node)
        {//��һ����Сֵ ��Ϊ�޷�ȷ�� ����ĸ�λ�ÿ�ʼ���Һ����ĸ�λ���ҵ����Բ��ҵĶ���
            *min_number = find_min(&a_node[source - 1]);
            if(*min_number != -1)
                min_node = &a_node[source - 1];
        }

        n = find_min(&a_node[source - 1]);//��distset�е���Сֵ���бȽ�
        if((n == -1) || (*min_number == -1))
            continue;
        if(distset[*min_number] > distset[n])
        {
            *min_number = n;
            min_node = &a_node[source - 1];
        }
    }

    return min_node;
}

//************************��ͼ����************************************************
int create_mapnode(struct map_head_node *head_map, FILE *Rfmap_txt);

int map_init(struct map_head_node *p_mhnode)
{//�Ա�ͷ����ʼ��
	int n = 0;
	int i, status = 1;
	FILE *Rfmap_txt = fopen("datadir/map.txt", "r");

	if (NULL == Rfmap_txt)
		exit(-1);//�򿪵�ͼ�ļ�

	for(i = 0; i < MAP_SIZE && status; i ++)
	{//ÿ�α���һ�� ͷ�ڵ� ����
		fscanf(Rfmap_txt, "%d", &n);
		p_mhnode[i].name = n;
		status = create_mapnode(&p_mhnode[i], Rfmap_txt);
	}
 
	fclose(Rfmap_txt);//�ļ��ر�
//����ֵΪ��ʼ��������
	return n;
}

//map�Ĵ���
int file_data(struct map_node *m_node, FILE* Rfmap_txt);

int create_mapnode(struct map_head_node *head_map, FILE *Rfmap_txt)
{
	int status = 1, i;
	struct map_node *phead = NULL,*pnode = NULL;//Ϊ����������ڶ���

	if(!(head_map->map_lnext = (struct map_node*)malloc(sizeof(struct map_node) ) ) )
		exit(-1);

	phead = head_map->map_lnext;
	//ͷ����ʼ�� Ĭ�� λ������Ϊ-1 next =NULL ȨֵΪ-1
	phead->mn_next = NULL;
	phead->weight = -1;//����ͷ��������

	for(i = 0; i < MAP_SIZE; i ++)
	{
		if(!(phead->mn_next = (struct map_node*)malloc(sizeof(struct map_node) ) ) )
        exit(-1);
		status = file_data(phead->mn_next, Rfmap_txt);//������ӽڵ���Ϣ

		phead = phead->mn_next;
		phead->mn_next = NULL;
        if(status == 0)
            break;
		if(status == -1)
			return 0;//�����ļ���β ������Ϣ���
	}


	return 1;//��ǰ�ڵ���ڽӽڵ�������
}
//Ϊһ��λ���������λ����Ϣ

//�ļ���ȡ ������
int file_data(struct map_node *m_node, FILE* Rfmap_txt)
{

	int ch = -1, ch2 = -1;
	int i = 0;

	//��ȡ�ļ����� ���浽�ڽӱ���ע�� �ļ���ʽ����
	fscanf(Rfmap_txt, "%d %d", &ch, &ch2);
	m_node->weight = ch;//����Ȩֵ
	m_node->head_number = ch2;//����λ��

    ch = fgetc(Rfmap_txt);
	if((ch = getc(Rfmap_txt)) == EOF)
		return -1;//�����ļ���β
	if('\n' == ch)
		return 0;//��ǰ�ڵ�����ӽ���
	
	return 1;
}



int input_number(void)
{
	int i, id;

	printf("������������У԰����������������\n");
	for(i = 0; i < MAP_SIZE; i++)
		printf("%d: %s\n",i+1, situation[i]);
	printf("0:�˳�\n");
	printf("��������������������������������\n");
	printf("������ص�ǰ�Ĵ���:");
	scanf("%d", &id);

	return id - 1;
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

int main(void)
{
	int i;
	struct map_head_node map_head[MAP_SIZE];
    map_init(map_head);
	//print_map(map_head);//����ͼ��ÿ��ͷ�ڵ�
    find_dis(map_head);

    return 0;
}

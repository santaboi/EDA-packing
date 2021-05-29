#include<iostream>
#include<fstream>
#include<vector>
#include<string.h>
#include "Module.h"
#include"Ychain.h"
using namespace std;

string stringname;
int nodes_num=0;
int nets_num=0;
int cases=0;
int c_ind=1;//contour index 每visit 一次++一次
int block_index=0;
double y_max=0,x_max=0;
string benchmark;
string testcase;
string nodespath;
string tempe;
string netspath;
char temp;
char *tempstr=new char[100];
char *allModules=new char[100];
vector<Node> contour;
vector<double> block_x[100];//每個block 的x
vector<double> block_y[100];//每個block 的y
vector<string> block_name;//1d
//順序依照tree travers order
Ychain tourList;
ifstream infile;

void inorder(Module*);//horse
void visit(Module*);//operation
void printName(Module*);//for testing use 
void moveOn();

int main()
{
    vector<Module> input_list;
    vector<int> nets[10];//2dimension
    input_list.clear();
    

    cout<<"total number of testcases"<<endl;
    cin>>cases;
    for(int i=0;i<cases;i++)
    {
        cout<<"step1:please input Benchmark name"<<endl;
        cin>>benchmark;
        cout<<"step2:please input testcase filename (without .nodes or .net)"<<endl;
        cin>>testcase;
        
        tempe="./"+benchmark;
        benchmark=tempe+"/";
        tempe=benchmark+testcase;
        benchmark=tempe+"/";
        tempe=benchmark+testcase;
        nodespath=tempe+".nodes";
        cout<<nodespath<<endl;
        /*
        tempe=".\\\\"+benchmark;
        benchmark=tempe+"\\\\";
        tempe=benchmark+testcase;
        nodespath=tempe+".nodes";
        cout<<nodespath<<endl;
        */
        infile.open(nodespath,ios::in);
        
    //t---------build Btree of nodes-----------------------------------------------
        if(!infile)
        {
            cout<<"cannot open input file(maybe error relative path)";
            cout<<nodespath<<endl;
            cout<<netspath;
            exit(1);
        }
        else
        {
            //---------------get num of nodes-----------
            moveOn();
            infile>>nodes_num;
            //block_x->clear();
            //block_y->clear();
            //block_x->reserve(nodes_num);
            //block_y->reserve(nodes_num);
            //5/29
            cout<<"success1"<<endl;
                
            
            //-------------------------------------------
            
            Module tempNode;
            input_list.resize(nodes_num);
            //for (int i = 0; i < nodes_num; i++)
            //{
            //    input_list.push_back(tempNode);
            //}
            

            for (int i = 0; i < nodes_num; i++)
            {
                moveOn();
                infile>>input_list[i].name;
                moveOn();
                infile>>input_list[i].width>>input_list[i].height;
                moveOn();
                infile>>tempstr>>input_list[i].l_name>>input_list[i].r_name;

            }
            //5/29
            cout<<"successful2"<<endl;

            //----------------------root information----------------------------------
            //root存在input_list[0]   ((其他nodes由lptr rptr 去走訪))
            //----------------------root information----------------------------------
            
            //root x cursor=0
            input_list[0].x=0;

            bool r_status=0;
            bool l_status=0;
            //intialize right pointer
            for (int j = 0; j < nodes_num; j++)
            {   
                
                for (int i = 0; i < nodes_num; i++)
                {
                    if(strcmp(input_list[j].r_name,input_list[i].name)==0)
                    {   input_list[j].rightPtr=&input_list[i];
                        r_status=1;
                        //右有指成功
                        //right child x cursor initialized*****************************************
                        input_list[i].x=input_list[j].x;
                    }
                    if(strcmp(input_list[j].l_name,input_list[i].name)==0)
                    {   input_list[j].leftPtr=&input_list[i];
                        l_status=1;
                        //左有指成功
                        //left child x cursor initialized*******************************************
                        input_list[i].x=input_list[j].x+input_list[j].width;
                    }  
                }
                
                if(r_status==0) input_list[j].rightPtr=NULL;
                if(l_status==0) input_list[j].leftPtr=NULL;
            
                r_status=0;
                l_status=0;
            }


    //t-----------------------------contour build--------------------------------
        contour.resize(nodes_num*2);
        //test
        //cout<<"contour.size()"<<contour.size()<<endl;
        contour[0].Xl=0;
        contour[0].Xr=100000;
        contour[0].Yt=0;
        contour[0].next=NULL;
        contour[0].previous=NULL;
        tourList.create1(&contour[0]);//first=current=&contour[0]

        //inorder function
        inorder(&input_list[0]);
        //最後一個visit沒有出來
        
        
        //結尾
        c_ind=1;//建完contour index歸1
        //最後應該把所有vector free掉!!!
        block_index=0;
    //b-----------------------------contour build--------------------------------

        //5/28 output (.m)
        cout<<"success3";
        ofstream outfile ("test.m");
            outfile<<"axis equal;"<<endl;
            outfile<<"hold on"<<endl;
            outfile<<"grid on"<<endl;
            outfile<<"% area range"<<endl;
            outfile<<"block_x=[ 0 0 "<<x_max<<' '<<x_max<<" 0];"<<endl;//要改大小
            outfile<<"block_y=[ 0 "<<y_max<<' '<<y_max<<" 0 0];"<<endl;//要改大小
            outfile<<"fill(block_x,block_y,'w','Edgecolor','r');"<<endl;
            outfile<<"% block location"<<endl;
            for (int i = 0; i < nodes_num; i++)
            {
                outfile<<"block_x=[ ";
                for (int j = 0; j < 5; j++)
                {outfile<<block_x[i][j]<<' ';}
                outfile<<"];"<<endl;
                outfile<<"block_y=[ ";
                for (int j = 0; j < 5; j++)
                {outfile<<block_y[i][j]<<' ';}
                outfile<<"];"<<endl;
                outfile<<"fill(block_x,block_y,'c');"<<endl;
                int tempx=0,tempy=0;
                tempx=(block_x[i][2]+block_x[i][0])/2;
                tempy=(block_y[i][2]+block_y[i][0])/2;
                cout<<tempx;
                cout<<tempy<<endl;
                outfile<<"text("<<tempx<<','<<tempy<<','<<'\''<<block_name[i]<<"\');"<<endl;
                      
            }
            
            y_max=x_max=0;//initialized
            infile.close();
            outfile.close();
            testcase=testcase+".m";
            const char* newname=testcase.c_str();
            if(rename("test.m",newname)!=0)
            cout<<"rename file error!\n";

        }
    }
//b---------build Btree of nodes-----------------------------------------------


    /*
    infile.open("simple.nets",ios::in);

    if(!infile)
    {
        cout<<"cannot open input file,break out";
        exit(1);
    }
    else
    {
        moveOn();
        infile>>nets_num;

        nets->resize(nets_num);
        for (int i = 0; i < nets_num; i++)
        {    nets[i].clear();}
        
        for (int i = 0; i < nets_num; i++)
        {
            infile>>tempstr;//存NETn 文字
            infile.getline(allModules);
            
        }
        
        
        infile.close();
    }
    */

    
    delete [] tempstr;
    system("PAUSE");
    return 0;
}




void moveOn()
{
    while (1)
    {
        infile.get(temp);
        if(temp==':')
        {   infile.get(temp);//get space 
            break;
        }
    }
}

void inorder(Module* currentNode)
{
    if(currentNode)
    {  
    visit(currentNode);
    inorder(currentNode->leftPtr);
    inorder(currentNode->rightPtr);
    }
}


//x x+width height 傳入 要決定每個module的y 及建立contour
//vector<node>contour 從1到last來用
void visit(Module*curM)//operation
{
    double tempx,tempxr,temph,largestY=0; 
    bool LL=0,LR=0,RL=0,RR=0 ;
    Node *rightest=NULL;
    Node* leftest=NULL;
    tempx=curM->x;
    tempxr=curM->x+curM->width;
    temph=curM->height;
    
 
    tourList.currentToFirst();
    
    if(c_ind==1)
    {
        contour[1].Xl=tempx;
        contour[1].Xr=tempxr;
        contour[1].Yt=temph;
        contour[1].previous=NULL;
        contour[1].next=&contour[0];
        contour[0].previous=&contour[1];
        contour[0].next=NULL;
        contour[0].Xl=tempxr;//modify1
        tourList.firstChange(&contour[1]);
        tourList.currentToFirst();

        curM->y=0;//改module Y
    }
    else//c_ind 2 3 4 .....
    {
            contour[c_ind].Xl=tempx;
            contour[c_ind].Xr=tempxr;
            /*尚未initialize
            contour[c_ind].Yt=
            contour[c_ind].previous=
            contour[c_ind].next=&
            */
        while(1)
        {   

            //modify1 if(tempx<=tourList.currentPtr->Xr&&tempx>=tourList.currentPtr->Xl)
            if(tempx<tourList.currentPtr->Xr&&tempx>=tourList.currentPtr->Xl)
            {
                leftest=tourList.currentPtr;
                if(tempx==tourList.currentPtr->Xl) LL=true;
                //if(tempx==tourList.currentPtr->Xr) LR=true;
            }
            if(tempxr<=tourList.currentPtr->Xr&&tempxr>=tourList.currentPtr->Xl)
            {
                rightest=tourList.currentPtr;
                //if(tempxr==tourList.currentPtr->Xl) RL=true;不可能會有 會被前一個RR抓下來
                if(tempxr==tourList.currentPtr->Xr) RR=true;
            }
            
            tourList.curNext();//cur++
            if(leftest!=NULL&&rightest!=NULL) break;
            if(tourList.currentPtr==NULL) break;
        }
        tourList.currentToFirst();//current 回到first
        //判斷完left right 



        if(leftest==rightest)//只cover一個node
        {
            largestY=leftest->Yt;
            //largestY is all we need
            //回去改module 的Y底
            
            //modify1
            curM->y=largestY;//改module Y
            contour[c_ind].Yt=largestY+temph;

            if(LL==true&&RR==true)//會蓋掉 (first 否)
            {
                if(leftest==tourList.first)
                {
                contour[c_ind].previous=NULL;
                contour[c_ind].next=tourList.first->next;
                tourList.first->next->previous=&contour[c_ind];
                tourList.firstChange(&contour[c_ind]);
                }
                else
                {
                contour[c_ind].previous=leftest->previous;
                contour[c_ind].next=leftest->next;

                leftest->previous->next=&contour[c_ind];
                leftest->next->previous=&contour[c_ind];//modify1

                }
            }
            if(LL==true&&RR==false)//新的在左 (first 否)
            {
                if(leftest==tourList.first)
                {
                contour[c_ind].previous=NULL;
                contour[c_ind].next=leftest;
                
                leftest->Xl=contour[c_ind].Xr;
                //leftest->Xr維持
                leftest->previous=&contour[c_ind];

                tourList.firstChange(&contour[c_ind]);
                }
                else
                {
                contour[c_ind].previous=leftest->previous;
                contour[c_ind].next=leftest;
                
                leftest->previous->next=&contour[c_ind];

                leftest->Xl=contour[c_ind].Xr;
                //leftest->Xr維持
                leftest->previous=&contour[c_ind];


                //testing
                /*
                if(c_ind==11)
                {
                    cout<<c_ind<<':';
                    cout<<" ("<<contour[c_ind].previous->Xl<<' ';
                    cout<<contour[c_ind].previous->Xr<<' ';
                    cout<<contour[c_ind].previous->Yt<<')';//previous 是對的
                    cout<<'('<<contour[c_ind].Xl;
                    cout<<' '<<contour[c_ind].Xr;
                    cout<<' '<<contour[c_ind].Yt;
                    cout<<')'<<endl;
                    cout<<" ("<<contour[c_ind].previous->next->Xl<<' ';
                    cout<<contour[c_ind].previous->next->Xr<<' ';
                    cout<<contour[c_ind].previous->next->Yt<<')';
                    cout<<' '<<tourList.first->Yt<<endl;
                    cout<<' '<<tourList.first->next->Xl<<endl;
                }
                */

                }
            }
            if(LL==false&&RR==true)//新的在右 (first 否)
            {
                //是不是first 沒差
                contour[c_ind].previous=leftest;
                contour[c_ind].next=leftest->next;
                
                leftest->Xr=contour[c_ind].Xl;
                leftest->next->previous=&contour[c_ind];
                leftest->next=&contour[c_ind];
                
                
            }
            if(LL==false&&RR==false)//新的在中 (first 否)
            {
                //是不是first 沒差
                //testing
                //cout<<"use more indexes";
                //cout<<"c_ind"<<c_ind<<endl;

                contour[c_ind+1].Xl=contour[c_ind].Xr;
                contour[c_ind+1].Xr=leftest->Xr;
                contour[c_ind+1].next=leftest->next;
                contour[c_ind+1].previous=&contour[c_ind];
                contour[c_ind+1].Yt=leftest->Yt;

                contour[c_ind].previous=leftest;
                contour[c_ind].next=&contour[c_ind+1];

                leftest->Xr=contour[c_ind].Xl;
                leftest->next=&contour[c_ind];
                
                c_ind++;//vector 多用掉一格
            }

        }
        else if(leftest!=rightest)
        {
            tourList.currentPtr=leftest;
            largestY=leftest->Yt;
            while(1)
            {
            
            if(tourList.currentPtr->Yt>=largestY) largestY=tourList.currentPtr->Yt;

            if(tourList.currentPtr==rightest) break;
            tourList.curNext();    
            }
            //currentPtr==rightest adrress
            //modify1
            tourList.currentToFirst();
            //largestY is all we need
            //回去改module 的Y底
            curM->y=largestY;//改module Y   modify1
            contour[c_ind].Yt=largestY+temph;

            if(LL==true&&RR==true)
            {
                if(leftest==tourList.first)
                {
                    rightest->next->previous=&contour[c_ind];
                    contour[c_ind].next=rightest->next;
                    contour[c_ind].previous=NULL;
                    tourList.firstChange(&contour[c_ind]);
                    
                }
                else
                {
                    rightest->next->previous=&contour[c_ind];
                    contour[c_ind].next=rightest->next;
                    contour[c_ind].previous=leftest->previous;
                    leftest->previous->next=&contour[c_ind];   
                }
            }
            if(LL==true&&RR==false)
            {
                if(leftest==tourList.first)
                {
                    rightest->Xl=contour[c_ind].Xr;
                    rightest->previous=&contour[c_ind];
                    contour[c_ind].next=rightest;
                    contour[c_ind].previous=NULL;
                    tourList.firstChange(&contour[c_ind]);
                }
                else
                {
                    rightest->Xl=contour[c_ind].Xr;
                    rightest->previous=&contour[c_ind];
                    contour[c_ind].next=rightest;
                    contour[c_ind].previous=leftest->previous;
                    leftest->previous->next=&contour[c_ind];
                }
            }
            if(LL==false&&RR==true)
            {
                //是不是first 沒差
                leftest->Xr=contour[c_ind].Xl;
                leftest->next=&contour[c_ind];
                contour[c_ind].previous=leftest;
                contour[c_ind].next=rightest->next;
                rightest->next->previous=&contour[c_ind];
            }
            if(LL==false&&RR==false)
            {
                //是不是first 沒差
                leftest->Xr=contour[c_ind].Xl;
                leftest->next=&contour[c_ind];
                contour[c_ind].previous=leftest;
                rightest->Xl=contour[c_ind].Xr;
                rightest->previous=&contour[c_ind];
                contour[c_ind].next=rightest;
            }
        }  
    }  
    cout<<"aaaaa"<<endl;
    tourList.currentToFirst();
    
    //build blockxy  name
    block_x[block_index].push_back(curM->x);
    block_x[block_index].push_back(curM->x);
    block_x[block_index].push_back(curM->x+curM->width);
    block_x[block_index].push_back(curM->x+curM->width);
    block_x[block_index].push_back(curM->x);
    
    block_y[block_index].push_back(curM->y);
    block_y[block_index].push_back(curM->y+curM->height);
    block_y[block_index].push_back(curM->y+curM->height);
    block_y[block_index].push_back(curM->y);
    block_y[block_index].push_back(curM->y);
    
    
    stringname=curM->name;
    cout<<stringname;
    block_name.push_back(stringname);
    block_index++;
    
    if((curM->y+curM->height)>y_max) y_max=curM->y+curM->height;
    if((curM->x+curM->width)>x_max) x_max=curM->x+curM->width;
    //leftest rightest 要變回null

    //testing
    /*
    for (Ynode* cur=tourList.first; cur!=NULL; cur=cur->next)
    {
    cout<<'(';
    cout<<cur->Xl<<' ';
    cout<<cur->Xr<<' ';
    cout<<cur->Yt;
    cout<<')';
    
    }
    cout<<endl;
    //testing
    */
    c_ind++; 
    
}



//test
void printName(Module*a)
{
    //cout<<a->name<<endl;
    cout<<"left x cursor"<<a->x<<endl;
    cout<<"modified Y cursor"<<a->y<<endl;
}







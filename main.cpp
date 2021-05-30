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
double area=0;
double totallength=0;
double min_pin_x=100000,max_pin_x=0;
double min_pin_y=100000,max_pin_y=0;
string benchmark;
string testcase;
string nodespath;
string tempe;
string temp2;
string netspath;
string netsnodes;
char temp;
char temp3;
char tem3[100];
char *tempstr=new char[100];
char *allModules=new char[100];
vector<Node> contour;
vector<double> block_x[100];//每個block 的x
vector<double> block_y[100];//每個block 的y
vector<string> block_name;//1d
vector<string> nets_list[100];
//順序依照tree travers order
Ychain tourList;
ifstream infile;
ifstream infile2;

void inorder(Module*);//horse
void visit(Module*);//operation
void inorder_X(Module*);
void create_x(Module*); 
void printName(Module*);//for testing use
void moveOn();
void moveon2();

int main()
{
    vector<Module> input_list;
    vector<int> nets[10];//2dimension
    input_list.clear();
    

    cout<<"total number of testcases"<<endl;
    cin>>cases;
    cout<<"step1:please input Benchmark name"<<endl;
    cin>>benchmark;
    for(int i=0;i<cases;i++)
    {
        cout<<"step2:please input testcase filename (without .nodes or .net)"<<endl;
        cin>>testcase;
        
        tempe="./"+benchmark;
        temp2=tempe+"/";
        tempe=temp2+testcase;
        temp2=tempe+"/";
        tempe=temp2+testcase;
        nodespath=tempe+".nodes";
        netspath=tempe+".nets";
        infile.open(nodespath,ios::in);
        infile2.open(netspath,ios::in);
        
    //t---------build Btree of nodes-----------------------------------------------
        if(!infile&&!infile2)
        {
            cout<<"cannot open input file(maybe error relative path)"<<endl;
            cout<<"nodespath:"<<nodespath<<endl;
            cout<<"netspath:"<<netspath;
            exit(1);
        }
        else
        {
            //---------------get num of nodes-----------
            moveOn();
            infile>>nodes_num;
            moveon2();
            infile2>>nets_num;
            //block_x->clear();
            //block_y->clear();
            //block_x->reserve(nodes_num);
            //block_y->reserve(nodes_num);
            
                
            
            //-------------------------------------------
            
            Module tempNode;
            input_list.resize(nodes_num);
            //for (int i = 0; i < nodes_num; i++)
            //{
            //    input_list.push_back(tempNode);
            //}
            
            //get nodes
            for (int i = 0; i < nodes_num; i++)
            {
                moveOn();
                infile>>input_list[i].name;
                moveOn();
                infile>>input_list[i].width>>input_list[i].height;
                moveOn();
                infile>>tempstr>>input_list[i].l_name>>input_list[i].r_name;

            }
            //getnodes end

            //getents
            //infile2.getline(tem3,100);
            infile2>>std::ws;
            for (int i = 0; i < nets_num; i++)
            {
                infile2.getline(tem3,100);//netsname useless
                infile2>>std::ws;
                infile2.getline(tem3,100);//netsnodes useful
                
                string str(tem3);
                string delimiter = " ";
                size_t pos = 0;
                string token;
                nets_list[i].clear();
                while ((pos = str.find(delimiter)) != std::string::npos) 
                {
                token = str.substr(0, pos);
                //std::cout << token << std::endl;
                if(token!=" ")  nets_list[i].push_back(token);
                str.erase(0, pos + delimiter.length());
                }
                //std::cout << str<< std::endl;
                nets_list[i].push_back(str);

                cout<<"nets"<<i<<endl;
                for(int j=0;j<nets_list[i].size();j++)
                cout<<" "<<nets_list[i][j];
                cout<<endl;
            }
            //getnets end
            
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
                        //create_x取代
                        //input_list[i].x=input_list[j].x;
                    }
                    if(strcmp(input_list[j].l_name,input_list[i].name)==0)
                    {   input_list[j].leftPtr=&input_list[i];
                        l_status=1;
                        //左有指成功
                        //left child x cursor initialized*******************************************
                        //create_x 取代
                        //input_list[i].x=input_list[j].x+input_list[j].width;
                    }  
                }
                
                if(r_status==0) input_list[j].rightPtr=NULL;
                if(l_status==0) input_list[j].leftPtr=NULL;
            
                r_status=0;
                l_status=0;
            }
            

            inorder_X(&input_list[0]);


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
        ofstream outfile ("fuck.m");
            
            outfile<<"figure(1)"<<endl;
            outfile<<"axis equal;"<<endl;
            outfile<<"hold on"<<endl;
            outfile<<"grid on"<<endl;
            outfile<<"% area range"<<endl;
            outfile<<"block_x=[ 0 0 "<<x_max<<' '<<x_max<<" 0];"<<endl;//要改大小
            outfile<<"block_y=[ 0 "<<y_max<<' '<<y_max<<" 0 0];"<<endl;//要改大小
            outfile<<"fill(block_x,block_y,'w','Edgecolor','r');"<<endl;
            outfile<<"% block location"<<endl;
            //draw blocks
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
            outfile<<"grid"<<endl;
            
            //draw line
            outfile<<"figure(2)"<<endl;
            outfile<<"axis equal;"<<endl;
            outfile<<"hold on"<<endl;
            outfile<<"grid on"<<endl;
            outfile<<"% area range"<<endl;
            tourList.currentToFirst();
            outfile<<"line([0 0],[0 "<<tourList.first->Yt<<"],'color','g')"<<endl;
            for (Ynode* cur=tourList.first; cur!=NULL;   )
            {   outfile<<"line(["<<cur->Xl<<' '<<cur->Xr<<"],["<<cur->Yt<<' '<<cur->Yt<<"],'color','g')"<<endl;
                outfile<<"line(["<<cur->Xr<<' '<<cur->Xr<<"],["<<cur->Yt;
                cur=cur->next;
                outfile<<' '<<cur->Yt<<"],'color','g')"<<endl;
                if(cur->Yt==0) break;
            }
            outfile<<"grid"<<endl;

            tourList.currentToFirst();
            //draw line end
            
            //report calculation
            area=y_max*x_max;//max區
            //vector<Module> input_list; nodes_num
            
            cout<<"nets number"<<nets_num<<endl;
            for (int i = 0; i < nets_num; i++)
            {
                for (int j = 0; j <nets_list[i].size(); j++)//一條nets 完成
                {
                    for (int m = 0; m < nodes_num; m++)
                    {   
                        string compare(input_list[m].name);
                        if(nets_list[i][j]==compare)    
                        {
                            input_list[m].pin_x=input_list[m].x+(input_list[m].width/2);
                            if(input_list[m].pin_x>max_pin_x) max_pin_x=input_list[m].pin_x;
                            if(input_list[m].pin_x<min_pin_x) min_pin_x=input_list[m].pin_x;
                            input_list[m].pin_y=input_list[m].y+(input_list[m].height/2);
                            if(input_list[m].pin_y>max_pin_y) max_pin_y=input_list[m].pin_y;
                            if(input_list[m].pin_y<min_pin_y) min_pin_y=input_list[m].pin_y;
                        }
                    }
                    
                }
                totallength=totallength+(max_pin_x-min_pin_x)+(max_pin_y-min_pin_y);
                cout<<"totallenth"<<totallength<<endl;

                min_pin_x=100000,max_pin_x=0;//initialized
                min_pin_y=100000,max_pin_y=0;//initialized
                
            }
            
            
            ofstream outfile2("reporttt.txt");
            outfile2<<"Benchmark:"<<testcase<<endl;
            outfile2<<"Area"<<area<<endl;
            outfile2<<"wirelength"<<totallength<<endl;

            outfile2.close();
            string nametemp;
            nametemp=testcase+".txt";
            const char* newname;
            newname=nametemp.c_str();
            if(rename("reporttt.txt",newname)!=0)
            cout<<"rename report error!\n";  
            



            y_max=x_max=0;//initialized
            totallength=0;
            for(int i=0;i<nodes_num;i++)
            {block_x[i].clear();
            block_y[i].clear();
            block_name.clear();}
            min_pin_x=100000,max_pin_x=0;//initialized
            min_pin_y=100000,max_pin_y=0;//initialized
            infile.close();
            infile2.close();
            outfile.close();
            testcase=testcase+".m";
            newname=testcase.c_str();
            if(rename("fuck.m",newname)!=0)
            cout<<"rename .mfile error!\n";

            

        }
    }
//b---------build Btree of nodes-----------------------------------------------


    

    
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

void moveon2()
{
    while (1)
    {
        infile2.get(temp3);
        if(temp3==':')
        {   infile2.get(temp3);//get space 
            break;
        }
    }
}

void inorder(Module* currentNode)
{
    if(currentNode)
    {  
    visit(currentNode);
    printName(currentNode);
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
    
    c_ind++; 
    
}



//test
void printName(Module*a)
{
    //cout<<a->name<<endl;
    cout<<"left x cursor"<<a->x<<endl;
    cout<<"modified Y cursor"<<a->y<<endl;
    cout<<"leftname"<<a->l_name;
    cout<<"rightname"<<a->r_name<<endl;
}

void create_x(Module* now)
{
    if(now->leftPtr!=NULL) now->leftPtr->x=now->x+now->width;
    if(now->rightPtr!=NULL) now->rightPtr->x=now->x;
}


void inorder_X(Module*currentNode)
{
    if(currentNode)
    {  
    create_x(currentNode);
    inorder_X(currentNode->leftPtr);
    inorder_X(currentNode->rightPtr);
    }
}








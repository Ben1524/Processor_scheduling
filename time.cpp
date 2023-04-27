/*
#include<iostream>
#include<vector>
#include<queue>
#include<string>

using namespace std;
const string name="祝景奇";
const string id="L12114014";
typedef struct ProcessSt
{
    string pName;         // 进程名
    int index;          // 进程在进程向量中的下标
    int priority;       // 优先级
    int arrival_time;   // 到达时间
    int status;          // 标记进程是否处于等待队列中状态 0表示未执行,1表示执行 ,2表示在等待队列中
    int service_time;   // 服务时间
    int burst_time;     // 执行时间
    int finish_time;    // 完成时间 = 服务时间 + 执行时间
    int turn_time;      // 周转时间 = 完成时间 - 到达时间
}ProcessSt;

class sortProcess
{
public:
    bool operator()(const ProcessSt * const p1, const ProcessSt *const p2) const
    {
        if (p1->priority == p2->priority)
        {
            // 优先级相同按照到达时间排序,到达时间越早越先执行
            return p1->arrival_time > p2->arrival_time;
        } else
        {
            // 优先级不同按照优先级排序,优先级越高越先执行
            // 优先级越大越靠近队头
            return p1->priority>p2->priority;
        }
    }
};

class process
{
public:
    void initProcess(int n);
    void changeBustTime(int i,int time);
    void changeFinishAndTurnTime(int i,int time);
    ProcessSt &getProcess(int &k);
    void printProcess();
    void pushWaitQueue(int time);
    void getWaitQueue(int &k);
    bool statusEmpty();
    void priorityAlgorithm();
    process(int n):process_vector(n)
    {
        initProcess(n);
    }
    ~process()
    {
        process_vector.clear();
        while(!wait_queue.empty())
            wait_queue.pop();
    }
private:
    vector<ProcessSt> process_vector;
    priority_queue<ProcessSt*,vector<ProcessSt*>,sortProcess>wait_queue; // 等待优先队列
};

void process::initProcess(int n)
{
        for(int i = 0; i < n; i++)
        {
            cin>>process_vector[i].pName>>process_vector[i].arrival_time>>process_vector[i].service_time>>process_vector[i].priority;
            process_vector[i].index = i;
            process_vector[i].status=0;
        }
}
void process::changeBustTime(int i,int time)
{
    process_vector[i].burst_time = time;
}
void process::changeFinishAndTurnTime(int i,int time)
{
    process_vector[i].status = 1;
    process_vector[i].finish_time = time;
    process_vector[i].turn_time = process_vector[i].finish_time - process_vector[i].arrival_time;
}

ProcessSt& process::getProcess(int &k)
{
    if(k==-1)
    {
        int min_index, min_arrivaltime = INT_MAX;
        for (int i = 0; i < process_vector.size(); i++)
        {
            min_arrivaltime = min(min_arrivaltime, process_vector[i].arrival_time);
            if (min_arrivaltime == process_vector[i].arrival_time)
                min_index = i;
        }
        k = min_index;
        return process_vector[min_index];
    }
    else
    {
        return process_vector[k];
    }
}

void process::printProcess()
{
    double avg_turn_time=0,avg_weight_turn_time=0;
    printf("进程名\t到达时间\t\t服务时间\t\t完成时间\t周转时间\t带权周转时间\n");
    for(int i=0;i<process_vector.size();i++)
    {
        cout<<process_vector[i].pName<<"\t   "<<process_vector[i].arrival_time<<"\t\t\t"<<process_vector[i].service_time<<"\t\t\t"<<process_vector[i].finish_time<<"\t\t"<<process_vector[i].turn_time<<"\t\t"<<
        (double)process_vector[i].turn_time/process_vector[i].service_time<<endl;
        avg_turn_time+=process_vector[i].turn_time;
        avg_weight_turn_time+=(double)process_vector[i].turn_time/process_vector[i].service_time;
    }
    cout<<"平均周转时间:"<<avg_turn_time/process_vector.size()<<endl;
    cout<<"平均带权周转时间:"<<avg_weight_turn_time/process_vector.size()<<endl;
}

void process::getWaitQueue(int &k)
{
     ProcessSt &temp=*wait_queue.top();
     k=temp.index;
     wait_queue.pop();
}

bool process::statusEmpty()
{
    return wait_queue.empty();
}

void process::pushWaitQueue(int time)
{
    for(int i=0;i<process_vector.size();i++)
    {
        if(process_vector[i].status==0&&process_vector[i].arrival_time<=time)
        {
            wait_queue.push(&process_vector[i]);
            process_vector[i].status=2;
        }
    }
}
void process::priorityAlgorithm()
{
    int time,finishnum=0, currIndex=-1;
    this->getProcess(currIndex);
    this->changeBustTime(currIndex,this->getProcess(currIndex).arrival_time);
    time=this->getProcess(currIndex).arrival_time;
    while(finishnum<process_vector.size())
    {
        time+=this->getProcess(currIndex).service_time;
        this->changeFinishAndTurnTime(currIndex,time);
        finishnum++;
        this->pushWaitQueue(time);
        while(finishnum<=process_vector.size())
        {
            if(!this->statusEmpty())
            {
                this->getWaitQueue(currIndex);
                this->changeBustTime(currIndex,time);
                break;
            }
            else
            {
                if(finishnum==process_vector.size())
                    break;
                time++;
                this->pushWaitQueue(time);
            }
        }
    }
    printProcess();
}

int main()
{
    cout<<"姓名"<<name<<endl;
    cout<<"学号"<<id<<endl;
    int n;
    cin>>n;
    process p(n);
    p.priorityAlgorithm();
    return 0;
}
*/
/*5
a 0 4 4
b 1 3 2
c 2 4 3
d 3 2 1
e 4 4 2*//*


*/
/*
6
a 6 8 3
b 13 3 2
c 2 4  1
d 8 2 4
e 11 4 3
f 7 7 6*/


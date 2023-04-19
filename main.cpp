#include<iostream>
#include<vector>
#include<queue>
#include<string>
using namespace std;
typedef struct ProcessSt
{
    string pName;         // ������
    int  status;        // ��ǽ����Ƿ��ڵȴ�������״̬ 0��ʾδִ��,1��ʾִ��
    int index;          // �����ڽ��������е��±�
    int priority;       // ���ȼ�
    int arrival_time;   // ����ʱ��
    int service_time;   // ����ʱ��
    int burst_time;     // ִ��ʱ��
    int finish_time;    // ���ʱ�� = ����ʱ�� + ִ��ʱ��
    int turn_time;      // ��תʱ�� = ���ʱ�� - ����ʱ��
}ProcessSt;

class sortProcess
{
public:
    bool operator()(ProcessSt *p1, ProcessSt *p2)
    {
        if (p1->priority == p2->priority)
        {
            // ���ȼ���ͬ���յ���ʱ������,����ʱ��Խ��Խ��ִ��
            return p1->arrival_time > p2->arrival_time;
        } else
        {
            // ���ȼ���ͬ�������ȼ�����,���ȼ�Խ��Խ��ִ��
            // ���ȼ�Խ��Խ������ͷ
            return p1->priority < p2->priority;
        }
    }
};
class process
{
public:
    void initProcess(int n);
    int decServiceTime(int i);
    void changeBustTime(int i,int time);
    void changeFinishAndTurnTime(int i,int time);
    ProcessSt &getProcess(int &k);
    void printProcess();
    void recoverServiceTime();
    void pushWaitQueue(int time);
    void getWaitQueue(int &k);
    void finishProcessPushed(ProcessSt &p);
    bool statusEmpty();
    void RR_Algorithm();
    process(int n,int k):process_vector(n),service_time_vector(n),RR(k)
    {
        initProcess(n);
    }
    ~process()
    {
        process_vector.clear();
        service_time_vector.clear();
        while(!wait_queue.empty())
            wait_queue.pop();
    }
private:
    vector<ProcessSt> process_vector;
    vector<int>service_time_vector;
    priority_queue<ProcessSt*,vector<ProcessSt*>,sortProcess>wait_queue; // �ȴ����ȶ���
    int RR;
};
void process::initProcess(int n)
{
        for(int i = 0; i < n; i++)
        {
            cin>>process_vector[i].pName>>process_vector[i].arrival_time>>process_vector[i].service_time;
            process_vector[i].status = 0;
            process_vector[i].index = i;
            process_vector[i].priority = 0;
            service_time_vector[i] = process_vector[i].service_time;
        }
}
int process::decServiceTime(int i)
{
    if(process_vector[i].service_time>RR)
    {
        process_vector[i].service_time-=RR;
        return -1;
    }
    else
    {
        ProcessSt temp=process_vector[i];
        process_vector[i].service_time=0;
        return RR-temp.service_time;
    }
}
void process::changeBustTime(int i,int time)
{
    process_vector[i].burst_time = time;
    this->getProcess(i).status=1; // ״̬��Ϊ����
}
void process::changeFinishAndTurnTime(int i,int time)
{
    process_vector[i].finish_time = time;
    process_vector[i].turn_time = process_vector[i].finish_time - process_vector[i].arrival_time;
}
void process::recoverServiceTime()
{
    for(int i = 0; i < process_vector.size(); i++)
        process_vector[i].service_time = service_time_vector[i];
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
    recoverServiceTime();
    double avg_turn_time=0,avg_weight_turn_time=0;
    printf("������\t����ʱ��\t����ʱ��\t���ʱ��\t��תʱ��\t��Ȩ��תʱ��\n");
    for(int i=0;i<process_vector.size();i++)
    {
        cout<<process_vector[i].pName<<"\t   "<<process_vector[i].arrival_time<<"\t\t"<<service_time_vector[i]<<"\t\t\t"<<process_vector[i].finish_time<<"\t\t"<<process_vector[i].turn_time<<"\t\t"<<
        (double)process_vector[i].turn_time/service_time_vector[i]<<endl;
        avg_turn_time+=process_vector[i].turn_time;
        avg_weight_turn_time+=(double)process_vector[i].turn_time/service_time_vector[i];
    }
    cout<<"ƽ����תʱ��:"<<avg_turn_time/process_vector.size()<<endl;
    cout<<"ƽ����Ȩ��תʱ��:"<<avg_weight_turn_time/process_vector.size()<<endl;
}
void process::pushWaitQueue(int time)
{
    for(int i=0;i<process_vector.size();i++)
    {
        if(process_vector[i].arrival_time<=time&&process_vector[i].status==0&&process_vector[i].service_time!=0)
        {
            wait_queue.push(&process_vector[i]);
            process_vector[i].status=1;
        }
    }
}
void process::getWaitQueue(int &k)
{
     ProcessSt &temp=*wait_queue.top();
     temp.status=0; // ״̬��Ϊ����
     temp.priority=0;
     k=temp.index;
     wait_queue.pop();
}
void process::finishProcessPushed(ProcessSt &p)
{
    wait_queue.push(&p);
    p.status=1; // ״̬��Ϊ�ȴ�
}
bool process::statusEmpty()
{
    return wait_queue.empty();
}
void process::RR_Algorithm()
{
    int time=0,finishnum=1, currIndex=-1,priority=-1;
    this->getProcess(currIndex);
    this->changeBustTime(currIndex,this->getProcess(currIndex).arrival_time);
    time=this->getProcess(currIndex).arrival_time;
    while(finishnum<=process_vector.size())
    {
        time+=RR; // ֱ�Ӽ�ʱ��Ƭ
        int temp=this->decServiceTime(currIndex);
        if(temp==-1) // ���̻�δ���
        {
            this->pushWaitQueue(time); // ������Ľ��̷���ȴ�����
            this->getProcess(currIndex).priority=priority--;
            this->finishProcessPushed(this->getProcess(currIndex));
            if(!this->statusEmpty()) // �ȴ����в�Ϊ��
            {
                this->getWaitQueue(currIndex); //�ı䵱ǰ���ڽ���
                this->changeBustTime(currIndex,time);
            }
        }
        else
        {
            finishnum++;
            time-=temp; //����ʵ����ɵ�ʱ��
            this->pushWaitQueue(time);
            this->changeFinishAndTurnTime(currIndex,time);
            if(!this->statusEmpty()) // �ȴ����в�Ϊ��
            {
                this->getWaitQueue(currIndex);
                this->changeBustTime(currIndex,time);
            }
        }
    }
    printProcess();
}
int main()
{
    int RR,n;  // RRʱ��Ƭ,nΪ������
    cin>>RR>>n;
    process p(n,RR);
    p.RR_Algorithm();
}

/*
4 5
a 0 4
b 1 3
c 2 4
d 3 2
e 4 4*/


/*1 5
a 0 4
b 1 3
c 2 4
d 3 2
e 4 4*/

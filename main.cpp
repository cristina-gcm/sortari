#include <iostream>
#include<bits/stdc++.h>
#include <chrono>
#include <queue>

using namespace std;
using namespace std::chrono;

unsigned int n, maxi;

void durata( void (*fct)(vector <unsigned int>&), vector <unsigned int> &v)
{
    auto start = high_resolution_clock::now();
    (*fct)(v);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);

    cout << "Time taken by function: "
         << duration.count() << " nanoseconds" << endl;
}

void schimba(vector <unsigned int> &v, int i, int j)
{
    unsigned int aux;
    aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}
void bubble_sort(vector <unsigned int> &v)
{unsigned int aux;
for (int i=0;i<v.size()-1;i++)
        for (int j=i+1; j<v.size();j++)
            if (v[i]>v[j])
                schimba(v, i, j);
}
void count_sort(vector <unsigned int> &v)
{
    vector <unsigned int> ap(maxi+1, 0);
    for (int i=0;i<v.size();i++)
        ap[v[i]]++;
    int i=0;
    while (ap[i]==0)
        i++;
    unsigned int poz=0;
    while (i<=maxi)
        {
            unsigned int j=ap[i];
            while (j!=0)
            {v[poz]=i;
            poz++;
            j--;}
            i++;
        }
}
int partitie (vector <unsigned int> &v, int start, int fin)
{
    unsigned int pivot=v[fin];
    int i=start-1;
    for (int j=start;j<fin;j++)
        { if (v[j]<pivot)
            {

                i++;
                schimba(v, i, j);
            }
        }
    schimba(v, i+1, fin);
    return(i+1);
}
void quick_sort(vector <unsigned int> &v, int start, int fin)
{
    if (start<fin)
        {
            int pi=partitie(v, start, fin);
            quick_sort(v, start, pi-1);
            quick_sort(v, pi+1, fin);
        }
}
vector <unsigned int> concatenare(vector<unsigned int> left, vector <unsigned int> right)
{
    vector <unsigned int> rez;
    while ( (int)left.size()!=0 || (int)right.size()!=0)
    {
        if ((int)left.size()>0 && (int)right.size()>0)
        {
            if ((int)left.front()<(int)right.front())
                {rez.push_back((int)left.front());
                 left.erase(left.begin());}
            else
                {rez.push_back((int)right.front());
                right.erase(right.begin());}
        }
        else if ((int)left.size()>0)
            {for (int i = 0; i < (int)left.size(); i++)
               rez.push_back(left[i]);
            break;}
        else if ((int)right.size() > 0)
            {for (int i = 0; i < (int)right.size(); i++)
               rez.push_back(right[i]);
            break;}
   }
   return rez;
}
vector <unsigned int> merge_sort(vector <unsigned int> v)
{
    if (v.size()<=1)
        return v;

    vector <unsigned int> left, right, rez;
    int m=(int)(v.size()+1)/2;

    for (int i=0;i<m;i++)
        left.push_back(v[i]);
    for (int i=m;i<v.size();i++)
        right.push_back(v[i]);

    left=merge_sort(left);
    right=merge_sort(right);
    rez=concatenare(left, right);

    return rez;
}
unsigned int getMax(vector <unsigned int> v)
{ unsigned int mx=v[0];
    for (int i=1;i<(int)v.size();i++)
    if (v[i]>mx)
        mx=v[i];
return mx;
}

int countDigits (unsigned int n)
{ int nr=0;
while (n!=0)
{
    n=n/10;
    nr++;
}
return nr;
}
void radix_sort(vector <unsigned int> &v)
{
    queue <unsigned int> Q[10];
    int steps=countDigits(getMax(v));
    int power=1;

    for (int k=1;k<=steps;k++)
    {
        for (int i=0;i<(int)v.size();i++)
        {
            int j=(v[i]/power)%10;
            Q[j].push(v[i]);
        }
    power=power*10;
    int j=0;
        for (int i=0;i<10;i++)
            while(!Q[i].empty())
                {
                v[j++]=Q[i].front();
                Q[i].pop();}
    }

}
void afisare (vector <unsigned int> v)
{
    for (int i=0;i<v.size();i++)
        cout << v[i] << " ";
}
 void copiere (vector <unsigned int> &v, vector <unsigned int> v1)
 {
     for (int i=0;i<v.size();i++)
        v[i]=v1[i];
 }
int main()
{
    ifstream fin("date.txt");
    int nr_teste;
    fin>>nr_teste;
    cout<<"---------------------------------------"<<endl;
    for(int test=1;test<=nr_teste;test++)
    {
    fin >> n;
    fin>>maxi;
    std::vector<unsigned int>v(n);
    std::vector<unsigned int>v1(n);

    std::generate(v.begin(), v.end(), []()
                  {
                    return rand() % maxi;
                });
    cout<<"TEST "<<test<<": "<<n<<" numbers, where the maximum value is "<<maxi<<endl;

    copiere(v1, v);

    cout<<"Bubble sort:"<<endl; durata(bubble_sort, v);//afisare(v);cout<<endl;

    copiere(v, v1);

    cout<<"Count sort"<<endl; durata(count_sort, v);

    copiere(v, v1);

    auto start1 = high_resolution_clock::now();
    quick_sort(v, 0, n-1);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);
    cout<< "Quick sort" <<endl;
    cout << "Time taken by function: "
         << duration1.count() << " nanoseconds" << endl;

    copiere(v, v1);

    auto start2 = high_resolution_clock::now();
    v=merge_sort(v);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<nanoseconds>(stop2 - start2);
    cout<< "Merge sort" << endl;
    cout << "Time taken by function: " << duration2.count() << " nanoseconds" << endl;

    copiere(v, v1);
    cout<<"Radix sort"<<endl;
    durata(radix_sort, v);
    cout<<"---------------------------------------"<<endl;}
return 0;}

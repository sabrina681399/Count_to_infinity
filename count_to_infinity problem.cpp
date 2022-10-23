#include <bits/stdc++.h>
#include <limits>
#include<windows.h>
using namespace std;
main()
{
    int x,i,position,j,k,t;
    int infinity = std::numeric_limits<int>::max();
    char nodes[10];
    char ascii='A';
    float distance[10];
    float distance_from_target[10]= {0};
    int arr1[10]= {0},arr2[10]= {0};
    cout<<"Enter Number of Routers for your Subnet:";
    cin>>x;
    for(i=1; i<=x; i++)
    {
        nodes[i]=ascii;
        ascii++;
    }
    for(i=1; i<=x-1; i++)
    {
        cout<<"\nDistance from "<<nodes[i]<<" to "<<nodes[i+1]<<" : ";
        cin>>distance[i];
    }
    system("cls");

    cout<<"\nHere is your Linear Subnet:\n\n";
    cout<<"\t\t\t\t"<<nodes[1];
    for(i=1; i<=x-1; i++)
    {
        cout<<"---"<<distance[i]<<"---"<<nodes[i+1];
    }

    cout<<"\n\nEnter the position of your target router:";
    cin>>position;

    j=position-1;
    k=position+1;
    distance_from_target[position]=0;
    while(1)
    {
        if(j<=0 && k>=x+1)
        {
            break;
        }

        else
        {
            if(j>0)
            {
                distance_from_target[j]=distance_from_target[j+1]+distance[j];
                j--;
            }

            if(k<x+1)
            {
                distance_from_target[k]=distance_from_target[k-1]+distance[k-1];
                k++;
            }
        }
    }

    distance_from_target[position]=infinity;
    j=position-1;
    k=position+1;
    if(j==1)
    {
        distance_from_target[j]=infinity;
    }

    else if(j>0)
    {
        distance_from_target[j]=distance_from_target[j-1]+distance[j-1];
        arr1[j]=1;
    }

    if(k==x)
    {
        distance_from_target[k]=infinity;
    }

    else if(j<x)
    {
        distance_from_target[k]=distance_from_target[k+1]+distance[k];
        arr1[k]=1;
    }

    cout<<"\n\n\t\t\t\t\t\t  ";
    for(i=1;i<=x;i++)
    {
        cout<<"       "<<nodes[i];
    }

    cout<<"\n\n\t\t\t\tExchange number 1 :   ";

    for(t=1; t<=x; t++)
    {
        if(distance_from_target[t]<10)
            {
                cout<<"      ";
            }
            else if(distance_from_target[t]<100)
            {
                cout<<"     ";
            }
            else if(distance_from_target[t]<1000)
            {
                cout<<"    ";
            }
        if(distance_from_target[t]>=infinity)
        {
            cout<<"   null";
        }

        else
        {
            cout<<distance_from_target[t];
        }

    }

    for(i=1; i<=104; i++)
    {
        j=position-1;
        k=position+1;

        while(1)
        {
            if(j<=0 && k>=x+1)
            {
                break;
            }

            else
            {
                if(arr1[j]==1)
                {
                    if(j-1>0)
                    {
                        distance_from_target[j-1]=distance_from_target[j]+distance[j-1];
                        arr2[j-1]=1;
                    }

                    if(j+2==position)
                    {
                        distance_from_target[j+1]=distance_from_target[j]+distance[j];
                        arr2[j+1]=1;
                    }
                }

                if(arr1[k]==1)
                {
                    if(k+1<x+1)
                    {
                        distance_from_target[k+1]=distance_from_target[k]+distance[k];
                        arr2[k+1]=1;
                    }

                    if(k-2==position)
                    {
                        distance_from_target[k-1]=distance_from_target[k]+distance[k-1];
                        arr2[k-1]=1;
                    }
                }

                j--;
                k++;
            }
        }

        for(t=1; t<=x; t++)
        {
            arr1[t]=arr2[t];
            arr2[t]=0;
        }

        if(i>4 && i<101)
        {
            continue;
        }
        cout<<"\n\n\t\t\t\tExchange number "<<i+1<<" :   ";

        for(t=1; t<=x; t++)
        {
            if(distance_from_target[t]<10)
            {
                cout<<"      ";
            }
            else if(distance_from_target[t]<100)
            {
                cout<<"     ";
            }
            else if(distance_from_target[t]<1000)
            {
                cout<<"    ";
            }

            if(distance_from_target[t]>=infinity)
            {
                cout<<"   null";
            }

            else
            {
                cout<<distance_from_target[t];
            }

        }

    }








}

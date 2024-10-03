#include <iostream>
using namespace std;
// Find out if the safe state exists or if deadlock occurs.

// In case safe state exists, display the sequence in which the processes will execute. 

// Also print the following, for each process--> "Allocation", "Maximum", "Requested". 

// Also print Available resource whenever there is an update in the available resources. 

// Verify that if safe state exists then Total resources are equal to available resources at the end.


int main() {

    int n;
    cout<<"Enter no of process(n)\n"<<endl;
    cin>>n;

    int r;
    cout<<"enter no. of resource TYPES(R)\n"<<endl;
    cin>>r;

    int maxAll[n][r];
    int currAll[n][r];
    int need[n][r];
    int maxAvl[r];
    int currAvl[r];
    
    for(int i =0;i<n;i++){
        cout<<"\nEnter maxRequired of process  "<<  i <<" : ";
        for(int j=0;j<r;j++){
            cin >>maxAll[i][j];
        }
    }
//    printing maxReq matrix 
    for(int i =0;i<n;i++){
        for(int j=0;j<r;j++){
            cout<<maxAll[i][j]<<" ";
        }
        cout<<endl;
    }

// ------------------------------------------------------------------
    for(int i =0;i<n;i++){
        cout<<"\nEnter currentAllocation of process  "<<  i <<" : ";
        for(int j=0;j<r;j++){
            cin >>currAll[i][j];
        }
    }
    // printing current Alocated matrix
    for(int i =0;i<n;i++){
       
        for(int j=0;j<r;j++){
            cout<<currAll[i][j]<<" ";
        }
        cout<<endl;
    }
// --------------------------------------------------------------------
    
for(int i =0;i<r;i++){
    cout<<"\nEnter max Available R-"<<i<<": ";
    cin>>maxAvl[i];
}
cout<<"\nMax Available";
for(int i =0;i<r;i++){
    cout<<"\n R"<<i<<": ";
    cout<<maxAvl[i];
}
// ------------------------------------------------------

for(int i =0;i<r;i++){
    cout<<"\nEnter Available R-"<<i<<": ";
    cin>>currAvl[i];
}
cout<<"\nCurrent Available";
for(int i =0;i<r;i++){
    cout<<"\n R"<<i<<": ";
    cout<<currAvl[i];
}

// printing need matrix
for(int i =0;i<n;i++){
        cout<<"\nNeed of process  "<<  i <<" : ";
        for(int j=0;j<r;j++){
            cout<<need[i][j]<<" " ;
        }
        cout<<endl;
    }






    return 0;
}
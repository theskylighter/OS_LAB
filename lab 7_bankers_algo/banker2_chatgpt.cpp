
#include <bits/stdc++.h>
using namespace std;

typedef struct{
    vector<int> max_res;
    vector<int> curr_res;
    vector<int> need;
}process;

bool isSafeState(vector<process> &p, vector<int> &available, int n, int res, vector<int> &safeSeq) {
    vector<bool> finish(n, false); 
    vector<int> work = available;  

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                
                bool canProceed = true;
                for (int j = 0; j < res; j++) {
                    if (p[i].need[j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                if (canProceed) {
                    
                    for (int j = 0; j < res; j++) {
                        work[j] += p[i].curr_res[j];
                    }
                    safeSeq.push_back(i); 
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }

        
        if (!found) {
            return false;
        }
    }

    return true;
}

void printstate(vector<process> &p , vector<int> &available , int n, int res){
    cout << "\nProcess\tAllocated\tMaximum\t\tNeed\t\tAvailable\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t";
        for (int j = 0; j < res; j++) cout << p[i].curr_res[j] << " ";
        cout << "\t\t";
        for (int j = 0; j < res; j++) cout << p[i].max_res[j] << " ";
        cout << "\t\t";
        for (int j = 0; j < res; j++) cout << p[i].need[j] << " ";
        if (i == 0) {
            cout << "\t\t";
            for (int j = 0; j < res; j++) cout << available[j] << " ";
        }
        cout << endl;
    }
}


int main() {
    int n ,res;
    cout<<"Number of processes: ";
    cin>>n;
    cout<<"\n Enter the type of resources: ";
    cin>>res;
    vector<process> p(n);
    // if(n<5 || res<4){
    //     cout<<"Enter atleast 5 process and atleast 4 resources.";
    //     return -1;
    // }
    for(int i=0 ; i<n ;i++){
        p[i].curr_res.resize(res);
        p[i].max_res.resize(res);
        p[i].need.resize(res);

        cout<<"\n Enter the current allocation of all resource type for process"<<i+1<<": ";
        for(int k=0 ; k<res ; k++){
            cin>>p[i].curr_res[k];
        }

        printf("\n Enter the maximum allocation of all resource type for process %d : ",i+1);
        for(int k=0 ; k<res ; k++){
            cin>>p[i].max_res[k];
        }
    }
    
    //need matrix
    for(int i=0 ; i<n ;i++){
        for(int k=0 ; k<res;k++){
            p[i].need[k] = p[i].max_res[k]-p[i].curr_res[k];
        }
    }

    
    vector<int> total(res);
    vector<int> available(res);
    cout<<"\n Enter the total resources of each type : ";
    for(int k=0 ; k<res ; k++){
        cin>>total[k];
    }
    cout<<"\n Enter the available resources of each type : ";
    for(int k=0 ; k<res ; k++){
        cin>>available[k];
    }
    
    printstate(p,available,n,res);

    // Check if the system is in a safe state and get the safe sequence
    vector<int> safeSeq;
    if (isSafeState(p, available, n, res, safeSeq)) {
        cout << "\nThe system is in a safe state.\nSafe sequence: ";
        for (int i = 0; i < safeSeq.size(); i++) {
            cout << "P" << safeSeq[i] + 1;
            if (i != safeSeq.size() - 1) cout << " -> ";
        }
        cout << endl;

        
        for (int i = 0; i < safeSeq.size(); i++) {
            int proc = safeSeq[i];
            
            for (int j = 0; j < res; j++) {
                available[j] += p[proc].curr_res[j];
            }

            // Print the updated available resources
            cout << "\nAfter process P" << proc + 1 << " execution, updated available resources: ";
            for (int j = 0; j < res; j++) {
                cout << available[j] << " ";
            }
            cout << endl;
        }

        cout << "\nVerifying total resources at the end: ";
        for (int j = 0; j < res; j++) {
            if (available[j] != total[j]) {
                cout << "\nResource mismatch detected!" << endl;
                return 0;
            }
        }
        cout <<"\nTotal resources verified successfully!"<< endl;
    } 
    else {
        cout << "\nThe system is in an unsafe state! Deadlock may occur." << endl;
    }

    return 0;
}
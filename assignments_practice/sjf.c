// 1. make a process struct  handling pid,burst Times 
// (assuming all arrived at 0)
// 2. sort the array of structs on the basis of their burst times
// then do a simple calculatin of their WAIT-TIME & TURN-A-TIME 
//~~~~~~~~~~ 
	//int wait[n]
	//int TA[n]
	// wait[i]= wait[i-1]+ burst[i-1]
	// TA[i]= wait[i]+burst[i]